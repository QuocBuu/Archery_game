#include "scr_archer_game.h"

#define ARCHERY_SIZE_X				(15)
#define ARCHERY_SIZE_Y				(15)

#define ARROW_MAX				(5)
#define ARROW_MAX_X				(120)
#define ARROW_SIZE_X				(10)
#define ARROW_SIZE_Y				(3)
#define ARROW_R					(2)

#define MINE_MAX				(5)
#define MINE_SIZE_X				(20)
#define MINE_SIZE_y				(10)

#define MINE_MIN_ARROW				(1)
#define MINE_MAX_ARROW				(8)

//ARCHERY
int ARCHERY_x  = 2, ARCHERY_y = 20;
// Arrow
int arrow_id[ARROW_MAX], arrow_x[ARROW_MAX], arrow_y[ARROW_MAX];
int count_arrow;
// mine
int mine_id[MINE_MAX], mine_x[MINE_MAX] = {130,200,150,250,110}, mine_y[MINE_MAX] = {2,12,22,32,42};
int mine_bumbum[MINE_MAX];
// dead_border
int dead_x = 20;
// speed
int arrow_speed;
int mine_speed;
//score
int score;
static uint8_t mine_run;

static const unsigned char PROGMEM ARCHERY_icon_1 [] = {
    	0x04, 0x00, 0x02, 0x00, 0x01, 0x00, 0x04, 0xc0, 0x00, 0x40, 0x08, 0x40, 0x00, 0x00, 0x1f, 0xf0, 
	0x00, 0x00, 0x08, 0x40, 0x00, 0x40, 0x04, 0xc0, 0x01, 0x00, 0x02, 0x00, 0x04, 0x00
};

static const unsigned char PROGMEM ARCHERY_icon_2 [] = {
    	0x04, 0x00, 0x02, 0x00, 0x01, 0x00, 0x04, 0xc0, 0x00, 0x40, 0x08, 0x40, 0x00, 0x20, 0x08, 0x40, 
	0x00, 0x20, 0x08, 0x40, 0x00, 0x40, 0x04, 0xc0, 0x01, 0x00, 0x02, 0x00, 0x04, 0x00
};

