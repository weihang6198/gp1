
#ifndef ITEM_H
#define ITEM_H

#define MAX_ITEM 100
#define MIN_ITEM_SPEED 5
#define TURBO_ITEM_SPEED 10
void item_init();
void item_deinit();
void item_update();
void item_render();

extern ITEM *item[MAX_ITEM];
extern int item_state;

#endif 