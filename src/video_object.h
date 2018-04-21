#include <string>

class VideoObject {
private:
    std::string video_filepath_; //relative filepath used for loading video
    std::string thumbnail_filepath_; //relative filepath used for loading thumbnail image
    ofImage thumbnail_image_; //thumbnail image used for selecting tv episode/movie title
    bool watched_; //boolean flag indicating whether the user has watched this tv episode/movie yet
public:
    std::string getFilepath();
    bool isWatched();
    void setWatched(bool watched);

    void initializeThumbnail();
};