// 'mine_icon_1', 20x10px
static const unsigned char PROGMEM epd_bitmap_mine_icon_1 [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x78, 0x00, 0xa8, 0x00, 0x00, 0xfe, 0x3e, 0x00, 0xa8, 
	0x00, 0x00, 0xfc, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'mine_icon_2', 20x10px
static const unsigned char PROGMEM epd_bitmap_mine_icon_2 [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xe3, 0xc0, 0xa8, 0x00, 0x00, 0xfd, 0xf1, 0xf0, 0xa8, 
	0x00, 0x00, 0xfc, 0xe3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'mine_icon_3', 20x10px
static const unsigned char PROGMEM epd_bitmap_mine_icon_3 [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x80, 0x40, 0xa8, 0x00, 0x00, 0xfb, 0xe0, 0x10, 0xa8, 
	0x00, 0x00, 0xff, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'icon_arrow', 10x5px
static const unsigned char PROGMEM epd_bitmap_icon_arrow [] = {
	0x00, 0x00, 0x80, 0x00, 0x7f, 0xc0, 0x80, 0x00, 0x00, 0x00
};

// 'icon_BUMBUM_1', 15x15px
static const unsigned char epd_bitmap_icon_BUMBUM_1 [] = {
	0x00, 0x00, 0x02, 0x20, 0x02, 0x60, 0x23, 0xe0, 0x1f, 0xe0, 0x1f, 0x7c, 0x0c, 0x30, 0x78, 0x70, 
	0x1c, 0x78, 0x0e, 0xfe, 0x1f, 0xe0, 0x13, 0x60, 0x03, 0x20, 0x02, 0x10, 0x00, 0x00
};

// 'icon_BUMBUM_2', 15x15px
static const unsigned char epd_bitmap_icon_BUMBUM_2 [] = {
	0x00, 0x00, 0x10, 0x80, 0x09, 0x80, 0x0d, 0x90, 0x0f, 0xf0, 0xfe, 0xe0, 0x3c, 0x70, 0x1c, 0x3c, 
	0x18, 0x60, 0x7d, 0xf0, 0x0f, 0xf0, 0x0f, 0x88, 0x0c, 0x80, 0x08, 0x80, 0x00, 0x00
};

// 'icon_BUMBUM_3', 10x10px
static const unsigned char epd_bitmap_icon_BUMBUM_3 [] = {
	0x04, 0x00, 0x24, 0x00, 0x1d, 0x00, 0x1f, 0x00, 0x63, 0x80, 0x23, 0x00, 0x7f, 0x00, 0x1d, 0x80, 
	0x14, 0x00, 0x00, 0x00
};

static void view_scr_archer_game();

view_dynamic_t dyn_view_item_archer_game = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_archer_game
};

view_screen_t scr_archer_game = {
	&dyn_view_item_archer_game,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

uint8_t mm;
void view_scr_archer_game() {
	// setup_level
	if(mm == 0) {
		eeprom_read(18, (uint8_t*)&count_arrow, 	1U);
		eeprom_read(20, (uint8_t*)&arrow_speed, 	1U);
		eeprom_read(22, (uint8_t*)&mine_speed, 	1U);
		mm =1;	
	}
	// screen
	view_render.setTextSize(1);
	view_render.setTextColor(WHITE);
	view_render.setCursor(2,55);
	view_render.print("Arrow:");
	view_render.print(count_arrow);
	view_render.setCursor(60,55);
	view_render.print(" Score:");
	view_render.print(score);
    	view_render.drawLine(0, LCD_HEIGHT , LCD_WIDTH, LCD_HEIGHT, WHITE);
    	view_render.drawLine(0, LCD_HEIGHT-10 , LCD_WIDTH, LCD_HEIGHT-10, WHITE);
	view_render.drawRect(0, 0, 128, 64, 1);
    // ARCHERY
	if (count_arrow == 0) {
		view_render.drawBitmap(ARCHERY_x, ARCHERY_y, ARCHERY_icon_2, ARCHERY_SIZE_X, ARCHERY_SIZE_Y, 1);
	}
	else {
		view_render.drawBitmap(ARCHERY_x, ARCHERY_y, ARCHERY_icon_1, ARCHERY_SIZE_X, ARCHERY_SIZE_Y, 1);
	}
	// dead_border
	view_render.drawFastVLine(dead_x, 2, 52, 1);
	
	for (int i = 0; i < 5; i++) {
		view_render.fillCircle(dead_x, mine_y[i]+5, 1, WHITE);
	// Arrow
	if (arrow_id[i] == 1) {
		view_render.drawBitmap(arrow_x[i], arrow_y[i], epd_bitmap_icon_arrow, ARROW_SIZE_X, ARROW_SIZE_Y+2, WHITE);
	}
	// Mine
	if (mine_id[i] == 0) {
		if (mine_run == 0) {
			view_render.drawBitmap(mine_x[i], mine_y[i], epd_bitmap_mine_icon_1, MINE_SIZE_X, MINE_SIZE_y,WHITE);
		}
		else if (mine_run == 1) {
			view_render.drawBitmap(mine_x[i], mine_y[i], epd_bitmap_mine_icon_2, MINE_SIZE_X, MINE_SIZE_y,WHITE);
		}
		else if (mine_run == 2) {
			view_render.drawBitmap(mine_x[i], mine_y[i], epd_bitmap_mine_icon_3, MINE_SIZE_X, MINE_SIZE_y,WHITE);
		}
	}
	// BumBum
		if (mine_id[i] == 1 && mine_bumbum[i] < 2) {
			view_render.drawBitmap(mine_x[i]-5, mine_y[i]+2, epd_bitmap_icon_BUMBUM_1, 15, 15,WHITE);
			
		}
		else if (mine_id[i] == 1 && mine_bumbum[i] < 3) {
			view_render.drawBitmap(mine_x[i]-5, mine_y[i]+2, epd_bitmap_icon_BUMBUM_2, 15, 15,WHITE);
		}
		else if (mine_id[i] == 1 && mine_bumbum[i] < 4) {
			view_render.drawBitmap(mine_x[i]-3, mine_y[i]+1, epd_bitmap_icon_BUMBUM_3, 10, 10,WHITE);
			mine_id[i] = 0;
			mine_x[i] = (rand() % 39) + 130;
			mine_bumbum[i] = 0;
		}
	}
}

void update_archer_game() {
	
	for (int i1 = 0; i1 < 5; i1++) {
	// arrow
		if (arrow_id[i1] == 1) {
			if (arrow_x[i1] == ARROW_MAX_X) {
				arrow_id[i1] 	= 	0;
				arrow_x[i1]	=	0;
				count_arrow++;
			}
		}
		//mine
		if (mine_id[i1] == 0) {
			for (int i2 = 0; i2 < 5; i2++) {
				if (mine_x[i1] < (arrow_x[i2]+ARROW_SIZE_X-3)) {
					if ((mine_y[i1] + MINE_MAX_ARROW) > arrow_y[i2]) {
						if ((mine_y[i1] - MINE_MIN_ARROW) < arrow_y[i2]) {
							mine_id[i1] = 1;
							arrow_id[i2] = 0;
							arrow_x[i2] = 0;
							score = score + 10;
							count_arrow++;
							BUZZER_PlayTones(tones_BUM);
						}
					}
				}
			}
		}
		//Dead
		if (mine_x[i1] <= dead_x-3) {
			for (int i3 = 0; i3 < 5; i3++) {
				mine_id[i3] = 0;
				mine_x[i3] = (rand() % (139)) + 110;
				arrow_id[i3] = 0;
				arrow_x[i3] = 0;
				mine_bumbum[i3] = 0;
			}
			BUZZER_PlayTones(tones_3beep);
			dead_x = 20;
			eeprom_write(2, (uint8_t*)&score, sizeof(score));
			score = 0;
			SCREEN_TRAN(scr_game_over_handle, &scr_game_over);
			mm = 0;
		}
	}
}

void scr_archer_game_handle(ak_msg_t* msg) {
	switch (msg->sig) {

	case SCREEN_ENTRY: {
		case AC_DISPLAY_INITIAL: {
		APP_DBG_SIG("AC_DISPLAY_INITIAL\n");
		view_render.initialize();
		view_render_display_on();
		timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_GAME, AC_DISPLAY_MAP_GAME, TIMER_PERIODIC);
		}
    }
        break;

    case AC_DISPLAY_SHOW_GAME: {
		APP_DBG_SIG("AC_DISPLAY_SHOW_GAME\n");
		//dead border
		if (score%200 == 0) {
			dead_x += (score/200)*5;
			score += 10;
		}
		// Arrow_&_Mine
		for (int i4 = 0; i4 < 5; i4++) {
			// arrow
			if (arrow_id[i4] == 1) {
				arrow_x[i4] += arrow_speed;
			}
			// mine
			if (mine_id[i4] == 0) {
				mine_x[i4] -= mine_speed;
			}
			if (mine_id[i4] == 1) {
				mine_bumbum[i4]++;
			}
		}
		//mine_run
		if (mine_run == 0) {mine_run = 1;}
		else if (mine_run == 1) {mine_run = 2;}
		else if (mine_run == 2) {mine_run = 0;}
		//update
		update_archer_game();	
	}
		break;

	case AC_DISPLAY_BUTON_MODE_LONG_PRESSED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_LONG_PRESSED\n");
		SCREEN_TRAN(scr_buu_handle, &scr_buu);	

	}
		break;

	case AC_DISPLAY_BUTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_RELEASED\n");
        //Arrow
		if (arrow_id[0] == 0 && count_arrow != 0) {
			count_arrow--;
			arrow_id[0] = 1;
			arrow_y[0] 	= ARCHERY_y+5;
			BUZZER_PlayTones(tones_cc);
 		}
		else if (arrow_id[1] == 0 && count_arrow != 0) {
			count_arrow--;
			arrow_id[1] = 1;
			arrow_y[1] 	= ARCHERY_y+5;
			BUZZER_PlayTones(tones_cc);
		}
		else if (arrow_id[2] == 0 && count_arrow != 0) {
			count_arrow--;
			arrow_id[2] = 1;
			arrow_y[2] 	= ARCHERY_y+5;
			BUZZER_PlayTones(tones_cc);
		}
		else if (arrow_id[3] == 0 && count_arrow != 0) {
			count_arrow--;
			arrow_id[3] = 1;
			arrow_y[3] 	= ARCHERY_y+5;
			BUZZER_PlayTones(tones_cc);
		}
		else if (arrow_id[4] == 0 && count_arrow != 0) {
			count_arrow--;
			arrow_id[4] = 1;
			arrow_y[4] 	= ARCHERY_y+5;
			BUZZER_PlayTones(tones_cc);
		}
		else {
			BUZZER_PlayTones(tones_3beep);
		}
	}
		break;

	case AC_DISPLAY_BUTON_UP_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_UP_RELEASED\n");
		 ARCHERY_y = ARCHERY_y - 5;
        if ( ARCHERY_y < -5) {  ARCHERY_y = -5; } 
	}
		break;
	
	case AC_DISPLAY_BUTON_DOWN_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_DOWN_RELEASED\n");
		 ARCHERY_y = ARCHERY_y + 5;
        if ( ARCHERY_y > 40) {  ARCHERY_y = 40;}
	}	
		break;

	default:
		break;
	}
}
