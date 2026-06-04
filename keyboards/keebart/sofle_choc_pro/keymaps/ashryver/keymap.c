#include QMK_KEYBOARD_H

enum layers {
    BASE,  // default layer
    LOWER, // symbols & navigation (right thumb)
    RAISE, // function keys & numpad / gaming (left thumb)
    MOUSE, // mouse control (hold both thumb layer keys)
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
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      | Boot |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /Enter  /       \Space \  |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[RAISE] = LAYOUT_split_4x6_5(
    QK_BOOT,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                             KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11,
     KC_NUM,  KC_P1,  KC_P2,  KC_P3,  KC_P4,  KC_P5,                             KC_P6,  KC_P7,  KC_P8,  KC_P9, KC_P0,  KC_F12,
    _______,_______,_______,_______,_______,_______,                           KC_PPLS,KC_PMNS,KC_PAST,KC_PSLS,KC_PENT,KC_PDOT,
    _______,_______,_______,_______,_______,_______,   _______,     _______,   _______,_______,_______,_______,_______,QK_BOOT,
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
#    define OLED_POWER_PIN GP20

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void keyboard_post_init_user(void) {
    gpio_set_pin_output(OLED_POWER_PIN);
    gpio_write_pin_low(OLED_POWER_PIN);
    wait_ms(5);
}

bool oled_task_user(void) {
    static bool oled_powered = false;
    if (!oled_powered) {
        gpio_write_pin_high(OLED_POWER_PIN);
        wait_ms(20);
        oled_clear();
        oled_powered = true;
    }
    oled_set_cursor(0, 0);
    switch (get_highest_layer(layer_state)) {
        case BASE:  oled_write_P(PSTR("BASE "), false); break;
        case LOWER: oled_write_P(PSTR("SYM  "), false); break;
        case RAISE: oled_write_P(PSTR("NUM  "), false); break;
        case MOUSE: oled_write_P(PSTR("MOUSE"), false); break;
        default:    oled_write_P(PSTR("?????"), false); break;
    }
    return false;
}
#endif
