<!-- prettier-ignore -->
#include QMK_KEYBOARD_H
enum {
  TD_CC,
  TD_BRCS,
  TD_SLSH,
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

/* #ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef CONSOLE_ENABLE
#include "print.h"
#endif */

extern uint8_t is_master;

enum layer_number {
  _COLEMAK = 0,
  _GAMESFT = 1,
  _GAME = 2,
  _LOWER = 3,
  _RAISE = 4,

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//TODO Consider Moving/Swapping out right side control key could potentially add new layer switch...

 [_COLEMAK] = LAYOUT( \
  KC_ESC,   KC_EXLM, KC_AT,   KC_HASH,  KC_DLR,  KC_PERC,                         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL, \
  KC_TAB,   KC_Q,    KC_W,    KC_F,     KC_P,    KC_G,                            KC_J,    KC_L,    KC_U,    KC_Y,    KC_BSPC, KC_MINS,\
  TD(TD_CC),KC_A,    KC_R,    KC_S,     KC_T,    KC_D,                            KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,\
  KC_LGUI,  KC_Z,    KC_X,    KC_C,     KC_V,    KC_B, TD(TD_SLSH),  TD(TD_BRCS), KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_QUES, KC_ENT, \
                   KC_LALT, TT(_LOWER), KC_LSFT, KC_LEAD,            TT(_RAISE),  KC_SPC,  TT(_GAMESFT), KC_DEL \
),

// --------------------------------------------------------------------------------

  [_GAMESFT] = LAYOUT( \
  KC_ESC, LCTL(KC_1), LCTL(KC_2), LCTL(KC_3),  LCTL(KC_4), LCTL(KC_5),                         LCTL(KC_6), LCTL(KC_7), LCTL(KC_8),    LCTL(KC_9),   LCTL(KC_0),    _______, \
  KC_TAB, LALT(KC_Q), LALT(KC_W), LALT(KC_F),  LALT(KC_P), LALT(KC_G),                         LALT(KC_J), LALT(KC_L), LALT(KC_U),    LALT(KC_Y),   LALT(KC_BSPC), LALT(KC_MINS),\
  KC_6  , LALT(KC_A), LALT(KC_R), LALT(KC_S),  LALT(KC_T), LALT(KC_D),                         LALT(KC_H), LALT(KC_N), LALT(KC_E),    LALT(KC_I),   LALT(KC_O),    LALT(KC_QUOT),\
  KC_7  , LALT(KC_Z), LALT(KC_X), LALT(KC_C),  LALT(KC_V), LALT(KC_B), TD(TD_SLSH),   XXXXXXX, LALT(KC_K), LALT(KC_M), LALT(KC_COMM), LALT(KC_DOT), LALT(KC_QUES), LALT(KC_ENT), \
                                            _______, _______, _______, MO(_GAME),     _______, _______,    _______, _______ \
  ),

// --------------------------------------------------------------------------------

  [_GAME] = LAYOUT( \
  KC_ESC,   KC_1,    KC_2,    KC_3,     KC_4,    KC_5,                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL, \
  KC_TAB,   KC_Q,    KC_W,    KC_F,     KC_P,    KC_G,                            KC_J,    KC_L,    KC_U,    KC_Y,    KC_BSPC, KC_MINS,\
  KC_6,     KC_A,    KC_R,    KC_S,     KC_T,    KC_D,                            KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,\
  KC_7,     KC_Z,    KC_X,    KC_C,     KC_V,    KC_B, TD(TD_SLSH),  TD(TD_BRCS), KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_QUES, KC_ENT, \
                           XXXXXXX, XXXXXXX, XXXXXXX, _______,      XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX \
  ),

// --------------------------------------------------------------------------------

[_LOWER] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                       XXXXXXX, XXXXXXX,  KC_NLCK,  KC_PSLS, KC_PAST, KC_PPLS,\
  _______, KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, KC_P7,    KC_P8,    KC_P9,   _______, KC_PMNS,\
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                         KC_P0,   KC_P4,    KC_P5,    KC_P6,   XXXXXXX, KC_GRV, \
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, XXXXXXX,      XXXXXXX, KC_PDOT, KC_P1,    KC_P2,    KC_P3,   XXXXXXX, KC_ENT, \
                            _______, _______, _______, _______,      XXXXXXX, _______, _______, _______ \
),

// --------------------------------------------------------------------------------

[_RAISE] = LAYOUT( \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_INS,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX,  _______, XXXXXXX, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, KC_MPRV, KC_MNXT, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LGUI(KC_SLSH),XXXXXXX,KC_HOME, KC_END,  XXXXXXX, KC_PGUP,  KC_PGDN, KC_MPLY, \
                             _______, XXXXXXX, _______, _______,      _______, _______, _______, _______ \
),
// --------------------------------------------------------------------------------

            
};

