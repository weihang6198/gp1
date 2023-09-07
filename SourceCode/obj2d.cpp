#include "all.h"

void SPACE_SHIP::spaceShipInit()
{
    
   pos = { 100,300 };
   scale = { 0.3,0.3 };
   texPos = { 0,0 };
   texSize = { 173,231 }; //spaceship size is 173x231
   pivot = { 0,0 };
   color = { 1,1,1,1 };
   speed = { 0 ,0 };
   maxSpeed = { 15,15 };
   inGameSize = { (texSize.x *scale.x) ,(texSize.y *scale.y) };
   fuel = 100;
   collisionCoord = {pos.x,pos.x +inGameSize.x,
       pos.y,pos.y +inGameSize.y };
   turboMode = false;
   beamCount = 0;
   objType = PLAYER;
   //testing
}

void BEAM::beamInit()
{
    pos = { 100,300};
    scale = { 0.35,0.2 };
    texPos = { 0,0 };
    texSize = { 300,100 }; //spaceship size is 173x231
    pivot = { 0,0 };
    color = { 1,1,1,1 };
    speed = { 0 ,0 };
    maxSpeed = { 30,30 };
    inGameSize = { (texSize.x * scale.x) ,(texSize.y * scale.y) };
    collisionCoord = { pos.x,pos.x + inGameSize.x,
    pos.y,pos.y + inGameSize.y };
    canFire = false;
    setInitLoc = false;
    objType = PROJECTILE;
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
void OBJ2D::processCollision(OBJ2D obj1,OBJ2D obj2 )
{
    //player collide with enemy
    //player will lose a life
    if (obj1.objType == PLAYER && obj2.objType == ENEMY) 
    {
        
    }

    //beam collide with enemy
    //enemy will be destroyed
    if (obj1.objType == PROJECTILE && obj2.objType == ENEMY)
    {

    }
   
    if (obj1.objType == PLAYER && obj2.objType == CONSUMABLE)
    {

    }
}
