//******************************************************************************
//
//
//      scene_game
//
//
//******************************************************************************

//----< インクルード >-----------------------------------------------------------
#include "all.h"
#include "player.h"
#include "enemy.h"
#include "item.h"
using namespace std;

//------< 定数 >----------------------------------------------------------------


//------< 構造体 >---------------------------------------------------------------


//------< 変数 >----------------------------------------------------------------
int game_state;
int game_timer;
int mapMoveSpeed;
int mapPosX;
int map2PosX = 1280;
bool moveFirstMap = true;
bool moveSecondMap = false;
int totalDistanceTravelled;
bool runOnce = true;
Sprite* sprBack;
SCORE score[SCOREBOARD_PLAYER];


//--------------------------------------
//  ゲームの初期設定
//--------------------------------------
void game_init()
{
    game_state      = 0;
    game_timer      = 0;
    //consumable_init();
}

//--------------------------------------
//  ゲームの終了処理
//--------------------------------------
void game_deinit()
{
#if 11
//******************************************************************************
// TODO:11 プレイヤーの終了処理関数を呼び出す
//------------------------------------------------------------------------------
/*
課題）
    下記でplayer_deinit関数を呼びましょう。
*/
//******************************************************************************
#endif
    //TODO_11

    item_deinit();
    meteor_deinit();
    player_deinit();
    safe_delete(sprBack);
}

//--------------------------------------
//  ゲームの更新処理
//--------------------------------------
void game_update()
{
    switch (game_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprBack = sprite_load(L"./Data/Images/space.png");



        game_state++;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        //GameLib::setBlendMode(Blender::BS_ALPHA);
      //  music::play(1);
        music::setVolume(1, 0.15f);
       mapPosX = 0;
       map2PosX = 1280;
      moveFirstMap = true;
      moveSecondMap = false;
      mapMoveSpeed = 5;
      totalDistanceTravelled = 0;
     
      for (int i = 0; i < SCOREBOARD_PLAYER; i++)
      {
          score[i] = { i+1,"moh wei hang",50+i*50 };
          
       }
      readAndWrite();
     // recordScore(score);
        game_state++;
        /*fallthrough*/
        
    case 2:
        
        //////// 通常時 ////////

        if (runOnce)
        {
            runOnce = false;
            OutputDebugStringA("insidde run once\n");
          // readScore();
          }
       /* if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE_TITLE;
            break;
        }*/
       
        mapLoopLogic();
        item_update();
        player_update();
        meteor_update(); 
        spaceShip->collisionDetector(spaceShip, &meteor);
        if (spaceShip->turboMode)
        {
          
            mapMoveSpeed = 10;
        }
        else
        {
            mapMoveSpeed = 5;
        }
        for (int i = 0; i < MAX_ITEM; i++)
        {
            if (item[i]) 
            {
                spaceShip->collisionDetector(spaceShip, item[i]);
            }
        }
        debug::setString("total distance travelled %d", totalDistanceTravelled);
      

       
        break;
    }

    game_timer++;
}

//--------------------------------------
//  ゲームの描画処理
//--------------------------------------
void game_render()
{
    GameLib::clear(0.2f, 0.2f, 0.4f);
    //firrst screen
    if (moveFirstMap)
        {
        sprite_render(sprBack, mapPosX, 0,
          MAP_SCALE, MAP_SCALE); //scale
        }
      
        if (moveSecondMap)
        {
            debug::setString("second screen");
            sprite_render(sprBack, map2PosX , 0,
                MAP_SCALE, MAP_SCALE); //scale
        }
  
    item_render();
    player_render();
    meteor_render(); 
  /*  text_out(1, "moh wei hang", 500, 500);*/


}

void game_reset()
{
    nextScene = SCENE_GAMEOVER;
   //// game_deinit();
    game_state = 0;
    meteor_state = 0;
    player_state = 0;
    item_state = 0;

  
}

void mapLoopLogic()
{
    totalDistanceTravelled += mapMoveSpeed;
    //screen size is 1280
      //image is 1920x1080
      //1920-1280=640
      //640 is where the blank will appear and it has to be replace with the new image
    if (mapPosX < -1900) // #3
    {
        mapPosX = 1280;
        moveFirstMap = false;
    }
    else if (moveFirstMap)  // #1
    {
        mapPosX -= mapMoveSpeed;
    }

    if (mapPosX < -640 || moveSecondMap) //#2
    {
        moveSecondMap = true;
        map2PosX -= mapMoveSpeed;
    }
    if (map2PosX < -1900) //#5
    {
        map2PosX = 1280;
        moveSecondMap = false;
    }
    if (map2PosX < -640)  //#4
    {
        moveFirstMap = true;
    }
}

void recordScore(SCORE score[3])
{
    std::ofstream outFile("binary_data.bin", std::ios::binary);
    if (!outFile) {
        OutputDebugStringA("Failed to open the file for writing.\n");
        return;
    }
    std::string test = "mohweihang";
        outFile.write(reinterpret_cast<const char*>(&test), sizeof(test));
   

    // Close the file
    outFile.close();

    OutputDebugStringA("Data has been written to binary_data.bin.");

    return;
}

void readScore()
{
    OutputDebugStringA("inside read score func\n");
    // Open the binary file for input
    std::ifstream inFile("binary_data.bin", std::ios::binary);

    if (!inFile) {
       // std::cerr << "Failed to open the file for reading." << std::endl;
        OutputDebugStringA("Failed to open the file for reading.\n");
        return;
    }
    OutputDebugStringA("inside read score func 3 \n");
    // Data variables to store the read values

    SCORE readData[3];
    // Read binary data from the file

    std::string test = "";
        inFile.read(reinterpret_cast<char*>(&test), sizeof(test));
    
   
    // Check if the read was successful
    if (!inFile) {
        //std::cerr << "Error while reading from the file." << std::endl;
        OutputDebugStringA("Error while reading from the file.\n");
        return;
    }
    OutputDebugStringA("inside read score func 2 \n");
    // Close the file
    inFile.close();

    // Use the read data
 
  //  std::string doubleAsString = std::to_string(readData[0].distanceTraveled);
    //OutputDebugStringA(doubleAsString.c_str());
    OutputDebugStringA(test.c_str());
   /* for (int i = 0; i < SCOREBOARD_PLAYER; i++)
    {
        std::string doubleAsString = std::to_string(readData[i].distanceTraveled);
        OutputDebugStringA("fuck");
    }*/
    return;
}

void readAndWrite()

{       // Writing data to a binary file
    int data_to_write[2] = { 42,44 };
    std::ofstream binary_file("data.bin", std::ios::binary);

    if (!binary_file) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    binary_file.write(reinterpret_cast<char*>(&data_to_write), sizeof(data_to_write));
    binary_file.close();

    // Reading data from the binary file
    int data_read[2];
    std::ifstream read_file("data.bin", std::ios::binary);

    if (!read_file) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return ;
    }

    read_file.read(reinterpret_cast<char*>(&data_read), sizeof(data_read));
    read_file.close();

    // Send the data read to the Debug Output
    char debugMessage[100];
    sprintf_s(debugMessage, "Data read from file: %d", data_read[1]);
    OutputDebugStringA(debugMessage);

    return;

}
