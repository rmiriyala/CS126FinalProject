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