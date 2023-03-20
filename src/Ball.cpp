#include "Ball.h"

Ball::Ball() {

}

Ball::Ball(float k, float kd, float rest_length, const float radius, const int num_points)
    : num(num_points), radius(radius), k(k), kd(kd), restLength(rest_length)
{
    const float angle_step = TWO_PI / num_points;
    for (int i = 0; i < num_points; ++i)
    {
        float x = radius * cos(angle_step * i);
        float y = radius * sin(angle_step * i);
        points.emplace_back(x, y, 5.0, 3.0);
    }

    for (int i = 0; i < num_points; ++i)
    {
        springs.emplace_back(&points[i], &points[(i+1)%num_points], k, kd, rest_length);
    }
}

void Ball::update(const float dt)
{
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 0));
    for (Spring& spring : springs)
    {
        spring.update(dt);
    }

    const float curr_area = area();
    constexpr float pressure_strength = 0.001f; // Adjust this value to control the pressure strength
    const float pressure = (PI * pow(radius, 2) - curr_area) * pressure_strength;
    
    // Calculate the average position of the points
    ofVec2f average_pos(0, 0);
    for (const Mass& mass : points)
    {
        average_pos += mass.pos;
    }
    average_pos /= points.size();

    for (auto& point : points)
    {
        // Calculate the direction from the average position to the point
        ofVec2f dir = point.pos - average_pos;
        dir.normalize();

        // Apply the pressure force in the direction of the point
        point.acc += dir * pressure * dt;

        point.vel *= 0.85;
        point.update(dt);
    }
}

void Ball::draw()
{
	for (Mass &m : points) m.draw();
    for (Spring &s : springs) s.draw();
}

float Ball::area() const
{
    float area = 0.0;

    for (int i = 0; i < num; ++i)
    {
        const ofVec2f& p1 = points[i].pos;
        const ofVec2f& p2 = points[(i + 1) % num].pos;
        area += p1.x * p2.y - p2.x * p1.y;
    }

    return 0.5 * abs(area);
}