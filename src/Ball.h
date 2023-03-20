#pragma once
#include "ofMain.h"
#include "Mass.h"

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

	void update(float dt) const
	{
		ofVec2f dir = b->pos - a->pos;
		const float x = dir.length() - length;

		// Check for non-zero length before normalizing
		if (x != 0) dir.normalize();

		// F = -k * (x - x0)
		const ofVec2f spring_force = dir * (-k * x);

		// Calculate damping force based on relative velocity
		const ofVec2f rel_velocity = b->vel - a->vel;
		const ofVec2f damping_force = -damp * rel_velocity;

		// Apply spring and damping forces
		const ofVec2f total_force = (spring_force + damping_force) * dt * 0.5f;
		a->acc -= total_force;
		b->acc += total_force;
	}

	void draw() const
	{
		ofVec2f dir = b->pos - a->pos;
		const float dist = dir.length();
		dir.normalize();

		int numSpikes = dist / 10;
		numSpikes = numSpikes > 0 ? numSpikes : 1;
		constexpr float spike_length = 5;

		ofPolyline polyline;
		polyline.addVertex(a->pos.x, a->pos.y, 0.0);

		for (int i = 1; i <= numSpikes; ++i)
		{
			ofVec2f spikeDir = (i % 2 == 0) ? ofVec2f(dir.y, -dir.x) : ofVec2f(-dir.y, dir.x);
			const ofVec2f spikePoint = a->pos + dir * (dist * i / numSpikes) + spikeDir * spike_length;
			polyline.addVertex(spikePoint.x, spikePoint.y, 0.0);
		}

		polyline.addVertex(b->pos.x, b->pos.y, 0.0);
		polyline.draw();
	}
};

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
	float radius;
    float k, kd, restLength;
};
