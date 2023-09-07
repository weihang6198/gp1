#include "all.h"
#include <random>

int meteor_state;

Sprite* meteorSpr; 
METEOR meteor;

struct METEOR_DATA  //heinŒN ’S“–
{
    Sprite* spr;
    const wchar_t* filePath;
    VECTOR2 texpos;
    VECTOR2 texSize;
    VECTOR2 pivot;
    float radius;
};

struct  METEOR_DATA meteor_data[3] ={  NULL, L"./Data/Images/meteor1.png", {0, 0}, {500, 500}, {128, 128}, 20,
                                  NULL, L"./Data/Images/meteor2.png", {0, 0}, {500, 500}, {128, 128} ,20,
                                  NULL, L"./Data/Images/meteor3.png", {0, 0}, {500, 500}, {128, 128}, 20
};

struct METEOR_SET {
    int meteor_type; 
    VECTOR2 pos; 
};

struct METEOR_SET meteor_set[] = {  0, {800, meteor_random_spawning(0, 400)},
                                    0, {800, meteor_random_spawning(0, 400)},
                                    0, {800, meteor_random_spawning(0, 400)},
                                    0, {800, meteor_random_spawning(0, 400)},
                                    0, {800, meteor_random_spawning(0, 400)},
                                    0, {800, meteor_random_spawning(0, 400)},
                                    0, {800, meteor_random_spawning(0, 400)},
                                    0, {800, meteor_random_spawning(0, 400)},
                                    1, {800, meteor_random_spawning(0, 400)},
                                    1, {800, meteor_random_spawning(0, 400)},
                                    1, {800, meteor_random_spawning(0, 400)},
                                    1, {800, meteor_random_spawning(0, 400)},
                                    1, {800, meteor_random_spawning(0, 400)},
                                    2, {800, meteor_random_spawning(0, 400)},
                                    2, {800, meteor_random_spawning(0, 400)},
                                    -1, {-1, -1}
};

void meteor_init() {
    meteor_state = 0; 
}


void meteor_deinit() {
    int dataNum;
    dataNum = sizeof(meteor_data) / sizeof(METEOR_DATA);
    //dataNum = ARRAYSIZE(enemyData); 
    for (int i = 0; i < dataNum; i++) {
        safe_delete(meteor_data[i].spr);
    }
}


void meteor_update() {
    switch (meteor_state) {
    case 0: 
        int dataNum;
        dataNum = sizeof(meteor_data) / sizeof(METEOR_DATA);
        //dataNum = ARRAYSIZE(enemyData); 
        for (int i = 0; i < dataNum; i++) {
            meteor_data[i].spr = sprite_load(meteor_data[i].filePath);
        }
        meteor_state++; 
        /*fallthrough*/
    case 1:
        /*meteor.timer = 0; 
        meteor.pos = { 800, meteor_random_spawning(0, 400)};
        meteor.scale = { 0.3f, 0.3f };
        meteor.texPos = { 0,0 };
        meteor.texSize = { 500, 500 };
        meteor.pivot = { 0,0 };
        meteor.color = { 1,1,1,1 };*/

        meteor_state++; 
        
        //wei hang's work
        //fixed the posX issue,no longer need to pos x-150
        //added collision coord 
        //added collision update
        meteor.collisionCoord = { meteor.pos.x ,(meteor.pos.x) + meteor.texSize.x * 3 / 10,
                                    meteor.pos.y,meteor.pos.y+ meteor.texSize.y * 3/10 };
        /*fallthrough*/

    case 2:
        debug::setString("meteor position x: %f, y: %f", meteor.pos.x, meteor.pos.y);
        meteor_move(); 
        meteor.updateCollisionCoord(&meteor.collisionCoord, meteor.pos.x, (meteor.pos.x) + meteor.texSize.x * 3 / 10,
            meteor.pos.y, meteor.pos.y + meteor.texSize.y * 3 / 10);

    }
}


void meteor_render() {
    sprite_render(meteorSpr,
        meteor.pos.x, meteor.pos.y, //pos
        meteor.scale.x, meteor.scale.y, //scale
        meteor.texPos.x, meteor.texPos.y, //texture pos
        meteor.texSize.x, meteor.texSize.y,//texture width and height
        meteor.pivot.x, meteor.pivot.y, 0);
    meteor.drawCollision(meteor.pos.x , meteor.pos.y, meteor.texSize.x*0.3, meteor.texSize.y*0.3);
}

void meteor_move() {
   // meteor.pos.x -= 1.0f; 
}

float meteor_random_spawning(int lower_bound, int upper_bound) {
    std::random_device rd;
    std::mt19937 gen(rd());
    // Create a distribution that maps the random numbers within the specified range
    std::uniform_int_distribution<> distribution(lower_bound, upper_bound);
    // Generate random numbers and print them

    int randomNumber = distribution(gen);
    return randomNumber;
}