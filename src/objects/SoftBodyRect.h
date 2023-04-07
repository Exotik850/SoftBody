#pragma once
#include "Ball.h"
#include "Mass.h"

class SoftBodyRect
{
    int num_points_w, num_points_h;
    float width, height;
    float k, kd;
    vector<Mass> points;
    vector<Spring> springs;
    ofMesh mesh;
    
public:
    SoftBodyRect();
    SoftBodyRect(float k, float kd, float width, float height, int num_points_w, int num_points_h);
    void update(float dt);
    void draw();
    void cut(ofVec2f a, ofVec2f b);
};
