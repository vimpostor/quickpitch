TEMPLATE = app

QT += quick quickcontrols2 qml multimedia charts
CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/../aubio/src

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    pitchdetector.cpp \
    pitchbuffer.cpp \
	util.cpp \
    pitchobj.cpp \
    aubiowrapper.cpp \
    settings.cpp

# aubio
QMAKE_CFLAGS += "-include $$_PRO_FILE_PWD_/compilerfix.h"
QMAKE_CXXFLAGS += "-include $$_PRO_FILE_PWD_/compilerfix.h"
HEADERS += compilerfix.h \
    aubiowrapper.h \
    settings.h
SOURCES += ../aubio/src/pitch/pitch.c \
	../aubio/src/fvec.c \
	../aubio/src/utils/log.c \
	../aubio/src/pitch/pitchyin.c \
	../aubio/src/spectral/phasevoc.c \
	../aubio/src/cvec.c \
	../aubio/src/pitch/pitchmcomb.c \
	../aubio/src/temporal/c_weighting.c \
	../aubio/src/pitch/pitchfcomb.c \
	../aubio/src/pitch/pitchschmitt.c \
	../aubio/src/pitch/pitchspecacf.c \
	../aubio/src/pitch/pitchyinfft.c \
	../aubio/src/temporal/filter.c \
	../aubio/src/mathutils.c \
	../aubio/src/spectral/fft.c \
	../aubio/src/lvec.c \
	../aubio/src/spectral/ooura_fft8g.c


RESOURCES += qml/qml.qrc

INCLUDEPATH += ../aubio/src

android {
	# Bundle Fluid QML plugins with the application
	ANDROID_EXTRA_PLUGINS = $$OUT_PWD/../fluid/qml

	# Android package sources
#	ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

macx {
	# Bundle Fluid QML plugins with the application
	APP_QML_FILES.files = $$OUT_PWD/../fluid/qml/Fluid
	APP_QML_FILES.path = Contents/MacOS
	QMAKE_BUNDLE_DATA += APP_QML_FILES
}

win32 {
	WINDEPLOYQT_OPTIONS = -qmldir $$OUT_PWD/../fluid/qml/Fluid
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$OUT_PWD/../fluid/qml

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    pitchdetector.h \
    pitchbuffer.h \
	util.h \
	pitchobj.h
