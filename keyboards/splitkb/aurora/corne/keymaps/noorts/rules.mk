# Copyright 2022 splitkb.com <support@splitkb.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# NOTE: These are already enabled by default at the revision level
#ENCODER_ENABLE = yes
#OLED_ENABLE = yes

# Note: the comments below seem to be outdated. Regardless, the current setup works.
# RGB Matrix is enabled at the revision level,
# while we use the regular RGB underglow for testing
RGBLIGHT_ENABLE = no # This is for the underglow lighting (facing away from you).
BACKLIGHT_ENABLE = no # This is per-key backlighting.

RGB_MATRIX_ENABLE = yes
SPLIT_KEYBOARD = yes
TRI_LAYER_ENABLE = yes

SRC += oneshot.c
