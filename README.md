# OpenXaml

## Dependencies

OpenXaml relies upon the following dependencies:

* GLFW
* GLEW
* cmake 3.5
* zlib

These are built within the project for each path, but it adds the following dependencies:

* Visual C++ (Windows)
* xcode (Mac)
* xorg-dev (Linux)

## Building

Before building for the first time you need to run make in the Dependencies/glew/auto folder. This can be done from unix, cygwin, or WSL easily.

ZLIB error on windows with ninja: https://stackoverflow.com/questions/22705751/cannot-open-include-file-unistd-h-no-such-file-or-directory