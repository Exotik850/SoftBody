#pragma once

#include "ofMain.h"
#include "objects/Ball.h"
#include "objects/SoftBodyRect.h"

class ofApp : public ofBaseApp{
	public:
		void setup() override;
		void update() override;
		void draw() override;
#if 0
		void mouseDragged(int x, int y, int button) override;
		void mouseMoved(int x, int y) override;
#endif
		//Ball b;
		SoftBodyRect b;
		ofVec2f center;
		ofVec2f prev_mouse;
};
