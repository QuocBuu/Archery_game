#ifndef __SCR_MENU_GAME_H__
#define __SCR_MENU_GAME_H__

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "sys_ctrl.h"
#include "sys_dbg.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"
#include "view_render.h"

#include "buzzer.h"

#include "screens.h"
#include "screens_bitmap.h"

// Menu
#define STEP_MENU_CHOSSE				(22)
#define NUMBER_MENU_ITEMS				(4)
#define	SCREEN_MENU_H					(64)
// Menu items
#define MENU_ITEM_ARRDESS_1				(STEP_MENU_CHOSSE)
#define MENU_ITEM_ARRDESS_2				(STEP_MENU_CHOSSE*2)
#define MENU_ITEM_ARRDESS_3				(STEP_MENU_CHOSSE*3)
#define MENU_ITEM_ARRDESS_4				(STEP_MENU_CHOSSE*4)
// Scroll bar
#define AR_GAME_MENU_SCROLL_BAR_AXIS_X		(126)
#define AR_GAME_MENU_SCROLL_BAR_AXIS_Y		(0)
#define AR_GAME_MENU_SCROLL_BAR_SIZE_W		(3)
#define AR_GAME_MENU_SCROLL_BAR_SIZE_H		(SCREEN_MENU_H / NUMBER_MENU_ITEMS)
// Frames
#define AR_GAME_MENU_FRAMES_AXIS_X			(0)
#define AR_GAME_MENU_FRAMES_AXIS_Y			(STEP_MENU_CHOSSE + menu_location.screen)
#define AR_GAME_MENU_FRAMES_SIZE_W			(123)
#define AR_GAME_MENU_FRAMES_SIZE_H			(20)
#define AR_GAME_MENU_FRAMES_SIZE_R			(3)
// ICON	
#define AR_GAME_MENU_ICON_AXIS_X			(7)
#define AR_GAME_MENU_ICON_AXIS_Y			(AR_GAME_MENU_FRAMES_AXIS_Y - 2)
#define AR_GAME_MENU_ICON_SIZE_W			(15)
#define AR_GAME_MENU_ICON_SIZE_H			(15)
// Text
#define AR_GAME_MENU_TEXT_AXIS_X			(20)
#define AR_GAME_MENU_TEXT_AXIS_Y			(AR_GAME_MENU_ICON_AXIS_Y - 5)

typedef struct {
	// menu object location
	uint8_t chosse;
	uint8_t scroll_bar;
	uint8_t screen;
} scr_menu_game_location_t;

typedef struct {
	// menu items
	bool archery_game;
	bool setting;
	bool charts;
	bool exit;
} scr_menu_game_chosse_t;

extern view_dynamic_t dyn_view_item_menu_game;
extern view_screen_t scr_menu_game;
extern void scr_menu_game_handle(ak_msg_t* msg);

#endif //__SCR_MENU_GAME_H__
