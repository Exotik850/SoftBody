#pragma once
#include "ofMain.h"
class Mass {
public:
	Mass(float x, float y, float r, float m);

	void update(float dt);
	void draw() const;
	ofVec2f vel() const;
	ofVec2f pos, prevPos, acc;

private:
	float radius, mass;
	const ofVec2f GRAV = ofVec2f(0, 1.0);
};
