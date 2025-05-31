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
		bool convertToBool(const std::string& str);
		Color convertHEXToRGB(std::string& hex);

		int abs(int value);
		int max(int a, int b);
		int min(int a, int b);

		Color brighten(Color color, float factor);
	}
}
