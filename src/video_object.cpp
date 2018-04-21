#include "video_object.h"


bool VideoObject::isWatched() {
    return watched_;
}

std::string VideoObject::getFilepath() {
    return video_filepath_;
}

void VideoObject::setWatched(bool watched) {
    VideoObject::watched_ = watched;
}

void VideoObject::initializeThumbnail() {
    ofVideoPlayer temp;
    temp.load(video_filepath_);
    temp.setPosition(0.50);
    thumbnail_image_.setFromPixels(temp.getPixelsRef());
    thumbnail_image_.saveImage(thumbnail_filepath_);
}
