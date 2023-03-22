#include "ofApp.h"


void ofApp::setup(){
	//this->b = SoftBodyRect(15, 0.7, 200, 200, 3, 3);
	this->b = Ball(10.0, 0.7, 100.0, 25);
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