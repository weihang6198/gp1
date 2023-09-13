
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
#define SCOREBOARD_PLAYER 4
#define SCOREBOARD_HOLDER 1
#define MIN_MAP_MOVE_SPEED 8
#define MAX_MAP_MOVE_SPEED 15
#define SCORE_ROW 5
#define SCORE_COL 3
#define DEFAULT_SCORE_MUL 1
#define TURBO_SCORE_MUL 1.5
using namespace std;
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

/*
1) when the game starts,read the score from binary file and store it inside score var
2) the only way that player can exit the game is by losing the game, therefore the rank comparison occurs when the game is over
3)record the score and make comparison , then write to the binary file

*/
string readAndWriteString(SCORE* score[]);
void RWBinary(SCORE* score[]);
void readScore(SCORE* score[]);
void sortScore(SCORE* score[]);
void processScore(string input[], SCORE* score[]);
void mapSpeedUpLogic();
//bool compareByScoreDescending(const SCORE* a, const SCORE* b) {
//    return a->distanceTraveled > b->distanceTraveled;
//}
//extern SCORE* score[SCOREBOARD_PLAYER];
#endif//SCENE_GAME_H
