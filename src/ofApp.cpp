#include "ofApp.h"


void ofApp::setup(){
	this->b = SoftBodyRect(10, 0.6, 40.0, 200, 200, 10, 5);
	ofEnableSmoothing();
	center = ofVec2f(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);
}


void ofApp::update(){
	this->b.update(ofGetElapsedTimef() * .1f);
}


void ofApp::draw(){
	ofBackground(0);
	ofTranslate(center);
	this->b.draw();
}