#include "scr_menu_game.h"

/*****************************************************************************/
/* Variable Declaration - Menu game */
/*****************************************************************************/
static bool setup_menu;
static scr_menu_game_location_t menu_location;
static scr_menu_game_chosse_t menu_chosse;

/*****************************************************************************/
/* View - Menu game */
/*****************************************************************************/
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

void view_scr_menu_game() {
	// Scroll bar
	view_render.drawBitmap(	AR_GAME_MENU_SCROLL_BAR_AXIS_X, \
							AR_GAME_MENU_SCROLL_BAR_AXIS_Y, \
							dot_icon, \
							1, \
							SCREEN_MENU_H, \
							WHITE);
	view_render.fillRect(	AR_GAME_MENU_SCROLL_BAR_AXIS_X - 1, \
							menu_location.scroll_bar, \
							AR_GAME_MENU_SCROLL_BAR_SIZE_W, \
							AR_GAME_MENU_SCROLL_BAR_SIZE_H, \
							WHITE);
	// Frames White
	view_render.fillRoundRect(	AR_GAME_MENU_FRAMES_AXIS_X, \
								menu_location.chosse - AR_GAME_MENU_FRAMES_AXIS_Y, \
								AR_GAME_MENU_FRAMES_SIZE_W, \
								AR_GAME_MENU_FRAMES_SIZE_H, \
								AR_GAME_MENU_FRAMES_SIZE_R, \
								WHITE);
	// Frames
	view_render.drawRoundRect(	AR_GAME_MENU_FRAMES_AXIS_X, \
								MENU_ITEM_ARRDESS_1-AR_GAME_MENU_FRAMES_AXIS_Y, \
								AR_GAME_MENU_FRAMES_SIZE_W, \
								AR_GAME_MENU_FRAMES_SIZE_H, \
								AR_GAME_MENU_FRAMES_SIZE_R, \
								WHITE);
	view_render.drawRoundRect(	AR_GAME_MENU_FRAMES_AXIS_X, \
								MENU_ITEM_ARRDESS_2-AR_GAME_MENU_FRAMES_AXIS_Y, \
								AR_GAME_MENU_FRAMES_SIZE_W, \
								AR_GAME_MENU_FRAMES_SIZE_H, \
								AR_GAME_MENU_FRAMES_SIZE_R, \
								WHITE);
	view_render.drawRoundRect(	AR_GAME_MENU_FRAMES_AXIS_X, \
								MENU_ITEM_ARRDESS_3-AR_GAME_MENU_FRAMES_AXIS_Y, \
								AR_GAME_MENU_FRAMES_SIZE_W, \
								AR_GAME_MENU_FRAMES_SIZE_H, \
								AR_GAME_MENU_FRAMES_SIZE_R, \
								WHITE);
	view_render.drawRoundRect(	AR_GAME_MENU_FRAMES_AXIS_X, \
								MENU_ITEM_ARRDESS_4-AR_GAME_MENU_FRAMES_AXIS_Y, \
								AR_GAME_MENU_FRAMES_SIZE_W, \
								AR_GAME_MENU_FRAMES_SIZE_H, \
								AR_GAME_MENU_FRAMES_SIZE_R, \
								WHITE);
	// Icon
	view_render.drawBitmap(	AR_GAME_MENU_ICON_AXIS_X, \
							MENU_ITEM_ARRDESS_1-AR_GAME_MENU_ICON_AXIS_Y, \
							archery_icon, \
							AR_GAME_MENU_ICON_SIZE_W, \
							AR_GAME_MENU_ICON_SIZE_H, \
							menu_chosse.archery_game);
	view_render.drawBitmap(	AR_GAME_MENU_ICON_AXIS_X, \
							MENU_ITEM_ARRDESS_2-AR_GAME_MENU_ICON_AXIS_Y, \
							setting_icon, \
							AR_GAME_MENU_ICON_SIZE_W + 1, \
							AR_GAME_MENU_ICON_SIZE_H + 1, \
							menu_chosse.setting);
	view_render.drawBitmap(	AR_GAME_MENU_ICON_AXIS_X, \
							MENU_ITEM_ARRDESS_3-AR_GAME_MENU_ICON_AXIS_Y, \
							chart_icon, \
							AR_GAME_MENU_ICON_SIZE_W + 1, \
							AR_GAME_MENU_ICON_SIZE_H + 1, \
							menu_chosse.charts);
	view_render.drawBitmap(	AR_GAME_MENU_ICON_AXIS_X, \
							MENU_ITEM_ARRDESS_4-AR_GAME_MENU_ICON_AXIS_Y, \
							exit_icon, \
							AR_GAME_MENU_ICON_SIZE_W, \
							AR_GAME_MENU_ICON_SIZE_H, \
							menu_chosse.exit);
	// Text Menu
	view_render.setTextSize(1);
	view_render.setTextColor(menu_chosse.archery_game);
	view_render.setCursor(AR_GAME_MENU_TEXT_AXIS_X, MENU_ITEM_ARRDESS_1 - AR_GAME_MENU_TEXT_AXIS_Y);
	view_render.print("   Archery Game");
	view_render.setTextColor(menu_chosse.setting);
	view_render.setCursor(AR_GAME_MENU_TEXT_AXIS_X, MENU_ITEM_ARRDESS_2 - AR_GAME_MENU_TEXT_AXIS_Y);
	view_render.print("   Setting");
	view_render.setTextColor(menu_chosse.charts);
	view_render.setCursor(AR_GAME_MENU_TEXT_AXIS_X, MENU_ITEM_ARRDESS_3 - AR_GAME_MENU_TEXT_AXIS_Y);
	view_render.print("   Charts");
	view_render.setTextColor(menu_chosse.exit);
	view_render.setCursor(AR_GAME_MENU_TEXT_AXIS_X, MENU_ITEM_ARRDESS_4 - AR_GAME_MENU_TEXT_AXIS_Y);
	view_render.print("   Exit");
}

