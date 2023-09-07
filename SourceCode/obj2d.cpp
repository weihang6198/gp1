#include "all.h"

void SPACE_SHIP::spaceShipInit()
{
    
   pos = { 100,100 };
   scale = { 0.5,0.5 };
   texPos = { 0,0 };
   texSize = { 173,231 }; //spaceship size is 173x231
   pivot = { 0,0 };
   color = { 1,1,1,1 };
   speed = { 0 ,0 };
   maxSpeed = { 9,9 };
   inGameSize = { (texSize.x *scale.x) ,(texSize.y *scale.y) };
   fuel = 100;
   collisionCoord = {pos.x,pos.x +inGameSize.x,
       pos.y,pos.y +inGameSize.y };
   turboMode = false;
   //testing
}

void BEAM::beamInit()
{
    pos = { 100,100}; 
    scale = { 0.5,0.5 };
    texPos = { 0,0 };
    texSize = { 300,100 }; //spaceship size is 173x231
    pivot = { 0,0 };
    color = { 1,1,1,1 };
    speed = { 0 ,0 };
    maxSpeed = { 30,30 };
    inGameSize = { (texSize.x * scale.x) ,(texSize.y * scale.y) };
    collisionCoord = { pos.x,pos.x + inGameSize.x,
        pos.y,pos.y + inGameSize.y };
   
}
OBJ2D* searchSet0(OBJ2D arr[], int dataNum, int moveAlg, VECTOR2 pos)
{
#if 12

#endif


    /*for (int i = 0; i < dataNum; i++) {
        if (arr[i].moveAlg != -1) {
            continue;
        }
        arr[i] = {};
        arr[i].moveAlg = moveAlg;
        arr[i].pos = pos;
        return &arr[i];
    }*/


    return NULL;                        // ¶¬‚Å‚«‚È‚©‚Á‚½
}

