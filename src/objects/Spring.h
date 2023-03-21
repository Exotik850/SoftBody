#pragma once
#include "Mass.h"
#include "ofMain.h"

class Spring
{
public:
    Mass* a;
    Mass* b;
    float k;
    float damp;
    float length;

    Spring(Mass* a, Mass* b, float k, float d, float l)
        : a(a), b(b), k(k), damp(d), length(l) {}
    void update(float dt) const;
    void draw() const;
};