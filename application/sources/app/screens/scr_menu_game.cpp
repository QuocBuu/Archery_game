#include "scr_menu_game.h"

// 'Exit_icon', 16x16px
static const unsigned char PROGMEM epd_bitmap_Exit_icon [] = {
	0x00, 0x00, 0x7f, 0x80, 0xff, 0xc0, 0xff, 0xc0, 0xff, 0xd8, 0xff, 0xcc, 0xff, 0xc6, 0xfc, 0x3f, 
	0xfc, 0x3f, 0xff, 0xc6, 0xff, 0xcc, 0xff, 0xd8, 0xff, 0xc0, 0xff, 0xc0, 0x7f, 0x80, 0x00, 0x00
};
// 'ARCHERY_icon', 15x15px
static const unsigned char PROGMEM ARCHERY_icon [] = {
    0x04, 0x00, 0x02, 0x00, 0x01, 0x00, 0x04, 0xc0, 0x00, 0x40, 0x08, 0x40, 0x00, 0x00, 0x1f, 0xf0, 
	0x00, 0x00, 0x08, 0x40, 0x00, 0x40, 0x04, 0xc0, 0x01, 0x00, 0x02, 0x00, 0x04, 0x00
};
// 'Cham_Cham', 1x64px
static const unsigned char PROGMEM epd_bitmap_Cham_Cham [] = {
	0x80, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 
	0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 
	0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 
	0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00
};
// 'xep_hang_icon', 16x16px
static const unsigned char PROGMEM epd_bitmap_xep_hang_icon [] = {
	0x10, 0x00, 0x10, 0x00, 0x6c, 0x00, 0x28, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 
	0x44, 0x00, 0x57, 0xe0, 0x54, 0x20, 0x54, 0x20, 0x54, 0x3e, 0x44, 0x22, 0x44, 0x22, 0x7f, 0xfe
};
// 'setting_icon', 16x16px
static const unsigned char PROGMEM epd_bitmap_setting_icon [] = {
	0x03, 0xc0, 0x12, 0x48, 0x3e, 0x7c, 0x60, 0x06, 0x20, 0x04, 0x23, 0xc4, 0xe4, 0x27, 0x84, 0x21, 
	0x84, 0x21, 0xe4, 0x27, 0x23, 0xc4, 0x20, 0x04, 0x60, 0x06, 0x3e, 0x7c, 0x12, 0x48, 0x03, 0xc0
};

static void view_scr_menu_game();

view_dynamic_t dyn_view_item_menu_game = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_menu_game
};

view_screen_t scr_menu_game = {
	&dyn_view_item_menu_game,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

float a;
uint8_t chosse_1 = 0;
uint8_t chosse_2 = 1;
uint8_t chosse_3 = 1;
uint8_t chosse_4 = 1;

int scroll_bar_location_y;
int screen_location_y;

void update_screen() {
	if (a == 0) {
		chosse_1=0;
		chosse_2=1;
		chosse_3=1;
		chosse_4=1;
		scroll_bar_location_y = 0;
		screen_location_y = 0;
	}
	if (a == 22) {
		chosse_1=1;
		chosse_2=0;
		chosse_3=1;
		chosse_4=1;
		scroll_bar_location_y = 16;
	}
	if (a == 44) {
		chosse_1=1;
		chosse_2=1;
		chosse_3=0;
		chosse_4=1;
		scroll_bar_location_y = 32;
	}
	if (a == 66) {
		chosse_1=1;
		chosse_2=1;
		chosse_3=1;
		chosse_4=0;
		scroll_bar_location_y = 48;
		screen_location_y = 22;
	}
}

void view_scr_menu_game() {
	//scroll bar
	view_render.fillRect(125, scroll_bar_location_y, 3, 16, 1);
	view_render.drawBitmap(126, 0, epd_bitmap_Cham_Cham, 1, 64, 1);
	// khung chon
	view_render.fillRoundRect(0, a-screen_location_y, 123, 20, 3, 1);
	// khung 
	view_render.drawRoundRect(0, 0-screen_location_y, 123, 20, 3, 1);
	view_render.drawRoundRect(0, 22-screen_location_y, 123, 20, 3, 1);
	view_render.drawRoundRect(0, 44-screen_location_y, 123, 20, 3, 1);
	view_render.drawRoundRect(0, 66-screen_location_y, 123, 20, 3, 1);
	// icon
	view_render.drawBitmap(	7, 	2-screen_location_y,		ARCHERY_icon, 				15, 15, chosse_1);
	view_render.drawBitmap(	7, 24-screen_location_y, 		epd_bitmap_setting_icon, 	16, 16, chosse_2);
	view_render.drawBitmap(	7, 46-screen_location_y, 		epd_bitmap_xep_hang_icon, 	16, 16, chosse_3);
	view_render.drawBitmap( 7, 68-screen_location_y, 		epd_bitmap_Exit_icon, 		15, 15, chosse_4);
	// name icon
	view_render.setTextSize(1);
	view_render.setTextColor(chosse_1);
    view_render.setCursor(20, 7-screen_location_y);
	view_render.print("   Archery Game");
	view_render.setTextColor(chosse_2);
    view_render.setCursor(20, 29-screen_location_y);
	view_render.print("   Setting");
	view_render.setTextColor(chosse_3);
    view_render.setCursor(20, 51-screen_location_y);
	view_render.print("   Charts");
	view_render.setTextColor(chosse_4);
	view_render.setCursor(20, 73-screen_location_y);
	view_render.print("   Exit");
}



void scr_menu_game_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
    }
		break;

	case AC_DISPLAY_BUTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_RELEASED\n");
		
        if ( a == 0     ){ SCREEN_TRAN(scr_archer_game_handle  	, &scr_archer_game)	;}
        if ( a == 22    ){ SCREEN_TRAN(scr_game_setting_handle  , &scr_game_setting);}
        if ( a == 44    ){ SCREEN_TRAN(scr_charts_game_handle  	, &scr_charts_game)	;}
        if ( a == 66    ){ SCREEN_TRAN(scr_idle_handle  		, &scr_idle)		;}
	}
		BUZZER_PlayTones(tones_cc);
		break;

	case AC_DISPLAY_BUTON_UP_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_UP_RELEASED\n");
		a=a-22;
        if (a < 0) { 
			a = 66; 
		}
		update_screen();
	}
		break;

	case AC_DISPLAY_BUTON_DOWN_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_DOWN_RELEASED\n");
		a=a+22;
        if (a > 66) { 
			a = 0;
		}
		update_screen();
	}	
		break;

	default:
		break;
	}
}