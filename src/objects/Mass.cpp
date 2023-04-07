#include "Mass.h"

Mass::Mass(float x, float y, float r, float m, bool k) :
	radius(r), mass(m), kinetic(k)
{
	pos = {x, y};
	prevPos = pos;
	acc = {0, 0};
}

ofVec2f Mass::vel() const 
{
	if (kinetic) return pos - prevPos;
	return {};
}



void Mass::update(float dt)
{
	if (!kinetic) return;
	const ofVec2f temp_pos = pos;
	const auto v = vel();
	pos += v * dt + (acc / mass) * dt * dt;
	prevPos = temp_pos;
	acc = GRAV * mass;
	if (pos.y + radius > ofGetHeight())
	{
		pos.y = ofGetHeight() - radius;
		prevPos = v * -0.8 + pos;
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
