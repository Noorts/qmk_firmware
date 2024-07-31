/* Copyright 2022 splitkb.com <support@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* The programmatic setup of this keymap is heavily inspired by https://github.com/Adam13531/qmk_firmware. You'll find
 * many similar or copied functions. Thanks Adam!
 *
 * Custom one shot mods by Callum. https://github.com/callum-oakley/qmk_firmware/tree/master/users/callum
 */

#include QMK_KEYBOARD_H

#include <stdio.h>
#include "oneshot.h"

enum layers {
    _BASE,
    _SYM,
    _NAV,
    _NUM,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
};

#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)
#define M_CUT G(KC_X)
#define M_COPY G(KC_C)
#define M_PSTE G(KC_V)

// Home row mods ordering as discussed in https://precondition.github.io/home-row-mods#home-row-mods-order
// CASG → COSC, Thus for left hand side: Ctrl - Option - Shift - Command.
//

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        XXXXXXX, KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,              KC_Y, KC_U,     KC_I,     KC_O,     KC_P,     XXXXXXX,
        XXXXXXX, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,              KC_H, KC_J,     KC_K,     KC_L,     KC_SCLN,  XXXXXXX,
        XXXXXXX, KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,              KC_N, KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  XXXXXXX,
                                     KC_LSFT,    LA_NAV,    KC_SPC,       KC_BSPC,    LA_SYM,    KC_ENT
    ),

    [_SYM] = LAYOUT_split_3x6_3(
        XXXXXXX, KC_TILD, KC_AT,   KC_LCBR, KC_RCBR, KC_GRV ,               KC_CIRC,  KC_EQL,   KC_PLUS, KC_MINS, KC_UNDS, XXXXXXX,
        XXXXXXX, KC_ESC,  KC_ASTR, KC_LPRN, KC_RPRN, KC_QUOT,               KC_PIPE,  OS_CMD,   OS_SHFT, OS_ALT,  OS_CTRL, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX,               KC_HASH,  KC_BSLS,  KC_AMPR, KC_QUES, KC_EXLM, XXXXXXX,
                                   _______, _______, _______,               _______,  _______,  _______
    ),

    [_NAV] = LAYOUT_split_3x6_3(
        XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_KB_MUTE,            KC_PSCR,  M_PSTE,   M_COPY,  M_CUT,   XXXXXXX , XXXXXXX,
        XXXXXXX, OS_CTRL, OS_ALT,  OS_SHFT, OS_CMD,  KC_MPLY,               KC_TAB,   KC_LEFT,  KC_DOWN, KC_UP  , KC_RIGHT, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MSTP,               KC_CAPS,  KC_HOME,  KC_PGDN, KC_PGUP, KC_END  , XXXXXXX,
                                   _______, _______, _______,               _______,  _______,  _______
    ),

    [_NUM] = LAYOUT_split_3x6_3(
        XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                  KC_6,     KC_7,     KC_8,    KC_9,    KC_0,     XXXXXXX,
        XXXXXXX, OS_CTRL, OS_ALT,  OS_SHFT, OS_CMD,  KC_F11,                KC_F12,   OS_CMD,   OS_SHFT, OS_ALT,  OS_CTRL,  XXXXXXX,
        XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                 KC_F6,    KC_F7,    KC_F8,   KC_F9,   KC_F10,   XXXXXXX,
                                   _______, _______, _______,               _______,  _______,  _______
    ),
};
    // Diagram of per-key LEDs on the RH side when viewed from above:
    //   46  47  48  49  50  51
    //   41  42  43  44  45  52
    //   36  37  38  39  40  53
    //  33  34  35

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _NUM);
}

// The LEDs are so bright on the Corne, so we set the intensity pretty low.
#define LED_INTENSITY 0x16
#define LED_INTENSITY_HALF 0xB

// https://www.rapidtables.com/web/color/RGB_Color.html
// Define the usual colors using the desired LED_INTENSITY defined above.
#define RGB_DARK_BLUE 0x00, 0x00, LED_INTENSITY
#define RGB_DARK_CYAN 0x00, LED_INTENSITY, LED_INTENSITY
#define RGB_DARK_GREEN 0x00, LED_INTENSITY, 0x00
#define RGB_DARK_MAGENTA LED_INTENSITY, 0x00, LED_INTENSITY
#define RGB_DARK_RED LED_INTENSITY, 0x00, 0x00
#define RGB_BRIGHT_ORANGE 0x32, 0x19, 0x00
#define RGB_DARK_ORANGE LED_INTENSITY, 0xB, 0x00
#define RGB_DARK_WHITE LED_INTENSITY, LED_INTENSITY, LED_INTENSITY
#define RGB_HALF_WHITE LED_INTENSITY_HALF, LED_INTENSITY_HALF, LED_INTENSITY_HALF
#define RGB_DARK_YELLOW LED_INTENSITY, LED_INTENSITY, 0x00

void set_color_split(uint8_t key_code, uint8_t r, uint8_t g, uint8_t b) {
    rgb_matrix_set_color(key_code, r, g, b);
}

