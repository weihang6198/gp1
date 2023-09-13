#include "all.h"
int scoreboard_state;
int scoreboard_timer;

Sprite* sprSB;

//--------------------------------------
//  初期設定
//--------------------------------------
void scoreboard_init()
{
    scoreboard_state = 0;
    scoreboard_timer = 0;
}

//--------------------------------------
//  終了処理
//--------------------------------------
void scoreboard_deinit()
{
    music::stop(0);

   
    safe_delete(sprSB);
   
}

//--------------------------------------
//  タイトルの更新処理
//--------------------------------------
void scoreboard_update()
{
    switch (scoreboard_state)
    {
    case 0:
        //////// 初期設定 ////////

   

        sprSB = sprite_load(L"./Data/Images/score.png");
     
        scoreboard_state++;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

      
        music::setVolume(0, 0.15f);

        scoreboard_state++;
        /*fallthrough*/

    case 2:
        //////// 通常時 ////////
      
        
        if (TRG(0) & PAD_START)
        {
            sound::play(4, 2);
            music::stop(2);
            nextScene = SCENE_TITLE;
            break;
        }
        readScore(score);
        for (int i = 0; i < 4; i++)
        {
            debug::setString("distance travelled %d", score[i]->distanceTraveled);
            debug::setString("name is %s", score[i]->name.c_str());

        }
        break;


    }


    scoreboard_timer++;
}

//--------------------------------------
//  タイトルの描画処理
//--------------------------------------
void scoreboard_render()
{
    // 画面を青で塗りつぶす
    GameLib::clear(0.3f, 0.5f, 1.0f);

    // タイトルの文字


    // "Push Enter Key" 点滅


    sprite_render(sprSB, 0, 0);
    //write ranking pos
    //every 70 is new row 
    for (int i = 0; i < 3; i++)
    {
        font::textOut(4, std::to_string(i+1), 250, 230+70*i, 1, 1);
        font::textOut(4, score[i]->name, 450, 230 + 70 * i, 1, 1);
        font::textOut(4, std::to_string(score[i]->distanceTraveled), 850, 230+70*i, 1, 1);
    }
  

    ////write name
    //font::textOut(4, "test name", 450, 230, 1, 1);
    //font::textOut(4, "test", 450, 300, 1, 1);
    //font::textOut(4, "test", 450, 370, 1, 1);

    ////write score
    //font::textOut(4, "score", 850, 230, 1, 1);
    //font::textOut(4, "test", 850, 300, 1, 1);
    //font::textOut(4, "test", 850, 370, 1, 1);
    font::textOut(4, "Press ENTER/BACKSPACE to go back", VECTOR2(390, 670), VECTOR2(1.0f, 1.0f));
}
