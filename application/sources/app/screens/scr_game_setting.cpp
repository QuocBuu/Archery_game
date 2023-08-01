#include "scr_game_setting.h"

/*****************************************************************************/
/* Variable Declaration - Setting game */
/*****************************************************************************/
#define STEP_SETTING_CHOSSE						(15)

#define SETTING_ITEM_ARRDESS_0					(0)
#define SETTING_ITEM_ARRDESS_1					(STEP_SETTING_CHOSSE)
#define SETTING_ITEM_ARRDESS_2					(STEP_SETTING_CHOSSE*2)
#define SETTING_ITEM_ARRDESS_3					(STEP_SETTING_CHOSSE*3)
#define SETTING_ITEM_ARRDESS_4					(STEP_SETTING_CHOSSE*4)

static const unsigned char PROGMEM chosse_icon [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf8, 0x00, 0xff, 0xfc, 0x00, 0x7f, 
	0xfe, 0x00, 0x3f, 0xff, 0x00, 0x1f, 0xff, 0x80, 0x0f, 0xff, 0xc0, 0x07, 0xff, 0xe0, 0x04, 0x00, 
	0x20, 0x08, 0x00, 0x40, 0x10, 0x00, 0x80, 0x20, 0x01, 0x00, 0x40, 0x02, 0x00, 0x80, 0x04, 0x00, 
	0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static ar_game_setting_t settingdata;
static uint8_t setting_location_chosse;

/*****************************************************************************/
/* View - Setting game */
/*****************************************************************************/
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

void view_scr_game_setting() {
// Text and Number
#define AR_GAME_SETTING_TEXT_AXIS_X				(20)
#define AR_GAME_SETTING_NUMBER_AXIS_X			(110)
// Chosse icon	
#define AR_GAME_SETTING_CHOSSE_ICON_AXIS_Y		(17)
#define AR_GAME_SETTING_CHOSSE_ICON_SIZE_W		(20)
#define AR_GAME_SETTING_CHOSSE_ICON_SIZE_H		(20)
// Frames	
#define AR_GAME_SETTING_FRAMES_AXIS_X			(20)
#define AR_GAME_SETTING_FRAMES_AXIS_Y_1			(2)
#define AR_GAME_SETTING_FRAMES_STEP				(15)
#define AR_GAME_SETTING_FRAMES_SIZE_W			(103)
#define AR_GAME_SETTING_FRAMES_SIZE_H			(13)
#define AR_GAME_SETTING_FRAMES_SIZE_R			(3)
	// Screen
	view_render.setTextSize(1);
	view_render.setTextColor(WHITE);
	// Icon
	view_render.drawBitmap(	0, 
							setting_location_chosse - AR_GAME_SETTING_CHOSSE_ICON_AXIS_Y, 
							chosse_icon, 
							AR_GAME_SETTING_CHOSSE_ICON_SIZE_W, 
							AR_GAME_SETTING_CHOSSE_ICON_SIZE_H, 
							WHITE);
	// Frames
	view_render.drawRoundRect(	AR_GAME_SETTING_FRAMES_AXIS_X, 
								AR_GAME_SETTING_FRAMES_AXIS_Y_1,	
								AR_GAME_SETTING_FRAMES_SIZE_W, 
								AR_GAME_SETTING_FRAMES_SIZE_H, 
								AR_GAME_SETTING_FRAMES_SIZE_R, 
								WHITE);
    view_render.drawRoundRect(	AR_GAME_SETTING_FRAMES_AXIS_X, 
								AR_GAME_SETTING_FRAMES_AXIS_Y_1 + AR_GAME_SETTING_FRAMES_STEP,	
								AR_GAME_SETTING_FRAMES_SIZE_W, 
								AR_GAME_SETTING_FRAMES_SIZE_H, 
								AR_GAME_SETTING_FRAMES_SIZE_R, 
								WHITE);
    view_render.drawRoundRect(	AR_GAME_SETTING_FRAMES_AXIS_X, 
								AR_GAME_SETTING_FRAMES_AXIS_Y_1 + AR_GAME_SETTING_FRAMES_STEP*2,	
								AR_GAME_SETTING_FRAMES_SIZE_W, 
								AR_GAME_SETTING_FRAMES_SIZE_H, 
								AR_GAME_SETTING_FRAMES_SIZE_R, 
								WHITE);
    view_render.drawRoundRect(	AR_GAME_SETTING_FRAMES_AXIS_X, 
								AR_GAME_SETTING_FRAMES_AXIS_Y_1 + AR_GAME_SETTING_FRAMES_STEP*3,	
								AR_GAME_SETTING_FRAMES_SIZE_W, 
								AR_GAME_SETTING_FRAMES_SIZE_H, 
								AR_GAME_SETTING_FRAMES_SIZE_R, 
								WHITE);	
	// Count Arrow
	view_render.setCursor(AR_GAME_SETTING_TEXT_AXIS_X, 5);
	view_render.print(" Arrow        { }");
	view_render.setCursor(AR_GAME_SETTING_NUMBER_AXIS_X, 5);
	view_render.print(settingdata.num_arrow);    
	// Arrow speed
	view_render.setCursor(AR_GAME_SETTING_TEXT_AXIS_X, 20);
	view_render.print(" Arrow speed  { }");
	view_render.setCursor(AR_GAME_SETTING_NUMBER_AXIS_X, 20);
	view_render.print(settingdata.arrow_speed);
	// Mine speed
	view_render.setCursor(AR_GAME_SETTING_TEXT_AXIS_X, 35);
	view_render.print(" Mine  speed  { }");
	view_render.setCursor(AR_GAME_SETTING_NUMBER_AXIS_X, 35);
	view_render.print(settingdata.meteoroid_speed);
	// EXIT
	view_render.setCursor(AR_GAME_SETTING_TEXT_AXIS_X + 30, 50);
	view_render.print("  EXIT ") ;
	view_render.update();
}

/*****************************************************************************/
/* Handle - Setting game */
/*****************************************************************************/
void scr_game_setting_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		// Clear view
		view_render.clear();
		// Chosse item arrdess 1
		setting_location_chosse = SETTING_ITEM_ARRDESS_1;
		// Read setting data
		eeprom_read(	EEPROM_SETTING_START_ADDR, \
						(uint8_t*)&settingdata, \
						sizeof(settingdata));
	}
		break;

	case AC_DISPLAY_BUTTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_MODE_RELEASED\n");
		// Change setting data
		switch (setting_location_chosse) {
		case SETTING_ITEM_ARRDESS_1: {
			// Change arrow number
			settingdata.num_arrow++;
			if (settingdata.num_arrow > 5) {
				settingdata.num_arrow = 1;
			}
		}
			break;

		case SETTING_ITEM_ARRDESS_2: {
			// Change arrow speed
			settingdata.arrow_speed++;
			if (settingdata.arrow_speed > 5) { 
				settingdata.arrow_speed = 1;
			}
		}
			break;

		case SETTING_ITEM_ARRDESS_3: {
			// Change meteoroid speed
			settingdata.meteoroid_speed++;
			if (settingdata.meteoroid_speed > 5) { 
				settingdata.meteoroid_speed = 1;
			}
		}
			break;

		case SETTING_ITEM_ARRDESS_4: {
			// Save change and exit
			eeprom_write(	EEPROM_SETTING_START_ADDR, \
							(uint8_t*)&settingdata, \
							sizeof(settingdata));
			SCREEN_TRAN(scr_menu_game_handle, &scr_menu_game);
			BUZZER_PlayTones(tones_startup);
		}
			break;
		
		default:
			break;
		}
	}
		BUZZER_PlayTones(tones_cc);
		break;
	
	case AC_DISPLAY_BUTTON_UP_LONG_PRESSED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_UP_LONG_PRESSED\n");
		// Change data max
		settingdata.num_arrow = 5;
		settingdata.arrow_speed = 5;
		settingdata.meteoroid_speed = 5;
	}
		BUZZER_PlayTones(tones_cc);
		break;

	case AC_DISPLAY_BUTTON_UP_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_UP_RELEASED\n");
		// Move up
		setting_location_chosse -= STEP_SETTING_CHOSSE;
		if (setting_location_chosse == SETTING_ITEM_ARRDESS_0) { 
			setting_location_chosse = SETTING_ITEM_ARRDESS_4;
		}
	}
		BUZZER_PlayTones(tones_cc);
		break;

	case AC_DISPLAY_BUTTON_DOWN_LONG_PRESSED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_DOWN_LONG_PRESSED\n");
		// Change data min
		settingdata.num_arrow = 1;
		settingdata.arrow_speed = 1;
		settingdata.meteoroid_speed = 1;
	}
		BUZZER_PlayTones(tones_cc);
		break;

	case AC_DISPLAY_BUTTON_DOWN_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_DOWN_RELEASED\n");
		// Move down
		setting_location_chosse += STEP_SETTING_CHOSSE;
		if (setting_location_chosse > SETTING_ITEM_ARRDESS_4) { 
			setting_location_chosse = SETTING_ITEM_ARRDESS_1;
		}
	}
		BUZZER_PlayTones(tones_cc);
		break;

	default:
		break;
	}
}