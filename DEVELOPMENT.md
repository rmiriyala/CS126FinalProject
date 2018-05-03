# Development

#### (4/21) Setup Project Commit

Had multiple issues with git, namely using the ProjectGenerator and merging those files with the given [uiuc-sp18-cs126](https://github.com/uiuc-sp18-cs126/final-project-rmiriyala) repository.  Fixed these problems through the command line interface from git, though most subsequent commits have been completed via GitHub Desktop.

#### (4/21) Video Player Commit

Many issues with the video player being able to play a file.  Began by receiving "ofDirectShowPlayer: Cannot load video of this file type..." error and eventually resolved this error by moving the video file into the bin/movies/.. relative path as well as installing a new codec pack, specifically the [12.1.0 version](https://dl2.filehippo.com/b1444920193b4174a2fbe98cac005f2b/K-Lite_Codec_Pack_1210_Full.exe?ttl=1524299126&token=e30fa08941b5a7c6f876bbe8b254ba59) since no other versions would work.

After these steps, the video player now loads and is able to load and play the [sample media](https://www.youtube.com/watch?v=yy_sHN0y3pM).

#### (4/22) Preliminary Playback Controls and Release.exe Build Created

When running the program through the x86 debug or x64 debug from Visual Studio, the video would lag and the frame rate would be slightly unnatural; using a newly built release version (rather than debug) as suggested on the openFrameworks forum, considerably speeds up performance and eliminates the lag.

In addition, also added preliminary playback controls like the pause/play control, which can be toggled using the 'p' button on the keyboard.

#### (4/22) Added Additional Playback Controls

Simply added new controls to toggle pause function on keys 'k' and 'spacebar' and on mouse-click, removing the option for the 'p' button.  In addition, similar to YouTube, the 'j' button allows the user to seek backwards by a set interval (2% of the video's length) and the 'l' button allows the user to seek forward by that same amount.

#### (4/27) Added ofxDatGUI Library

Downloaded and added [ofxDatGUI](https://braitsch.github.io/ofxDatGui/index.html) library to the project using ProjectGenerator and including a header in ofApp.h.  Will implement a video scrubbing bar with their slider GUI interface.

#### (4/27) Added Video Scrubber

Created video scrubber with the ofxDatGUI library's slider tool; set the code up in a way that allows the playback slider to be updated by any change in the video's playback position including the jump-position 'j' and 'k' keys.  Also avoids the issue of toggling pause, which used to be the standard mouse-click action.

#### (4/27) Update GUI for Resized Window and Beginning to Add File System

Updated all GUI elements for a resized window, including the video scrubbing element. Also added the feature where if you leave the mouse stagnant (on the video screen), after 3 seconds it will disappear. Plan on extending this to the rest of the video interface. Thumbnail creation is successful, though loading the thumbnails is proving to be seriously difficult- only getting black squares (correct size and dimensions) instead of the loaded image.  In the filesystem (windows explorer), these images in the location they are stored bin/data/thumbs appear to be working fine.

#### (4/27) Fixed Thumbnail Load Issue

The thumbnail load issue stemmed from ofBackground being displayed over the object and being displayed at RGB(0, 0, 0).  After changing the location of where the program sets ofBackground, the problem was resolved and the image files showed up as expected.  After a bit of resizing, the images now are displayed properly and resize with the window, if necessary.

#### (4/27) Added ofRectangle Objects, Makes Thumbnails Clickable

Added ofRectangle objects (because they store x-position, y-position, width and height) and programmed the on-click methods for these rectangles to load the video filepath that is embedded in the data pair.  Later plan on changing each rectangle object to link to a video object.

#### (4/28) Implemented GUI Video Selection With Objects

Now have a VideoObject to represent the video, which will allow it to save the image/video filepath, whether it was watched, the rating, and the playback position of the video.  The user class, which has yet to be created, is planned to hold an vector of video objects (currently held in ofApp) and will be able to see/recall their preferences and watch times based on their history.

#### (4/28) Added Video Closing System

The video closing system has been implemented, but the saving of the time is not working; will probably look into what is going wrong, best guess at this point is there may be a problem with copying and I will have to directly change the object using a memory address in the future.

#### (4/29) Added and Implemented All Playback Controls on Interface

Added a graphical interface for the playback controls, including the pause, play, forward, rewind and back buttons.  This was done using the ofImage class for the buttons, after multiple failed attempts to continue to use the ofxDatGUI class, and by placing ofRectangles behind them in the same way the thumbnail buttons are used.

The playback controls will now disappear along with the mouse after a 2.5 second delay that is traced by the global variable *last_mouse_usage_*; on a side note, the playback controls from the keyboard also will force the display of this interface, though that can be (and may be) removed by deleting the call to *last_mouse_usage_* at the end of *TogglePause()*, *Forward()*, and *Rewind()*.

#### (4/29) Fixed Bugs Related to Thumbnail Creation, Added Proper Labels

Using [ofTrueTypeFont](http://halfdanj.github.io/ofDocGenerator/ofTrueTypeFont.html), I changed the bitmap string drawings for labels into correctly sized labels (including one in the playback control interface) so the user is now able to read the labels without strain.  In addition, added an optional Netflix logo that can be removed by commenting and uncommenting two statements of code.

#### (4/30) Changed Playback Controls Interface

Since the video was stretched to fill the entire gap between the playback control bars, it left the user uncomfortable when watching, having to adjust to different video ratios; to compensate, I maintained the same ratio amongst the height and width and centered the video, so black bars will now appear to either side when playing.  All videos continue to play in the 16:9 ratio.

#### (4/30) Window Resizing for the Playback Screen; Reformatted Code

Changed the way things were being drawn so that on window resizing (such as going full screen) the video player would compensate and not look smushed or with some parts out of phase and misaligned.  In addition, reformatted the code to provide a better separation of the GUI features and the update features.

#### (4/30) Implemented a Like/Dislike System

After each video is finished, the user will now be forced to select a rating for the video, being either like or dislike, and the program will save this to the VideoObject's data.  The program will not force users to continually re-rate the program if they are rewatching a particular video.  The like/dislike system was implemented in a very similar way to the playback control and required the creation of a few more states in the enum of possible states.

#### (4/30) Added Label to the Rating Screen

Added a label to the rating screen using [ofTrueTypeFont](http://openframeworks.cc/documentation/graphics/ofTrueTypeFont/), which allowed me to resize the text and center it exactly.  Applied these principles to all labels being used and resized them appropriately so they were easier to see.

#### (5/1) Restructured Code and Added Comments

Had to restructure the code and add comments since this file was now getting very large. In addition, began laying the groundworks for the load and delete system.

#### (5/1) Implemented Load/Save Mechanism

A few issues arose when creating this system.  After multiple failed attempts to use ofFile, which wouldn't let me write to the directory I wanted (or any directory for that matter), I switched to the standard if/ofstream, which worked fine.  When saving, I discovered that thumbnail_button_links kept adding elements each time draw was called, so I built a quasi '.contains()' method that checked if a video object already existed in the vector before adding it again (since draw is called about 60 times a second, this became a real issue when 700+ objects were being saved to a file).

In addition, the filepath refused to be saved correctly when using the >> operator, so I used a getLine() call instead and had to crop the beginning parse space by calling string::substr

#### (5/1) Added Login Functionality

Login screen GUI added, but had to dig through and edit the core of ofxdatGui in order to create a setHeight() function, since the original height being used was a wrapper around size 12 font.  In addition had to dig through ofxSmartFont to change the font height constant.

Added new state progression so the user must login or create a username before accessing the app; when the user wants to create a new username, they must fail first, a button will appear, and they can click that and follow instructions to be added to the database.  The user's data file is saved after every time they watch a video and their password is saved every time the data is saved.

#### (5/2) Fixed Login/Creation Bugs:

When the input field was blank, the computer was processing too fast and using those blank fields as the username and password.  Also for error messages displayed in the text input, like "try again..." it would save that.  Now, I built in a defense by checking basic username and password characteristics such as they must have positive length, be distinct from each other and contain no spaces.

#### (5/2) Fixed Bug for Playback Slider:

Not working for mouse-click directly on the slider; after looking into the ofxDatGui class, realized that because I set the focus (in a different gui, though for some reason it still affected this one) on the login_box, it would not work; unset the focus from login_box after use was over and now works most of the time.

#### (5/2) Created Recommendation System:

Built a recommendation system that takes the other users and generates a fraction of how well they represent you.  Then, the program builds an aggregate data list for each video, with a vector for all other user's preferences.  By combining these ratings as well as how well the current user matches other users' preferences, the computer generates probabilities (not in the standard 0-1 scale) on what the user will like and returns the string of the filepath to the video with the greatest probability.  Difficulties in creation led to object structure, but using a vector and map allowed me to do this most easily, after experimenting with multimaps and vectors of pairs.

The recommendation system is very inaccurate with only one other user, but quickly gains accuracy when more users are added and those users' preferences vary.

#### (5/2) Updates to Style and Comments

Updated style elements; decided to leave all openFrameworks functions as is in terms of naming since that is the standard for openFrameworks.  All general non-openFrameworks functions I have created however, have been named with the appropriate conventions.  In addition, updated comments for each function with more descriptive and accurate insights into the code.
