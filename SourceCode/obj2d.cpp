#include "all.h"

void SPACE_SHIP::spaceShipInit()
{
    
   pos = { 100,300 };
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
   
}
