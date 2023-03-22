#pragma once
#include "Ball.h"
#include "Mass.h"

class SoftBodyRect
{
private:
    int num_points_w, num_points_h;
    float width, height;
    float k, kd;
    vector<Mass> points;
    vector<Spring> springs;
    
public:
    SoftBodyRect();
    SoftBodyRect(float k, float kd, float width, float height, int num_points_w, int num_points_h);
    void update(float dt);
    void draw();
};
