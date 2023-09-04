#ifndef PLAYER_H
#define PLAYER_H


#define PLAYER_MAX_SPEED 10
#define SCREEN_BORDER_LEFT 0

void player_init();
void player_deinit();
void player_update();
void player_render();

//
void player_moveX();
void player_moveY();

#endif//PLAYER_H