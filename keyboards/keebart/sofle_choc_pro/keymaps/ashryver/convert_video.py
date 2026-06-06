#!/usr/bin/env python3
"""Convert a video into a compressed 1-bit frame stream for THEME_VIDEO.

The Sofle Choc Pro OLED runs in OLED_ROTATION_270, so each frame is a 64 px
wide x 128 px tall (portrait) 1-bit bitmap, stored page-major exactly like
convert_image.py / art.h: 16 pages of 64 columns, each byte = 8 vertical
pixels (bit 0 = topmost pixel of the page).

A full frame is 1024 bytes; a 3.5 min clip at 12 fps would be megabytes raw.
To make it fit in flash we store only what changes between frames:

  inter-frame delta + run-length encoding. Frame N is encoded relative to
  frame N-1 as alternating runs over the 1024 byte positions:
        0nnnnnnn            -> skip the next n bytes (unchanged from last frame)
        1nnnnnnn b1..bn     -> write the next n bytes (their new absolute values)
  (n = 1..127; longer runs are split across several tokens.)

The firmware writes literal bytes straight into the OLED framebuffer with
oled_write_raw_byte() and leaves skipped bytes untouched (the framebuffer still
holds the previous frame), so no extra RAM buffer is needed and only changed
bytes are pushed over I2C. Frame 0 is encoded against a blank frame, so after an
oled_clear() it draws a full keyframe; on loop the player clears and replays
from the top, so no seek table is needed.

Usage:
    python3 convert_video.py badapple.mp4 [options] > video.h

Options:
    --fps N        target playback frame rate (default 12)
    --mode MODE    how to map landscape video onto the tall screen:
                     crop    fill screen, crop the sides   (default)
                     fit     whole frame, letterboxed band
                     rotate  rotate 90 deg, fills screen near-lossless
    --threshold N  1-bit cutoff 0..255 (default 128); brighter = on
    --invert       swap black/white
    --dither       Floyd-Steinberg (for greyscale source; Bad Apple needs none)

Requires: ffmpeg on PATH.
"""
import subprocess
import sys

WIDTH, HEIGHT = 64, 128
FRAME_BYTES = WIDTH * HEIGHT // 8  # 1024


def arg(name, default=None):
    if name in sys.argv:
        i = sys.argv.index(name)
        return sys.argv[i + 1] if i + 1 < len(sys.argv) else default
    return default


def ffmpeg_filter(mode):
    if mode == "rotate":
        # rotate 90 deg clockwise, then cover-and-crop the (now portrait) frame
        return ("transpose=1,"
                "scale=%d:%d:force_original_aspect_ratio=increase,"
                "crop=%d:%d" % (WIDTH, HEIGHT, WIDTH, HEIGHT))
    if mode == "fit":
        # whole frame visible, letterboxed into a centered band
        return ("scale=%d:%d:force_original_aspect_ratio=decrease,"
                "pad=%d:%d:(ow-iw)/2:(oh-ih)/2:color=black"
                % (WIDTH, HEIGHT, WIDTH, HEIGHT))
    # crop (default): scale to cover the screen, crop the overflow (sides)
    return ("scale=%d:%d:force_original_aspect_ratio=increase,"
            "crop=%d:%d" % (WIDTH, HEIGHT, WIDTH, HEIGHT))


