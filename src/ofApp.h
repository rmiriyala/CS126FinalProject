#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "video_object.h"
#include <string>


class ofApp : public ofBaseApp{

	enum AppState {
		WATCHING_VIDEO,
		MENU_SCREEN
	};

	private:
		//State Control
		AppState current_state_ = MENU_SCREEN;

		//Video Player Variables
		ofxDatGui * gui_;
		ofxDatGuiSlider* playback_scrubber_;
		ofxDatGuiMatrix* video_matrix_;

		VideoObject media_;
		ofVideoPlayer video_;

		std::size_t last_mouse_usage_;
		bool is_paused_;

	public:
		void setup();
		void update();
		void draw();

		void drawMenuScreen();
		void drawWatchingVideo();

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
		void LoadVideo(std::string filepath);
		void InitializeThumbnails();
};
