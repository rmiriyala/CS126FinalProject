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
		//USER ELEMENTS
		string user_;
		string password_;
		bool show_create_button_ = false;
		bool is_creating_new_user_ = false;

		//STATE CONTROL ELEMENTS
		AppState current_state_ = GETTING_USERNAME; //intialized to username screen

		//VIDEO CONTROL ELEMENTS
		//objects
		vector<pair<ofRectangle, VideoObject>> thumbnail_button_links;
		vector<VideoObject> loaded_video_objects_;
		ofVideoPlayer video_;
		
		//boolean flags and tracking variables
		int current_video_object_;
		std::size_t last_mouse_usage_;
		bool is_paused_;

		//RECOMMENDATION SYSTEM ELEMENTS
		map<string, vector<double>> aggregate_user_data_;
		string recommended_video_filepath_ = "nothing";
		
		//GUI ELEMENTS
		//ofxDatGui
		ofxDatGui* slider_gui_;
		ofxDatGuiSlider* playback_scrubber_;
		ofxDatGui* login_gui_;
		ofxDatGuiTextInput* login_input_box_;
		
		//labels
		ofTrueTypeFont login_label_;
		ofTrueTypeFont video_label_;
		ofTrueTypeFont menu_label_;
		ofTrueTypeFont rating_instructions_;

		//images
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

		//image 'buttons'
		ofRectangle create_new_user_button_;
		ofRectangle like_button_;
		ofRectangle dislike_button_;
		ofRectangle play_pause_button_;
		ofRectangle forward_button_;
		ofRectangle rewind_button_;
		ofRectangle back_button_;

		//button containers
		vector<ofRectangle> playback_buttons_;
		vector<ofRectangle> rating_buttons_;

	public:
		//PROGRAM-DRIVING FUNCTIONS
		void setup();
		void update();
		void draw();

		//INITIALIZATION FUNCTIONS
		void GenerateThumbnails();
		void InitializeImages();
		void InitializeLabels();

		//GUI UPDATE FUNCTIONS
		void drawUsernameScreen();
		void drawPasswordScreen();
		void drawMenuScreen();
		void drawVideoFull();
		void drawVideoSmall();
		void drawPlaybackControls();
		void hidePlaybackControls();
		void drawClosingScreen();
		void drawRatingBox();
		void DisplayThumbnails();
		void DisplayRecommendationBox();
		void DisplayNetflixLogo();
		void DisplayUsernameInputBox(int width);
		void DisplayCreateAccountElements();

		//ON EVENT FUNCTIONS
		void keyPressed(int key);
		void mouseMoved(int x, int y );
		void mousePressed(int x, int y, int button);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void onTextInputEvent(ofxDatGuiTextInputEvent e);
		void onSliderEvent(ofxDatGuiSliderEvent e);
		
		//VIDEO PLAYBACK ADJUSTMENTS
		void TogglePause();
		void Forward();
		void Rewind();
		void LoadVideo(VideoObject &video);
		void CloseVideo(VideoObject &video);

		//FILE SAVING/LOADING
		bool Save();
		bool Load();
		vector<VideoObject> Load(string user);
		bool ExistsUser(string user);
		void CreateNewUser(string user);

		//RECOMMENDATION SYSTEM
		string GenerateRecommendation();
		void BuildAggregateUserComparisonDatabase();
		double CalculateAlikenessToUser(string other_user);
		string GetUserFromPath(string path);
		template <typename ElementType>
		ElementType Sum(vector<ElementType> vector);

		//FIXED VALUE CONSTANTS
		const int ICON_SIZE = 100;
		const float DISPLAY_RATIO = 2;
		const string FONT = OF_TTF_SANS;
};
