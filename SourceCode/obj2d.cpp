#include "all.h"


void SPACE_SHIP::spaceShipInit()
{
   
   pos = { 100,300 };
   scale = { 0.3,0.3};
   texPos = { 0,0 };
   texSize = { 356,136 }; //spaceship size is 356x136
   pivot = { 0,0 };
   color = { 1,1,1,1 };
   speed = { 0 ,0 };
   maxSpeed = { MIN_SPEED, MIN_SPEED };
   inGameSize = { (texSize.x *scale.x) ,(texSize.y *scale.y) };
   fuel = 100;
   collisionCoord = {pos.x,pos.x +inGameSize.x,
       pos.y,pos.y +inGameSize.y };
   turboMode =true;
   timer = 0;
   beamCount = 0;
   objType = PLAYER;
   collided = false;
   currentLife = 3;
   playerScore.distanceTraveled = 0;
   playerScore.name = "tester1";
   playerScore.rank = 0;
   batteryLife = 100;
   batteryDepleted = false;
}

void BEAM::beamInit()
{
    pos = { 100,300 };
    scale = { 0.35,0.2 };
    texPos = { 0,0 };
    texSize = { 300,100 }; //spaceship size is 173x231
    pivot = { 0,0 };
    color = { 1,1,1,1 };
    speed = { 0 ,0 };
    maxSpeed = { 22,30 };
    inGameSize = { (texSize.x * scale.x) ,(texSize.y * scale.y) };
    collisionCoord = { pos.x,pos.x + inGameSize.x,
    pos.y,pos.y + inGameSize.y };
    canFire = false;
    setInitLoc = false;
    objType = PROJECTILE;
}

void ITEM::itemInit(float posX,float posY, ITEM_TYPE itemType, Sprite* sprImg)
{
    pos = { posX , posY };
    scale = { 0.4, 0.6 };
    texPos = { 0, 0 };
    texSize = { 100, 100 };
    pivot = { 0.5, 0.5 };
    color = { 1, 1, 1, 1 };
    inGameSize = { (texSize.x * scale.x) ,(texSize.y * scale.y) };
    collisionCoord = { pos.x,pos.x + inGameSize.x,
    pos.y,pos.y + inGameSize.y };
    objType = CONSUMABLE;
    this->itemType = itemType;
    this->sprImg = sprImg;

}

void OBJ2D::drawCollision(int posX, int posY, int width, int height)
{
    {
        //to draw top line
        primitive::line(
            posX, posY, posX + width, posY, //pos
            1, 1, 1, 1, //rgba
            1); //thicness

        //to draw bottom line
        primitive::line(
            posX, posY + height, posX + width, posY + height, //pos
            1, 1, 1, 1, //rgba
            1); //thicness

        //to draw right line
        primitive::line(
            posX + width, posY, posX + width, posY + height, //pos
            1, 1, 1, 1, //rgba
            1); //thicness
        //to draw left line
        primitive::line(
            posX, posY, posX, posY + height, //pos
            1, 1, 1, 1, //rgba
            1); //thicness
    }
}

void OBJ2D::collisionDetector(OBJ2D* obj1, OBJ2D* obj2)
{
    /*type of collision expecting from this
    * 1)beam hitting the enemy
    * 2)player clash with enemy
    * 3)player use the consumable
    */
    if (obj1->collisionCoord.right > obj2->collisionCoord.left && obj1->collisionCoord.right < obj2->collisionCoord.right
        && obj1->collisionCoord.top <obj2->collisionCoord.bottom && obj1->collisionCoord.bottom >obj2->collisionCoord.top)

    {
       // debug::setString("collided the left side ");
        processCollision(obj1, obj2);
    }

    /* type of collision expecting from this
    * 1)player clash behind the enemy
    * 2)player use the consumable
    */
    else if (obj2->collisionCoord.right > obj1->collisionCoord.left && obj2->collisionCoord.right < obj1->collisionCoord.right
        && obj2->collisionCoord.top <obj1->collisionCoord.bottom && obj2->collisionCoord.bottom >obj1->collisionCoord.top)

    {
      //  debug::setString("collided the right side ");
        processCollision(obj1, obj2);
    }
    else
    {
       // debug::setString("did not collided");
    }
}

void OBJ2D::updateCollisionCoord(COLLISION_COORD* obj1, float left, float right, float top, float bottom)
{
    obj1->left = left;
    obj1->right = right;
    obj1->top = top;
    obj1->bottom = bottom;

}

