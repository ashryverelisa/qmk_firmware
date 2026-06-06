#include QMK_KEYBOARD_H

enum layers {
    BASE,  // default layer
    LOWER, // symbols & navigation (right thumb)
    RAISE, // function keys & numpad / gaming (left thumb)
    MOUSE, // mouse control (hold both thumb layer keys)
};

// OLED motifs (themes) the user can cycle through with OLED_NEXT
enum oled_theme {
    THEME_HUD,   // the full status HUD (layer, locks, wpm, uptime, balance)
    THEME_ART,   // a static full-screen pixel-art picture
    THEME_BONGO, // WPM-reactive bongo animation
    THEME_VIDEO, // looping 1-bit video (Bad Apple), see video.h
    THEME_COUNT, // keep last: number of themes
};

enum custom_keycodes {
    OLED_NEXT = QK_USER_0, // cycle to the next OLED motif
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  Mute |    | Pause |------+------+------+------+------+------|
 * |OSShft|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |OSShft|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCTL | LGUI | LALT | Bspc | /Enter  /       \Space \  | RGUI | DEL  | RALT | RCTL |
 *            |      |      |      |  LT1 |/       /         \      \ | LT1  |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[BASE] = LAYOUT_split_4x6_5(
    KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,     KC_7,     KC_8,    KC_9,    KC_0,    KC_EQL,
    KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                           KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                           KC_H,     KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    OSM(MOD_LSFT),  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,   KC_MPLY,    KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH, OSM(MOD_LSFT),
                 KC_LCTL, KC_LGUI, KC_LALT, LT(RAISE,KC_BSPC), KC_ENT,  KC_SPC, LT(LOWER,KC_RGUI),  KC_DEL,  KC_RALT, KC_RCTL
),

/*
 * LOWER - Symbols & Navigation  (held by RIGHT thumb)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |CapsWd|      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Home |  ←   |  ↓   |  ↑   |   →  | End  |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  | Del  | Ins  |   \  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /Enter  /       \Space \  |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[LOWER] = LAYOUT_split_4x6_5(
    _______,_______,_______,_______,_______,_______,                           _______,_______,_______,_______,_______,_______,
    _______,_______,CW_TOGG,_______,_______,_______,                           _______,_______,_______,_______,_______,_______,
    KC_HOME, KC_LEFT,KC_DOWN, KC_UP,KC_RGHT, KC_END,                           _______,_______,_______,_______,_______,_______,
    _______, KC_EQL,KC_MINS,KC_PLUS,KC_LCBR,KC_RCBR,   _______,     _______,   KC_LBRC,KC_RBRC, KC_DEL, KC_INS,KC_BSLS,KC_PIPE,
                    _______,_______,_______,_______,   _______,     _______,   _______,_______,_______,_______
),

/*
 * RAISE - Function keys & Numpad  (held by LEFT thumb, gaming)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Boot |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Num |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|   +  |   -  |   *  |   /  | PEnt |   .  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|OLEDnx|      |      |      |      | Boot |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /Enter  /       \Space \  |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 *  OLEDnx = cycle OLED motif (HUD -> Art -> Bongo), saved to EEPROM
 */
[RAISE] = LAYOUT_split_4x6_5(
    QK_BOOT,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                             KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11,
     KC_NUM,  KC_P1,  KC_P2,  KC_P3,  KC_P4,  KC_P5,                             KC_P6,  KC_P7,  KC_P8,  KC_P9, KC_P0,  KC_F12,
    _______,_______,_______,_______,_______,_______,                           KC_PPLS,KC_PMNS,KC_PAST,KC_PSLS,KC_PENT,KC_PDOT,
    _______,_______,_______,_______,_______,_______,   _______,     _______,   OLED_NEXT,_______,_______,_______,_______,QK_BOOT,
                    _______,_______,_______,_______,   _______,     _______,   _______,_______,_______,_______
),

/*
 * MOUSE - Mouse control  (hold BOTH thumb layer keys)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      | WhUp |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | MsL  | MsD  | MsU  | MsR  |      |-------.    ,-------|      | Btn1 | Btn2 | Btn3 |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | WhDn |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /Enter  /       \Space \  |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[MOUSE] = LAYOUT_split_4x6_5(
    _______,_______,_______,_______,_______,_______,                           _______,_______,_______,_______,_______,_______,
    _______,_______,_______,_______,_______,_______,                           _______,MS_WHLU,_______,_______,_______,_______,
    _______,MS_LEFT,MS_DOWN,MS_UP,MS_RGHT,_______,                              _______,MS_BTN1,MS_BTN2,MS_BTN3,_______,_______,
    _______,_______,_______,_______,_______,_______,   _______,     _______,   _______,MS_WHLD,_______,_______,_______,_______,
                    _______,_______,_______,_______,   _______,     _______,   _______,_______,_______,_______
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [LOWER] = { ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(C(KC_MINS), C(KC_EQL)) },
    [RAISE] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [MOUSE] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU), ENCODER_CCW_CW(MS_WHLL, MS_WHLR) }
};
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, LOWER, RAISE, MOUSE);
}

#ifdef OLED_ENABLE
#    include "bitmaps.h"
#    include "transactions.h"
// generated picture for THEME_ART (run convert_image.py to (re)create art.h)
#    include "art.h"
// generated frame stream for THEME_VIDEO (run convert_video.py to (re)create video.h)
#    include "video.h"

#    define OLED_POWER_PIN GP20
#    define VIDEO_FRAME_BYTES 1024 // 64x128 / 8: one full 1-bit portrait frame

static const uint8_t OLED_WIDTH = OLED_DISPLAY_HEIGHT;
static const uint16_t SPLASH_DURATION_MS = 2500;

// One combined master->slave packet carries everything the slave half needs for
// the HUD. Keeping it to a single, infrequent transaction keeps the single-wire
// split serial link free for the critical matrix sync.
typedef struct {
    uint32_t press_left;
    uint32_t press_right;
    uint16_t last_keycode;
    uint8_t  theme;
    bool     oled_on;
} oled_sync_m2s_t;

static bool            g_oled_init_done   = false;
static uint8_t         g_oled_max_char    = 0;
static bool            g_splash_active    = true;
static bool            g_splash_rendered  = false;
static uint32_t        g_splash_start_ms  = 0;
static uint32_t        g_user_ontime      = 0;
static uint16_t        g_last_keycode     = KC_NO;
static uint32_t        g_press_left       = 0;
static uint32_t        g_press_right      = 0;
static oled_sync_m2s_t g_remote           = {0, 0, KC_NO, THEME_HUD, false};
static uint8_t         g_oled_theme       = THEME_HUD; // active motif (master is authoritative)
static int16_t         g_oled_theme_shown = -1;        // last motif actually drawn (-1 = none yet)
static bool            g_theme_dirty      = false;     // theme changed: persist + push on next housekeeping

void oled_blit_16x16_P(const char *icon, uint8_t x, uint8_t page) {
    for (uint8_t i = 0; i < 16; i++) {
        char top = pgm_read_byte(&icon[i]);      // column i, top 8 pixels
        char bot = pgm_read_byte(&icon[16 + i]); // column i, bottom 8 pixels
        oled_write_raw_byte(top, page * OLED_WIDTH + x + i);
        oled_write_raw_byte(bot, (page + 1) * OLED_WIDTH + x + i);
    }
}

uint16_t unwrap_keycode(uint16_t kc) {
    if (kc >= QK_MOD_TAP && kc <= QK_MOD_TAP_MAX) {
        return QK_MOD_TAP_GET_TAP_KEYCODE(kc);
    }
    if (kc >= QK_LAYER_TAP && kc <= QK_LAYER_TAP_MAX) {
        return QK_LAYER_TAP_GET_TAP_KEYCODE(kc);
    }
    return kc;
}

uint8_t round_percentage(float x) {
    float   f = x + 0.5f;
    uint8_t r = (uint8_t)f;
    if ((f - (float)r) == 0.0f && (r & 1)) {
        r--; // round half to even
    }
    return r;
}

void oled_print_right_aligned(const char *text, const uint8_t width) {
    uint8_t len = strlen(text);
    uint8_t pad = (len < width) ? (width - len) : 0;
    for (uint8_t i = 0; i < pad; i++) {
        oled_write_P(PSTR(" "), false);
    }
    oled_write(text, false);
}

void print_current_layer(uint8_t row) {
    char layer_str[8];
    switch (get_highest_layer(layer_state)) {
        case BASE:  strcpy(layer_str, "Base");  break;
        case LOWER: strcpy(layer_str, "Sym");   break;
        case RAISE: strcpy(layer_str, "Num");   break;
        case MOUSE: strcpy(layer_str, "Mouse"); break;
        default:    snprintf(layer_str, sizeof(layer_str), "%d", get_highest_layer(layer_state));
    }
    oled_set_cursor(0, row);
    oled_print_right_aligned(layer_str, g_oled_max_char);
}

void print_uptime(uint8_t row) {
    uint32_t time_ms   = timer_read32();
    uint32_t total_min = time_ms / 60000u;
    uint32_t hours     = total_min / 60u;
    uint32_t minutes   = total_min % 60u;
    if (hours > 999u) {
        hours   = 999u;
        minutes = 59u;
    }
    char buf[8];
    snprintf(buf, sizeof(buf), "%3luh%02lum", (unsigned long)hours, (unsigned long)minutes);
    oled_set_cursor(0, row);
    oled_print_right_aligned(buf, g_oled_max_char);
}

void print_wpm(uint8_t row) {
    uint16_t wpm = (uint16_t)get_current_wpm() * 10u;
    char     buf[11];
    snprintf(buf, sizeof(buf), "%3u.%1u WPM", wpm / 10u, wpm % 10u);
    oled_set_cursor(0, row);
    oled_print_right_aligned(buf, g_oled_max_char);
}

void print_balance(uint8_t row, uint8_t pct) {
    char buf[6];
    snprintf(buf, sizeof(buf), "%3u %%", pct);
    oled_set_cursor(0, row);
    oled_print_right_aligned(buf, g_oled_max_char);
}

void render_splash(void) {
    if (g_splash_rendered) {
        return;
    }
    oled_clear();
    oled_set_cursor(0, 0);
    oled_write_raw_P(STARTUP_BITMAP, sizeof(STARTUP_BITMAP));
    g_splash_rendered = true;
}

static void user_sync_data_slave(uint8_t in_len, const void *in_data, uint8_t out_len, void *out_data) {
    if (in_len >= sizeof(oled_sync_m2s_t)) {
        memcpy(&g_remote, in_data, sizeof(oled_sync_m2s_t));
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void keyboard_post_init_user(void) {
    // restore the last selected OLED motif from EEPROM
    uint32_t stored = eeconfig_read_user();
    g_oled_theme    = (stored < THEME_COUNT) ? (uint8_t)stored : THEME_HUD;
    g_remote.theme  = g_oled_theme;

    gpio_set_pin_output(OLED_POWER_PIN);
    gpio_write_pin_low(OLED_POWER_PIN);
    wait_ms(5);

    transaction_register_rpc(USER_SYNC_DATA, user_sync_data_slave);

    if (!is_keyboard_master()) {
        wait_ms(90); // wait for master to be ready
    }
}

void housekeeping_task_user(void) {
    // All master->slave syncing happens here. This is the only safe place to run
    // blocking split transactions; doing them in process_record/oled_task desyncs
    // the halves. Sends are throttled so we never flood the split link.
    if (!is_keyboard_master()) {
        return;
    }

    static uint32_t last_sync = 0;

    // One combined transaction, ~2x/second. A theme change forces it immediately
    // (and persists to EEPROM once). We deliberately keep this rare and singular
    // so the split serial link stays free for matrix syncing.
    bool theme_changed = g_theme_dirty;
    if (theme_changed || timer_elapsed32(last_sync) > 500) {
        if (theme_changed) {
            eeconfig_update_user(g_oled_theme);
            g_theme_dirty = false;
        }
        oled_sync_m2s_t pkt = {g_press_left, g_press_right, g_last_keycode, g_oled_theme, is_oled_on()};
        (void)transaction_rpc_send(USER_SYNC_DATA, sizeof(pkt), &pkt);
        last_sync = timer_read32();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    g_user_ontime = timer_read32();

    // NOTE: never call transaction_rpc_send() or eeconfig_update_*() from here.
    // process_record runs inside the matrix scan; blocking split transactions or
    // flash writes desync the halves and freeze key forwarding. We only touch
    // local state and let housekeeping_task_user() do the syncing/persisting.
    if (keycode == OLED_NEXT) {
        if (record->event.pressed) {
            g_oled_theme   = (g_oled_theme + 1) % THEME_COUNT;
            g_remote.theme = g_oled_theme;
            g_theme_dirty  = true; // housekeeping persists + pushes it
        }
        return false; // consume, never sent as a keystroke
    }

    if (record->event.pressed) {
        g_last_keycode = keycode;

        if (record->event.key.row < MATRIX_ROWS / 2) {
            g_press_left++;
        } else {
            g_press_right++;
        }
    }
    return true;
}

// THEME_HUD: the original status screen (left and right halves differ)
static void render_hud(void) {
    uint32_t local_presses_left  = is_keyboard_master() ? g_press_left : g_remote.press_left;
    uint32_t local_presses_right = is_keyboard_master() ? g_press_right : g_remote.press_right;

    uint32_t total = local_presses_left + local_presses_right;
    if (total == 0) {
        total = 1; // avoid div by 0
    }
    uint8_t pct_left  = round_percentage((100.0f * local_presses_left) / total);
    uint8_t pct_right = round_percentage((100.0f * local_presses_right) / total);

    if (is_keyboard_left()) {
        // current layer
        oled_set_cursor(0, 0);
        oled_write_P(PSTR("Layer:"), false);
        print_current_layer(1);

        // lock status icons
        led_t led_state = host_keyboard_led_state();
        oled_blit_16x16_P(led_state.num_lock ? NUM_LOCK_BITMAP : EMPTY_BITMAP, 0, 3);
        oled_blit_16x16_P(led_state.caps_lock ? CAPS_LOCK_BITMAP : EMPTY_BITMAP, 24, 3);
        oled_blit_16x16_P(led_state.scroll_lock ? SCROLL_LOCK_BITMAP : EMPTY_BITMAP, 48, 3);

        // split balance
        oled_set_cursor(0, 7);
        oled_write_P(PSTR("Left:"), false);
        print_balance(8, pct_left);

        // last key pressed
        oled_set_cursor(0, 10);
        oled_write_P(PSTR("Last Key:"), false);
        oled_set_cursor(0, 11);
        oled_print_right_aligned(get_keycode_string(unwrap_keycode(g_last_keycode)), g_oled_max_char);
    } else {
        // uptime
        oled_set_cursor(0, 0);
        oled_write_P(PSTR("Uptime:"), false);
        print_uptime(1);

        // typing speed
        oled_set_cursor(0, 3);
        oled_write_P(PSTR("Avg Speed"), false);
        oled_set_cursor(0, 4);
        oled_write_P(PSTR("(25 s):"), false);
        print_wpm(5);

        // split balance
        oled_set_cursor(0, 7);
        oled_write_P(PSTR("Right:"), false);
        print_balance(8, pct_right);

        // label
        oled_set_cursor(2, 15);
        oled_write_P(PSTR("Ashryver"), false);
    }
}

// THEME_ART: a static full-screen 64x128 picture.
// convert_image.py generates art.h which defines HAVE_ART_BITMAP + ART_BITMAP
// (1024 bytes); it is auto-included above. Without it a placeholder is shown.
static void render_art(void) {
#ifdef HAVE_ART_BITMAP
    oled_set_cursor(0, 0);
    oled_write_raw_P(ART_BITMAP, sizeof(ART_BITMAP));
#else
    oled_set_cursor(0, 2);
    oled_write_P(PSTR("  Art\n"), false);
    oled_set_cursor(0, 6);
    oled_write_P(PSTR(" Bild\n folgt"), false);
    oled_set_cursor(0, 13);
    oled_write_P(PSTR("Ashryver"), false);
#endif
}

// THEME_BONGO: a WPM-reactive ASCII cat. Idles when you are not typing and
// taps its paws faster the quicker you type.
static void render_bongo(void) {
    static uint32_t paw_timer = 0;
    static bool     paw_down  = false;

    uint8_t wpm = get_current_wpm();

    // flip the paws faster the higher the WPM (clamped); idle when slow
    uint16_t interval = 250;
    if (wpm > 10) {
        interval = (wpm >= 90) ? 60 : (250 - (wpm - 10) * 2);
        if (timer_elapsed32(paw_timer) > interval) {
            paw_down  = !paw_down;
            paw_timer = timer_read32();
        }
    } else {
        paw_down = false;
    }

    oled_set_cursor(2, 0);
    oled_write_P(PSTR("Bongo"), false);

    // face / paws (each line <= 10 chars wide)
    oled_set_cursor(0, 3);
    oled_write_P(PSTR("  /\\_/\\\n"), false);
    if (wpm > 10) {
        oled_write_P(PSTR(" ( o.o )\n"), false);
    } else {
        oled_write_P(PSTR(" ( -.- )\n"), false);
    }
    if (paw_down) {
        oled_write_P(PSTR(" o/   \\o\n"), false);
    } else {
        oled_write_P(PSTR("  \\o_o/ \n"), false);
    }

    // WPM readout near the bottom
    oled_set_cursor(0, 10);
    oled_write_P(PSTR("Speed:"), false);
    print_wpm(11);
}

// THEME_VIDEO: a looping 1-bit video. video.h holds a per-frame delta + RLE
// stream (see convert_video.py): changed bytes are written straight into the
// OLED framebuffer and unchanged bytes are left as-is, so no extra RAM buffer
// is needed and only changed bytes go over I2C. Each half free-runs its own
// player off its local clock, so the screens may drift slightly but both loop.
static void render_video(void) {
#ifdef HAVE_VIDEO_BITMAP
    static uint32_t pos     = 0;
    static uint16_t idx     = 0;
    static uint32_t last_ms = 0;
    const uint16_t  interval = 1000 / VIDEO_FPS;

    // hold the current frame until it is time for the next one
    if (idx != 0 && timer_elapsed32(last_ms) < interval) {
        return;
    }
    // frame 0 is a keyframe encoded against a blank frame: clear the framebuffer
    // and rewind the stream (this is also how the clip loops)
    if (idx == 0) {
        oled_clear();
        pos = 0;
    }

    // decode one frame: walk exactly VIDEO_FRAME_BYTES framebuffer positions
    uint16_t i = 0;
    while (i < VIDEO_FRAME_BYTES && pos < VIDEO_STREAM_LEN) {
        uint8_t tok = pgm_read_byte(&VIDEO_STREAM[pos++]);
        uint8_t n   = tok & 0x7F;
        if (tok & 0x80) { // literal run: write n new bytes into the framebuffer
            while (n-- && i < VIDEO_FRAME_BYTES) {
                oled_write_raw_byte(pgm_read_byte(&VIDEO_STREAM[pos++]), i++);
            }
        } else { // skip run: n bytes unchanged from the previous frame
            i += n;
        }
    }

    last_ms = timer_read32();
    if (++idx >= VIDEO_FRAME_COUNT) {
        idx = 0; // loop back to the keyframe
    }
#else
    oled_set_cursor(0, 2);
    oled_write_P(PSTR(" Video\n"), false);
    oled_set_cursor(0, 6);
    oled_write_P(PSTR(" folgt"), false);
#endif
}

static void oled_post_init(void) {
    if (g_oled_init_done) {
        return;
    }
    g_oled_max_char = oled_max_chars();

    // enable the OLED charge pump / power
    gpio_write_pin_high(OLED_POWER_PIN);
    wait_ms(20);
    oled_clear();

    g_splash_start_ms = timer_read32();
    g_splash_active   = true;
    g_oled_init_done  = true;
}

bool oled_task_user(void) {
    oled_post_init();

    // splash screen on boot
    if (g_splash_active) {
        if (timer_elapsed32(g_splash_start_ms) > SPLASH_DURATION_MS) {
            g_splash_active = false;
            oled_clear();
            g_user_ontime = timer_read32();
        } else {
            render_splash();
        }
        return false;
    }

    // manage on/off state based on idle time; housekeeping_task_user() syncs the
    // resulting state to the slave (never send transactions from oled_task).
    if (is_keyboard_master()) {
        // keep the screen awake while a video is playing (you are watching, not
        // typing); the slave follows the synced oled_on state.
        if (g_oled_theme == THEME_VIDEO) {
            g_user_ontime = timer_read32();
        }
        const uint32_t idle_time = timer_elapsed32(g_user_ontime);
        if (!is_oled_on()) {
            if (idle_time > OLED_TIMEOUT_USER) {
                return false; // stay off
            }
            oled_on();
        } else if (idle_time > OLED_TIMEOUT_USER) {
            oled_off();
            return false;
        }
    } else {
        if (g_remote.oled_on) {
            if (!is_oled_on()) {
                oled_on();
            }
        } else {
            if (is_oled_on()) {
                oled_off();
            }
            return false;
        }
    }

    // on the slave, follow the master: motif + last key come over the wire
    if (!is_keyboard_master()) {
        g_oled_theme   = g_remote.theme;
        g_last_keycode = g_remote.last_keycode;
    }

    // wipe the screen once on motif change so nothing bleeds through
    if (g_oled_theme_shown != (int16_t)g_oled_theme) {
        oled_clear();
        g_oled_theme_shown = (int16_t)g_oled_theme;
    }

    switch (g_oled_theme) {
        case THEME_ART:
            render_art();
            break;
        case THEME_BONGO:
            render_bongo();
            break;
        case THEME_VIDEO:
            render_video();
            break;
        case THEME_HUD:
        default:
            render_hud();
            break;
    }
    return false;
}
#endif
