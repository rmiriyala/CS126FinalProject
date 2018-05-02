#include "ofApp.h"


void ofApp::setup(){
	ofBackground(50, 50, 50);

	/*user_ = GetUser();
	while (user_ == "") {
		GetUser();
	}
	Load(user_);
	std::cout << "loading user data...done" << std::endl;*/

	InitializeThumbnails();
	std::cout << "loading thumbnails...done" << std::endl;

	InitializeImages();
	std::cout << "loading icons...done" << std::endl;

	//Setup GUI
	slider_gui_ = new ofxDatGui(ofxDatGuiAnchor::BOTTOM_LEFT);
	int x = ofGetWidth() / 1.40;
	int y = (ofGetHeight() / 20) + ((((ofGetWidth() * 2.7) / 10) * (netflix_logo_.getHeight() / netflix_logo_.getWidth())) * 2.5);
	login_gui_ = new ofxDatGui(x, y);

	//Setup Login Box
	login_input_box_ = login_gui_->addTextInput("Username", "");

	//Setup Playback Scrubber
	playback_scrubber_ = slider_gui_->addSlider("Playback Slider", 0, 1, 0);
	playback_scrubber_->setWidth(ofGetWidth(), 0);
	playback_scrubber_->setBorderVisible(false);

	//Setup Labels
	video_label_.load(OF_TTF_SANS, 40);
	menu_label_.load(OF_TTF_SANS, 25);
	rating_instructions_.load(OF_TTF_SANS, 60);

	//Hide GUIs
	slider_gui_->setVisible(false);
	login_gui_->setVisible(false);
}

void ofApp::update() {
	if (current_state_ == GETTING_USERNAME) {
		login_input_box_->onTextInputEvent(this, &ofApp::onTextInputEvent);
		login_input_box_->update();
	}
	else if (current_state_ == MENU_SCREEN) {
		//do nothing
	}
	else if (current_state_ == WATCHING_VIDEO || current_state_ == USING_PLAYBACK_CONTROLS) {
		current_state_ = (ofGetElapsedTimeMillis() - last_mouse_usage_ > 2500) ? WATCHING_VIDEO : USING_PLAYBACK_CONTROLS;
		video_.update();
		playback_scrubber_->setValue(video_.getPosition());

		if (video_.getPosition() > 0.999) {
			video_.stop();
			thumbnail_button_links.at(current_video_object_).second.setWatched(true);
			current_state_ = RATING_VIDEO;
		}
	}
	else if (current_state_ == RATING_VIDEO || current_state_ == CLOSING_VIDEO) {
		bool isRated = (thumbnail_button_links.at(current_video_object_).second.getRating() != -1);
		bool isWatched = thumbnail_button_links.at(current_video_object_).second.isWatched();
		current_state_ = (!isRated && isWatched) ? RATING_VIDEO : CLOSING_VIDEO;

		if (current_state_ == RATING_VIDEO) {
			//wait for mouse click somewhere
		}
		else {
			CloseVideo(thumbnail_button_links.at(current_video_object_).second);
		}
	}
}

void ofApp::draw() {
	if (current_state_ == GETTING_USERNAME) {
		drawUsernameScreen();
	}
	else if (current_state_ == GETTING_PASSWORD) {
		drawPasswordScreen();
	}
	else if (current_state_ == MENU_SCREEN) {
		drawMenuScreen();
	}
	else if (current_state_ == WATCHING_VIDEO) {
		ofHideCursor();
		hidePlaybackControls();
		drawVideoFull();
	}
	else if (current_state_ == USING_PLAYBACK_CONTROLS) {
		ofShowCursor();
		drawVideoSmall();
		drawPlaybackControls();
	}
	else if (current_state_ == RATING_VIDEO) {
		ofShowCursor();
		hidePlaybackControls();
		drawRatingBox();
	}
	else if (current_state_ == CLOSING_VIDEO) {
		hidePlaybackControls();
		drawClosingScreen();
	}
}

//------------------------------------------------------------------------------------

void ofApp::drawUsernameScreen() {
	login_screen_background_.resize(ofGetWidth(), ofGetHeight());
	login_screen_background_.draw(0, 0);


	float ratio = netflix_logo_.getHeight() / netflix_logo_.getWidth();
	int width = (ofGetWidth() * 2.7) / 10;
	netflix_logo_.resize(width, ratio * width);

	int x = ofGetWidth() / 1.40;
	int y = ofGetHeight() / 20;
	netflix_logo_.draw(x, y);

	y += netflix_logo_.getHeight()* 1.5; //allows for some padding
	DisplayUsernameInputBox(width);
}

