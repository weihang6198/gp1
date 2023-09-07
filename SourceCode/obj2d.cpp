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
   collided = false;
   //testing
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
    maxSpeed = { 30,30 };
    inGameSize = { (texSize.x * scale.x) ,(texSize.y * scale.y) };
    collisionCoord = { pos.x,pos.x + inGameSize.x,
    pos.y,pos.y + inGameSize.y };
    canFire = false;
    setInitLoc = false;
    objType = PROJECTILE;
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
        debug::setString("collided the left side ");
        processCollision(obj1, obj2);
    }

    /* type of collision expecting from this
    * 1)player clash behind the enemy
    * 2)player use the consumable
    */
    else if (obj2->collisionCoord.right > obj1->collisionCoord.left && obj2->collisionCoord.right < obj1->collisionCoord.right
        && obj2->collisionCoord.top <obj1->collisionCoord.bottom && obj2->collisionCoord.bottom >obj1->collisionCoord.top)

    {
        debug::setString("collided the right side ");
    }
    else
    {
        debug::setString("did not collided");
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
            OutputDebugStringA("this is player with enemy collision\n");
            obj1->collided = true;
           // obj2->collided = true;
        }
      
    }

   
    if (obj1->objType == PROJECTILE && obj2->objType == ENEMY)
    {
        //beam collide with enemy
        //enemy will be destroyed
        if (!obj1->collided )
        {
            OutputDebugStringA("this is projectile with enemy collision\n");
            obj1->collided = true;
           // obj2->collided = true;
        }
      
    }


    if (obj1->objType == PLAYER && obj2->objType == CONSUMABLE)
    {
        if (!obj1->collided && !obj2->collided)
        {
            OutputDebugStringA("this is consumable with player \n");
            obj1->collided = true;
            obj2->collided = true;
        }
    }
}

void ITEM::itemInit()
{
}
