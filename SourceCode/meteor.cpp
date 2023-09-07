#include "all.h"
#include <random>
#define METEOR_MAX (1)
int meteor_state;

Sprite* meteorSpr; 
METEOR meteor[METEOR_MAX];
struct METEOR meteor_obj;

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
        meteor.color = { 1,1,1,1 };
        meteor.objType = ITEM::ENEMY;
        meteor_state++; 
        
        //wei hang's work
        //fixed the posX issue,no longer need to pos x-150
        //added collision coord 
        //added collision update
        meteor.collisionCoord = { meteor.pos.x ,(meteor.pos.x) + meteor.texSize.x * 3 / 10,
                                    meteor.pos.y,meteor.pos.y+ meteor.texSize.y * 3/10 };
        /*fallthrough*/

    case 2:
        for (int i = 0; i < METEOR_MAX; i++) {
            debug::setString("meteor position x: %f, y: %f", meteor[i].pos.x, meteor[i].pos.y);
            meteor_move();
            meteor[i].updateCollisionCoord(&meteor[i].collisionCoord, meteor[i].pos.x, (meteor[i].pos.x) + meteor[i].texSize.x * 3 / 10,
                meteor[i].pos.y, meteor[i].pos.y + meteor[i].texSize.y * 3 / 10);
        }
       

    }
}


void meteor_render() {
    for (int i = 0; i < METEOR_MAX; i++) {
        sprite_render(meteor[i].spr,
            meteor[i].pos.x, meteor[i].pos.y, //pos
            meteor[i].scale.x, meteor[i].scale.y, //scale
            meteor[i].texPos.x, meteor[i].texPos.y, //texture pos
            meteor[i].texSize.x, meteor[i].texSize.y,//texture width and height
            meteor[i].pivot.x, meteor[i].pivot.y, 0);
        meteor[i].drawCollision(meteor[i].pos.x, meteor[i].pos.y, meteor[i].texSize.x * 0.3, meteor[i].texSize.y * 0.3);
    }
    
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