// Sets all keycodes specified in the array to the given color. This is good for
// coloring arbitrary keys like WASD or all of the number keys at once.
void set_all_keys_colors(const uint8_t keycodes[], uint8_t len, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < len; ++i) {
        set_color_split(keycodes[i], r, g, b);
    }
}

// Sets keys that fall within a contiguous keycode range to a given color.
// The start and end codes are inclusive.
void set_color_for_contiguous_keycodes(uint8_t start_code, uint8_t end_code, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = start_code; i <= end_code; ++i) {
        set_color_split(i, r, g, b);
    }
}

void light_up_left_mods(uint8_t r, uint8_t g, uint8_t b) {
    const uint8_t left_mod_keycodes[] = {18, 17, 16, 15};
    set_all_keys_colors(left_mod_keycodes, sizeof(left_mod_keycodes) / sizeof(uint8_t), r, g, b);
}

void light_up_right_mods(uint8_t r, uint8_t g, uint8_t b) {
    const uint8_t right_mod_keycodes[] = {42, 43, 44, 45};
    set_all_keys_colors(right_mod_keycodes, sizeof(right_mod_keycodes) / sizeof(uint8_t), r, g, b);
}

void light_up_left_mods_preset(void) {
    set_color_split(18, RGB_DARK_BLUE);    // 'A' key - Ctrl
    set_color_split(17, RGB_DARK_WHITE);    // 'S' key - Alt
    set_color_split(16, RGB_DARK_CYAN);    // 'D' key - Shift
    set_color_split(15, RGB_DARK_MAGENTA);    // 'F' key - Cmd
}

void light_up_right_mods_preset(void) {
    set_color_split(45, RGB_DARK_BLUE);    // ';' key - Ctrl
    set_color_split(44, RGB_DARK_WHITE);    // 'L' key - Alt
    set_color_split(43, RGB_DARK_CYAN);    // 'K' key - Shift
    set_color_split(42, RGB_DARK_MAGENTA);    // 'J' key - Cmd
}

bool is_shift_held(void) { return (get_mods() & MOD_BIT(KC_LSFT)) || (get_mods() & MOD_BIT(KC_RSFT)); }
bool is_ctrl_held(void) { return get_mods() & MOD_BIT(KC_LCTL); }
bool is_gui_held(void) { return get_mods() & MOD_BIT(KC_LGUI); }
bool is_alt_held(void) { return get_mods() & MOD_BIT(KC_LALT); }

