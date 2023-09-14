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
#include <sstream>
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
Sprite* scoreSpr;
//SCORE *score[SCOREBOARD_PLAYER];
float scoreMultiplier;


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
        scoreSpr = sprite_load(L"./Data/Images/scorebar.png");
       /* for (int i = 0; i < SCOREBOARD_PLAYER; i++)
        {
            score[i] = new SCORE();
            score[i]->rank = 0;
            score[i]->distanceTraveled = 0;
            score[i]->name = "test";
       }*/
        game_state++;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        //GameLib::setBlendMode(Blender::BS_ALPHA);
        music::play(1, 1);
        

       
        music::setVolume(1, 0.13f);
       mapPosX = 0;
       map2PosX = 1280;
      moveFirstMap = true;
      moveSecondMap = false;
      mapMoveSpeed = MIN_MAP_MOVE_SPEED;
      totalDistanceTravelled = 0;
      scoreMultiplier = 1;
   
     
    
        game_state++;
        /*fallthrough*/
        
    case 2:
        
        //////// 通常時 ////////

       
        mapLoopLogic();
        item_update();
        player_update();
        meteor_update(); 
       
        for (int i = 0; i < METEOR_MAX; i++)
        {
            if (meteor[i])
            {
                spaceShip->collisionDetector(spaceShip, meteor[i]);
            }
        }
        
        (score);
        readScore(score);
        spaceShip->playerScore.distanceTraveled = totalDistanceTravelled;
      //  spaceShip->endGameResult(score, spaceShip);
        mapSpeedUpLogic();
        for (int i = 0; i < MAX_ITEM; i++)
        {
            if (item[i]) 
            {
                spaceShip->collisionDetector(spaceShip, item[i]);
            }
        }
       // debug::setString("total distance travelled %d", spaceShip->playerScore.distanceTraveled);
      //  debug::setString("score multiplier %f", scoreMultiplier);
       
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
    //
  
   
    if (moveFirstMap)
        {
        sprite_render(sprBack, mapPosX, 0,
          MAP_SCALE, MAP_SCALE); //scale
        }
      
        if (moveSecondMap)
        {
            //debug::setString("second screen");
            sprite_render(sprBack, map2PosX , 0,
                MAP_SCALE, MAP_SCALE); //scale
        }
       
    sprite_render(scoreSpr, 535, -50,2,2);
    text_out(1, std::to_string(totalDistanceTravelled), 640, 0, 1, 1);
    item_render();
    player_render();
    meteor_render(); 
    text_out(1, "WASD to move", 0, 0);
    text_out(1, "K to shoot", 0, 20);


}

void game_reset()
{
    music::stop(1);
    nextScene = SCENE_GAMEOVER;
   //// game_deinit();
    game_state = 0;
    meteor_state = 0;
    player_state = 0;
    item_state = 0;

  
}

void mapLoopLogic()
{
    totalDistanceTravelled += mapMoveSpeed*scoreMultiplier;
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



string readAndWriteString(SCORE* score[])
{
    // Strings to write to the binary file (5 rows and 3 columns)
    std::string data_to_write[5][3] = {
        { "1", "moh", "50" },
        { "2", "alice", "75" },
        { "3", "bob", "60" },
        { "4", "carol", "90" },
        { "5", "dave", "70" }
    };

    // Writing the strings to a binary file
    std::ofstream binary_file("string_data.bin", std::ios::binary);
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 3; col++) {
            int str_len = data_to_write[row][col].size();
            binary_file.write(reinterpret_cast<char*>(&str_len), sizeof(int)); // Write string length
            binary_file.write(data_to_write[row][col].c_str(), str_len); // Write the string
        }
    }
    binary_file.close();

    // Reading the strings from the binary file into a two-dimensional array
    std::ifstream read_file("string_data.bin", std::ios::binary);
    std::string read_strings[5][3];

    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 3; col++) {
            int str_len;
            read_file.read(reinterpret_cast<char*>(&str_len), sizeof(int)); // Read string length
            char* buffer = new char[str_len + 1];
            read_file.read(buffer, str_len); // Read the string
            buffer[str_len] = '\0'; // Null-terminate the string
            read_strings[row][col] = buffer;
            delete[] buffer;
        }
    }
    read_file.close();
    
    // Send the read strings to the Debug Output
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 3; col++) {
          //  std::string test = read_strings[row][col];
            if (col == 1)
            {

                score[0]->name = read_strings[row][col].c_str();
                score[0]->distanceTraveled =10;
               // debug::setString("name output is %s", score[row]->name.c_str());
              //  debug::setString("output is %s", read_strings[row][col].c_str());
            }
           /* else if (col == 2)
            {
                score[row]->name = read_strings[row][col].c_str();
            }
            else if (col == 3)
            {
                score[row]->distanceTraveled = std::stoi(read_strings[row][col].c_str());
            }*/
           // debug::setString("output is %s", read_strings[row][col].c_str());
            
        }
    }
 
    return "test";
}

