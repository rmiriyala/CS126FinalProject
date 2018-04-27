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

#### (4/27) Added ofDatGUI Library

Downloaded and added ofDatGUI library to the project using ProjectGenerator and including a header in ofApp.h.  Will implement a video scrubbing bar with their slider GUI interface.

#### (4/27) Added Video Scrubber

Created video scrubber with the ofDatGUI library's slider tool; set the code up in a way that allows the playback slider to be updated by any change in the video's playback position including the jump-position 'j' and 'k' keys.  Also avoids the issue of toggling pause, which used to be the standard mouse-click action.
