#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(50, 50, 50);

	InitializeThumbnails();
	std::cout << "loading thumbnails...done" << std::endl;

	InitializeIcons();
	std::cout << "loading icons...done" << std::endl;

	//Setup GUI
	gui_ = new ofxDatGui(ofxDatGuiAnchor::BOTTOM_LEFT);

	//Setup Playback Scrubber
	playback_scrubber_ = gui_->addSlider("Playback Slider", 0, 1, 0);
	playback_scrubber_->setWidth(ofGetWidth(), 0);
	playback_scrubber_->setBorderVisible(false);

	//Setup Labels
	video_label_.load(OF_TTF_SANS, 40);
	menu_label_.load(OF_TTF_SANS, 25);

	//Hide GUIs
	gui_->setVisible(false);
}

//--------------------------------------------------------------
void ofApp::update() {
	if (current_state_ == MENU_SCREEN) {
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

//--------------------------------------------------------------
void ofApp::draw() {
	if (current_state_ == MENU_SCREEN) {
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

//ALL GOOD
void ofApp::drawMenuScreen() {
	ofBackground(50, 50, 50);
	DisplayLogo();
	DisplayThumbnails();
}

//ALL GOOD
void ofApp::drawVideoFull() {
	int video_width = ofGetWidth();
	int video_height = ofGetHeight();
	int x_position = 0;
	int y_position = 0;
	video_.draw(x_position, y_position, video_width, video_height);
}

//ALL GOOD
void ofApp::drawVideoSmall() {
	ofBackground(0, 0, 0);
	int video_height = ofGetHeight() - (2.2 * ICON_SIZE) - (playback_scrubber_->getHeight());
	int video_width = video_height * DISPLAY_RATIO;
	int x_position = (ofGetWidth() - video_width) / 2; //centers the video
	int y_position = 1.1 * ICON_SIZE;
	video_.draw(x_position, y_position, video_width, video_height);
}

//ALL GOOD
void ofApp::drawPlaybackControls() {
	gui_->setVisible(true);

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

//ALL GOOD
void ofApp::hidePlaybackControls() {
	gui_->setVisible(false);
	//as long as we don't explicitly draw the rest of the controls, they won't show up
}

//IN PROGRESS
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

		//Draw Like Button
		x = (ofGetWidth() - 2 * like_icon_.getWidth()) / 3;
		y = y + rating_box_background_.getHeight() - like_icon_.getHeight();
		like_icon_.draw(x, y);
		like_button_ = ofRectangle(x, y, like_icon_.getWidth(), like_icon_.getHeight());

		//Draw Dislike Button
		x = (2 * (ofGetWidth() - 2 * like_icon_.getWidth())) / 3;
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

//ALL GOOD
void ofApp::drawClosingScreen() {
	ofShowCursor();
	drawMenuScreen();
	current_state_ = MENU_SCREEN;
}

//OPENFRAMEWORKS ACTIONS

//ALL GOOD
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

//ALL GOOD
void ofApp::mouseMoved(int x, int y) {
	last_mouse_usage_ = ofGetElapsedTimeMillis();
}

//WORK IN PROGRESS - LIKE/DISLIKE BUGGY
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
					std::cout << "Liked" << std::endl;
					break;
				case 1:
					thumbnail_button_links.at(current_video_object_).second.setRating(0);
					break;
				default:
					break;
				}
				std::cout << "IF BREAK" << std::endl;
				break;
			}
		}
		std::cout << "state changed" << std::endl;
		current_state_ = CLOSING_VIDEO;
	}
}

//ALL GOOD
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e) {
	video_.setPosition(e.value);
}

//ALL GOOD
void ofApp::mouseExited(int x, int y) {
	last_mouse_usage_ = ofGetElapsedTimeMillis() - 2500; //once the mouse leaves, trigger the hiding of playback controls
}

//WORK IN PROGRESS -- ACCEPTABLE FOR NOW
void ofApp::windowResized(int w, int h) {
	playback_scrubber_->setWidth(ofGetWidth(), 0);
}

	
//VIDEO PLAYING CONTROLS -- ALL GOOD
void ofApp::TogglePause() {
	float position = video_.getPosition();
	is_paused_ = !is_paused_;
	video_.setPaused(is_paused_);
	
	if (current_state_ == USING_PLAYBACK_CONTROLS) {
		last_mouse_usage_ = ofGetElapsedTimeMillis();
	}
}

