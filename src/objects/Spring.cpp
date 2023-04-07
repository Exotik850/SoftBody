#include "Spring.h"

#define MAX_FORCE 100
#define MIN_FORCE 0.25f
#define EPSILON 0.001f

Spring::~Spring(){}

void Spring::update(float dt)
{
    ofVec2f dir = b->pos - a->pos;
    const float x = dir.length() - length;

    // Check for non-zero length before normalizing
    if (fabsf(x) <= EPSILON) return;
    dir.normalize();

    // Fs = -k * (x - x0)
    const float spring_force = k * x;

    // Fd = kd * Relative Velocity 
    const float damping_force = damp * (b->vel() - a->vel()).dot(dir);

    // Apply spring and damping forces
    ofVec2f total_force = (spring_force + damping_force) * dir * 0.5f;
    const float len = total_force.length();
    if (len > MAX_FORCE)
        total_force = total_force.getLimited(MAX_FORCE);

    if (len > MIN_FORCE)
    {
        a->acc += total_force;
        b->acc -= total_force;
    }

    force = total_force;
}

void Spring::draw() const
{
    ofDrawLine(a->pos, b->pos);
}