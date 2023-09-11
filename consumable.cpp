//#include "SourceCode/all.h"
//
//int consumable_state = 0;
//Sprite* itemSpr[3];
//ITEM* item[MAX_CONSUMABLE];
//
//void consumable_init()
//{
//	int consumable_state = 0;
//
//}
//
//void consumable_deinit()
//{
//	for (int i = 0; i < MAX_CONSUMABLE; i++)
//	{
//		
//		safe_delete(item[i]);
//	}
//}
//
//void consumable_update()
//{
//    switch (consumable_state)
//    {
//    case 0:
//        // Khởi tạo sprite và các thông số của item
//
//
//        itemSpr[0] = sprite_load(L"./Data/Images/battery.png");
//        itemSpr[1] = sprite_load(L"./Data/Images/repair_kit.png");
//        itemSpr[2] = sprite_load(L"./Data/Images/fuel.png");
//        // Khởi tạo các thông số của từng item
//        for (int i = 0; i < MAX_CONSUMABLE; i++) {
//            float j = i;
//            item[i] = new ITEM();
//            item[i]->itemInit(300, 100 + i * 100, ITEM::battery, itemSpr[0]);
//
//        }
//        ++consumable_state;
//        break;
//
//    case 1:
//
//     
//       
//        ++consumable_state;
//        break;
//
//    case 2:
//        for (int i = 0; i < MAX_CONSUMABLE; i++) {
//            item[i]->updateCollisionCoord(&item[i]->collisionCoord, item[i]->pos.x, item[i]->pos.x + item[i]->inGameSize.x,
//                item[i]->pos.y, item[i]->pos.y + item[i]->inGameSize.y);
//        }
//        if (item[0]->sprImg)
//        {
//            debug::setString("the img exist");
//        }
//
//
//        break;
//    }
//}
//
//void consumable_render()
//{
//    if (item[0]->sprImg)
//    {
//        debug::setString("the img exist");
//    }
//
//    sprite_render(item[0]->sprImg,
//                item[0]->pos.x, item[0]->pos.y,
//                item[0]->scale.x, item[0]->scale.y,
//                item[0]->texPos.x, item[0]->texPos.y,
//                item[0]->texSize.x, item[0]->texSize.y, item[0]->pivot.x, item[0]->pivot.y, ToRadian(0)); 
//  
//}