void writeScore(SCORE* score[])
{
    OutputDebugStringA("writting score \n");
    string str[3];
    int integer[3];
    int integer2[3];
    for (int i = 0; i < 3; i++)
    {
       

        {
            str[i] = { "player"+i};
            integer[i] = { score[i]->rank };
            integer2[i] = { score[i]->distanceTraveled };
        }
     
    
    }
    //string str[3] = { "mohfuk 123","wei","hang" };
    //int integer[3] = { 1,2,3 }; //rank
    //int integer2[3] = { 110,100,120 }; //distance
    // Write data to a binary file
    std::ofstream binaryFileOut("data.bin", std::ios::binary);

    if (!binaryFileOut) {
        OutputDebugStringA("Error opening the binary file for writing.\n");
        return;
    }

    // Write the strings to the binary file
    for (int i = 0; i < 3; ++i) {
        const std::string& currentStr = str[i];
        size_t strLength = currentStr.size();
        binaryFileOut.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
        binaryFileOut.write(currentStr.c_str(), strLength);
    }

    // Write the integers to the binary file
    //this is for rank
    binaryFileOut.write(reinterpret_cast<const char*>(integer), 3 * sizeof(int));
    //write 2nd integer to binary file
    //this is for distance
    binaryFileOut.write(reinterpret_cast<const char*>(integer2), 3 * sizeof(int));

    binaryFileOut.close();

}

void readScore(SCORE* score[])
{
    // Read data from the same binary file
    std::ifstream binaryFileIn("data.bin", std::ios::binary);

    if (!binaryFileIn) {
        OutputDebugStringA("Error opening the binary file for reading.\n");
        return;
    }

    // Read the strings from the binary file
    std::string readStr[3];
    for (int i = 0; i < 3; ++i) {
        size_t strLength;
        binaryFileIn.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
        readStr[i].resize(strLength);
        binaryFileIn.read(&readStr[i][0], strLength);
    }

    // Read the integers from the binary file
    int readInt[3];
    binaryFileIn.read(reinterpret_cast<char*>(readInt), 3 * sizeof(int));
    int readInt2[3];
    binaryFileIn.read(reinterpret_cast<char*>(readInt2), 3 * sizeof(int));
    binaryFileIn.close();

    // Display the read data
    //store the value into score
   // OutputDebugStringA("Read Strings:\n");
    for (int i = 0; i < 3; ++i) {
        score[i]->name = readStr[i];
        //  OutputDebugStringA((score[i]->name+ "\n").c_str());

    }

    // OutputDebugStringA("Read Integers:\n");
    for (int i = 0; i < 3; ++i) {
        score[i]->rank = readInt[i];
        std::string message = std::to_string(score[i]->rank);
        const char* charMessage = message.c_str();
        // OutputDebugStringA((charMessage));

        score[i]->distanceTraveled = readInt2[i];
        // OutputDebugStringA((std::to_string(readInt2[i]) + "\n").c_str());
    }
   sortScore(score);
}

void sortScore(SCORE* score[])
{
    std::sort(score, score + SCOREBOARD_PLAYER,
        [](const SCORE* a, const SCORE* b) { return a->distanceTraveled > b->distanceTraveled; });
   // std::sort(score, score + SCOREBOARD_PLAYER, compareByScoreDescending);
}




void mapSpeedUpLogic()
{
    if (spaceShip->turboMode)
    {
        mapMoveSpeed = MAX_MAP_MOVE_SPEED;
        scoreMultiplier = TURBO_SCORE_MUL;
    }
    else
    {
        mapMoveSpeed = MIN_MAP_MOVE_SPEED;
        scoreMultiplier = DEFAULT_SCORE_MUL;
    }
}
