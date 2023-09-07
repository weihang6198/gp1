#include "all.h"
#include "item.h"
int item_state = 0;
Sprite* itemspr[3];
ITEM item[15]; // Sử dụng mảng ITEM item[15] thay vì con trỏ ITEM* item
float scaleSpeed = 0.005f; // Tốc độ tăng/giảm scale
bool increasing[15]; // Sử dụng mảng increasing để theo dõi tốc độ tăng/giảm cho từng item

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
        ++item_state;
        break;

    case 1:
     
            // Khởi tạo các thông số của từng item
        for(int i=0;i<15;i++){
            float j = i;
            item[i].pos = { 300 + j * 50, 200 };
            item[i].scale = { 1, 1 };
            item[i].texPos = { 0, 0 };
            item[i].texSize = { 100, 100 };
            item[i].pivot = { 0.5, 0.5 };
            item[i].color = { 1, 1, 1, 1 };
            
        }
      
        ++item_state;
        break;

    case 2:
        item->updateCollisionCoord(&item->collisionCoord, item->pos.x, item->pos.x + item->inGameSize.x,
            item->pos.y, item->pos.y + item->inGameSize.y);
       
        //for (int i = 0; i < MAX_ITEM; ++i) {
        //    // Cập nhật scale của từng item tương tự như trước
        //    if (increasing[i]) {
        //        item[i].scale.x += scaleSpeed;
        //        item[i].scale.y += scaleSpeed;
        //        if (item[i].scale.x >= 1.2f || item[i].scale.y >= 1.2f) {
        //            increasing[i] = false;
        //        }
        //    }
        //    else {
        //        item[i].scale.x -= scaleSpeed;
        //        item[i].scale.y -= scaleSpeed;
        //        if (item[i].scale.x <= 0.8f || item[i].scale.y <= 0.8f) {
        //            increasing[i] = true;
        //        }
        //    }
        //}
        break;
    }
}

void item_render() {
    for (int i = 0; i < MAX_ITEM; ++i) {
        // Render từng item trong mảng
        sprite_render(itemspr[i % 3],
            item[i].pos.x, item[i].pos.y,
            item[i].scale.x, item[i].scale.y,
            item[i].texPos.x, item[i].texPos.y,
            item[i].texSize.x, item[i].texSize.y, item[i].pivot.x, item[i].pivot.y, ToRadian(0));
        item[i].drawCollision(item[i].pos.x, item[i].pos.y, item[i].texSize.x, item[i].texSize.y);
    }

   
}
