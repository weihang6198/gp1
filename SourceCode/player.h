#ifndef PLAYER_H
#define PLAYER_H


#define PLAYER_MAX_SPEED 10
#define SCREEN_BORDER_LEFT 0

#define MAX_BULLET 99
void player_init();
void player_deinit();
void player_update();
void player_render();

//
extern SPACE_SHIP *spaceShip;
extern BEAM * beam[99];
void player_moveX();
void player_moveY();
void triggerAccelerateMode();
void fireBeam();


#endif//PLAYER_H