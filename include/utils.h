#pragma once
#include "game.h"
#include <string>
#include <iostream>

namespace BoardGame
{
	namespace utils
	{
		bool convertToUint16(const std::string& str, uint16_t& result);
		bool convertToInt(const std::string& str, int& result);
		Color convertHEXToRGB(std::string& hex);

		int abs(int value);
	}
}
