#include <string>
#include "ofMain.h"
#include "ofxDatGui.h"

using std::string;

class VideoObject {
private:
	std::string label_;
	std::string video_filepath_; //relative filepath used for loading video
	std::string image_filepath_; //relative filepath used for loading thumbnail
	bool watched_; //boolean flag indicating whether the user has watched this tv episode/movie yet
	int rating_; //int rating for like, dislike or not watched/completed
	double playback_position_ = 0; //stores the point the user left at for future loading
public:
	VideoObject();
	explicit VideoObject(string filename);

	std::string getLabel();
	std::string getVideoFilepath();
	std::string getImageFilepath();
	bool isWatched();
	double getVideoPlaybackPosition();
	int getRating();

	void setLabel(std::string label);
	void setVideoFilepath(string filepath);
	void setImageFilepath(string filepath);
	void setWatched(bool watched);
	void setPlaybackPosition(double position);
	void setRating(int rating);
};