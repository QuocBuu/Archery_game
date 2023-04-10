#include "scr_game_setting.h"

static const unsigned char PROGMEM chosse_icon2 [] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf8, 0x00, 0xff, 0xfc, 0x00, 0x7f, 
	0xfe, 0x00, 0x3f, 0xff, 0x00, 0x1f, 0xff, 0x80, 0x0f, 0xff, 0xc0, 0x07, 0xff, 0xe0, 0x04, 0x00, 
	0x20, 0x08, 0x00, 0x40, 0x10, 0x00, 0x80, 0x20, 0x01, 0x00, 0x40, 0x02, 0x00, 0x80, 0x04, 0x00, 
	0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static void view_scr_game_setting();

view_dynamic_t dyn_view_item_game_setting = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_game_setting
};

view_screen_t scr_game_setting = {
	&dyn_view_item_game_setting,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

int c;
uint8_t arrow1;
uint8_t arrow1_speed;
uint8_t mine_speed_lv;
uint8_t m = 0;

void view_scr_game_setting() {
#define AK_LOGO_AXIS_X		(18)
#define AK_LOGO_TEXT		(AK_LOGO_AXIS_X + 4)
	if(m == 0) {
		eeprom_read(18, (uint8_t*)&arrow1, 	1U);
		eeprom_read(20, (uint8_t*)&arrow1_speed, 	1U);
		eeprom_read(22, (uint8_t*)&mine_speed_lv, 	1U);
		m =1;	
	}
	view_render.clear();
	view_render.setTextSize(1.8);
	view_render.setTextColor(WHITE);
    view_render.drawBitmap(0, c+1, chosse_icon2, 20, 20, 1);
    
    view_render.setCursor(AK_LOGO_TEXT, 7);
		if ( arrow1 == 1 ) { view_render.print(" Arrow        (1)") ;}
		if ( arrow1 == 2 ) { view_render.print(" Arrow        (2)") ;}
		if ( arrow1 == 3 ) { view_render.print(" Arrow        (3)") ;}
		if ( arrow1 == 4 ) { view_render.print(" Arrow        (4)") ;}
		if ( arrow1 == 5 ) { view_render.print(" Arrow        (5)") ;}
    view_render.setCursor(AK_LOGO_TEXT, 27);
		if ( arrow1_speed == 1 ) { view_render.print(" Arrow speed  (1)") ;}
		if ( arrow1_speed == 2 ) { view_render.print(" Arrow speed  (2)") ;}
		if ( arrow1_speed == 3 ) { view_render.print(" Arrow speed  (3)") ;}
		if ( arrow1_speed == 4 ) { view_render.print(" Arrow speed  (4)") ;}
		if ( arrow1_speed == 5 ) { view_render.print(" Arrow speed  (5)") ;}
    view_render.setCursor(AK_LOGO_TEXT, 47);
	    if ( mine_speed_lv  == 1 ) { view_render.print(" Mine speed   (1)") ;}
        if ( mine_speed_lv  == 2 ) { view_render.print(" Mine speed   (2)") ;}
        if ( mine_speed_lv  == 3 ) { view_render.print(" Mine speed   (3)") ;}
		if ( mine_speed_lv  == 4 ) { view_render.print(" Mine speed   (4)") ;}
        if ( mine_speed_lv  == 5 ) { view_render.print(" Mine speed   (5)") ;}
	view_render.update();
}

void scr_game_setting_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
    }
		break;

	case AC_DISPLAY_BUTON_MODE_LONG_PRESSED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_LONG_PRESSED\n");
		eeprom_write(18, (uint8_t*)&arrow1, 	1U);
		eeprom_write(20, (uint8_t*)&arrow1_speed, 	1U);
		eeprom_write(22, (uint8_t*)&mine_speed_lv, 	1U);
		m = 0;
		SCREEN_TRAN(scr_buu_handle, &scr_buu);
	}
		BUZZER_PlayTones(tones_startup);
		break;
	
	case AC_DISPLAY_BUTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_RELEASED\n");
		if (c == 0) {
            arrow1++;
            if (arrow1    > 5)   { arrow1 = 1;}
        }
        if (c == 20) {
            arrow1_speed++;
            if (arrow1_speed   > 5)  { arrow1_speed = 1;}
        }
        if (c == 40) {
            mine_speed_lv++;
            if (mine_speed_lv    > 5)   { mine_speed_lv = 1;}
        } 
	}
		BUZZER_PlayTones(tones_cc);
		break;
    
	case AC_DISPLAY_BUTON_UP_LONG_PRESSED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_UP_LONG_PRESSED\n");
		arrow1 = 5;
		arrow1_speed = 5;
		mine_speed_lv = 5;
	}
		BUZZER_PlayTones(tones_cc);
		break;

	case AC_DISPLAY_BUTON_UP_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_UP_RELEASED\n");
		c = c - 20;
        if (c < 0) { c = 40;}     
	}
		BUZZER_PlayTones(tones_cc);
		break;

	case AC_DISPLAY_BUTON_DOWN_LONG_PRESSED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_DOWN_LONG_PRESSED\n");
		arrow1 = 1;
		arrow1_speed = 1;
		mine_speed_lv = 1;
	}
		BUZZER_PlayTones(tones_cc);
		break;

	case AC_DISPLAY_BUTON_DOWN_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_DOWN_RELEASED\n");
        c = c + 20;
        if (c > 40) { c = 0;}
    }
		BUZZER_PlayTones(tones_cc);
		break;

	default:
		break;
	}
}