# Project Proposal

#### The Idea
I plan on creating a program that will function, in essence, like Netflix.  The user will be able to play movies or tv episodes from a selected list of titles and have access to playback controls (such as pause, play, forward, rewind, etc.) using the application.

#### Implementation
In order to do this, I will implement the [ofVideoPlayer library](http://openframeworks.cc/documentation/video/ofVideoPlayer/), which allows for video playback volume and framerate controls.  The player will be activated when the user clicks on a specific title, and will display info about the particular title (year made, type, etc.) as well as the current playback position (whether the user has started, is some number of minutes in, etc.).  Upon a second click, the user can then choose to resume playback from this point or begin play from the beginning.

For the controls, play, pause, forward and rewind are pretty much covered by the [ofVideoPlayer library](http://openframeworks.cc/documentation/video/ofVideoPlayer/), but I plan on adding a 10 second frame skip, similar to what YouTube has with the double tap or L button.

If the user is watching a tv series (one that has multiple consecutive episodes available on the app), I plan on having the player remember the last one watched and highlight or bolden the next unwatched episode in the series for ease of use.

OpenFrameworks has many tutorials on loading and playing videos, such as [this one](http://openframeworks.cc/learning/04_video/load_and_play_video/) and I figure accessing information on how to accomplish this task will not be too difficult.

#### File Hosting
In order for this app to function, it will need access to a collection of movies and/or tv episodes.  To do this, I plan on using previously stored videos on local storage, or if possible, streaming from some exterior site, though libraries for this task are sparse.

## *Amendment II*

#### Recommendation System

Now, using pre-collected data from 10 "users" (will gather data through a survey), I will build 10 unique user profiles.  Then, using all current likes and dislikes from the current user's profile, the program will recommend what he/she is most likely to enjoy watching next as a result of their previous likes. It will do this by fitting the user to each of the compiled user-profiles (with percentages, e.g. 50% match with User 1, 25% User 2, 25% User 3) and matching their opinions of each unwatched movie to the current user (e.g. if Users 1 and 2 like Movie X, and User 3 does not, (((.50)(1) + (.25)(1) + (.25)(0)) / 1) = 75% chance of liking the show).  The program will scan each of these probabilities and return the one with the highest chance of the user liking it.

*Login System*

If possible, I would extend this functionality to allow the creation of different users of the program, each with their own user-profile, and with custom recommendations based on the other n-1 users preferences using the same logic as the standard recommendation system; in theory, this would result in infinite scalability and a more accurate recommmendation than that of one using just 10 base users.
