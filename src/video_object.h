#include <string>
#include "ofMain.h"
#include "ofxDatGui.h"

class VideoObject {
private:
	std::string label_;
    std::string video_filepath_; //relative filepath used for loading video
	std::string image_filepath_; //relative filepath used for loading thumbnail
    bool watched_; //boolean flag indicating whether the user has watched this tv episode/movie yet
	int rating_; //int rating for like, dislike or not watched/completed
	double playback_position_ = 0; //stores the point the user left at for future loading
public:
	VideoObject(string filename);

    std::string getVideoFilepath();
	std::string getLabel();
	double getVideoPlaybackPosition();
    bool isWatched();

	void setLabel(std::string label);
    void setWatched(bool watched);
	void setPlaybackPosition(double position);
	void setRating(int rating);
};