void ofApp::drawPasswordScreen() {
	login_input_box_->setLabel("Password");
	drawUsernameScreen();
}

//Draws the Netflix logo and the thumbnails for the videos
void ofApp::drawMenuScreen() {
	login_gui_->setVisible(false);
	ofBackground(50, 50, 50);
	DisplayNetflixLogo();
	DisplayThumbnails();
}

//Draws a fullscreen version of the video
void ofApp::drawVideoFull() {
	int video_width = ofGetWidth();
	int video_height = ofGetHeight();
	int x_position = 0;
	int y_position = 0;
	video_.draw(x_position, y_position, video_width, video_height);
}

//Resizes the video, maintaining the same dimensions, but allowing the playback controls to appear
void ofApp::drawVideoSmall() {
	ofBackground(0, 0, 0);
	int video_height = ofGetHeight() - (2.2 * ICON_SIZE) - (playback_scrubber_->getHeight());
	int video_width = video_height * DISPLAY_RATIO;
	int x_position = (ofGetWidth() - video_width) / 2; //centers the video
	int y_position = 1.1 * ICON_SIZE;
	video_.draw(x_position, y_position, video_width, video_height);
}

//Draws all playback controls, including the ofxDatGui slider
void ofApp::drawPlaybackControls() {
	slider_gui_->setVisible(true);

	//Draw background
	int x = (ofGetWidth() - playback_background_.getWidth()) / 2;
	int y = ofGetHeight() - playback_scrubber_->getHeight() - playback_background_.getHeight();
	playback_background_.draw(x, y); //bottom bar (play/pause, forward, rewind buttons)
	playback_background_.draw(x, 0); //top bar (label, back button)

									 //Draw label
	string label = thumbnail_button_links.at(current_video_object_).second.getLabel();
	x = (ofGetWidth() - video_label_.stringWidth(label)) / 2;
	y = (ICON_SIZE * 1.1 + video_label_.stringHeight(label)) / 2;
	video_label_.drawString(label, x, y);

	//Draw play/pause
	x = (ofGetWidth() - ICON_SIZE) / 2;
	y = ofGetHeight() - playback_scrubber_->getHeight() - ICON_SIZE;
	if (is_paused_) { //draw the opposite of the current state
		play_icon_.draw(x, y);
	}
	else {
		pause_icon_.draw(x, y);
	}
	play_pause_button_ = ofRectangle(x, y, ICON_SIZE, ICON_SIZE);

	//Draw rewind
	rewind_icon_.draw(x - 1.5 * ICON_SIZE, y);
	rewind_button_ = ofRectangle(x - 1.5 * ICON_SIZE, y, ICON_SIZE, ICON_SIZE);

	//Draw forward
	forward_icon_.draw(x + 1.5 * ICON_SIZE, y);
	forward_button_ = ofRectangle(x + 1.5 * ICON_SIZE, y, ICON_SIZE, ICON_SIZE);

	//Draw back button
	y = (1.1 * ICON_SIZE - back_icon_.getHeight()) / 2;
	x = y;
	back_icon_.draw(x, y);
	back_button_ = ofRectangle(x, y, back_icon_.getWidth(), back_icon_.getHeight());

	//Add to array, if not already in there
	if (playback_buttons_.size() != 4) {
		while (playback_buttons_.size() > 0) {
			playback_buttons_.pop_back();
		}

		if (playback_buttons_.size() <= 0) {
			playback_buttons_.push_back(play_pause_button_);
			playback_buttons_.push_back(forward_button_);
			playback_buttons_.push_back(rewind_button_);
			playback_buttons_.push_back(back_button_);
		}
		else {
			playback_buttons_[0] = play_pause_button_;
			playback_buttons_[1] = forward_button_;
			playback_buttons_[2] = rewind_button_;
			playback_buttons_[4] = back_button_;
		}
	}
}

//Hides app playback controls, including the ofxDatGui slider
void ofApp::hidePlaybackControls() {
	slider_gui_->setVisible(false);
	//as long as we don't explicitly draw the rest of the controls, they won't show up
}

