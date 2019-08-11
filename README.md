# OpenXaml

OpenXaml is a cross platform GUI renderer that takes xml as input. It utilized OpenGL for rendering and is targeting the [Xaml Standard](https://github.com/Microsoft/xaml-standard) spec. Currently the project only supports basic rectangles, text blocks, buttons, and grids.

## Building

Building OpenXaml requires the cmake build tool. Libraries it utilizes are downloaded to build with the project. These include

* GLFW
* GLAD
* xerces-c
* Freetype

GLFW adds a dependency on Visual C++ (Windows), xcode (OSX), or xorg-dev (Linux).

## Building applications

Currently the project is very early in development. Cmake files are provided by the installation that should allow for the building of your own xaml files through the AddXamlSources cmake function. Note, you have to include the OpenXaml.cmake file. The installer is still a work in progress and untested, so I advise building as part of the source for the moment. The Sample directory contains a barebones example project.