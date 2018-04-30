#include "video_object.h"


//constructor
VideoObject::VideoObject(string filepath) {
	image_filepath_ = ("thumbs/" + filepath + ".jpg");
	video_filepath_ = ("movies/" + filepath + ".mp4");
	playback_position_ = 0;
	rating_ = -1; //not watched
	watched_ = false;
}

//Getters and Setters
bool VideoObject::isWatched() {
	return watched_;
}

std::string VideoObject::getVideoFilepath() {
    return video_filepath_;
}

std::string VideoObject::getLabel() {
	return label_;
}

double VideoObject::getVideoPlaybackPosition() {
	return playback_position_;
}

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