//Draws the box to get the user's like/dislike preference, including the label
void ofApp::drawRatingBox() {
	bool isRated = (thumbnail_button_links.at(current_video_object_).second.getRating() != -1);
	bool isWatched = thumbnail_button_links.at(current_video_object_).second.isWatched();
	//Doing this allows us to avoid the 0.01 (but visible) drawing and undrawing of the rating box when these conditions aren't met
	if (isWatched && !isRated) {
		ofBackground(0, 0, 0);

		//Draw Background
		int x = ofGetWidth() / 4;
		int y = ofGetHeight() / 4;
		rating_box_background_.draw(x, y);

		//Draw Label
		string label = "Please Rate the Video";
		int x_pos = x + (rating_box_background_.getWidth() - rating_instructions_.stringWidth(label)) / 2;
		int y_pos = y + 2*rating_instructions_.getSize();
		rating_instructions_.drawString(label, x_pos, y_pos);

		//Draw Like Button
		like_icon_.resize(rating_box_background_.getHeight() / 2, rating_box_background_.getHeight() / 2);
		x = x + ((rating_box_background_.getWidth()- 2 * like_icon_.getWidth()) / 3);
		y = y + rating_box_background_.getHeight() - 1.2* like_icon_.getHeight();
		like_icon_.draw(x, y);
		like_button_ = ofRectangle(x, y, like_icon_.getWidth(), like_icon_.getHeight());

		//Draw Dislike Button
		dislike_icon_.resize(rating_box_background_.getHeight() / 2, rating_box_background_.getHeight() / 2);
		x = x + ((rating_box_background_.getWidth() - 2*like_icon_.getWidth()) / 3) + like_icon_.getWidth();
		dislike_icon_.draw(x, y);
		dislike_button_ = ofRectangle(x, y, like_icon_.getWidth(), like_icon_.getHeight());

		//Add to array, if not already in there
		if (rating_buttons_.size() != 2) {
			while (rating_buttons_.size() > 0) {
				rating_buttons_.pop_back();
			}

			if (rating_buttons_.size() <= 0) {
				rating_buttons_.push_back(like_button_);
				rating_buttons_.push_back(dislike_button_);
			}
			else {
				rating_buttons_[0] = like_button_;
				rating_buttons_[1] = dislike_button_;
			}
		}
	}
}

//Shows the cursor and transitions back to the menu page
void ofApp::drawClosingScreen() {
	ofShowCursor();
	drawMenuScreen();
	current_state_ = MENU_SCREEN;
}

//------------------------------------------------------------------------------------

//Various functions on key press at different states
void ofApp::keyPressed(int key) {
	if (current_state_ == WATCHING_VIDEO || current_state_ == USING_PLAYBACK_CONTROLS) {
		switch (key) {
		case 'k':
			TogglePause();
			break;
		case ' ':
			TogglePause();
			break;
		case 'l':
			Forward();
			break;
		case 'j':
			Rewind();
			break;
		case OF_KEY_BACKSPACE:
			current_state_ = CLOSING_VIDEO;
			break;
		default:
			break;
		}
	}
}

//Used to track the last time the mouse was moved in order to auto-hide the playback controls
void ofApp::mouseMoved(int x, int y) {
	last_mouse_usage_ = ofGetElapsedTimeMillis();
}

//Various functions on mouse click (buttons, playback slider, etc.)
void ofApp::mousePressed(int x, int y, int button) {
	if (current_state_ == MENU_SCREEN) {
		//Load the thumbnail that was clicked, if any were clicked
		for (auto pair : thumbnail_button_links) {
			auto image = pair.first;
			if (x > image.x && x < (image.x + image.width) && y > image.y &&  y < (image.y + image.height)) {
				current_state_ = LOADING_VIDEO;
				LoadVideo(pair.second);
				break;
			}
		}
	} else if (current_state_ == WATCHING_VIDEO) {
		TogglePause();
	} else if (current_state_ == USING_PLAYBACK_CONTROLS) {
			if (y >= ofGetHeight() - playback_scrubber_->getHeight()) { //if we are operating on the playback slider
				playback_scrubber_->onSliderEvent(this, &ofApp::onSliderEvent);
			} else if ((y > 1.1 * ICON_SIZE && y < ofGetHeight() - (1.1 * ICON_SIZE) - (playback_scrubber_->getHeight()))) { //on smaller video
				TogglePause();
			} else { //will look to see if the click intersects one of the buttons
				ofRectangle button;
				for (int i = 0; i < playback_buttons_.size(); i++) {
					button = playback_buttons_.at(i);
					if (x > button.x && x < (button.x + button.width) && y > button.y &&  y < (button.y + button.height)) {
						switch (i) {
						case 0:
							TogglePause();
							break;
						case 1:
							Forward();
							break;
						case 2:
							Rewind();
							break;
						case 3:
							current_state_ = CLOSING_VIDEO;
							break;
						default:
							break;
						}
						break;
					}

				}
			}
	} else if (current_state_ == RATING_VIDEO) {
		ofRectangle button;
		for (int i = 0; i < rating_buttons_.size(); i++) {
			button = rating_buttons_.at(i);
			if (x > button.x && x < (button.x + button.width) && y > button.y &&  y < (button.y + button.height)) {
				switch (i) {
				case 0:
					thumbnail_button_links.at(current_video_object_).second.setRating(1); //using at because it won't create one if it doesn't exist
					break;
				case 1:
					thumbnail_button_links.at(current_video_object_).second.setRating(0);
					break;
				default:
					break;
				}
				break; //can't click on two objects at the same time (since we know for a fact they don't intersect
			}
		}
		current_state_ = CLOSING_VIDEO;
	}
}