#ifdef RGB_MATRIX_ENABLE
// Note: all keys mentioned in this function go by QWERTY.
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Diagram of underglow LEDs on the LH side when viewed from above:
    // 2   1   0
    // 3   4   5
    // (i.e. LED 0 is underneath the "R" key on a QWERTY keyboard)
    //
    // Diagram of per-key LEDs on the LH side when viewed from above:
    //  24  23  22  21  20  19
    //  25  18  17  16  15  14
    //  26  13  12  11  10   9
    //               8   7   6
    //
    // Diagram of underglow LEDs on the RH side when viewed from above:
    // 27  28  29
    // 32  31  30
    // (i.e. LED 29 is underneath the "P" key on a QWERTY keyboard)
    //
    // Diagram of per-key LEDs on the RH side when viewed from above:
    //   46  47  48  49  50  51
    //   41  42  43  44  45  52
    //   36  37  38  39  40  53
    //  33  34  35

    set_color_for_contiguous_keycodes(0, 53, RGB_OFF);

    switch (get_highest_layer(layer_state)) {
        case _BASE: {
            // LH thumbs as in 8, 7, 6
            set_color_split(8, RGB_DARK_CYAN);  // LH thumb key 1
            set_color_split(7, RGB_DARK_MAGENTA);  // LH thumb key 2
            // set_color_split(6, RGB_DARK_WHITE);  // LH thumb key 3

            // RH thumbs as in 33, 34, 35
            // set_color_split(33, RGB_DARK_CYAN);     // RH thumb key 1
            set_color_split(34, RGB_DARK_BLUE);  // RH thumb key 2
            // set_color_split(35, RGB_DARK_RED);     // RH thumb key 3

            break;
        }
        case _NUM: {
            light_up_left_mods_preset();
            light_up_right_mods_preset();

            // Numbers
            set_color_for_contiguous_keycodes(19, 23, RGB_DARK_GREEN);
            set_color_for_contiguous_keycodes(46, 50, RGB_DARK_GREEN);

            // Function keys
            set_color_for_contiguous_keycodes(9, 13, RGB_DARK_ORANGE);
            set_color_for_contiguous_keycodes(36, 40, RGB_DARK_ORANGE);
            set_color_split(14, RGB_DARK_ORANGE);    // 'G' key
            set_color_split(41, RGB_DARK_ORANGE);    // 'H' key

            break;
        }
        case _SYM: {
            light_up_right_mods_preset();

            // Highlight brackets
            set_color_split(21, RGB_DARK_CYAN);    // 'E' key
            set_color_split(20, RGB_DARK_CYAN);    // 'R' key
            set_color_split(16, RGB_DARK_BLUE);    // 'D' key
            set_color_split(15, RGB_DARK_BLUE);    // 'F' key
            set_color_split(11, RGB_DARK_MAGENTA);    // 'C' key
            set_color_split(10, RGB_DARK_MAGENTA);    // 'V' key

            set_color_split(18, RGB_DARK_RED);    // 'A' key - Esc

            const uint8_t other_used_keycodes[] = {23, 22, 19, 17, 14, 46, 47, 48, 49, 50, 41, 36, 37, 38, 39, 40};
            set_all_keys_colors(other_used_keycodes, sizeof(other_used_keycodes) / sizeof(uint8_t), RGB_HALF_WHITE);

            break;
        }
        case _NAV: {
            light_up_left_mods_preset();

            // Arrow keys
            set_color_for_contiguous_keycodes(42, 45, RGB_DARK_ORANGE);
            // The row below the arrow keys
            set_color_for_contiguous_keycodes(37, 40, RGB_DARK_YELLOW);

            // Music controls
            set_color_split(23, RGB_DARK_CYAN);    // 'Q' key - Prev
            set_color_split(22, RGB_DARK_ORANGE);    // 'W' key - Vol down
            set_color_split(21, RGB_DARK_RED);    // 'E' key - Vol up
            set_color_split(20, RGB_DARK_BLUE);    // 'R' key - Next

            set_color_split(14, RGB_DARK_GREEN);    // 'G' key - Play
            set_color_split(19, RGB_DARK_YELLOW);    // 'T' key - Mute
            set_color_split(9, RGB_DARK_RED);    // 'B' key - Stop

            // Cut, copy, paste
            set_color_split(49, RGB_DARK_CYAN);    // 'O' key - Cut
            set_color_split(48, RGB_DARK_BLUE);    // 'I' key - Copy
            set_color_split(47, RGB_DARK_MAGENTA);    // 'U' key - Paste

            // Misc
            set_color_split(41, RGB_DARK_WHITE);    // 'H' key - Tab
            set_color_split(36, RGB_DARK_RED);    // 'N' key - Caps lock
            // TODO: Could add num lock here similar to caps lock if I start using it.
            set_color_split(46, RGB_DARK_YELLOW);    // 'Y' key - Print screen

            break;
        }
        default:
            break;
    }

    // Show which modifiers are currently active.
    if (is_ctrl_held()) {
        set_color_split(18, RGB_DARK_WHITE);    // 'A' key
        set_color_split(45, RGB_DARK_WHITE);    // ';' key
    }
    if (is_shift_held()) {
        set_color_split(16, RGB_DARK_WHITE);    // 'D' key
        set_color_split(43, RGB_DARK_WHITE);    // 'K' key
        set_color_split(8, RGB_DARK_WHITE);    // RH thumb key 1
    }
    if (is_alt_held()) {
        set_color_split(17, RGB_DARK_WHITE);    // 'S' key
        set_color_split(44, RGB_DARK_WHITE);    // 'L' key
    }
    if (is_gui_held()) {
        set_color_split(15, RGB_DARK_WHITE);    // 'F' key
        set_color_split(42, RGB_DARK_WHITE);    // 'J' key
    }

    return true;
}
#endif

/*
Easy to copy keys.

set_color_split(23, );    // 'Q' key
set_color_split(22, );    // 'W' key
set_color_split(21, );    // 'E' key
set_color_split(20, );    // 'R' key
set_color_split(19, );    // 'T' key
set_color_split(18, );    // 'A' key
set_color_split(17, );    // 'S' key
set_color_split(16, );    // 'D' key
set_color_split(15, );    // 'F' key
set_color_split(14, );    // 'G' key
set_color_split(13, );    // 'Z' key
set_color_split(12, );    // 'X' key
set_color_split(11, );    // 'C' key
set_color_split(10, );    // 'V' key
set_color_split(9, );    // 'B' key

// LH thumbs as in 8, 7, 6
set_color_split(8, );  // LH thumb key 1
set_color_split(7, );  // LH thumb key 2
set_color_split(6, );  // LH thumb key 3

set_color_split(50, );    // 'P' key
set_color_split(49, );    // 'O' key
set_color_split(48, );    // 'I' key
set_color_split(47, );    // 'U' key
set_color_split(46, );    // 'Y' key
set_color_split(45, );    // ';' key
set_color_split(44, );    // 'L' key
set_color_split(43, );    // 'K' key
set_color_split(42, );    // 'J' key
set_color_split(41, );    // 'H' key
set_color_split(40, );    // '/' key
set_color_split(39, );    // '.' key
set_color_split(38, );    // ',' key
set_color_split(37, );    // 'M' key
set_color_split(36, );    // 'N' key

// RH thumbs as in 33, 34, 35
set_color_split(33, );    // RH thumb key 1
set_color_split(34, );    // RH thumb key 2
set_color_split(35, );    // RH thumb key 3
*/
