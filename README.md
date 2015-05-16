# Glidenote
A simple app that slides out from the edge of the screen for note taking.

Based on the premise of Pierre Châtel's sidenote application for Mac OS X 10.6 and older, this has a quick notepad slide in from off the screen when needed, and disappear when not.

This has been made with QT, & LibQxT, and coded in C++. The idea is to have a cross platform app, so users can have the same workflow, even if they hop between systems.

I would like to thank Pierre Châtel for developing the original sidenote, as well as Laurent Baumann for the design. Also, without the Qt Project, and the guys at #qt, I'd have probably given up again on ever having something like this in my life again. Also, I'd like to thank simplenote and Notational Velocity for making me remember how handy a good note taking app could be, and getting me back on the path for doing this, after a few failed attempts in RealBASIC/Mojo and other languages.

# Build requirements and procedure

## Introduction

At the current time, it is required to have QT 4.8.5 or newer. Will also build and work with QT 5.1. Also required is LibQxT 0.6, for the GlobalShortcut? that operates the code for the hotkey. These should already be available for most Linux distributions. QT has packages for various systems at http://qt-project.org/downloads/. LibQxT's source is available from http://libqxt.org.

I do have to note that LibQxT is difficult to build on some systems, and making sure you have these libraries installed and functioning is your responsibility. I cannot provide support for these libraries.

If you have an recommendations for library additions or replacements, please submit your thoughts on the matter. I am not married to anything, provided it doesn't require a complete rebuild from scratch.

## Details
At this point the build process should consist of 3 commands

* qmake -project
* qmake
* make

# To Do
This is basically a list of things I have planned for eventually doing, in no particular order.

* ~~Allow syncing with Simplenote.~~
* Icons.
* About screen.
* Migrate to a toolbar instead of file menu, so is more crossplatform friendly.
* Build packages for i386/x86_64 debian, Mac OS X, and Windows.
* Configuration options page.
* ~~Allow docking to different areas of the screen.~~
* Options for adjusting the window size (use percentage based).
* Options for setting the hotkey.
* ~~Allowing the markup that Simplenote allows.~~
* ~~Making linewrap optional.~~
* ~~Break out the scaling code into a separate function, so it could be called each time the window is made to appear (may potentially cause fewer glitches when shifting screen resolutions, and thus could in theory allow it to be used for games.~~


## Maybe
These are items that may or may not be implemented, depending on interest, time, and difficulty.

* Mouseover hotzone for triggering.
* Fullscreen toggling, for those wanting it to use it as an editor and jump between reference and code views.
* Toggling the always on top setting of the window
* Transparency of the window.
* Coloring backgrounds of different notes.
