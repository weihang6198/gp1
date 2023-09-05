#ifndef METEOR_H
#define METEOR_H

void meteor_init();
void meteor_deinit();
void meteor_update();
void meteor_render();

void meteor_move();
float meteor_random_spawning(int lower_bound, int upper_bound);
void meteor_rotation();

#endif //METEOR_H