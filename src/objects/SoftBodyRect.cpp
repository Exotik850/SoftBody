#include "SoftBodyRect.h"

#include "ofAppRunner.h"

SoftBodyRect::SoftBodyRect() {

}

SoftBodyRect::SoftBodyRect(float k, float kd, float rest_length, const float width, const float height, const int num_points_w, const int num_points_h)
    : num_points_w(num_points_w), num_points_h(num_points_h), width(width), height(height), k(k), kd(kd), restLength(rest_length)
{
    const float step_w = width / (num_points_w - 1);
    const float step_h = height / (num_points_h - 1);

    for (int i = 0; i < num_points_h; ++i)
    {
        for (int j = 0; j < num_points_w; ++j)
        {
            float x = step_w * j;
            float y = step_h * i;
            points.emplace_back(x, y, 5.0, 3.0);
        }
    }

    for (int i = 0; i < num_points_h; ++i)
    {
        for (int j = 0; j < num_points_w; ++j)
        {
            const int index = i * num_points_w + j;
            if (j + 1 < num_points_w)
                springs.emplace_back(&points[index], &points[index + 1], k, kd, rest_length);
            if (i + 1 < num_points_h)
                springs.emplace_back(&points[index], &points[index + num_points_w], k, kd, rest_length);
            if (j + 1 < num_points_w && i + 1 < num_points_h) {
                springs.emplace_back(&points[index], &points[index + num_points_w + 1], k, kd, rest_length * sqrt(2));
                if (j > 0)
                    springs.emplace_back(&points[index], &points[index + num_points_w - 1], k, kd, rest_length * sqrt(2));
            }
        }
    }
}

void SoftBodyRect::update(const float dt)
{
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 1));
    for (auto& spring : springs)
    {
        spring.update(dt);
    }

    for (auto& point : points)
    {
        point.update(dt);
    }
}

void SoftBodyRect::draw()
{
    for (Mass &m : points) m.draw();
    for (Spring &s : springs) s.draw();
}