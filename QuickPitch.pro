TEMPLATE = app

QT += quick quickcontrols2 qml multimedia charts
CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/aubio/src

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += src/main.cpp \
	src/pitchdetector.cpp \
	src/pitchbuffer.cpp \
	src/util.cpp \
	src/pitchobj.cpp \
	src/aubiowrapper.cpp \
	src/settings.cpp

# aubio
QMAKE_CFLAGS += "-include $$_PRO_FILE_PWD_/src/compilerfix.h"
QMAKE_CXXFLAGS += "-include $$_PRO_FILE_PWD_/src/compilerfix.h"
HEADERS += src/compilerfix.h \
    src/aubiowrapper.h \
    src/settings.h
SOURCES += aubio/src/pitch/pitch.c \
	aubio/src/fvec.c \
	aubio/src/utils/log.c \
	aubio/src/pitch/pitchyin.c \
	aubio/src/spectral/phasevoc.c \
	aubio/src/cvec.c \
	aubio/src/pitch/pitchmcomb.c \
	aubio/src/temporal/c_weighting.c \
	aubio/src/pitch/pitchfcomb.c \
	aubio/src/pitch/pitchschmitt.c \
	aubio/src/pitch/pitchspecacf.c \
	aubio/src/pitch/pitchyinfft.c \
	aubio/src/temporal/filter.c \
	aubio/src/mathutils.c \
	aubio/src/spectral/fft.c \
	aubio/src/lvec.c \
	aubio/src/spectral/ooura_fft8g.c


RESOURCES += src/qml/qml.qrc

INCLUDEPATH += aubio/src

android {
	# Android package sources
#	ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/pitchdetector.h \
    src/pitchbuffer.h \
	src/util.h \
	src/pitchobj.h

TARGET = QuickPitch
