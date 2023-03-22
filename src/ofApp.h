#pragma once

#include "ofMain.h"
#include "objects/Ball.h"
#include "objects/SoftBodyRect.h"

class ofApp : public ofBaseApp{
	public:
		void setup() override;
		void update() override;
		void draw() override;
		//Ball b;
		SoftBodyRect b;
		ofVec2f center;
};