// // Setting ADJUST layer RGB back to default
// void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
//   if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
//     layer_on(layer3);
//   } else {
//     layer_off(layer3);
//   }
// }

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk

// Disable OLED
/* #ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    #ifdef CONSOLE_ENABLE
        if (record->event.pressed) {
            uprintf("0x%04X,%u,%u,%u\n", keycode, record->event.key.row, record->event.key.col, get_highest_layer(layer_state));
        }
    #endif
//#ifdef OLED_DRIVER_ENABLE
//    set_keylog(keycode, record);
//#endif
    // set_timelog();
  }
  return true;
} */

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
    
// SEARCH
    SEQ_ONE_KEY(KC_LGUI) {
      register_code(KC_LGUI);
      tap_code(KC_SPC);
      unregister_code(KC_LGUI);
    }

// FIND
    SEQ_ONE_KEY(KC_F) {
      register_code(KC_LGUI);
      register_code(KC_LALT);
      tap_code(KC_SPC);
      unregister_code(KC_LALT);
      unregister_code(KC_LGUI);
    }

// UNDO
    SEQ_ONE_KEY(KC_Z) {
      register_code(KC_LCTL);
      tap_code(KC_Z);
      unregister_code(KC_LCTL);
    }

// REDO
    SEQ_TWO_KEYS(KC_Z, KC_Z) {
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      tap_code(KC_Z);
      unregister_code(KC_LCTL);
      unregister_code(KC_LSFT);
    }

// CUT
    SEQ_ONE_KEY(KC_X) {
      register_code(KC_LCTL);
      tap_code(KC_X);
      unregister_code(KC_LCTL);
    }

// SELECT ALL/CUT
    SEQ_TWO_KEYS(KC_X, KC_X) {
      register_code(KC_LCTL);
      tap_code(KC_A);
      tap_code(KC_X);
      unregister_code(KC_LCTL);
    }

// COPY
    SEQ_ONE_KEY(KC_C) {
      register_code(KC_LCTL);
      tap_code(KC_C);
      unregister_code(KC_LCTL);
    }

// SELECT ALL
    SEQ_ONE_KEY(KC_A) {
      register_code(KC_LCTL);
      tap_code(KC_A);
      unregister_code(KC_LCTL);
    }

// SELECT ALL/COPY
    SEQ_TWO_KEYS(KC_C, KC_C) {
      register_code(KC_LCTL);
      tap_code(KC_A);
      tap_code(KC_C);
      unregister_code(KC_LCTL);
    }

// PASTE
    SEQ_ONE_KEY(KC_V) {
      register_code(KC_LCTL);
      tap_code(KC_V);
      unregister_code(KC_LCTL);
    }

// SELECT ALL/PASTE
    SEQ_TWO_KEYS(KC_V, KC_V) {
      register_code(KC_LCTL);
      tap_code(KC_A);
      tap_code(KC_V);
      unregister_code(KC_LCTL);
    }    

// SAVE
    SEQ_ONE_KEY(KC_S) {
      register_code(KC_LCTL);
      tap_code(KC_S);
      unregister_code(KC_LCTL);
    }

// SAVE AS
    SEQ_TWO_KEYS(KC_S, KC_S) {
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      tap_code(KC_S);
      unregister_code(KC_LCTL);
      unregister_code(KC_LSFT);
    }

// CTRL\ALT\DEL
        SEQ_THREE_KEYS(KC_EXLM, KC_EXLM, KC_EXLM) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_DEL);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
//      did_leader_succeed = true;
    }

// VSCODE FOCUS ACTIVE TERMINAL
        SEQ_ONE_KEY(KC_T) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        tap_code(KC_T);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
    }

// OPEN TERMINAL
        SEQ_TWO_KEYS(KC_T, KC_T) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code(KC_T);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
//      did_leader_succeed = true;
    }
// POWER OFF
      SEQ_ONE_KEY(KC_ESC) {
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_P);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
    }

// REBOOT
      SEQ_ONE_KEY(KC_R) {
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_B);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
    }
  }
}
