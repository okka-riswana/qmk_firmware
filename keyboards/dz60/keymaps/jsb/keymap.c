#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_ansi(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        MO(1), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), MO(2), KC_RCTL
    ),
    [1] = LAYOUT_60_ansi(
        KC_TILD, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
        KC_NO, KC_BTN1, KC_MS_U, KC_BTN2, KC_NO, KC_NO, KC_NO, KC_NO, KC_INS, KC_NO, KC_PSCR, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, KC_NO,
        KC_NO, DM_PLY1, DM_PLY2, KC_NO, KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO
    ),
    [2] = LAYOUT_60_ansi(
        KC_GRV, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F22, KC_F24, KC_NO,
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_CAPS, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_NO, KC_NO, KC_NO,
        KC_NO, DM_REC1, DM_REC2, DM_RSTP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        QK_BOOT, GUI_TOG, NK_TOGG, KC_MPLY, KC_NO, KC_NO, KC_TRNS, KC_NO
    ),
};
// clang-format on

const rgblight_segment_t PROGMEM rgb_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, RGBLED_NUM / 2, HSV_PINK},
    {RGBLED_NUM / 2, RGBLED_NUM / 2, HSV_MAGENTA}
);
const rgblight_segment_t PROGMEM rgb_red_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_RED});
const rgblight_segment_t PROGMEM rgb_green_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_GREEN});
const rgblight_segment_t PROGMEM rgb_blue_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_BLUE});
const rgblight_segment_t PROGMEM rgb_yellow_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_YELLOW});
const rgblight_segment_t PROGMEM rgb_white_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_WHITE});
const rgblight_segment_t PROGMEM rgb_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_WHITE}, {14, 2, HSV_WHITE});
const rgblight_segment_t PROGMEM rgb_nogui_layer[] = RGBLIGHT_LAYER_SEGMENTS({RGBLED_NUM / 2, RGBLED_NUM / 2, HSV_RED});

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_base_layer,
    rgb_red_layer,
    rgb_green_layer,
    rgb_blue_layer,
    rgb_yellow_layer,
    rgb_white_layer,
    rgb_capslock_layer,
    rgb_nogui_layer
);

enum rgb_layer_names {
    RGB_LAYER_BASE = 0,
    RGB_LAYER_RED = 1,
    RGB_LAYER_GREEN = 2,
    RGB_LAYER_BLUE = 3,
    RGB_LAYER_YELLOW = 4,
    RGB_LAYER_WHITE = 5,
    RGB_LAYER_CAPSLOCK = 6,
    RGB_LAYER_NOGUI = 7
};

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
    rgblight_set_layer_state(RGB_LAYER_BASE, true);
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GUI_TOG:
        case GUI_ON:
        case GUI_OFF:
            rgblight_blink_layer_repeat(keymap_config.no_gui ? RGB_LAYER_GREEN : RGB_LAYER_RED, 200, 3);
            rgblight_unblink_all_but_layer(keymap_config.no_gui ? RGB_LAYER_GREEN : RGB_LAYER_RED);
            rgblight_set_layer_state(RGB_LAYER_NOGUI, keymap_config.no_gui);
            break;
        case NK_TOGG:
        case NK_ON:
        case NK_OFF:
            rgblight_blink_layer_repeat(keymap_config.nkro ? RGB_LAYER_GREEN : RGB_LAYER_RED, 200, 3);
            break;
        default:
            break;
    }
}

void dynamic_macro_record_start_user(int8_t direction) {
    rgblight_blink_layer_repeat(RGB_LAYER_RED, 200, 3);
    rgblight_unblink_all_but_layer(RGB_LAYER_RED);
}

void dynamic_macro_record_end_user(int8_t direction) {
    rgblight_blink_layer_repeat(RGB_LAYER_GREEN, 200, 3);
    rgblight_unblink_all_but_layer(RGB_LAYER_GREEN);
}

void dynamic_macro_play_user(int8_t direction) {
    rgblight_blink_layer_repeat(RGB_LAYER_WHITE, 200, 3);
    rgblight_unblink_all_but_layer(RGB_LAYER_WHITE);
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(RGB_LAYER_CAPSLOCK, led_state.caps_lock);
    return true;
}