void ofApp::Forward() {
	float position = video_.getPosition();
	position = (position + 0.01 > 1) ? 1 : position + 0.02; //will cap position to 1
	video_.setPosition(position);

	if (current_state_ == USING_PLAYBACK_CONTROLS) {
		last_mouse_usage_ = ofGetElapsedTimeMillis();
	}
}

void ofApp::Rewind() {
	float position = video_.getPosition();
	position = (position - 0.01 < 0) ? 0 : position - 0.02; //will floor position at 0
	video_.setPosition(position);

	if (current_state_ == USING_PLAYBACK_CONTROLS) {
		last_mouse_usage_ = ofGetElapsedTimeMillis();
	}
}


//LOADING AND CLOSING -- ALL GOOD
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

void ofApp::CloseVideo(VideoObject &video) {
	current_state_ = CLOSING_VIDEO;
	video.setPlaybackPosition(video_.getPosition());
	if (video_.getPosition() > 0.99) {
		video.setPlaybackPosition(0);
	}
	video_.stop();

}

//INITIALIZATION
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

void ofApp::InitializeIcons() {
	//Playback control icons
	playback_background_ = ofImage("icons/background.png");
	playback_background_.setColor(ofColor(50, 50, 50));
	playback_background_.resize(ofGetWidth(), ICON_SIZE * 1.1);

	rating_box_background_ =  ofImage("icons/background.png");
	rating_box_background_.setColor(ofColor(50, 50, 50));
	rating_box_background_.resize(ofGetWidth() / 2, ofGetHeight() / 2);

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
	logo_ = ofImage("icons/Netflix.png");
	float ratio = logo_.getHeight() / logo_.getWidth();
	int width = (ofGetWidth() * 5) / 10;
	logo_.resize(width, ratio * width);

	//Like and Dislike Icons
	like_icon_ = ofImage("icons/like.png");
	dislike_icon_ = ofImage("icons/dislike.png");

	like_icon_.resize(ICON_SIZE, ICON_SIZE);
	dislike_icon_.resize(ICON_SIZE, ICON_SIZE);
}


//DISPLAY IMAGES ON MENU SCREEN
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
			img.load("thumbs/" + ofFilePath::getBaseName(image_path) + ".jpg");

			//Add video objects to our array if they aren't already there
			VideoObject vid = VideoObject(ofFilePath::getBaseName(image_path));
			bool contains_video = false;
			for (auto video : video_objects_) {
				if (video.getVideoFilepath() == "movies/" + ofFilePath::getBaseName(image_path) + ".mp4") {
					contains_video = true;
				}
			}
			if (!contains_video) {
				video_objects_.push_back(vid);
			}

			//perform check to see if we have reached the end of a row
			if (column >= 6) {
				row++;
				column = 0;
			}
			
			//calculate next x and y
			int x = horizontal_padding + column * (image_width + horizontal_padding);
			int y = vertical_padding + ((ofGetHeight() / 10) + (logo_.getHeight())) +  row * (image_height + vertical_padding); //with logo
			//int y = vertical_padding + row * (image_height + vertical_padding);

			//draw image thumbnail and label using x and y coordinates
			img.draw(x, y, image_width, image_height);

			string label = ofFilePath::getBaseName(image_path);
			std::replace(label.begin(), label.end(), '_', ' ');
			vid.setLabel(label);

			int x_pos = x + ((image_width - menu_label_.stringWidth(label)) / 2);
			int y_pos = y + image_height + menu_label_.getSize() + vertical_padding / 6;
			menu_label_.drawString(label, x_pos, y_pos);

			//place a rectangle behind each image since we can use ofRectangle.intersects() and rectangles hold position and dimensions
			ofRectangle rect = ofRectangle(x, y, image_width, image_height);
			thumbnail_button_links.push_back(std::make_pair(rect, vid));

			//move to next column
			column++;
		}
	}
}

void ofApp::DisplayLogo() {
	int x = (ofGetWidth() - logo_.getWidth()) / 2;
	int y = ofGetHeight() / 10;
	logo_.draw(x, y); //optional netflix logo
}
