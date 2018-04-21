#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255, 255, 255);
	ofSetVerticalSync(false);

	video.load("movies/Pats_Broncos_2013.mov");
	video.play();

	is_paused = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	video.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	// ofSetHexColor(0xFFFFFF);
	int video_width = ofGetWidth();
	int video_height = ofGetHeight();
	int x_position = 0;
	int y_position = 0;
	video.draw(x_position, y_position, video_width, video_height);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	float position = video.getPosition();

	switch (key) {
	case 'k':
		TogglePause();
		break;
	case ' ':
		TogglePause();
		break;
	case 'l':
		position = (position + 0.01 > 1) ? 1 : position + 0.02; //will cap position to 1
		video.setPosition(position);
		break;
	case 'j':
		position = (position - 0.01 < 0) ? 0 : position - 0.02; //will floor position at 0
		video.setPosition(position);
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
	TogglePause();
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
	is_paused = !is_paused;
	video.setPaused(is_paused);
}