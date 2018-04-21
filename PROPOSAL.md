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

### *Amendment*
In order to add further complexity to this assignment, I have decided to add a speech recognition component using the library [Voce](http://voce.sourceforge.net/) and will use the speech recognition to either have the user be able to voice-control media playback or to search for titles amongst the collection that the app offers.