def frame_to_pages(gray, threshold, invert, dither):
    """Convert one WxH greyscale frame (bytes, row-major) to page-major 1-bit."""
    # optional Floyd-Steinberg dithering on a working copy
    if dither:
        buf = [float(b) for b in gray]
        for y in range(HEIGHT):
            for x in range(WIDTH):
                i = y * WIDTH + x
                old = buf[i]
                new = 255.0 if old >= threshold else 0.0
                buf[i] = new
                err = old - new
                if x + 1 < WIDTH:
                    buf[i + 1] += err * 7 / 16
                if y + 1 < HEIGHT:
                    if x > 0:
                        buf[i + WIDTH - 1] += err * 3 / 16
                    buf[i + WIDTH] += err * 5 / 16
                    if x + 1 < WIDTH:
                        buf[i + WIDTH + 1] += err * 1 / 16
        on = lambda x, y: buf[y * WIDTH + x] >= 128
    else:
        on = lambda x, y: gray[y * WIDTH + x] >= threshold

    out = bytearray(FRAME_BYTES)
    idx = 0
    for page in range(HEIGHT // 8):
        for col in range(WIDTH):
            byte = 0
            for bit in range(8):
                lit = on(col, page * 8 + bit)
                if invert:
                    lit = not lit
                if lit:
                    byte |= (1 << bit)
            out[idx] = byte
            idx += 1
    return out


def rle_frame(frame, prev):
    """Encode frame relative to prev as skip/literal run tokens.

    A byte position is a "skip" if unchanged from prev, otherwise a "literal"
    carrying the new absolute byte value."""
    out = bytearray()
    i = 0
    n = len(frame)
    while i < n:
        if frame[i] == prev[i]:
            run = 0
            while i < n and frame[i] == prev[i] and run < 127:
                run += 1
                i += 1
            out.append(run)  # 0nnnnnnn : skip
        else:
            start = i
            run = 0
            while i < n and frame[i] != prev[i] and run < 127:
                run += 1
                i += 1
            out.append(0x80 | run)  # 1nnnnnnn : literal
            out.extend(frame[start:start + run])
    return out


def main():
    if len(sys.argv) < 2 or sys.argv[1].startswith("--"):
        sys.exit(__doc__)

    src = sys.argv[1]
    fps = int(arg("--fps", "12"))
    mode = arg("--mode", "crop")
    threshold = int(arg("--threshold", "128"))
    invert = "--invert" in sys.argv
    dither = "--dither" in sys.argv

    cmd = [
        "ffmpeg", "-v", "error", "-i", src,
        "-vf", "fps=%d,%s,format=gray" % (fps, ffmpeg_filter(mode)),
        "-f", "rawvideo", "-pix_fmt", "gray", "-",
    ]
    print("running:", " ".join(cmd), file=sys.stderr)
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE)

    prev = bytearray(FRAME_BYTES)  # blank: first frame is a full keyframe
    stream = bytearray()
    frames = 0
    raw_bytes = 0
    while True:
        chunk = proc.stdout.read(WIDTH * HEIGHT)
        if len(chunk) < WIDTH * HEIGHT:
            break
        frame = frame_to_pages(chunk, threshold, invert, dither)
        stream.extend(rle_frame(frame, prev))
        prev = frame
        frames += 1
        raw_bytes += FRAME_BYTES
        if frames % 100 == 0:
            print("  %d frames, %d KB compressed so far"
                  % (frames, len(stream) // 1024), file=sys.stderr)
    proc.wait()

    comp = len(stream)
    print("frames=%d  raw=%d KB  compressed=%d KB  ratio=%.1fx  fps=%d"
          % (frames, raw_bytes // 1024, comp // 1024,
             raw_bytes / max(comp, 1), fps), file=sys.stderr)

    w = sys.stdout.write
    w("#pragma once\n")
    w("// generated by convert_video.py from %s (mode=%s, fps=%d)\n"
      % (src, mode, fps))
    w("#define HAVE_VIDEO_BITMAP\n")
    w("#define VIDEO_FRAME_COUNT %d\n" % frames)
    w("#define VIDEO_FPS %d\n" % fps)
    w("static const uint8_t VIDEO_STREAM[] PROGMEM = {\n")
    for i in range(0, comp, 16):
        row = ", ".join("0x%02X" % b for b in stream[i:i + 16])
        w("    %s,\n" % row)
    w("};\n")
    w("static const uint32_t VIDEO_STREAM_LEN = sizeof(VIDEO_STREAM);\n")


if __name__ == "__main__":
    main()
