#include "all.h"

int item_state = 0;
Sprite* itemspr;
ITEM item;
float scaleSpeed = 0.001f; // Tốc độ tăng/giảm scale
bool increasing = true;

void item_init() {
    item_state = 0;
}

void item_deinit() {
    safe_delete(itemspr);
}

void item_update() {
    switch (item_state)
    {
    case 0:
        itemspr = sprite_load(L"./Data/Images/battery.png");
        ++item_state;
        break;

    case 1:
        item.pos = { 300, 200 };
        item.scale = { 0.05, 0.05 };
        item.texPos = { 0, 0 };
        item.texSize = { 1024, 1024 };
        item.pivot = { 0.5, 0.5 };
        item.color = { 1, 1, 1, 1 };
        
        ++item_state;
        break;

    case 2:
        if (increasing) {
            item.scale.x += scaleSpeed;
            item.scale.y += scaleSpeed;
            if (item.scale.x >= 0.1f || item.scale.y >= 0.1f) {
                increasing = false;
            }
        }
        else {
            item.scale.x -= scaleSpeed;
            item.scale.y -= scaleSpeed;
            if (item.scale.x <= 0.05f || item.scale.y <= 0.05f) {
                increasing = true;
            }
        }
        break;
    }
}

void item_render() {
    sprite_render(itemspr,
        item.pos.x, item.pos.y,
        item.scale.x, item.scale.y,
        item.texPos.x, item.texPos.y,
        item.texSize.x, item.texSize.y, item.pivot.x, item.pivot.y, ToRadian(0));
}
