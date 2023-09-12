
#ifndef SCENE_GAME_H
#define SCENE_GAME_H

//******************************************************************************
//
//
//      scene_game.h
//
//
//******************************************************************************
#define MAP_SCALE 1.1
#define SCOREBOARD_PLAYER 3
struct SCORE
{
    int rank;
    std::string name;
    int distanceTraveled;
};
// 関数のプロトタイプ宣言
void game_init();
void game_deinit();
void game_update();
void game_render();
void game_reset();
void mapLoopLogic();

void recordScore(SCORE score[]);
void readScore();
void readAndWrite();
#endif//SCENE_GAME_H
