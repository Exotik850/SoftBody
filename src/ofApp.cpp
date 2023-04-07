#include "ofApp.h"

enum
{
	NUM_ITER = 10,
	WIDTH = 200,
	HEIGHT = 300
};

void ofApp::setup(){
	this->b = SoftBodyRect(0.5, 0.5, WIDTH, HEIGHT, 12, 12);
	//this->b = Ball(90.0, 1.0, 100.0, 30);
	ofEnableSmoothing();
	center = ofVec2f(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);
}


void ofApp::update(){
	//const auto start_time = chrono::high_resolution_clock::now();

	const float dt = ofGetElapsedTimef() * 0.05f;
	for (int _ = 0; _ < NUM_ITER; _++) this->b.update(dt);
	
	//const auto dur = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time).count();
	//cout << "Update time: " << dur << "ms\n";
}


void ofApp::draw(){
	ofBackground(0);
	ofTranslate(center);
	b.draw();
}

#if 0
void ofApp::mouseDragged(int x, int y, int button)
{
	b.cut(prev_mouse, {static_cast<float>(x), static_cast<float>(y)});
}

void ofApp::mouseMoved(int x, int y)
{
	prev_mouse = {static_cast<float>(x), static_cast<float>(y)};
}
#endif