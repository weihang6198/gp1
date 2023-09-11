
#ifndef ITEM_H
#define ITEM_H

#define MAX_ITEM 3
void item_init();
void item_deinit();
void item_update();
void item_render();

extern ITEM *item[MAX_ITEM];


#endif 