//Behavior that occurs when the slider is clicked at a certain point
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e) {
	video_.setPosition(e.value);
}

//Manipulates the last mouse usage time so that the playback controls are hidden
void ofApp::mouseExited(int x, int y) {
	last_mouse_usage_ = ofGetElapsedTimeMillis() - 2500; //once the mouse leaves, trigger the hiding of playback controls
}

//Adjusts the playback slider on resize
void ofApp::windowResized(int w, int h) {
	playback_scrubber_->setWidth(ofGetWidth(), 0);
}

//------------------------------------------------------------------------------------

//Will toggle the video playing state
void ofApp::TogglePause() {
	float position = video_.getPosition();
	is_paused_ = !is_paused_;
	video_.setPaused(is_paused_);
	
	if (current_state_ == USING_PLAYBACK_CONTROLS) {
		last_mouse_usage_ = ofGetElapsedTimeMillis();
	}
}

//Forwards by exactly 2% of the video's length; capped at max video position
void ofApp::Forward() {
	float position = video_.getPosition();
	position = (position + 0.01 > 1) ? 1 : position + 0.02; //will cap position to 1
	video_.setPosition(position);

	if (current_state_ == USING_PLAYBACK_CONTROLS) {
		last_mouse_usage_ = ofGetElapsedTimeMillis();
	}
}

//Rewinds by exactly 2% of the video's length; capped at min video position
void ofApp::Rewind() {
	float position = video_.getPosition();
	position = (position - 0.01 < 0) ? 0 : position - 0.02; //will floor position at 0
	video_.setPosition(position);

	if (current_state_ == USING_PLAYBACK_CONTROLS) {
		last_mouse_usage_ = ofGetElapsedTimeMillis();
	}
}

//------------------------------------------------------------------------------------

//Will load a video from a VideoObject
void ofApp::LoadVideo(VideoObject &video) {
	current_state_ = LOADING_VIDEO; //here in case I want to implement a loading screen
	string filepath = video.getVideoFilepath();
	for (int i = 0; i < thumbnail_button_links.size(); i++) {
		if (thumbnail_button_links[i].second.getVideoFilepath() == filepath) {
			current_video_object_ = i;
			break;
		}
	}
	video_.load(filepath);
	video_.play();
	video_.setLoopState(ofLoopType(ofLoopType::OF_LOOP_NONE));
	video_.setPosition(video.getVideoPlaybackPosition());
	video_.update();

	is_paused_ = false;
	current_state_ = WATCHING_VIDEO;
}

//Will stop playing a video given a VideoObject that is playing
void ofApp::CloseVideo(VideoObject &video) {
	current_state_ = CLOSING_VIDEO;
	video.setPlaybackPosition(video_.getPosition());
	if (video_.getPosition() > 0.99) {
		video.setPlaybackPosition(0);
	}
	video_.stop();
	Save(user_);
}

//Will save all created video objects from thumbnail button links
bool ofApp::Save(string username) {
	std::ofstream save_file("../data/" + username + "-data.txt");
	if (!save_file) {
		return false;
	}

	std::cout << thumbnail_button_links.size() << std::endl;
	for (auto pair : thumbnail_button_links) {
		VideoObject video_object = pair.second;
		save_file << "! " << video_object.getVideoFilepath() << "\n";
		save_file << "@ " << video_object.getRating() << " ";
		save_file << "# " << video_object.isWatched() << " ";
		save_file << "$ " << video_object.getVideoPlaybackPosition() << " ";
		save_file << "% " << std::endl;
	}

	return true;
}

