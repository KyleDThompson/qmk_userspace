#include QMK_KEYBOARD_H
#include "version.h"
#define KC_CAD	LALT(LCTL(KC_DEL))

char wpm_str[10];

static uint32_t cat_timer = 0;
static bool cat_frame = false;

enum custom_layers {
    BASE,   // default layer
    NUMBER,
	SYMBOL,
	NUMPAD,// symbols
    MDIA,   // media keys
	EPRM,
	RGB_SLD
};

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  VRSN,
  PWD1,
  PWD2,
  PWD3,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // keypress animation trigger for bongocat
    if (record->event.pressed) {
        if (timer_elapsed32(cat_timer) > 150) {
            cat_frame = !cat_frame;
            cat_timer = timer_read32();
        } else {
            cat_timer = timer_read32();
        }
    }
    switch (keycode) {
    case PWD1:
        if (record->event.pressed) {
            SEND_STRING("NotSc#00lthistime");
        } else {
        }
        break;

    case PWD2:
        if (record->event.pressed) {
            // when keycode is pressed
            SEND_STRING("Online treadmill gullible primate!");
        } else {
            // when keycode is released
        }
        break;

    case PWD3:
        if (record->event.pressed) {
           SEND_STRING("DucksUnderBridgesDontQuack!");
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | ESC    |   Q  |   W  |   E  |   R  |   T  |  L   |           |  L   |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|  Num |           |  NUM |------+------+------+------+------+--------|
 * | TAB    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| ENTER  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/LN| Ctrl |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | CAD  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|  LR  |------|       |------|  LAYER |Backsp|
 *                                 |      |NUMBER| End  |       | PgDn | SYMBOL |ace   |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left handvrsn
        KC_EQL,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LEFT,
        KC_ESC,         KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   TG(NUMPAD),
        KC_TAB,        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        CTL_T(KC_Z),  KC_X,   KC_C,   KC_V,   KC_B,   ALL_T(KC_NO),
        LT(NUMPAD,KC_GRV),KC_LCTL,      LALT(KC_LSFT),  KC_LEFT,KC_RGHT,
                                              KC_CAD,  KC_LGUI,
                                                              KC_HOME,
                                               KC_SPC,MO(NUMBER),KC_END,
        // right hand
             KC_RGHT,     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_MINS,
             TG(NUMPAD),    KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_BSLS,
                          KC_H,   KC_J,  KC_K,   KC_L,   LT(MDIA, KC_SCLN),GUI_T(KC_QUOT),
             MEH_T(KC_NO),KC_N,   KC_M,  KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_ENT,
                                  KC_UP, KC_DOWN,KC_LBRC,KC_RBRC,          TT(NUMPAD),
             KC_LALT,        CTL_T(KC_ESC),
             KC_PGUP,
             KC_PGDN,MO(SYMBOL), KC_BSPC
    ),
/* Keymap 1: Numbers Shifted Down
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
   |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F11 |           |  F12 |  F6  |  F7  |  F8  |  F9  |  F10 |        | 
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        | 
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        | 
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  LEFT | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | CAD  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space| TAB  |------|       |------|  Enter |Backsp|
 *                                 |      |      | End  |       | PgDn |        |ace   |
 *                                 `--------------------'       `----------------------'
 */
[NUMBER] = LAYOUT_ergodox(  
        // left handvrsn
        KC_TRNS,        KC_F1,   KC_F2,  KC_F3,   KC_F4,   KC_F5,   KC_F11,
		KC_EQL,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LEFT,
        KC_TRNS,  KC_TRNS,   KC_TRNS,         KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
		KC_TRNS,  KC_TRNS,   KC_TRNS,         KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,        KC_TRNS,         KC_TRNS,   KC_TRNS,   KC_TRNS,   
                                              KC_CAD,  KC_LGUI,
                                                              KC_HOME,
                                               KC_SPC,KC_TRNS,KC_END,
        // right hand
             KC_F12,    KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10, KC_TRNS,
			 KC_RGHT,     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_MINS,
             KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,
             KC_TRNS,    KC_TRNS,   KC_UP,  KC_TRNS,   KC_TRNS,   KC_TRNS, 
                                  KC_LEFT, KC_DOWN,KC_RIGHT,KC_RBRC,          TT(NUMPAD),
             KC_LALT,        CTL_T(KC_ESC),
             KC_PGUP,
             KC_PGDN,KC_TRNS, KC_BSPC
    ),
/* Keymap 2: Symbols Shifted Down
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
   |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        | 
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   =    |   !  |   @  |   #  |   $  |   %  | LEFT |           | RIGHT|   ^  |   &  |   *  |   (  |   )  |   -    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        | 
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   |        |      |      |      |      |      |      |           |      |      |      |  UP  |      |      |        | 
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       | LEFT | DOWN | RIGHT|   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | CAD  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space| TAB  |------|       |------|  Enter |Backsp|
 *                                 |      |      | End  |       | PgDn |        |ace   |
 *                                 `--------------------'       `----------------------'
 */
[SYMBOL] = LAYOUT_ergodox(  
        // left handvrsn
        KC_TRNS,        KC_TRNS,         KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,
		KC_EQL,         KC_EXLM,         KC_AT,   KC_HASH,   KC_DLR,   KC_PERC,   KC_LEFT,
        KC_TRNS,        KC_TRNS,         KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,
		KC_TRNS, 		KC_TRNS,		 KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,
        KC_TRNS,        KC_TRNS,         KC_TRNS,   KC_TRNS,   KC_TRNS,   
                                              KC_CAD,  KC_LGUI,
                                                              KC_HOME,
                                               KC_SPC,KC_TRNS,KC_END,
        // right hand
             KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,
			 KC_RGHT,     KC_CIRC,   KC_AMPR,  KC_ASTR,   KC_LPRN,   KC_RPRN,   KC_MINS,
             KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,
             KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_UP,   KC_TRNS,   KC_TRNS,
                                  KC_LEFT, KC_DOWN,KC_RIGHT,KC_RBRC,          TT(NUMPAD),
             KC_LALT,        CTL_T(KC_ESC),
             KC_PGUP,
             KC_PGDN,KC_TRNS, KC_BSPC
   ),
/* Keymap 3: Numpad
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |EE_CLR |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[NUMPAD] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       EE_CLR, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       LM_NEXT,PWD1,
                                               PWD2,
                               LM_BRID,LM_BRIU,PWD3,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
       LM_TOGG, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};
/*bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = get_highest_layer(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }
*/

//Test of different visualizer code
#ifdef ST7565_ENABLE
void render_bongo_cat(void) {

    // If no recent keypresses, show idle cat.
    // process_record_user updates cat_timer on every keypress.
    if (timer_elapsed32(cat_timer) > 1000) { // 1000 ms idle timeout; adjust as desired
		st7565_write_ln_P(PSTR("       /\\_/\\ "), false);
        st7565_write_ln_P(PSTR("      ( o.o )"), false);
        st7565_write_ln_P(PSTR("       > ^ < "), false);
        st7565_write_ln_P(PSTR("      /^\\ /^\\ "), false);
        return;
    }

    // Animated paws (driven by cat_frame toggled in process_record_user)
    if (cat_frame) {
		st7565_write_ln_P(PSTR("        /\\_/\\ pat "), false);
        st7565_write_ln_P(PSTR("       ( ^.^ )"), false);
        st7565_write_ln_P(PSTR("        > ^ < "), false);
        st7565_write_ln_P(PSTR("       ,., /^\\ "), false);
    } else {
		st7565_write_ln_P(PSTR("  pit   /\\_/\\ "), false);
        st7565_write_ln_P(PSTR("       ( ^.^ )"), false);
        st7565_write_ln_P(PSTR("        > ^ < "), false);
        st7565_write_ln_P(PSTR("       ,., /^\\ "), false);
    }
}

void st7565_task_user(void) {

    if (is_keyboard_master()) {
        // Draw bongocat typing animation
        switch (get_highest_layer(layer_state)) {
            case BASE:
                ergodox_infinity_lcd_color(32767, 32767, 32767); // white 50%
                render_bongo_cat();
                break;
            case NUMBER:
                ergodox_infinity_lcd_color(32767, 65535, 32767); // greeney
                render_bongo_cat();
                break;
            case SYMBOL:
                ergodox_infinity_lcd_color(65535, 32767, 32767); // reddy
                render_bongo_cat();
                break;
            case NUMPAD:
                ergodox_infinity_lcd_color(32767, 32767, 65535); // bluey
                render_bongo_cat();
                break;
            default:
                // Or use the write_ln shortcut over adding '\n' to the end of your string
                st7565_write_ln_P(PSTR("Undefined"), false);
                st7565_on_user();
        }
    } else {
        // Draw layer
        switch (get_highest_layer(layer_state)) {
            case BASE:
                ergodox_infinity_lcd_color(32767, 32767, 32767); // white 50%
        st7565_write_ln_P(PSTR(" /\\_/\\         "), false);
        st7565_write_ln_P(PSTR("( o.o ) ________ "), false);
        st7565_write_ln_P(PSTR(" > ^ < |_QUERTY_|"), false);
        st7565_write_ln_P(PSTR(",.,   /^/        "), false);
                break;
            case NUMBER:
                ergodox_infinity_lcd_color(32767, 65535, 32767); // greeney
        st7565_write_ln_P(PSTR(" /\\_/\\         "), false);
        st7565_write_ln_P(PSTR("( o.o ) ________ "), false);
        st7565_write_ln_P(PSTR(" > ^ < |_NUMBER_|"), false);
        st7565_write_ln_P(PSTR(",.,   /^/        "), false);
                break;
            case SYMBOL:
                ergodox_infinity_lcd_color(65535, 32767, 32767); // reddy
        st7565_write_ln_P(PSTR(" /\\_/\\         "), false);
        st7565_write_ln_P(PSTR("( o.o ) ________ "), false);
        st7565_write_ln_P(PSTR(" > ^ < |_SYMBOL_|"), false);
        st7565_write_ln_P(PSTR(",.,   /^/        "), false);
                break;
            case NUMPAD:
                ergodox_infinity_lcd_color(32767, 32767, 65535); // bluey
        st7565_write_ln_P(PSTR(" /\\_/\\         "), false);
        st7565_write_ln_P(PSTR("( o.o ) ________ "), false);
        st7565_write_ln_P(PSTR(" > ^ < |_NUMPAD_|"), false);
        st7565_write_ln_P(PSTR(",.,   /^/        "), false);
                break;
            default:
                // Or use the write_ln shortcut over adding '\n' to the end of your string
                st7565_write_ln_P(PSTR("Undefined"), false);
                st7565_on_user();

        }
    }
}
#endif



