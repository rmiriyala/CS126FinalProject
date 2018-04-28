#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(50, 50, 50);
	//ofSetVerticalSync(true);

	InitializeThumbnails();
	std::cout << "done" << std::endl;

	//Setup GUI
	gui_ = new ofxDatGui(ofxDatGuiAnchor::BOTTOM_LEFT);
	playback_scrubber_ = gui_->addSlider("Playback Slider", 0, 1, 0);
	playback_scrubber_->setWidth(ofGetWidth(), 0);
	gui_->setVisible(false);
}

//--------------------------------------------------------------
void ofApp::update(){

	if (current_state_ == MENU_SCREEN) {
		//do nothing
	} else if (current_state_ == WATCHING_VIDEO) {
		if (ofGetElapsedTimeMillis() - last_mouse_usage_ > 3000) {
			ofHideCursor();
		}

		video_.update();
		playback_scrubber_->setValue(video_.getPosition());
	}

}

//--------------------------------------------------------------
void ofApp::draw() {
	if (current_state_ == MENU_SCREEN) {
		drawMenuScreen();
	} else if (current_state_ == WATCHING_VIDEO) {
		drawWatchingVideo();
	}
}

void ofApp::drawMenuScreen() {
	DisplayThumbnails();
}

void ofApp::drawWatchingVideo() {
	int video_width = ofGetWidth();
	int video_height = ofGetHeight() - playback_scrubber_->getHeight();
	int x_position = 0;
	int y_position = 0;
	video_.draw(x_position, y_position, video_width, video_height);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (current_state_ == WATCHING_VIDEO) {
		float position = video_.getPosition();
		switch (key) {
		case 'k':
			TogglePause();
			break;
		case ' ':
			TogglePause();
			break;
		case 'l':
			position = (position + 0.01 > 1) ? 1 : position + 0.02; //will cap position to 1
			video_.setPosition(position);
			break;
		case 'j':
			position = (position - 0.01 < 0) ? 0 : position - 0.02; //will floor position at 0
			video_.setPosition(position);
			break;
		case OF_KEY_BACKSPACE:
			//break from video
		default:
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	last_mouse_usage_ = ofGetElapsedTimeMillis();
	ofShowCursor();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (current_state_ == MENU_SCREEN) {
		for (auto pair : thumbnail_button_links) {
			auto image = pair.first;
			if (x > image.x && x < (image.x + image.width) && y > image.y &&  y < (image.y + image.height)) {
				current_state_ = LOADING_VIDEO;
				LoadVideo(pair.second.getVideoFilepath());
				break;
			}
		}
	} else if (current_state_ == WATCHING_VIDEO) {
		//will prevent mouse clicks not on slider from triggering pause
		if (y >= ofGetHeight() - playback_scrubber_->getHeight()) {
			playback_scrubber_->onSliderEvent(this, &ofApp::onSliderEvent);
		}
		else {
			TogglePause();
		}
	}
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e) {
	video_.setPosition(e.value);
	//cout << "slider = " << e.value << endl; //debug statement
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	playback_scrubber_->setWidth(ofGetWidth(), 0);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::TogglePause() {
	is_paused_ = !is_paused_;
	video_.setPaused(is_paused_);
}

void ofApp::LoadVideo(std::string filepath) {
	gui_->setVisible(true);
	video_.load(filepath);
	video_.play();
	is_paused_ = false;
	current_state_ = WATCHING_VIDEO;
}

//Referenced from: https://forum.openframeworks.cc/t/technique-to-generate-thumbnails-from-a-lot-of-videos/14804/3
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
			tmp.setPosition(0.1);
			tmp.update();
			tmp.stop();
			

			//create thumbnail from frame in middle of video
			ofImage img;
			img.setFromPixels(tmp.getPixelsRef());

			//resize the thumbnail
			float thumbWidth = 400;
			img.resize(thumbWidth, thumbWidth * (img.getHeight() / img.getWidth()));

			//save image in thumbnail folder
			img.saveImage("thumbs/" + ofFilePath::getBaseName(videoPath) + ".jpg");
			std::cout << i << std::endl;
		}
	}
}

void ofApp::DisplayThumbnails() {
	std::string thumbs_folder = "thumbs";
	ofDirectory dir;
	dir.allowExt("jpg");
	dir.listDir(thumbs_folder);

	int column = 0;
	int row = 0;

	ofImage img;
	for (int i = 0; i < dir.size(); i++) {
		string image_path = dir.getPath(i);
		ofFile file;
		file.open(ofToDataPath("movies/" + ofFilePath::getBaseName(image_path) + ".mp4"), ofFile::ReadWrite, false);

		if (file.exists()) {
			img.load("thumbs/" + ofFilePath::getBaseName(image_path) + ".jpg");

			//when we get to the last column move to the next row
			if (column >= 6) {
				row++;
				column = 0;
			}

			int unit = ofGetWidth() / 30;
			int image_width = 4 * unit; //scales up width & height maintaining 16:9 ratio
			int image_height = 2.25 * unit;
			int horizontal_padding = unit;
			int vertical_padding = unit;
			
			int x = horizontal_padding + column * (image_width + horizontal_padding);
			int y = vertical_padding + row * (image_height + vertical_padding);

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

			//place a rectangle behind each image since we can use ofRectangle.intersects() and rectangles hold position and dimensions
			ofRectangle rect = ofRectangle(x, y, image_width, image_height);
			thumbnail_button_links.push_back(std::make_pair(rect, vid));

			//draw image thumbnail and label
			img.draw(x, y, image_width, image_height);

			string label = ofFilePath::getBaseName(image_path);
			std::replace(label.begin(), label.end(), '_', ' ');
			ofDrawBitmapString(label, x + (image_width - 8 * label.size()) / 2, y + image_height + (vertical_padding / 6));

			//move to next column
			column++;
		}
	}
}