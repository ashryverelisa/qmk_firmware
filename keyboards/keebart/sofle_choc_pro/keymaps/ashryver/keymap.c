#include QMK_KEYBOARD_H

enum layers {
    BASE,  // default layer
    LOWER, // lower layer
};

enum tap_dance_keys {
    TD_ENT, // Tap = Enter, Hold = LShift, Double-Tap = Caps Lock
};

typedef enum {
    TD_NONE,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
} td_state_t;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  Mute |    | Pause |------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCTL | LGUI | LALT | Bspc | /Enter  /       \Space \  | RGUI | DEL  | RALT | RCTL |
 *            |      |      |      |  LT1 |/       /         \      \ | LT1  |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[BASE] = LAYOUT_split_4x6_5(
    KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,     KC_7,     KC_8,    KC_9,    KC_0,    KC_GRV,
    KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                           KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,    KC_BSPC,
    _______,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                           KC_H,     KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    _______,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,   KC_MPLY,    KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                 KC_LCTL, KC_LGUI, KC_LALT, LT(LOWER,KC_BSPC), TD(TD_ENT),  KC_SPC, LT(LOWER,KC_RGUI),  KC_DEL,  KC_RALT, KC_RCTL
),

/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  |  F10 | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Num |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |      | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /Enter  /       \Space \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[LOWER] = LAYOUT_split_4x6_5(
    _______,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                             KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11,
     KC_NUM,  KC_P1,  KC_P2,  KC_P3,  KC_P4,  KC_P5,                             KC_P6,  KC_P7,  KC_P8,  KC_P9,_______, KC_F12,
    _______,_______,_______,_______,_______,_______,                           _______,_______,_______,_______,_______,_______,
    _______, KC_EQL,KC_MINS,KC_PLUS,KC_LCBR,KC_RCBR,   _______,     _______,   KC_LBRC,KC_RBRC,KC_SCLN,KC_COLN,KC_BSLS,KC_PIPE,
                    _______,_______,_______,_______,   _______,     _______,   _______,_______,_______,_______
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [LOWER] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) }
};
#endif

static td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        return state->pressed ? TD_SINGLE_HOLD : TD_SINGLE_TAP;
    }
    if (state->count == 2) return TD_DOUBLE_TAP;
    return TD_NONE;
}

static td_state_t ent_td_state = TD_NONE;

static void ent_finished(tap_dance_state_t *state, void *user_data) {
    ent_td_state = cur_dance(state);
    switch (ent_td_state) {
        case TD_SINGLE_TAP:  register_code(KC_ENT);  break;
        case TD_SINGLE_HOLD: register_code(KC_LSFT); break;
        case TD_DOUBLE_TAP:  tap_code(KC_CAPS);      break; // tap = press+release
        default: break;
    }
}

static void ent_reset(tap_dance_state_t *state, void *user_data) {
    switch (ent_td_state) {
        case TD_SINGLE_TAP:  unregister_code(KC_ENT);  break;
        case TD_SINGLE_HOLD: unregister_code(KC_LSFT); break;
        default: break;
    }
    ent_td_state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ent_finished, ent_reset),
};
