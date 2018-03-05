#ifndef UTIL_H
#define UTIL_H

#include <math.h>

namespace Util {
	template<typename T>
	int round(T arg) {
#ifdef ANDROID
		return static_cast<int>(arg + 0.5);
#else
		return std::round(arg);
#endif
	}

	template<typename T>
	constexpr T log(T arg) {
#ifdef ANDROID
		// TODO: Reimplement log, the shitty Android NDK does not provide it
		return 1;
#else
		return std::log(arg);
#endif
	}

	template<typename T>
	constexpr T log2(T arg) {
#ifdef ANDROID
		return Util::log(arg) / Util::log(2.f);
#else
		return std::log2(arg);
#endif
	}
}

#endif // UTIL_H
