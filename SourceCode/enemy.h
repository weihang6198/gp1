#ifndef METEOR_H
#define METEOR_H

#define METEOR_MAX 100
#define MAX_METEOR_SPEED 25
#define MIN_METEOR_SPEED 10
void meteor_init();
void meteor_deinit();
void meteor_update();
void meteor_render();

void meteor_move();
float random_spawning(int lower_bound, int upper_bound);
void meteor_rotation();

extern METEOR* meteor[METEOR_MAX];
extern int meteor_state;
#endif //METEOR_H