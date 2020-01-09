#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

enum custom_keycodes {
  RGBRST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	//Colemak Mod-DH
	[0] = LAYOUT(
		KC_ESC , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   ,/* */KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_BSPC, 
  CTL_T(KC_TAB), KC_A   , KC_R   , KC_S   , KC_T   , KC_G   ,/* */KC_K   , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT, 
		KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_D   , KC_V   ,/* */KC_M   , KC_H   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT, 
								   KC_LGUI, MO(1)  , KC_SPC ,/* */KC_ENT , MO(2)  , LALT_T(XXXXXXX)),
	//Navigation
	[1] = LAYOUT(
		//Paredit
		KC_ESC , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,/* */XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_DEL , 
CTL_T(KC_TAB),LCA(KC_J),MEH(KC_BSLS),XXXXXXX,XXXXXXX,XXXXXXX,/* */KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_END , XXXXXXX, 
	  KC_LSFT,LCA(KC_K),MEH(KC_X), XXXXXXX, XXXXXXX, XXXXXXX,/* */XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
								   KC_LGUI, _______, KC_SPC ,/* */KC_ENT , MO(3)  , LALT_T(XXXXXXX)),
	[2] = LAYOUT(
		//Symbols												//NumPad
		KC_ESC , KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,/* */KC_PAST, KC_P1  , KC_P2  , KC_P3  , KC_PPLS, KC_BSPC, 
  CTL_T(KC_TAB), KC_LPRN, KC_LCBR, KC_LBRC, KC_CIRC, KC_AMPR,/* */KC_EQL , KC_P4  , KC_P5  , KC_P6  , KC_MINS, KC_GRV , 
		KC_LSFT, KC_RPRN, KC_RCBR, KC_RBRC, KC_TILD, KC_BSLS,/* */KC_PSLS, KC_P7  , KC_P8  , KC_P9  , KC_P0  , KC_PIPE, 
								   KC_LGUI, MO(3)  , KC_SPC ,/* */KC_ENT , _______, LALT_T(XXXXXXX)),
	[3] = LAYOUT(
		//Staging area											//FKeys
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,/* */XXXXXXX, KC_F1  , KC_F2  , KC_F3  , KC_F4  , XXXXXXX, 
		XXXXXXX, TO(4)  , XXXXXXX, XXXXXXX, TO(5)  , XXXXXXX,/* */XXXXXXX, KC_F5  , KC_F6  , KC_F7  , KC_F8  , XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,/* */XXXXXXX, KC_F9  , KC_F10 , KC_F11 , KC_F12 , XXXXXXX, 
								   KC_LGUI, MO(1)  , KC_SPC ,/* */KC_ENT , MO(2)  , LALT_T(XXXXXXX)),
	[4] = LAYOUT(
		//RGB Control + misc
		RGBRST , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,/* */RESET  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_NLCK, 
		RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,/* */XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,/* */XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
								   KC_LGUI, TO(0)  , KC_SPC ,/* */KC_ENT , TO(0)  , LALT_T(XXXXXXX)),
	[5] = LAYOUT(
		//Mouse
		XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, KC_WH_U,/* */XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,/* */XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX,/* */XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
								   KC_LGUI, TO(0)  , KC_BTN1,/* */KC_BTN2, TO(0)  , LALT_T(XXXXXXX))
};

int RGB_current_mode;

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
//void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    //matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  	if (record->event.pressed) {
#ifdef SSD1306OLED
    //set_keylog(keycode, record);
#endif
    // set_timelog();
  	}

	switch (keycode) {
		case RGB_MOD:
			#ifdef RGBLIGHT_ENABLE
				if (record->event.pressed) {
				rgblight_mode(RGB_current_mode);
				rgblight_step();
				RGB_current_mode = rgblight_config.mode;
				}
			#endif
			return false;
		case RGBRST:
			#ifdef RGBLIGHT_ENABLE
				if (record->event.pressed) {
				eeconfig_update_rgblight_default();
				rgblight_enable();
				RGB_current_mode = rgblight_config.mode;
				}
			#endif
			break;
  	}
  	return true;
}
