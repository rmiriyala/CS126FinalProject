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

void VideoObject::initializeThumbnails() {
    /* ofVideoPlayer temp;
    temp.load(video_filepath_);
    temp.setPosition(0.50);
    thumbnail_image_.setFromPixels(temp.getPixelsRef());
    thumbnail_image_.saveImage(thumbnail_filepath_); */

	//Referenced from:
	//https://forum.openframeworks.cc/t/technique-to-generate-thumbnails-from-a-lot-of-videos/14804/3
	string videosFolder = "movies";
	ofDirectory dir;
	dir.allowExt("mov");//change this to use different files. Duplicate this line to add more filetypes.
	dir.allowExt("mp4");
	dir.listDir(videosFolder);	
	ofVideoPlayer tmp;
	for (int i = 0; i < dir.size(); i++) {
		string videoPath = dir.getPath(i);
		tmp.loadMovie(videoPath);
		tmp.play();
		tmp.setPosition(0.1);
		img.setFromPixels(tmp.getPixelsRef());
		float thumbWidth = 120;//change this for another thumb size
		img.resize(thumbWidth, thumbWidth * (img.getHeight() / img.getWidth()));
		img.saveImage("thumbs/" + ofFilePath::getBaseName(videoPath) + ".jpg");
	}
}
