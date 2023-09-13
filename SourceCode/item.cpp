#include "all.h"


Sprite* itemspr[3];
int item_state = 0;
float scaleSpeed = 0.005f; // Tốc độ tăng/giảm scale
bool increasing[15]; // Sử dụng mảng increasing để theo dõi tốc độ tăng/giảm cho từng item

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
        safe_delete(item[i]);
    }
}

void item_update() {
    switch (item_state)
    {
    case 0:
        // Khởi tạo sprite và các thông số của item
       
            
            itemspr[0] = sprite_load(L"./Data/Images/battery.png");
            itemspr[1] = sprite_load(L"./Data/Images/repair_kit.png");
            //itemspr[2] = sprite_load(L"./Data/Images/fuel.png");

            for (int i = 0; i < 3; i++) {
                float j = i;
                item[i] = new ITEM();
                if (i < 1)
                {
                    item[i]->itemInit(300, 100 + i * 100, ITEM::battery, itemspr[0]);
                }
                else if (i < 2)
                {
                    item[i]->itemInit(300, 100 + i * 100, ITEM::repair_kit, itemspr[1]);
                }
                else if (i < 3)
                {
                    item[i]->itemInit(300, 100 + i * 100, ITEM::repair_kit, itemspr[1]);
                }

            }
        ++item_state;
        break;

    case 1:
     
      
        ++item_state;
        break;

    case 2:
        for (int i = 0; i < MAX_ITEM; i++) {
            if (item[i])
            {
                if (item[i]->destroySelf)
                {
                    safe_delete(item[i]);

                }
                else
                {
                    debug::setString("item enum %d",item[i]->itemType);
                    item[i]->updateCollisionCoord(&item[i]->collisionCoord, item[i]->pos.x, item[i]->pos.x + item[i]->inGameSize.x,
                        item[i]->pos.y, item[i]->pos.y + item[i]->inGameSize.y);
                }
               
            }
           
        }

        break;
    }
}

void item_render()
{
    for (int i = 0; i < MAX_ITEM; i++)
    {
        if (item[i])
        {
            sprite_render(item[i]->sprImg,
                item[i]->pos.x, item[i]->pos.y,
                item[i]->scale.x, item[i]->scale.y,
                item[i]->texPos.x, item[i]->texPos.y,
                item[i]->texSize.x, item[i]->texSize.y, item[i]->pivot.x, item[i]->pivot.y, ToRadian(0));

            item[0]->drawCollision(item[i]->collisionCoord.left, item[i]->collisionCoord.top, item[i]->inGameSize.x, item[i]->inGameSize.y);

        }
    }
   
}