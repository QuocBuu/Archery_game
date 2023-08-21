#ifndef __AR_GAME_STRUCT_H__
#define __AR_GAME_STRUCT_H__

typedef struct {
    bool visible;
    uint32_t x, y;
    uint8_t action_image;
} ar_game_t;

extern ar_game_t archery;

#endif //__AR_GAME_STRUCT_H__