#include "Mass.h"
#define GRAV ofVec2f(0, 1)

Mass::Mass(float x, float y, float r, float m) :
	radius(r), mass(m)
{
	pos = ofVec2f(x, y);
	prevPos = pos;
	acc = ofVec2f(0, 0);
}

ofVec2f Mass::vel() const 
{
	return pos - prevPos;
}

void Mass::update(float dt)
{
	const ofVec2f temp_pos = pos;
	pos += (pos - prevPos) + (acc / mass) * dt * dt;
	prevPos = temp_pos;
	acc = GRAV;
	//acc *= 0;

	if (pos.y > ofGetHeight() / 2 - radius) {
		pos.y = ofGetHeight() / 2 - radius;
		//prevPos.y = pos.y + (pos.y - prevPos.y) * -0.8; // restitution coefficient of 0.8
	}
}

void Mass::draw() const
{
	ofPushMatrix();
	ofSetLineWidth(0);
	ofSetColor(255);
	ofDrawCircle(pos, radius);
	ofPopMatrix();
}