/*****************************************************************************/
/* Handle - Menu game */
/*****************************************************************************/
void update_menu_screen_chosse() {
	switch (menu_location.chosse) {
	case MENU_ITEM_ARRDESS_1: {
		menu_chosse.archery_game = BLACK;
		menu_chosse.setting = WHITE;
		menu_chosse.charts = WHITE;
		menu_chosse.exit = WHITE;
		menu_location.scroll_bar = 0;
		menu_location.screen = 0;
	}
		break;

	case MENU_ITEM_ARRDESS_2: {
		menu_chosse.archery_game = WHITE;
		menu_chosse.setting = BLACK;
		menu_chosse.charts = WHITE;
		menu_chosse.exit = WHITE;
		menu_location.scroll_bar = AR_GAME_MENU_SCROLL_BAR_SIZE_H;
	}
		break;

	case MENU_ITEM_ARRDESS_3: {
		menu_chosse.archery_game = WHITE;
		menu_chosse.setting = WHITE;
		menu_chosse.charts = BLACK;
		menu_chosse.exit = WHITE;
		menu_location.scroll_bar = AR_GAME_MENU_SCROLL_BAR_SIZE_H*2;
	}
		break;

	case MENU_ITEM_ARRDESS_4: {
		menu_chosse.archery_game = WHITE;
		menu_chosse.setting = WHITE;
		menu_chosse.charts = WHITE;
		menu_chosse.exit = BLACK;
		menu_location.scroll_bar = AR_GAME_MENU_SCROLL_BAR_SIZE_H*3;
		menu_location.screen = STEP_MENU_CHOSSE;
	}
		break;

	default:
		break;
	}
}

void scr_menu_game_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		// setup one shot
		if(setup_menu == 0) {
			menu_chosse.archery_game = BLACK;
			menu_chosse.setting = WHITE;
			menu_chosse.charts = WHITE;
			menu_chosse.exit = WHITE;
			menu_location.chosse = MENU_ITEM_ARRDESS_1;
			setup_menu = 1;
		}
		// timer switch to scr_idle
		timer_set(	AC_TASK_DISPLAY_ID, \
					AC_DISPLAY_SHOW_IDLE, \
					AC_DISPLAY_IDLE_INTERVAL, \
					TIMER_ONE_SHOT);
	}
		break;
	
	case AC_DISPLAY_SHOW_IDLE: {
		SCREEN_TRAN(scr_idle_handle,&scr_idle);
	}
		break;

	case AC_DISPLAY_BUTTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_MODE_RELEASED\n");
		// Screen transition
		switch (menu_location.chosse) {
		case MENU_ITEM_ARRDESS_1: {
			SCREEN_TRAN(scr_archery_game_handle,	&scr_archery_game	);
		}
			break;

		case MENU_ITEM_ARRDESS_2: {
			SCREEN_TRAN(scr_game_setting_handle,	&scr_game_setting	);
		}
			break;

		case MENU_ITEM_ARRDESS_3: {
			SCREEN_TRAN(scr_charts_game_handle,		&scr_charts_game	);
		}
			break;

		case MENU_ITEM_ARRDESS_4: {
			SCREEN_TRAN(scr_idle_handle,			&scr_idle			);
		}
			break;

		default:
			break;
		}
	}
		BUZZER_PlayTones(tones_cc);
		break;

	case AC_DISPLAY_BUTTON_UP_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_UP_RELEASED\n");
		// Move up
		menu_location.chosse -= STEP_MENU_CHOSSE;
		if (menu_location.chosse < MENU_ITEM_ARRDESS_1) { 
			menu_location.chosse = MENU_ITEM_ARRDESS_4; 
		}
		// Update menu screen
		update_menu_screen_chosse();
		// Reset timer switch to scr_idle
		timer_set(	AC_TASK_DISPLAY_ID, \
					AC_DISPLAY_SHOW_IDLE, \
					AC_DISPLAY_IDLE_INTERVAL, \
					TIMER_ONE_SHOT);	
		}
		break;

	case AC_DISPLAY_BUTTON_DOWN_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTTON_DOWN_RELEASED\n");
		// Move down
		menu_location.chosse += STEP_MENU_CHOSSE;
		if (menu_location.chosse > MENU_ITEM_ARRDESS_4) { 
			menu_location.chosse = MENU_ITEM_ARRDESS_1;
		}
		// Update menu screen
		update_menu_screen_chosse();
		// Reset timer switch to scr_idle
		timer_set(	AC_TASK_DISPLAY_ID, \
					AC_DISPLAY_SHOW_IDLE, \
					AC_DISPLAY_IDLE_INTERVAL, \
					TIMER_ONE_SHOT);
	}
		break;

	default:
		break;
	}
}