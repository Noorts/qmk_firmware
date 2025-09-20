###
# Formats the keymap layout produced by keymapviz (https://github.com/yskoht/keymapviz) for consumption by
# http://www.keyboard-layout-editor.com/#/.

# This is a quick and dirty Python script to perform a formatting job. This is to improve readability of the final
# keymap png.

# For some proper automation (which this script is not) see: https://github.com/manna-harbour/miryoku_babel
###

import sys, re, os, glob

# Mappings (source: https://github.com/manna-harbour/miryoku_babel?tab=readme-ov-file#keycode-translation)
# Includes the source and svg columns. Right versions (e.g., RALT) of the modifiers were added manually.
mappings = {
    "A": "A",
    "B": "B",
    "C": "C",
    "D": "D",
    "E": "E",
    "F": "F",
    "G": "G",
    "H": "H",
    "I": "I",
    "J": "J",
    "K": "K",
    "L": "L",
    "M": "M",
    "N": "N",
    "O": "O",
    "P": "P",
    "Q": "Q",
    "R": "R",
    "S": "S",
    "T": "T",
    "U": "U",
    "V": "V",
    "W": "W",
    "X": "X",
    "Y": "Y",
    "Z": "Z",
    "0": "0",
    "1": "1",
    "2": "2",
    "3": "3",
    "4": "4",
    "5": "5",
    "6": "6",
    "7": "7",
    "8": "8",
    "9": "9",
    "ALGR": "AltGr",
    "AMPR": "&",
    "APP": "App",
    "ASTR": "*",
    "AT": "@",
    "BSLS": "\\",
    "BSPC": "Back Space",
    "BOOT": "U_BOOT",
    "BT_CLR": "BT Clear",
    "BT_CLR_0": "BT  0 Clear",
    "BT_CLR_1": "BT  1 Clear",
    "BT_CLR_2": "BT  2 Clear",
    "BT_CLR_3": "BT  3 Clear",
    "BT_CLR_4": "BT  4 Clear",
    "BT_SEL_0": "BT  0 Select",
    "BT_SEL_1": "BT  1 Select",
    "BT_SEL_2": "BT  2 Select",
    "BT_SEL_3": "BT  3 Select",
    "BT_SEL_4": "BT  4 Select",
    "BTN1": "Left Button",
    "BTN2": "Right Button",
    "BTN3": "Middle ",
    "CAPS": "Caps Lock",
    "CIRC": "^",
    "COLN": ":",
    "COMM": "S_COMM",
    "CPSWRD": "Caps Word",
    "DEL": "Delete",
    "DF(U_BASE)": "U_DF(U_BASE)",
    "DF(U_EXTRA": "U_DF(U_EXTRA",
    "DF(U_TAP)": "U_DF(U_TAP)",
    "DLR": "$",
    "DOT": ".",
    "DOWN": "Down",
    "DQUO": "\"",
    "END": "End",
    "ENT": "Enter",
    "EP_OFF": "EP Off",
    "EP_TOG": "EP Toggle",
    "EQL": "=",
    "ESC": "Esc",
    "EXLM": "!",
    "F1": "F1",
    "F2": "F2",
    "F3": "F3",
    "F4": "F4",
    "F5": "F5",
    "F6": "F6",
    "F7": "F7",
    "F8": "F8",
    "F9": "F9",
    "F10": "F10",
    "F11": "F11",
    "F12": "F12",
    "GRV": "`",
    "GT": ">",
    "HASH": "#",
    "HOME": "Home",
    "INS": "Insert",
    "LALT": "Alt",
    "RALT": "Alt",
    "LBRC": "[",
    "LCBR": "{",
    "LCTL": "Ctrl",
    "RCTL": "Ctrl",
    "LEFT": "Left",
    "LGUI": "Meta",
    "RGUI": "Meta",
    "LPRN": "S_LPRN",
    "LSFT": "Shift",
    "RSFT": "Shift",
    "LT": "<",
    "MINS": "-",
    "MNXT": "Next",
    "MPLY": "Play Pause",
    "MPRV": "Prev",
    "MS_D": "Mouse Down",
    "MS_L": "Mouse Left",
    "MS_R": "Mouse Right",
    "MS_U": "Mouse Up",
    "MSTP": "Stop",
    "MUTE": "Mute",
    "NO": "",
    "OUT_TOG": "Out Toggle",
    "OUT_BT": "Out BT",
    "OUT_USB": "Out USB",
    "PAUS": "Pause Break",
    "PERC": "%",
    "PGDN": "Page Down",
    "PGUP": "Page Up",
    "PIPE": "S_PIPE",
    "PLUS": "+",
    "PSCR": "PrtScn SysRq",
    "QUES": "?",
    "QUOT": "'",
    "RBRC": "]",
    "RCBR": "}",
    "RESET": "Reset",
    "RGB_HUD": "RGB Hue  -",
    "RGB_HUI": "RGB Hue  +",
    "RGB_MOD": "RGB Mode  +",
    "RGB_RMOD": "RGB Mode  -",
    "RGB_OFF": "RGB Off",
    "RGB_SAD": "RGB Sat  -",
    "RGB_SAI": "RGB Sat  +",
    "RGB_TOG": "RGB Toggle",
    "RGB_VAD": "RGB Value  -",
    "RGB_VAI": "RGB Value  +",
    "RGHT": "Right",
    "RPRN": "S_RPRN",
    "SCLN": ";",
    "SLCK": "Scroll Lock",
    "SLSH": "/",
    "SPC": "Space",
    "TAB": "Tab",
    "TILD": "~",
    "TRNS": "Trans",
    "UNDS": "_",
    "UP": "Up",
    "VOLD": "Volume Down",
    "VOLU": "Volume Up",
    "WH_D": "Scroll Down",
    "WH_L": "Scroll Left",
    "WH_R": "Scroll Right",
    "WH_U": "Scroll Up",
}

