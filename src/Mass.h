#pragma once
#include "ofMain.h"
class Mass
{
public:
	ofVec2f pos, vel, acc;
	float radius, mass;
	Mass();
	Mass(float x, float y, float r, float m);
	void update(float dt);
	void draw() const;
};

