#include "all.h"

int title_state;
int title_timer;
int selecting=1;
int help = 1;
Sprite* sprbg;
Sprite* sprarrow;
SCORE* score[SCOREBOARD_PLAYER];
//--------------------------------------
//  初期設定
//--------------------------------------
void title_init()
{
    title_state = 0;
    title_timer = 0;
}

//--------------------------------------
//  終了処理
//--------------------------------------
void title_deinit()
{
    music::stop(0);

    safe_delete(sprbg);
    safe_delete(sprarrow);
  
}

//--------------------------------------
//  タイトルの更新処理
//--------------------------------------
void title_update()
{
    switch (title_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprbg = sprite_load(L"./Data/Images/back1.png");
        sprarrow = sprite_load(L"./Data/Images/arrow.png");
         for (int i = 0; i < SCOREBOARD_PLAYER; i++)
        {
            score[i] = new SCORE();
            score[i]->rank = 0;
            score[i]->distanceTraveled = 0;
            score[i]->name = "test";
       }
        title_state++;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        music::play(0);
        music::setVolume(0, 0.15f);

        title_state++;
        /*fallthrough*/

    case 2:
        
        debug::setString("selecting %d", selecting);
          // selecting code start=1,help=2,score=3,help page 1 = 4, help page 2 = 11,score page = 5
        if ((selecting==1)  && (TRG(0) & PAD_START))
        {
           
            sound::play(4, 2);

            nextScene = SCENE_GAME;
            
            break;
        }
        if ((selecting == 11) && (TRG(0) & PAD_START))
        {
            sound::play(4, 2);
            sprbg = sprite_load(L"./Data/Images/help3.png");
            selecting = 12;
           
            break;
        }
        if ((selecting == 12) && (TRG(0) & PAD_SELECT))
        {
            sound::play(4, 2);
            sprbg = sprite_load(L"./Data/Images/help2.png");
            selecting = 11;

            break;
        }
        if ((selecting == 12) && (TRG(0) & PAD_START))
        {
            sound::play(4, 2);
            sprbg = sprite_load(L"./Data/Images/back1.png");
            selecting = 1;

            break;
        }

        if ((selecting == 1) && TRG(0) & PAD_RIGHT)
        {
            sound::play(4, 2);
            sprbg = sprite_load(L"./Data/Images/back2.png");
            selecting = 2;
            break;
        }
        //backspace
        if ((selecting == 4) && TRG(0) & PAD_SELECT)
        {
            debug::setString("main menu");
            sound::play(4, 2);
            sprbg = sprite_load(L"./Data/Images/back1.png");
            selecting = 1;
            break;
        }
        if ((selecting == 2) && TRG(0) & PAD_LEFT) {
            sound::play(4, 2);
            sprbg = sprite_load(L"./Data/Images/back1.png");
            selecting = 1;

            break;
        }
        if ((selecting == 3) && TRG(0) & PAD_START) {//enter scoreboard
            sound::play(4, 2);
            selecting = 1;
            nextScene = SCENE_SCOREBOARD;
      

            break;
        }
      
        if ((selecting == 5) && TRG(0) & PAD_SELECT) {
            sound::play(4, 2);
            sprbg = sprite_load(L"./Data/Images/back1.png");
            selecting = 1;

            break;
        }
        if ((selecting == 2) && (TRG(0) & PAD_START)) {
            sound::play(4, 2);
            sprbg = sprite_load(L"./Data/Images/help1.png");
            selecting = 4;
            break;
        }
        if ((selecting == 2) && (TRG(0) & PAD_RIGHT)) {
            sound::play(4, 2);
            sprbg = sprite_load(L"./Data/Images/back3.png");
            selecting = 3;
            break;
        }
        if ((selecting == 3) && (TRG(0) & PAD_LEFT)) {
            sound::play(4, 2);
            sprbg = sprite_load(L"./Data/Images/back2.png");
            selecting = 2;
            break;
        }
        //backspace
        if ((selecting == 11) && TRG(0) & PAD_SELECT)
        {
            sound::play(4, 2);
            sprbg = sprite_load(L"./Data/Images/help1.png");
            selecting = 4;
            break;
        }
        if ((selecting == 4) && (TRG(0) & PAD_START)) {
            sound::play(4, 2);
            sprbg = sprite_load(L"./Data/Images/help2.png");
            selecting = 11;
        }

        if ((selecting == 4) && (TRG(0) & PAD_TRG1)) {
            sound::play(4,3);
            sound::setVolume(4, 3, 2.0f);
            sprbg = sprite_load(L"./Data/Images/jumpscare.jpg");
        }

        break;


    }
    

    title_timer++;
}

//--------------------------------------
//  タイトルの描画処理
//--------------------------------------
void title_render()
{
    // 画面を青で塗りつぶす
    GameLib::clear(0.3f, 0.5f, 1.0f);

    // タイトルの文字


    // "Push Enter Key" 点滅


    sprite_render(sprbg, 0, 0);
  

    sprite_render(sprarrow, 460, 590, -0.3f, 0.3f);
    sprite_render(sprarrow, 710, 590, 0.3f, 0.3f);
    font::textOut(4, "A   |   D", VECTOR2(460, 590), VECTOR2(1.4f, 1.4f));
    font::textOut(4, "BACKSPACE to back", VECTOR2(410, 630), VECTOR2(1.4f, 1.4f));
    font::textOut(4, "ENTER to continue", VECTOR2(410, 670), VECTOR2(1.4f, 1.4f));


}