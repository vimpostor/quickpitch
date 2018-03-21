#include "settings.h"


Settings &Settings::get()
{
	static Settings result;
	return result;
}
