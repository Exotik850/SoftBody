#include "Mass.h"
#define GRAV ofVec2f(0, 1)

Mass::Mass() {}

Mass::Mass(float x, float y, float r, float m) :
radius(r), mass(m)
{
	this->pos = ofVec2f(x, y);
	this->vel = ofVec2f(0, 0);
	this->acc = GRAV;
}

void Mass::update(float dt)
{
	this->vel += (acc / mass) * dt;
	this->pos += this->vel * dt;
	this->acc *= 0;
	this->acc += GRAV * dt;
	if (this->pos.y > ofGetHeight() / 2 - this->radius) {
		this->pos.y = ofGetHeight() / 2 - this->radius;
		this->vel.y *= -0.8; // restitution coefficient of 0.8
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
