# Development

#### Setup Project Commit

Had multiple issues with git, namely using the ProjectGenerator and merging those files with the given [uiuc-sp18-cs126](https://github.com/uiuc-sp18-cs126/final-project-rmiriyala) repository.  Fixed these problems through the command line interface from git, though most subsequent commits have been completed via GitHub Desktop.

#### Video Player Commit

Many issues with the video player being able to play a file.  Began by receiving "ofDirectShowPlayer: Cannot load video of this file type..." error and eventually resolved this error by moving the video file into the bin/movies/.. relative path as well as installing a new codec pack, specifically the [12.1.0 version](https://dl2.filehippo.com/b1444920193b4174a2fbe98cac005f2b/K-Lite_Codec_Pack_1210_Full.exe?ttl=1524299126&token=e30fa08941b5a7c6f876bbe8b254ba59) since no other versions would work.

After these steps, the video player now loads and is able to load and play the [sample media](https://www.youtube.com/watch?v=yy_sHN0y3pM).
