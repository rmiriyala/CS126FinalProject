#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "video_object.h"
#include <string>

class ofApp : public ofBaseApp{
	private:
		ofxDatGui * gui_;
		ofxDatGuiSlider* playback_scrubber_;

		VideoObject media_;
		ofVideoPlayer video_;

		bool is_paused_;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void onSliderEvent(ofxDatGuiSliderEvent e);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		

		void TogglePause(); //toggles the pause/play functionality in video
};
