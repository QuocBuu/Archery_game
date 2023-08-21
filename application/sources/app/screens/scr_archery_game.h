#ifndef __SCR_ARCHERY_GAME_H__
#define __SCR_ARCHERY_GAME_H__

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

#include "eeprom.h"
#include "app_eeprom.h"

#include "buzzer.h"

#include "screens.h"
#include "screens_bitmap.h"

#define game_off		(0)
#define game_on			(1)
#define game_lose		(2)

extern ar_game_setting_t settingsetup;
extern uint8_t ar_game_status;

extern view_dynamic_t dyn_view_item_archery_game;
extern view_screen_t scr_archery_game;
extern void scr_archery_game_handle(ak_msg_t* msg);

#endif //__SCR_ARCHERY_GAME_H__
