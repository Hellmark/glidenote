# Introduction #

At the current time, it is required to have QT 4.8.5 or newer. Will also build and work with QT 5.1. Also required is LibQxT 0.6, for the GlobalShortcut that operates the code for the hotkey. These should already be available for most Linux distributions. QT has packages for various systems at http://qt-project.org/downloads/. LibQxT's source is available from http://libqxt.org.

I do have to note that LibQxT is difficult to build on some systems, and making sure you have these libraries installed and functioning is your responsibility. I cannot provide support for these libraries.

If you have an recommendations for library additions or replacements, please submit your thoughts on the matter. I am not married to anything, provided it doesn't require a complete rebuild from scratch.


# Details #

At this point the build process should consist of 3 commands
  * qmake --project
  * qmake
  * make