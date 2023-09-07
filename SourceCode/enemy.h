#ifndef METEOR_H
#define METEOR_H

#define METEOR_MAX 1
void meteor_init();
void meteor_deinit();
void meteor_update();
void meteor_render();

void meteor_move();
float meteor_random_spawning(int lower_bound, int upper_bound);
void meteor_rotation();

extern METEOR meteor;
#endif //METEOR_H