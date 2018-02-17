#!/usr/bin/env bash

ci_env=`bash <(curl -s https://codecov.io/env)`
docker run $ci_env -t --rm=true base/archlinux /bin/sh -c "pacman -Syu --noconfirm make gcc git qt5-base qt5-declarative qt5-svg qt5-quickcontrols2 qt5-graphicaleffects qt5-multimedia aubio gtest gmock && git clone --recursive https://github.com/magnus-gross/quickpitch.git && cd quickpitch && scripts/build.sh && scripts/clean.sh && scripts/genCodeCov.sh && cd build && ../scripts/uploadCodeCov.sh"
