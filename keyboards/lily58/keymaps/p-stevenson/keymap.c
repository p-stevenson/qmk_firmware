#include QMK_KEYBOARD_H
enum {
  TD_CC,
  TD_BRCS,
  TD_SLSH,
};

enum my_keycodes {
    TERM = LALT(KC_F12),
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CC] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_CAPS), //  Tap once for LCTRL, twice for CAPS
  [TD_BRCS] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC), //  Tap once for LEFT Braces, twice for RIGHT
  [TD_SLSH] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS), // Tap once for BACK Slash, twice for FORWARD
};

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

extern uint8_t is_master;

enum layer_number {
  _COLEMAK = 0,
  _LOWER = 1,
  _RAISE = 2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


 [_COLEMAK] = LAYOUT( \
  KC_ESC,   KC_1,    KC_2,    KC_3,     KC_4,    KC_5,                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL, \
  KC_TAB,   KC_Q,    KC_W,    KC_F,     KC_P,    KC_G,                            KC_J,    KC_L,    KC_U,    KC_Y,    KC_BSPC, KC_MINS,\
  TD(TD_CC),KC_A,    KC_R,    KC_S,     KC_T,    KC_D,                            KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,\
  KC_LGUI,  KC_Z,    KC_X,    KC_C,     KC_V,    KC_B, TD(TD_SLSH),  TD(TD_BRCS), KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_QUES, KC_ENT, \
                             KC_LEAD, KC_LALT, KC_LSFT, KC_SPC,      TT(_RAISE),  KC_SPC,  TT(_LOWER), KC_DEL \
),

// --------------------------------------------------------------------------------

[_LOWER] = LAYOUT( \
  KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_MPRV, KC_MNXT,                       XXXXXXX, XXXXXXX,  KC_NLCK,  KC_PSLS, KC_PAST, KC_PPLS,\
  _______, KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, KC_P7,    KC_P8,    KC_P9,   _______, KC_PMNS,\
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                         KC_P0,   KC_P4,    KC_P5,    KC_P6,   XXXXXXX, KC_GRV, \
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, XXXXXXX,      XXXXXXX, KC_PDOT, KC_P1,    KC_P2,    KC_P3,   XXXXXXX, KC_ENT, \
                            _______, _______, _______, _______,      XXXXXXX, _______, _______, _______ \
),

// --------------------------------------------------------------------------------

[_RAISE] = LAYOUT( \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_INS,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX,  _______, XXXXXXX, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, TERM,    XXXXXXX,                       XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LGUI(KC_SLSH),XXXXXXX,KC_HOME, KC_END,  XXXXXXX, KC_PGUP,  KC_PGDN, XXXXXXX, \
                             _______, _______, _______, _______,      _______, _______, XXXXXXX, _______ \
),
// --------------------------------------------------------------------------------


};

// TODO Tidy up Leader Keys
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

// Other
    SEQ_ONE_KEY(KC_P) {
      SEND_STRING("");
    }

// COLON
    SEQ_ONE_KEY(KC_O) {
      SEND_STRING(":");
    }

// SEMICOLON
    SEQ_TWO_KEYS(KC_O, KC_O) {
      SEND_STRING(";");
    }
  }
}
