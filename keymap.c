#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer = 0;
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
  CTL_T(KC_TAB), XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,/* */XXXXXXX, KC_ACL2, KC_ACL1, KC_ACL0, XXXXXXX, XXXXXXX, 
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,/* */XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
								   KC_LGUI, TO(0)  , KC_BTN1,/* */KC_BTN2, TO(0)  , KC_BTN3)
};

int RGB_current_mode;

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("corne"), false);
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    if(layer_state_is(3)) {
        oled_write_P(adjust_layer, false);
    } else if(layer_state_is(4)) {
        oled_write_P(lower_layer, false);
    } else if(layer_state_is(5)) {
        oled_write_P(raise_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

void render_status_main(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void render_status_secondary(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 30000) {
        oled_off();
        return;
    }
#ifndef SPLIT_KEYBOARD
    else { oled_on(); }
#endif

    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  	if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
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
			#ifdef RGB_MATRIX_ENABLE
				if (record->event.pressed) {
					eeconfig_update_rgb_matrix_default();
					rgb_matrix_enable();
				}
			#endif
			break;
  	}
  	return true;
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

#endif
