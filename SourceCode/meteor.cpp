#include "all.h"

int meteor_state;

Sprite* meteorSpr; 
METEOR meteor;


void meteor_init() {
    meteor_state = 0; 
}


void meteor_deinit() {
    safe_delete(meteorSpr);
}


void meteor_update() {
    switch (meteor_state) {
    case 0: 
        meteorSpr = sprite_load(L"./Data/Images/meteor.png");
        meteor_state++; 
        /*fallthrough*/
    case 1:
        meteor.timer = 0; 
        meteor.pos = { 1000, 100 };
        meteor.scale = { 0.3f, 0.3f };
        meteor.texPos = { 0,0 };
        meteor.texSize = { 500, 500 };
        meteor.pivot = { 0,0 };
        meteor.color = { 1,1,1,1 };

        meteor_state++; 
        debug::setString("meteor position x: %f, y: %f", meteor.pos.x, meteor.pos.y);
        /*fallthrough*/

    case 2:
        meteor_move(); 
    }
}


void meteor_render() {
    sprite_render(meteorSpr,
        meteor.pos.x, meteor.pos.y, //pos
        meteor.scale.x, meteor.scale.y, //scale
        meteor.texPos.x, meteor.texPos.y, //texture pos
        meteor.texSize.x, meteor.texSize.y,//texture width and height
        meteor.pivot.x, meteor.pivot.y, ToRadian(90));
    meteor.drawCollision(meteor.pos.x, meteor.pos.y, meteor.texSize.x*0.3, meteor.texSize.y*0.3);
}

void meteor_move() {
    meteor.pos.x -= 2.0f; 
}