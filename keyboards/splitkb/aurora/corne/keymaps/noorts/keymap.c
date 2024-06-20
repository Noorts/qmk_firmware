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

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _NUM,
    _SYMB,
    _MISC
};

#define MO_NUM MO(_NUM)
#define MO_SYMB MO(_SYMB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T,                       KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G,                       KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                       KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ESC,
                                KC_LGUI, MO_NUM, KC_SPC,     KC_ENT, MO_SYMB, KC_RALT
    ),

    [_SYMB] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_BSPC,
        KC_LCTL, _______, _______, _______, _______, _______,                       KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______,
        KC_LSFT, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
                                    KC_LGUI, _______, KC_SPC,                       KC_ENT, MO_SYMB, KC_RALT
    ),

};
