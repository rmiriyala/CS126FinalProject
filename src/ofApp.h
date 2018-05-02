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
		GETTING_USERNAME,
		GETTING_PASSWORD,
		WATCHING_VIDEO, //for drawVideo()
		LOADING_VIDEO, //to prompt LoadVideo()
		CLOSING_VIDEO,
		USING_PLAYBACK_CONTROLS,
		RATING_VIDEO,
		MENU_SCREEN // for drawMain()
	};

	private:
		//User Control
		string user_;
		string password_;
		bool show_create_button_ = false;
		bool is_creating_new_user_ = false;

		//State Control
		AppState current_state_ = GETTING_USERNAME;

		//Objects
		vector<pair<ofRectangle, VideoObject>> thumbnail_button_links;
		vector<VideoObject> loaded_video_objects_;
		ofVideoPlayer video_;
		
		//GUI Elements
		ofxDatGui* slider_gui_;
		ofxDatGuiSlider* playback_scrubber_;
		ofxDatGui* login_gui_;
		ofxDatGuiTextInput* login_input_box_;

		ofTrueTypeFont login_label_;
		ofTrueTypeFont video_label_;
		ofTrueTypeFont menu_label_;
		ofTrueTypeFont rating_instructions_;

		ofImage login_screen_background_;
		ofImage create_new_user_icon_;
		ofImage like_icon_;
		ofImage dislike_icon_;
		ofImage netflix_logo_;
		ofImage playback_background_;
		ofImage rating_box_background_;
		ofImage play_icon_;
		ofImage pause_icon_;
		ofImage forward_icon_;
		ofImage rewind_icon_;
		ofImage back_icon_;

		ofRectangle create_new_user_button_;
		ofRectangle like_button_;
		ofRectangle dislike_button_;
		ofRectangle play_pause_button_;
		ofRectangle forward_button_;
		ofRectangle rewind_button_;
		ofRectangle back_button_;

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

		void drawUsernameScreen();
		void drawPasswordScreen();
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
		bool Save();
		bool Load();
		bool ExistsUser(string user);
		void CreateNewUser(string user);

		//Display Helpers
		void InitializeThumbnails();
		void InitializeImages();
		void DisplayThumbnails();
		void DisplayNetflixLogo();
		void DisplayUsernameInputBox(int width);
		void DisplayCreateAccountElements();

		void onTextInputEvent(ofxDatGuiTextInputEvent e);

		//Constants
		const int ICON_SIZE = 100;
		const float DISPLAY_RATIO = 2;
};
