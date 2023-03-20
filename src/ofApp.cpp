#include "ofApp.h"


void ofApp::setup(){
	this->b = Ball(3, 0.1, 3.0, 100.0, 32);
	ofEnableSmoothing();
	center = ofVec2f(ofGetWidth() / 2.0f, ofGetHeight() / 2.0f);
}


void ofApp::update(){
	this->b.update(ofGetElapsedTimef() * .1);
}


void ofApp::draw(){
	ofBackground(0);
	ofTranslate(center);
	this->b.draw();
}