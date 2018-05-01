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
		USING_PLAYBACK_CONTROLS,
		RATING_VIDEO,
		MENU_SCREEN // for drawMain()
	};

	private:
		//State Control
		AppState current_state_ = MENU_SCREEN;

		//Objects
		vector<pair<ofRectangle, VideoObject>> thumbnail_button_links;
		vector<VideoObject> loaded_video_objects_;
		ofVideoPlayer video_;
		
		//GUI Elements
		ofxDatGui* gui_;
		ofxDatGuiSlider* playback_scrubber_;

		ofTrueTypeFont video_label_;
		ofTrueTypeFont menu_label_;
		ofTrueTypeFont rating_instructions_;

		ofImage like_icon_;
		ofImage dislike_icon_;
		ofImage logo_;
		ofImage playback_background_;
		ofImage rating_box_background_;
		ofImage play_icon_;
		ofImage pause_icon_;
		ofImage forward_icon_;
		ofImage rewind_icon_;
		ofImage back_icon_;

		ofRectangle play_pause_button_;
		ofRectangle forward_button_;
		ofRectangle rewind_button_;
		ofRectangle back_button_;
		ofRectangle like_button_;
		ofRectangle dislike_button_;

		vector<ofRectangle> playback_buttons_;
		vector<ofRectangle> rating_buttons_;

		//Tracking Variables
		int current_video_object_;
		std::size_t last_mouse_usage_;
		bool is_paused_;

	public:
		void setup();
		void update();
		void draw();

		void drawMenuScreen();
		void drawVideoFull();
		void drawVideoSmall();
		void drawPlaybackControls();
		void hidePlaybackControls();
		void drawClosingScreen();
		void drawRatingBox();

		void keyPressed(int key);
		void mouseMoved(int x, int y );
		void mousePressed(int x, int y, int button);
		void onSliderEvent(ofxDatGuiSliderEvent e);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);

		/*Unused OpenFrameworks Commands*/
		//void keyReleased(int key);
		//void mouseDragged(int x, int y, int button);
		//void mouseReleased(int x, int y, int button);
		//void mouseEntered(int x, int y);
		//void dragEvent(ofDragInfo dragInfo);
		//void gotMessage(ofMessage msg);
		

		//Playback Controls
		void TogglePause();
		void Forward();
		void Rewind();

		//Object Control
		void LoadVideo(VideoObject &video);
		void CloseVideo(VideoObject &video);

		//Display Helpers
		void InitializeThumbnails();
		void InitializeIcons();
		void DisplayThumbnails();
		void DisplayLogo();

		//Constants
		const int ICON_SIZE = 100;
		const float DISPLAY_RATIO = 2;
};
