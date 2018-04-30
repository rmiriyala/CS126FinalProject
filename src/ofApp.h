#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "video_object.h"
#include <string>
#include <vector>
#include <map>

using std::vector;
using std::map;
using std::pair;

class ofApp : public ofBaseApp{

	enum AppState {
		WATCHING_VIDEO, //for drawVideo()
		LOADING_VIDEO, //to prompt LoadVideo()
		CLOSING_VIDEO,
		MENU_SCREEN // for drawMain()
	};

	private:
		//State Control
		AppState current_state_ = MENU_SCREEN;

		//Load Variables
		vector<pair<ofRectangle, VideoObject>> thumbnail_button_links;
		vector<VideoObject> video_objects_;

		//GUI Elements
		ofxDatGui* gui_;
		ofxDatGuiSlider* playback_scrubber_;

		//Video Player Elements
		ofVideoPlayer video_;
		int current_video_object_;

		//Playback Control Elements
		ofTrueTypeFont video_label_;

		ofImage playback_background_;
		ofImage play_icon_;
		ofImage pause_icon_;
		ofImage forward_icon_;
		ofImage rewind_icon_;
		ofImage back_icon_;

		ofRectangle play_pause_button_;
		ofRectangle forward_button_;
		ofRectangle rewind_button_;
		ofRectangle back_button_;
		vector<ofRectangle> playback_buttons_;

		std::size_t last_mouse_usage_;
		bool is_paused_;

	public:
		void setup();
		void update();
		void draw();

		void drawMenuScreen();
		void drawWatchingVideoFull();
		void drawWatchingVideoSmall();
		void drawPlaybackControls();
		void hidePlaybackControls();

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
		void Forward();
		void Rewind();

		void LoadVideo(VideoObject &video);
		void CloseVideo(VideoObject &video);

		void InitializeThumbnails();
		void InitializeIcons();
		void DisplayThumbnails();

		const int ICON_SIZE = 100;
};
