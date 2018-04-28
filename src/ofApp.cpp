#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255, 255, 255);
	ofSetVerticalSync(true);

	InitializeThumbnails();
	std::cout << "done" << std::endl;

	gui_ = new ofxDatGui(ofxDatGuiAnchor::BOTTOM_LEFT);
	playback_scrubber_ = gui_->addSlider("Playback Slider", 0, 1, 0);
	playback_scrubber_->setWidth(ofGetWidth(), 0);

}

//--------------------------------------------------------------
void ofApp::update(){

	if (current_state_ == MENU_SCREEN) {
		
	} else if (current_state_ == WATCHING_VIDEO) {
		if (ofGetElapsedTimeMillis() - last_mouse_usage_ > 3000) {
			ofHideCursor();
		}

		video_.update();
		playback_scrubber_->setValue(video_.getPosition());
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	// ofSetHexColor(0xFFFFFF);

	if (current_state_ == MENU_SCREEN) {
		drawMenuScreen();
	}
	if (current_state_ == WATCHING_VIDEO) {
		drawWatchingVideo();
	}
}

void ofApp::drawMenuScreen() {
	ofSetHexColor(0xFFFFFF);
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
	default:
		break;
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
	//will prevent mouse clicks not on slider from triggering pause
	if (y >= ofGetHeight() - playback_scrubber_->getHeight()) {
		playback_scrubber_->onSliderEvent(this, &ofApp::onSliderEvent);
	} else {
		TogglePause();
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
	video_.load("movies/Vince_Wilfork_Highlights.mp4"); // will need to replace with given filepath
	video_.play();
	is_paused_ = false;
}

//Referenced from: https://forum.openframeworks.cc/t/technique-to-generate-thumbnails-from-a-lot-of-videos/14804/3
void ofApp::InitializeThumbnails() {
	std::string videosFolder = "movies";
	ofDirectory dir;
	dir.allowExt("mov");
	dir.allowExt("mp4");
	dir.listDir(videosFolder);
	ofVideoPlayer tmp;

	for (int i = 0; i < dir.size(); i++) {
		string videoPath = dir.getPath(i);

		//my addition to check if it exists, speeds up program 
		ofFile file;
		file.open(ofToDataPath("thumbs/" + ofFilePath::getBaseName(videoPath) + ".jpg"), ofFile::ReadWrite, false);
		if (!file.exists()) {
			tmp.loadMovie(videoPath);
			tmp.play();
			tmp.setPosition(0.1);

			ofImage img;
			img.setFromPixels(tmp.getPixelsRef());

			float thumbWidth = 120;//change this for another thumb size
			img.resize(thumbWidth, thumbWidth * (img.getHeight() / img.getWidth()));

			img.saveImage("thumbs/" + ofFilePath::getBaseName(videoPath) + ".jpg");
		}

	}
}