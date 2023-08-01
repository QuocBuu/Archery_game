#include "scr_game_over.h"

/*****************************************************************************/
/* Variable Declaration - game over */
/*****************************************************************************/
// 'icon_restart', 15x15px
static const unsigned char PROGMEM epd_bitmap_icon_restart [] = {
	0x01, 0x00, 0x07, 0x00, 0x0f, 0xc0, 0x0f, 0xf0, 0x07, 0x78, 0x63, 0x9c, 0x61, 0x0c, 0x60, 0x0c, 
	0x60, 0x0c, 0x60, 0x0c, 0x60, 0x0c, 0x70, 0x1c, 0x38, 0x38, 0x1f, 0xf0, 0x07, 0xc0
};
// 'icon_xep_hang', 17x15px
static const unsigned char PROGMEM epd_bitmap_icon_xep_hang [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x08, 0x00, 0x00, 0x28, 0x00, 0x00, 
	0xa8, 0x00, 0x00, 0xa8, 0x00, 0x02, 0xa8, 0x00, 0x02, 0xa8, 0x00, 0x0a, 0xa8, 0x00, 0x0a, 0xa8, 
	0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'icon_go_home', 16x16px
static const unsigned char PROGMEM epd_bitmap_icon_go_home [] = {
	0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x02, 0x40, 0x05, 0xa0, 0x0b, 0xd0, 0x17, 0xe8, 0x2f, 0xf4, 
	0x5f, 0xfb, 0xbc, 0x3d, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x1c, 0x38, 0x00, 0x00
};

static ar_game_score_t GameScore;

/*****************************************************************************/
/* View - game over */
/*****************************************************************************/
static void view_scr_game_over();

view_dynamic_t dyn_view_item_game_over = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_game_over
};

view_screen_t scr_game_over = {
	&dyn_view_item_game_over,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void view_scr_game_over() {
	// Screen
	view_render.fillScreen(WHITE);
	view_render.setTextSize(2);
	view_render.setTextColor(BLACK);
	view_render.setCursor(11, 10);
	view_render.print("GAME OVER");
	view_render.setTextSize(1);
	view_render.setTextColor(BLACK);
	view_render.setCursor(16, 35);
	view_render.print("Your score:");
	view_render.setCursor(81, 35);
	view_render.print(GameScore.score_now);
	// Icon
	view_render.drawBitmap(10, 	48,	epd_bitmap_icon_restart,	15,	15,	0);
	view_render.drawBitmap(55, 	50,	epd_bitmap_icon_xep_hang,	17,	15,	0);
	view_render.drawBitmap(100,	48,	epd_bitmap_icon_go_home,	16,	16,	0);
}

/*****************************************************************************/
/* Handle - game over */
/*****************************************************************************/
void rank_ranking() {
	if (GameScore.score_now > GameScore.score_1st) {
		GameScore.score_3rd = GameScore.score_2nd;
		GameScore.score_2nd = GameScore.score_1st;
		GameScore.score_1st = GameScore.score_now;
	}
	else if (GameScore.score_now > GameScore.score_2nd) {
		GameScore.score_3rd = GameScore.score_2nd;
		GameScore.score_2nd = GameScore.score_now;
	}
	else if (GameScore.score_now > GameScore.score_3rd) {
		GameScore.score_3rd = GameScore.score_now;
	}
}

void scr_game_over_handle(ak_msg_t* msg) {
	switch (msg->sig) {
		case SCREEN_ENTRY: {
			APP_DBG_SIG("SCREEN_ENTRY\n");
			// View render
			view_render.initialize();
			view_render_display_on();
			// Read score
			eeprom_read(EEPROM_SCORE_START_ADDR, \
						(uint8_t*)&GameScore, \
						sizeof(GameScore));
			eeprom_read(EEPROM_SCORE_PLAY_ADDR, \
						(uint8_t*)&GameScore.score_now, \
						sizeof(GameScore.score_now));
			// reorganize
			rank_ranking();
		}
			break;

		case AC_DISPLAY_BUTTON_MODE_RELEASED: {
			APP_DBG_SIG("AC_DISPLAY_BUTTON_MODE_RELEASED\n");
			// Save score and go Menu game
			eeprom_write(	EEPROM_SCORE_START_ADDR, \
							(uint8_t*)&GameScore, \
							sizeof(GameScore));
			SCREEN_TRAN(scr_menu_game_handle, &scr_menu_game);
		}
			BUZZER_PlayTones(tones_cc);
			break;

		case AC_DISPLAY_BUTTON_UP_RELEASED: {
			APP_DBG_SIG("AC_DISPLAY_BUTTON_UP_RELEASED\n");
			// Save score and go Charts
			eeprom_write(	EEPROM_SCORE_START_ADDR, \
							(uint8_t*)&GameScore, \
							sizeof(GameScore));
			SCREEN_TRAN(scr_charts_game_handle, &scr_charts_game );
		}
			BUZZER_PlayTones(tones_cc);
			break;

		case AC_DISPLAY_BUTTON_DOWN_RELEASED: {
			APP_DBG_SIG("AC_DISPLAY_BUTTON_DOWN_RELEASED\n");
			// Save score and restart game
			eeprom_write(	EEPROM_SCORE_START_ADDR, \
							(uint8_t*)&GameScore, \
							sizeof(GameScore));
			SCREEN_TRAN(scr_archery_game_handle, &scr_archery_game );
		}	
			BUZZER_PlayTones(tones_cc);
			break;

		default:
			break;
	}
}