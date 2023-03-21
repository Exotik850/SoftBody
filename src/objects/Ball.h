#pragma once
#include "ofMain.h"
#include "Mass.h"
#include "Spring.h"

class Ball
{
public:
    vector<Mass> points;
    vector<Spring> springs;
    float gas_amt;
    Ball();
    Ball(float k, float kd, float rest_length, float radius, int num_points);
    void update(float dt);
    void draw();
    float area() const;
	int num;
	float radius, desired_area;
    float k, kd, restLength;
};
