#include "all.h"

int item_state = 0;
Sprite* itemspr[3];

float scaleSpeed = 0.005f; // Tốc độ tăng/giảm scale
bool increasing[15]; // Sử dụng mảng increasing để theo dõi tốc độ tăng/giảm cho từng item
int x;
ITEM* item[MAX_ITEM];
void item_init() {
    item_state = 0;

    // Khởi tạo giá trị mặc định cho mảng increasing
    for (int i = 0; i < MAX_ITEM; ++i) {
        increasing[i] = true;
    }
}

void item_deinit() {
    for (int i = 0; i < MAX_ITEM; i++) {
        safe_delete(itemspr[i]);
    }
}

void item_update() {
    switch (item_state)
    {
    case 0:
        // Khởi tạo sprite và các thông số của item
       
            
            itemspr[0] = sprite_load(L"./Data/Images/battery.png");
            itemspr[1] = sprite_load(L"./Data/Images/repair_kit.png");
            itemspr[2] = sprite_load(L"./Data/Images/fuel.png");

            for (int i = 0; i < MAX_ITEM; i++) {
                float j = i;
                item[i] = new ITEM();
                item[i]->itemInit(300, 100 + i * 100, ITEM::battery, itemspr[0]);

            }
        ++item_state;
        break;

    case 1:
     
      
        ++item_state;
        break;

    case 2:
        for (int i = 0; i < MAX_ITEM; i++) {
            item[i]->updateCollisionCoord(&item[i]->collisionCoord, item[i]->pos.x, item[i]->pos.x + item[i]->inGameSize.x,
                item[i]->pos.y, item[i]->pos.y + item[i]->inGameSize.y);
        }
        if (item[0]->sprImg)
        {
            debug::setString("the img exist");
        }
       
    
        break;
    }
}

void item_render()
{
    sprite_render(item[0]->sprImg,
        item[0]->pos.x, item[0]->pos.y,
        item[0]->scale.x, item[0]->scale.y,
        item[0]->texPos.x, item[0]->texPos.y,
        item[0]->texSize.x, item[0]->texSize.y, item[0]->pivot.x, item[0]->pivot.y, ToRadian(0)); 

    item[0]->drawCollision(item[0]->collisionCoord.left, item[0]->collisionCoord.top, item[0]->inGameSize.x, item[0]->inGameSize.y);
}