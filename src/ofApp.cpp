#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255, 255, 255);
	ofSetVerticalSync(true);

	gui_ = new ofxDatGui(ofxDatGuiAnchor::BOTTOM_LEFT);
	playback_scrubber_ = gui_->addSlider("", 0, 1);
	playback_scrubber_->setWidth(3000, 0);
	playback_scrubber_->setValue(0);

	video_.load("movies/Pats_Broncos_2013.mov");
	video_.play();

	is_paused_ = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	video_.update();
	playback_scrubber_->setValue(video_.getPosition());
}

//--------------------------------------------------------------
void ofApp::draw(){
	// ofSetHexColor(0xFFFFFF);
	int video_width = ofGetWidth();
	int video_height = ofGetHeight();
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

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	/*if (click_on_slider_ - video_.getPosition() > 0.01 || click_on_slider_ - video_.getPosition() < 0.01) {
		video_.setPosition(click_on_slider_);
	} else {
		TogglePause();
	}*/
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
	click_on_slider_ = e.value;
	cout << "the new value of the slider = " << e.value << endl;
	//cout << "the new scale of the slider = " << e.scale << endl;
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