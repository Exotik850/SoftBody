#pragma once

#include "ofMain.h"
#include "objects/Ball.h"
#include "objects/SoftBodyRect.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		Ball b;
		//SoftBodyRect b;
		ofVec2f center;
};
