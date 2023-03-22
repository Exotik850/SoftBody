#include "SoftBodyRect.h"

#include "ofAppRunner.h"

const float SQRT_2 = sqrt(2);

SoftBodyRect::SoftBodyRect() {

}

SoftBodyRect::SoftBodyRect(float k, float kd, const float width, const float height, const int num_points_w, const int num_points_h)
    : num_points_w(num_points_w), num_points_h(num_points_h), width(width), height(height), k(k), kd(kd)
{
    const float step_w = width / num_points_w;
    const float step_h = height / num_points_h;

    for (int i = 0; i < num_points_h; ++i)
    {
        for (int j = 0; j < num_points_w; ++j)
        {
            float x = step_w * j;
            float y = step_h * i;
            points.emplace_back(x, y, 5.0, 3.0);
        }
    }

    const float diag = sqrt(step_w * step_w + step_h * step_h);
    for (int i = 0; i < num_points_h; ++i)
    {
        for (int j = 0; j < num_points_w; ++j)
        {
            const int index = i * num_points_w + j;
            if (j + 1 < num_points_w)
                springs.emplace_back(&points[index], &points[index + 1], k, kd, step_w);
            if (i + 1 < num_points_h)
                springs.emplace_back(&points[index], &points[index + num_points_w], k, kd, step_h);
            if (j + 1 < num_points_w && i + 1 < num_points_h) 
                springs.emplace_back(&points[index], &points[index + num_points_w + 1], k, kd, diag);
            if (j > 0 && i + 1 < num_points_h)
                springs.emplace_back(&points[index], &points[index + num_points_w - 1], k, kd, diag);
        }
    }
}

void SoftBodyRect::update(const float dt)
{
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 1));
    for (auto& spring : springs) spring.update(dt);
    for (auto& point : points) point.update(dt);
}

void SoftBodyRect::draw()
{
    for (Mass &m : points) m.draw();
    for (Spring &s : springs) s.draw();
}