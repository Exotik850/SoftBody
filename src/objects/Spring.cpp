#include "Spring.h"

#define MAX_FORCE 100
#define EPSILON 0.001f

void Spring::update(float dt) const
{
    ofVec2f dir = b->pos - a->pos;
    const float x = dir.length() - length;

    // Check for non-zero length before normalizing
    if (fabsf(x) > FLT_EPSILON) dir.normalize();

    // F = -k * (x - x0)
    if (x - EPSILON > length && x + EPSILON < length) return;
    const ofVec2f spring_force = dir * (k * x);

    const ofVec2f avel = a->vel();
    const ofVec2f bvel = b->vel();
    const ofVec2f rel_velocity = bvel - avel;
    const ofVec2f damping_force = damp * rel_velocity;

    // Apply spring and damping forces
    ofVec2f total_force = (spring_force + damping_force) * dt * 0.5f;
    total_force = total_force.getLimited(MAX_FORCE);

    if (total_force.lengthSquared() > 0.5f)
    {
        a->acc += total_force;
        b->acc -= total_force;
    }

}

void Spring::draw() const

{
    //ofVec2f dir = b->pos - a->pos;
    //const float dist = dir.length();
    //dir.normalize();
    //
    //int numSpikes = dist / 10;
    //numSpikes = numSpikes > 0 ? numSpikes : 1;
    //constexpr float spike_length = 5;
    //
    //ofPolyline polyline;
    //polyline.addVertex(a->pos.x, a->pos.y, 0.0);
    //
    //for (int i = 1; i <= numSpikes; ++i)
    //{
    //    ofVec2f spikeDir = (i % 2 == 0) ? ofVec2f(dir.y, -dir.x) : ofVec2f(-dir.y, dir.x);
    //    const ofVec2f spikePoint = a->pos + dir * (dist * i / numSpikes) + spikeDir * spike_length;
    //    polyline.addVertex(spikePoint.x, spikePoint.y, 0.0);
    //}
    //
    //polyline.addVertex(b->pos.x, b->pos.y, 0.0);
    //polyline.draw();
    ofDrawLine(a->pos, b->pos);
}