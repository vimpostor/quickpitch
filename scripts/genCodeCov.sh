#!/usr/bin/env bash

mkdir build
cd build
qmake "QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage" "LIBS += -lgcov" ../tests/gtest
make
./gtest
for filename in `find ../src -name '*.cpp'`; do
	gcov -o . $filename
done
