project(quickpitch)
cmake_minimum_required(VERSION 3.18)
set(QT_MIN_VERSION "5.15")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (UNIX AND NOT APPLE)
	set(LINUX ON)
endif()

list(APPEND QT_MODULES Core Qml Quick QuickControls2 Multimedia Charts)
find_package(Qt5 "${QT_MIN_VERSION}" COMPONENTS ${QT_MODULES} REQUIRED)

include_directories(
	"src"
	"aubio/src"
)

# aubio
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -include ${CMAKE_SOURCE_DIR}/src/compilerfix.h")
file(GLOB AUBIO_SRCS
	"aubio/src/pitch/pitch.c"
	"aubio/src/fvec.c"
	"aubio/src/utils/log.c"
	"aubio/src/pitch/pitchyin.c"
	"aubio/src/spectral/phasevoc.c"
	"aubio/src/cvec.c"
	"aubio/src/pitch/pitchmcomb.c"
	"aubio/src/temporal/c_weighting.c"
	"aubio/src/pitch/pitchfcomb.c"
	"aubio/src/pitch/pitchschmitt.c"
	"aubio/src/pitch/pitchspecacf.c"
	"aubio/src/pitch/pitchyinfft.c"
	"aubio/src/pitch/pitchyinfast.c"
	"aubio/src/temporal/filter.c"
	"aubio/src/mathutils.c"
	"aubio/src/spectral/fft.c"
	"aubio/src/lvec.c"
	"aubio/src/spectral/ooura_fft8g.c"
)


file(GLOB_RECURSE SRCS "src/*.cpp")
file(GLOB_RECURSE HDRS "src/*.h")

file(GLOB_RECURSE RSRC "src/*.qrc")

if (CMAKE_BUILD_TYPE MATCHES Release)
	find_package(Qt5QuickCompiler)
	qtquick_compiler_add_resources(RESOURCES ${RSRC})
else()
	qt5_add_resources(RESOURCES ${RSRC})
endif()

add_executable(${PROJECT_NAME} ${SRCS} ${AUBIO_SRCS} ${RESOURCES})
set(QT_PREFIXED_MODULES ${QT_MODULES})
list(TRANSFORM QT_PREFIXED_MODULES PREPEND "Qt5::")
target_link_libraries(${PROJECT_NAME} ${QT_PREFIXED_MODULES})