custom_mappings = {
    "NUBS": "\\",
    "S_COMM": ",",
    "AGIN": "Redo",
    "PSTE": "Paste",
    "COPY": "Copy",
    "CUT": "Cut",
    "UNDO": "Undo",
    "LEFT": "Left",
    "RIGHT": "Right",
    "KB_Mute": "Mute",

    "Meta": "Cmd",
}

shift_mappings = {
    "[": "{",
    "]": "}",
    "\\": "|",

    ";": ":",
    "'": '"',

    "/": "?",
    ",": "<",
    ".": ">",

    "`": "~",
    "1": "!",
    "2": "@",
    "3": "#",
    "4": "$",
    "5": "%",
    "6": "^",
    "7": "&",
    "8": "*",
    "9": "(",
    "0": ")",
    "-": "_",
    "=": "+",
}


def process_file(filename):
    # Load the file
    content = None
    with open(filename, 'r') as file:
        content = file.read()

    # Format
    ## Clean up pre- and postfixes.
    content = content.replace("KC_", "")
    content = content.replace("_T", "")

    ## Clean up mod-taps
    mod_tap_regex = r"LT\(_([^,]+),([^,]+)\)"
    content = re.sub(mod_tap_regex, r"\1, \2", content)

    ## Rename to friendly format
    # Note: sorted by length for priority (a "MINS" match is higher priority than an "INS" match)
    sorted_mappings = dict(sorted(mappings.items(), key=lambda item: len(item[0]), reverse=True))

    for key, value in sorted_mappings.items():
        content = content.replace(key, value)

    for key, value in custom_mappings.items():
        content = content.replace(key, value)

    for key, value in shift_mappings.items():
        content = content.replace(f"S({key})", value)

    # Write a cleaned version of the file
    with open(os.path.splitext(os.path.basename(filename))[0] + '_cleaned.json', 'w') as file:
        file.write(content)


def main():
    pattern = 'keymap_export_*.json'
    files = glob.glob(pattern)
    filename_filter_pattern = re.compile(r'keymap_export_(\d+)\.json')
    for file in files:
        if filename_filter_pattern.match(os.path.basename(file)):
            process_file(file)


if __name__ == "__main__":
    main()
