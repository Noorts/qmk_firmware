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

#pragma once

// ** Handedness and RGB settings from https://github.com/Adam13531/qmk_firmware. Thanks Adam! **

/* Select hand configuration */
#define MASTER_LEFT

// This sends whether or not ctrl, shift, etc. are held to the secondary half of
// the keyboard. Note that it seems to "break" one half entirely unless BOTH
// halves have this enabled.
#define SPLIT_MODS_ENABLE

// Allow the current layer to be synced between the halves.
#define SPLIT_LAYER_STATE_ENABLE

// Allow the state of caps lock, num lock, etc. to be synced between the halves.
#define SPLIT_LED_STATE_ENABLE
#define RGBLED_SPLIT \
    { 27, 27 }

#define USE_SERIAL_PD2

#ifdef RGBLIGHT_ENABLE
#    undef RGBLED_NUM
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_SPLIT
#    define RGBLED_NUM
#    define RGBLIGHT_LIMIT_VAL 120
#    define RGBLIGHT_HUE_STEP 10
#    define RGBLIGHT_SAT_STEP 17
#    define RGBLIGHT_VAL_STEP 17
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGBLED_NUM 54  // Number of LEDs
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGB_MATRIX_SPLIT \
        { 27, 27 }
#endif

// ** From https://precondition.github.io/home-row-mods **
// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0
// ****
