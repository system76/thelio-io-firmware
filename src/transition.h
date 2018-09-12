#ifndef TRANSITION_H
#define TRANSITION_H

#include <stdint.h>

struct Transition {
    double speed;
    uint64_t time;
    double start;
    double target;
    double value;
};

struct Transition transition_new(double speed);

void transition_set(struct Transition * transition, uint64_t time, double target);
double transition_step(struct Transition * transition, uint64_t time);

#endif // TRANSITION_H
