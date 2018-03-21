# Quick Pitch

[![Build Status](https://travis-ci.org/magnus-gross/quickpitch.svg?branch=master)](https://travis-ci.org/magnus-gross/quickpitch)
[![codecov](https://codecov.io/gh/magnus-gross/quickpitch/branch/master/graph/badge.svg)](https://codecov.io/gh/magnus-gross/quickpitch)

Quick Pitch can be used to analyze audio pitch.

![alt tag](https://i.imgur.com/WX9AI8b.png)

# Build Instructions

## Dependencies

Quick Pitch requires:

* A C++ compiler with C++14 support
* make
* At least Qt 5.10
* The following Qt modules:
	- Qt Core (qt5-base)
	- Qt GUI (qt5-base)
	- Qt Quick (qt5-declarative)
	- Qt QML (qt5-declarative)
	- Qt SVG (qt5-svg)
	- Qt QUick Controls 2 (qt5-quickcontrols2)
	- Qt Graphical Effects (qt5-graphicaleffects)
	- Qt Charts (qt5-charts)
	- Qt Multimedia (qt5-multimedia)
* Aubio (Pulled as a submodule)
* Fluid (Pulled as a submodule)

## Building

First make sure, that you have pulled all submodules.
Either clone with the `--recursive` flag, or run `git submodule update --init` in the already cloned repo.

Then run in the quickpitch directory the following commands:

```bash
mkdir build
cd build
qmake ..
make
```
Once that building is finished, you can run the executable at `src/src`.

# Acknowledgements
- QuickPitch uses [aubio](https://github.com/aubio/aubio) for audio processing
- QuickPitch uses [fluid](https://github.com/lirios/fluid), which is a neat QML Material Design library.
