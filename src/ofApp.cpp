#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255, 255, 255);
	ofSetVerticalSync(true);

	gui_ = new ofxDatGui(ofxDatGuiAnchor::BOTTOM_LEFT);
	playback_scrubber_ = gui_->addSlider("Playback Slider", 0, 1);
	playback_scrubber_->setWidth(ofGetWidth(), 0);
	playback_scrubber_->setValue(0);

	video_.load("movies/Pats_Broncos_2013.mov");
	video_.play();

	is_paused_ = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (ofGetElapsedTimeMillis() - last_mouse_usage_ > 3000) {
		ofHideCursor();
	}

	video_.update();
	playback_scrubber_->setValue(video_.getPosition());
}

//--------------------------------------------------------------
void ofApp::draw(){
	// ofSetHexColor(0xFFFFFF);
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
	case 'i':
		//gui_->addButton("Click!");
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