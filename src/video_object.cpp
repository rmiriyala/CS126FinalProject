#include "video_object.h"


//Constructors

//Used only for loading
VideoObject::VideoObject() {
	video_filepath_ = ""; //used for comparison in pilfering
	watched_ = false;
	rating_ = -1;
	playback_position_ = 0;
}

VideoObject::VideoObject(string filepath) {
	image_filepath_ = ("thumbs/" + filepath + ".jpg");
	video_filepath_ = ("movies/" + filepath + ".mp4");
	playback_position_ = 0;
	rating_ = -1; //not watched
	watched_ = false;
}

//Getters
std::string VideoObject::getLabel() {
	return label_;
}

std::string VideoObject::getVideoFilepath() {
	return video_filepath_;
}

std::string VideoObject::getImageFilepath() {
	return image_filepath_;
}

bool VideoObject::isWatched() {
	return watched_;
}

double VideoObject::getVideoPlaybackPosition() {
	return playback_position_;
}

int VideoObject::getRating() {
	return rating_;
}

//Setters
void VideoObject::setLabel(std::string label) {
	label_ = label;
}

void VideoObject::setWatched(bool watched) {
	VideoObject::watched_ = watched;
}

void VideoObject::setPlaybackPosition(double position) {
	playback_position_ = position;
}

void VideoObject::setRating(int rating) {
	rating_ = rating;
}

void VideoObject::setVideoFilepath(string filepath) {
	video_filepath_ = filepath;
}

void VideoObject::setImageFilepath(string filepath) {
	image_filepath_ = filepath;
}