//Will load all saved video objects to loaded_video_objects
bool ofApp::Load(string username) {
	std::ifstream load_file("../data/" + username + "-data.txt");
	if (!load_file) {
		return false;
	}

	string input;
	VideoObject video;
	while (load_file >> input) { // NOLINT
		if (input == "!") {
			string path;
			std::getline(load_file, path); //accidentally gets the space following "!"
			video.setVideoFilepath(path.substr(1));
		}
		else if (input == "@") {
			int rating;
			load_file >> rating; // NOLINT
			video.setRating(rating);
		}
		else if (input == "#") {
			bool watched;
			load_file >> watched; // NOLINT
			video.setWatched(watched);
		}
		else if (input == "$") {
			double position;
			load_file >> position;
			video.setPlaybackPosition(position);
		}
		else if (input == "%") {
			loaded_video_objects_.push_back(video);
			video = VideoObject();
		}
	}
}

//Returns the username if authentication passes, empty string otherwise
bool ofApp::ExistsUser(string user) {
	std::ifstream data_file("../data/" + user + "-data.txt");
	std::ifstream password_file("../data/" + user + "-password.txt");

	if (!password_file || !data_file) {
		std::cout << "User " << user << " does not exist.  Please create an account." << std::endl;
		return false;
	}

	string password;
	password_file >> password_;

	return true;
}


//------------------------------------------------------------------------------------

//InitializeThumbnails() referenced from: https://forum.openframeworks.cc/t/technique-to-generate-thumbnails-from-a-lot-of-videos/14804/3
void ofApp::InitializeThumbnails() {
	std::string videosFolder = "movies";
	ofDirectory dir;
	dir.allowExt("mp4");
	dir.listDir(videosFolder);

	ofVideoPlayer tmp;

	int column = 0;
	int row = 0;

	for (int i = 0; i < dir.size(); i++) {
		string videoPath = dir.getPath(i);
		ofFile file;
		file.open(ofToDataPath("thumbs/" + ofFilePath::getBaseName(videoPath) + ".jpg"), ofFile::ReadWrite, false);

		if (!file.exists()) {
			//for every video, skim to the middle
			tmp.loadMovie(videoPath);
			tmp.play();
			tmp.setPosition(0.25);
			tmp.setPaused(true);
			tmp.update();
			

			//create thumbnail from frame in middle of video
			ofImage img;
			img.setFromPixels(tmp.getPixelsRef());

			//resize the thumbnail
			float thumbWidth = 400;
			img.resize(thumbWidth, thumbWidth * (img.getHeight() / img.getWidth()));

			//save image in thumbnail folder
			img.saveImage("thumbs/" + ofFilePath::getBaseName(videoPath) + ".jpg");
		}
	}
}

//Initialized all ofImages with icons
void ofApp::InitializeImages() {
	//Playback background icon
	playback_background_ = ofImage("icons/background.png");
	playback_background_.setColor(ofColor(50, 50, 50));
	playback_background_.resize(ofGetWidth(), ICON_SIZE * 1.1);

	//Rating box background icon
	rating_box_background_ =  ofImage("icons/background.png");
	rating_box_background_.setColor(ofColor(50, 50, 50));
	rating_box_background_.resize(ofGetWidth() / 2, ofGetHeight() / 2);

	//Playback control icons
	play_icon_ = ofImage("icons/play.png");
	pause_icon_ = ofImage("icons/pause.png");
	forward_icon_ = ofImage("icons/forward.png");
	rewind_icon_ = ofImage("icons/rewind.png");
	back_icon_ = ofImage("icons/back.png");

	play_icon_.resize(ICON_SIZE, ICON_SIZE);
	pause_icon_.resize(ICON_SIZE, ICON_SIZE);
	forward_icon_.resize(ICON_SIZE, ICON_SIZE);
	rewind_icon_.resize(ICON_SIZE, ICON_SIZE);
	back_icon_.resize(0.9 * ICON_SIZE, 0.9 * ICON_SIZE);

	//Netflix logo
	netflix_logo_ = ofImage("icons/Netflix.png");
	float ratio = netflix_logo_.getHeight() / netflix_logo_.getWidth();
	int width = (ofGetWidth() * 5) / 10;
	netflix_logo_.resize(width, ratio * width);

	//Like and Dislike Icons
	like_icon_ = ofImage("icons/like.png");
	dislike_icon_ = ofImage("icons/dislike.png");

	like_icon_.resize(ICON_SIZE, ICON_SIZE);
	dislike_icon_.resize(ICON_SIZE, ICON_SIZE);

	//Login Screen
	login_screen_background_ = ofImage("icons/loginbackground.png");
}

