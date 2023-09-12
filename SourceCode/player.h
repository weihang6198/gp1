#ifndef PLAYER_H
#define PLAYER_H

#define MAX_LIFE	3
#define MAX_BULLET	99
#define MAX_SPEED	20
#define MIN_SPEED	12

void player_init();
void player_deinit();
void player_update();
void player_render();


extern SPACE_SHIP *spaceShip;
extern BEAM * beam[99];

extern int player_state;

void player_moveX();
void player_moveY();
void triggerAccelerateMode();
void fireBeam();
void LimitSpaceShipToScreen();
void spaceShipLogic();


#endif//PLAYER_H