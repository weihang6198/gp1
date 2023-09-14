#include "all.h"
#include <random>



Sprite* meteorSpr; 
METEOR *meteor[METEOR_MAX];
int meteor_state = 0;


//struct  METEOR_DATA meteor_data[3] ={  NULL, L"./Data/Images/meteor1.png", {0, 0}, {500, 500}, {128, 128}, 20,
//                                  NULL, L"./Data/Images/meteor2.png", {0, 0}, {500, 500}, {128, 128} ,20,
//                                  NULL, L"./Data/Images/meteor3.png", {0, 0}, {500, 500}, {128, 128}, 20
//};



void meteor_init() {
    meteor_state = 0; 
}


void meteor_deinit() {
    //int dataNum;
    //dataNum = sizeof(meteor_data) / sizeof(METEOR_DATA);
    ////dataNum = ARRAYSIZE(enemyData); 
    //for (int i = 0; i < dataNum; i++) {
    //    safe_delete(meteor_data[i].spr);
    //}
}


void meteor_update() {
    switch (meteor_state) {
    case 0: 
      
      
      
        meteorSpr = sprite_load(L"./Data/Images/meteor1.png");
        meteor_state++; 
        /*fallthrough*/
    case 1:
        
        for (int i = 0; i < METEOR_MAX; i++)
        {
            meteor[i] = new METEOR();
            meteor[i]->meteorInit(random_spawning(700+i*400,900+i*400),random_spawning(0, 500));
      }
     
        /*fallthrough*/
        meteor_state++;
    case 2:
       // debug::setString("meteor position x: %f, y: %f", meteor.pos.x, meteor.pos.y);
        //meteor_move(); 
        meteor_move();
        for (int i = 0; i < METEOR_MAX; i++)
        {
            if (meteor[i])
            {
              //  debug::setString("meteor exissitng");
                if (meteor[i]->pos.x < -1000)
                {
                    safe_delete(meteor[i]);
                }
                if (meteor[i])
                {
                    meteor[i]->updateCollisionCoord(&meteor[i]->collisionCoord, meteor[i]->pos.x, (meteor[i]->pos.x) + meteor[i]->texSize.x * 3 / 10,
                        meteor[i]->pos.y, meteor[i]->pos.y + meteor[i]->texSize.y * 3 / 10);
                    if (meteor[i]->destroySelf)
                    {
                        safe_delete(meteor[i]);
                    }
                }
             
               
            }
        }
     

    }
}


void meteor_render() {
    for (int i = 0; i < METEOR_MAX; i++)
    {
        if (meteor[i])
        {
            sprite_render(meteorSpr,
                meteor[i]->pos.x, meteor[i]->pos.y, //pos
                meteor[i]->scale.x, meteor[i]->scale.y, //scale
                meteor[i]->texPos.x, meteor[i]->texPos.y, //texture pos
                meteor[i]->texSize.x, meteor[i]->texSize.y,//texture width and height
                meteor[i]->pivot.x, meteor[i]->pivot.y, 0);
          //  meteor[i]->drawCollision(meteor[i]->pos.x, meteor[i]->pos.y, meteor[i]->texSize.x * 0.3, meteor[i]->texSize.y * 0.3);
        }
        
    }
   
}

void meteor_move() {
   // meteor.pos.x -= 1.0f; 
    for (int i = 0; i < METEOR_MAX; i++)
    {
        if (meteor[i])
        {
            if (spaceShip->turboMode)
            {
                meteor[i]->pos.x -= MAX_METEOR_SPEED;
            }
            else
            {
                meteor[i]->pos.x -= MIN_METEOR_SPEED;
            }
            
        }
    }
}

float random_spawning(int lower_bound, int upper_bound) {
    std::random_device rd;
    std::mt19937 gen(rd());
    // Create a distribution that maps the random numbers within the specified range
    std::uniform_int_distribution<> distribution(lower_bound, upper_bound);
    // Generate random numbers and print them

    int randomNumber = distribution(gen);
    return randomNumber;
}