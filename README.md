# CS 126 FinalProject

## Overview

My final project for CS 126 is a low-level version of Netflix that plays videos from a local data folder in the repository.  Users of this app can create a username and password and begin watching a variety of different videos, with the app providing recommendations on which video to watch next.  The app also keeps track of your playback position, so if you stop watching midway through, the next time you load that video, it will resume at the point you left off at.

## Installation Instructions (Windows 10)
- Install [Visual Studio](https://www.visualstudio.com/downloads/) and set it up. Instructions are [here](https://docs.microsoft.com/en-us/visualstudio/install/install-visual-studio).  Make sure to install the Windows SDK 8.1 option as well.
- Install [OpenFrameworks](http://openframeworks.cc/versions/v0.9.8/of_v0.9.8_vs_release.zip) and follow the setup instructions posted [here](http://openframeworks.cc/setup/vs/), including downloading the OpenFrameworks plugin for Visual Studio.  This app requires the [K-Lite Codec Pack](http://filehippo.com/download_klite_codec_pack/67445/) the site recommends.
- Navigate to of_v0.9.8_vs_release/examples and run one of the examples to check if the installation is correct; if not, revise both the Visual Studio installation and the OpenFrameworks installation.
- Install [ofxDatGui](https://github.com/braitsch/ofxDatGui) by following the instructions [here](http://braitsch.github.io/ofxDatGui/index.html#installation).
- Clone this repository and open it using projectGenerator.exe in the of_v0.9.8_vs_release folder you downloaded.  Be sure to add ofxGui and ofxDatGui as addons.
- Download the current 'Netflix' movies [here](https://drive.google.com/open?id=1KeIeFzZtkCg_7EnCCMs0Sz6a8fmJZrvl) and place them in a folder called 'movies' in your projects bin/data/ folder

## Running

- Compile the x32 release version in Visual Studio or use the .exe file
- Create a username and password
- Start watching videos!
