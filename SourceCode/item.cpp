#include "all.h"

int item_state = 0;
Sprite* itemspr;
ITEM item[15]; // Sử dụng mảng ITEM item[15] thay vì con trỏ ITEM* item
float scaleSpeed = 0.001f; // Tốc độ tăng/giảm scale
bool increasing[15]; // Sử dụng mảng increasing để theo dõi tốc độ tăng/giảm cho từng item

void item_init() {
    item_state = 0;

    // Khởi tạo giá trị mặc định cho mảng increasing
    for (int i = 0; i < 15; ++i) {
        increasing[i] = true;
    }
}

void item_deinit() {
    safe_delete(itemspr);
}

void item_update() {
    switch (item_state)
    {
    case 0:
        // Khởi tạo sprite và các thông số của item
        itemspr = sprite_load(L"./Data/Images/battery.png");

        ++item_state;
        break;

    case 1:
        for (int i = 0; i < 15; ++i) {
            // Khởi tạo các thông số của từng item
           float j = i;
            item[i].pos = { 300 + j * 50, 200 };
            item[i].scale = { 0.05, 0.05 };
            item[i].texPos = { 0, 0 };
            item[i].texSize = { 1024, 1024 };
            item[i].pivot = { 0.5, 0.5 };
            item[i].color = { 1, 1, 1, 1 };
        }

        ++item_state;
        break;

    case 2:
        for (int i = 0; i < 15; ++i) {
            // Cập nhật scale của từng item tương tự như trước
            if (increasing[i]) {
                item[i].scale.x += scaleSpeed;
                item[i].scale.y += scaleSpeed;
                if (item[i].scale.x >= 0.1f || item[i].scale.y >= 0.1f) {
                    increasing[i] = false;
                }
            }
            else {
                item[i].scale.x -= scaleSpeed;
                item[i].scale.y -= scaleSpeed;
                if (item[i].scale.x <= 0.05f || item[i].scale.y <= 0.05f) {
                    increasing[i] = true;
                }
            }
        }
        break;
    }
}

void item_render() {
    for (int i = 0; i < 15; ++i) {
        // Render từng item trong mảng
        sprite_render(itemspr,
            item[i].pos.x, item[i].pos.y,
            item[i].scale.x, item[i].scale.y,
            item[i].texPos.x, item[i].texPos.y,
            item[i].texSize.x, item[i].texSize.y, item[i].pivot.x, item[i].pivot.y, ToRadian(0));
    }
}