//process what happen to the obj when two diff obj collided
/*
* OBJ TYPE:
* 1)SPACESHIP   =player
* 2)ALIEN       =enemy
* 3)METEOR      =enemy
* 4)ITEM        =consumable
* 5)BEAM        =projectile
*
* OBJ reaction to each other:
*1)when player and enemy collide,player will lose a life
*2)when projectile collide with enemy, enemy will be destroy
*3)when player collide with consumable, the item will be used.
*4)projectile will ignore consumable
*5)enemy will ignore consumable
*
* player <- enemy
* beam-> enemy
* enemy X consumable
* player->consumable
* beam X consumable
*
* 5 types of collision is expected from here
*/
void OBJ2D::processCollision(OBJ2D* obj1, OBJ2D* obj2)
{

    if (obj1->objType == PLAYER && obj2->objType == ENEMY)
    {
       
      //player collide with enemy
      //player will lose a life
        if (!obj1->collided)
        {
            sound::play(4, 4);
            OutputDebugStringA("this is player with enemy collision\n");
            obj1->collided = true;
           // obj1->currentLife -=1;
            obj1->currentLife -= 1;
            obj1->HPSpr[currentLife] = sprite_load(L"./Data/Images/empty_HP.png");
            obj2->destroySelf = true;
            obj1->processTimer = true;
           // healthIconSpr[1] = sprite_load();
            
            if (obj1->currentLife <= 0) //player lose the game when life reaches 0
            {
                sound::stop(4, 4);
                sound::play(4, 3);
               // writeScore(score);
                spaceShip->endGameResult(score, spaceShip);
                game_reset();
             

            }
           // obj2->collided = true;
        }
      
    }

   
    if (obj1->objType == PROJECTILE && obj2->objType == ENEMY)
    {
        sound::play(4, 0);
    
        //beam collide with enemy
        //enemy will be destroyed
        if (!obj1->collided )
        {
            OutputDebugStringA("this is projectile with enemy collision\n");
            obj1->collided = true;
            obj1->destroySelf = true;
            obj2->destroySelf = true;
            //obj2->collided = true;
            
        }
      
    }

    //PLAYER can collide with unlimited amount of CONSUMABLE
    //CONSUMABLE can only be collide once and destroy after that
    if (obj1->objType == PLAYER && obj2->objType == CONSUMABLE)
    {
        sound::play(4, 7);
        if ( !obj2->collided)
        {
            OutputDebugStringA("this is consumable with player \n");
            
            obj2->collided = true;
            //process the item and destroy after processing it
            processItem(obj2,obj1);
           
           
        }
    }
}

void OBJ2D::animation(OBJ2D* obj)
{
    //destroy obj when the animation is finished
    safe_delete(obj);
}

void OBJ2D::destroyObj(OBJ2D* obj)
{
}


void OBJ2D::processItem(OBJ2D* item,OBJ2D* player)
{
    switch (item->itemType)
    {
    case   battery:
        OutputDebugStringA("this is battery");
      
           
            player->batteryLife += 20;
            if (player->batteryLife > 100)
            {
                player->batteryLife = 100;
        }

        break;
    case repair_kit:
        OutputDebugStringA("this is repair kit");
        if (player->currentLife < MAX_LIFE)
        {
            player->currentLife++;
            player->HPSpr[currentLife - 1] = sprite_load(L"./Data/Images/filled_HP.png");
       }
     
        break;
    default: 
        OutputDebugStringA("this is def");
    }
    item->destroySelf = true;
}

void OBJ2D::endGameResult(SCORE* score[], OBJ2D* player)
{
    score[SCOREBOARD_PLAYER - 1]->name = "player-1";
    score[SCOREBOARD_PLAYER-1]->rank = player->playerScore.rank;
    score[SCOREBOARD_PLAYER-1]->distanceTraveled = player->playerScore.distanceTraveled;
   
   // debug::setString("inside end game result distance travelled %d", score[SCOREBOARD_PLAYER - 1]->distanceTraveled);
    std::sort(score, score + SCOREBOARD_PLAYER,
        [](const SCORE* a, const SCORE* b) { return a->distanceTraveled > b->distanceTraveled; });


    for (int i = 0; i < 3; i++)
    {
       // debug::setString("distance travelled %d", score[i]->distanceTraveled);
     //   debug::setString("name is %s", score[i]->name.c_str());

    }

    writeScore(score);
    /*for (int i = 0; i < SCOREBOARD_PLAYER; i++)
    {
        debug::setString("distance travelled in result %d", score[i]->distanceTraveled);
    }*/

}



void METEOR::meteorInit(float posX, float posY)
{
  timer = 0;
  pos = {posX,posY};
  scale = { 0.3f, 0.3f };
  texPos = { 0,0 };
  texSize = { 500, 500 };
  pivot = { 0,0 };
  color = { 1,1,1,1 };
  objType = OBJ_TYPE::ENEMY;
  collisionCoord = {pos.x ,(pos.x) + texSize.x * 3 / 10,
                                    pos.y,pos.y + texSize.y * 3 / 10 };
}
