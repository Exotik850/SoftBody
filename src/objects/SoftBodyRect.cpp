#include "SoftBodyRect.h"
#include "ofAppRunner.h"

const float SQRT_2 = sqrtf(2);

SoftBodyRect::SoftBodyRect() {}

SoftBodyRect::SoftBodyRect(float k, float kd, const float width, const float height, const int num_points_w, const int num_points_h)
    : num_points_w(num_points_w), num_points_h(num_points_h), width(width), height(height), k(k), kd(kd)
{
    const float step_w = width / num_points_w;
    const float step_h = height / num_points_h;

    //auto after = true;
    for (int i = 0; i < num_points_h; ++i)
    {
        for (int j = 0; j < num_points_w; ++j)
        {
            bool after = i > 0 || j % 5 != 0;
            
            float x = step_w * j;
            float y = step_h * i;
            points.emplace_back(x, y, 5.0, 0.1, after);
        }
    }

    const float diag = sqrtf(step_w * step_w + step_h * step_h) + FLT_EPSILON;
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

    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    for (auto& mass: points) mesh.addVertex(ofPoint(mass.pos.x, mass.pos.y));
    for (int i = 0; i < num_points_h - 1; ++i)
    {
        for (int j = 0; j < num_points_w - 1; ++j)
        {
            int index = i * num_points_w + j;
            
            // Add two triangles to form a quad
            mesh.addIndex(index);               // current point
            mesh.addIndex(index + 1);           // next point in the same row
            mesh.addIndex(index + num_points_w); // next point in the same column

            mesh.addIndex(index + 1);                   // next point in the same row
            mesh.addIndex(index + num_points_w + 1);     // diagonal point
            mesh.addIndex(index + num_points_w);         // next point in the same column
        }
    }
}

void SoftBodyRect::update(const float dt)
{
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 1));

    #pragma omp parallel for
    for (int i = 0; i < springs.size(); ++i)
    {
        springs[i].update(dt);
    }

    #pragma omp parallel for
    for (int i = 0; i < points.size(); ++i)
    {
        points[i].update(dt);
    }
}

void SoftBodyRect::draw()
{
    //auto start_time = chrono::high_resolution_clock::now();

    //for (Spring &s : springs) s.draw();
    for (std::size_t i = 0; i < points.size(); i++) {
        mesh.setVertex(i, ofPoint(points[i].pos.x, points[i].pos.y));
    }
    mesh.drawWireframe();
    
    //const auto dur = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time).count();
    //cout << "Draw time: " << dur << "ms\n";
}

void SoftBodyRect::cut(ofVec2f a, ofVec2f b)
{
    
}
