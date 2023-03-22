#include "ofApp.h"


void ofApp::setup(){
	this->b = SoftBodyRect(45, 1.5, 450, 300, 9, 4);
	//this->b = Ball(10.0, 0.5, 100.0, 20);
	ofEnableSmoothing();
	center = ofVec2f(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);
}


void ofApp::update(){
	const float dt = ofGetElapsedTimef();
	for (int _ = 0; _ < 10; _++) this->b.update(dt * .01f);
}


void ofApp::draw(){
	ofBackground(0);
	ofTranslate(center);
	this->b.draw();
}