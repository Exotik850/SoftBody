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
    ofVec2f force;

    Spring(Mass* a, Mass* b, float k, float d, float l)
        : a(a), b(b), k(k), damp(d), length(l) { force = ofVec2f(0, 0); }

    ~Spring();
    void update(float dt);
    void draw() const;
};