//Displays the thumbnails after they have been initialized, also pilfers from loaded videos if there are any
void ofApp::DisplayThumbnails() {
	std::string thumbs_folder = "thumbs";
	ofDirectory dir;
	dir.allowExt("jpg");
	dir.listDir(thumbs_folder);

	int column = 0;
	int row = 0;

	ofImage img;

	int unit = ofGetWidth() / 31;
	int image_width = 4 * unit; //scales up width & height maintaining 16:9 ratio
	int image_height = 2.25 * unit;
	int horizontal_padding = unit;
	int vertical_padding = unit;

	for (int i = 0; i < dir.size(); i++) {
		string image_path = dir.getPath(i);
		ofFile file;
		file.open(ofToDataPath("movies/" + ofFilePath::getBaseName(image_path) + ".mp4"), ofFile::ReadWrite, false);

		if (file.exists()) {
			VideoObject vid = VideoObject(ofFilePath::getBaseName(image_path));
			for (auto video_object : loaded_video_objects_) {
				//If we have existing data, use it; otherwise, go with standard defaults
				if (video_object.getVideoFilepath() == vid.getVideoFilepath()) {
					//pilfer data from existing video
					vid.setRating(video_object.getRating());
					vid.setWatched(video_object.isWatched());
					vid.setPlaybackPosition(video_object.getVideoPlaybackPosition());
				}
			}

			//perform check to see if we have reached the end of a row
			if (column >= 6) {
				row++;
				column = 0;
			}
			
			//calculate next x and y
			int x = horizontal_padding + column * (image_width + horizontal_padding);
			int y = vertical_padding + ((ofGetHeight() / 10) + (netflix_logo_.getHeight())) +  row * (image_height + vertical_padding); //with logo
			//int y = vertical_padding + row * (image_height + vertical_padding);

			//draw image thumbnail and label using x and y coordinates
			img.load("thumbs/" + ofFilePath::getBaseName(image_path) + ".jpg");
			img.draw(x, y, image_width, image_height);

			string label = ofFilePath::getBaseName(image_path);
			std::replace(label.begin(), label.end(), '_', ' ');
			vid.setLabel(label);

			int x_pos = x + ((image_width - menu_label_.stringWidth(label)) / 2);
			int y_pos = y + image_height + menu_label_.getSize() + vertical_padding / 6;
			menu_label_.drawString(label, x_pos, y_pos);

			//place a rectangle behind each image since we can use ofRectangle.intersects() and rectangles hold position and dimensions
			ofRectangle rect = ofRectangle(x, y, image_width, image_height);

			bool already_contains_vid = false;
			for (auto pair : thumbnail_button_links) {
				VideoObject video = pair.second;
				if (vid.getVideoFilepath() == video.getVideoFilepath()) {
					already_contains_vid = true;
				}
			}
			if (!already_contains_vid) {
				thumbnail_button_links.push_back(std::make_pair(rect, vid));
			}

			//move to next column
			column++;
		}
	}
}

//Displays the Netflix Logo
void ofApp::DisplayNetflixLogo() {
	float ratio = netflix_logo_.getHeight() / netflix_logo_.getWidth();
	int width = (ofGetWidth() * 5) / 10;
	netflix_logo_.resize(width, ratio * width);
	int x = (ofGetWidth() - netflix_logo_.getWidth()) / 2;
	int y = ofGetHeight() / 10;
	netflix_logo_.draw(x, y); //optional netflix logo
}

//Displays the login input box, specifically for the username portion
void ofApp::DisplayUsernameInputBox(int width) {
	login_gui_->setVisible(true);
	login_input_box_->setHeight(100); //to change text size, edit ofxSmartFont.h at line 61, current size is 20
	login_input_box_->setTextUpperCase(false);
	login_input_box_->setWidth(width, width / 3);
}

void ofApp::DisplayCreateButton() {
	//ADD STUFF
}


void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e) {
	string input = e.text;
	if (current_state_ == GETTING_USERNAME) {
		if (ExistsUser(input)) {
			login_input_box_->setText("");
			current_state_ = GETTING_PASSWORD;
		}
		else {
			login_input_box_->setText("Could Not Find User: " + input);
			show_create_button_ = true;
		}
	} else if (current_state_ == GETTING_PASSWORD) {
		if (input == password_) {
			current_state_ = MENU_SCREEN;
		} else {
			login_input_box_->setText("Please Try Again...");
		}
	}
}