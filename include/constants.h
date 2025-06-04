#pragma once
#include "raylib.h"
#include <filesystem>

namespace BoardGame
{
	namespace paths
	{
		const std::filesystem::path gamesDirPath = "games";
		const std::filesystem::path gameDataTextFilePath = "game.txt";
		const std::filesystem::path gameFontsPath = "assets/fonts";
		const std::filesystem::path gameFontOpenSans = gameFontsPath / "OpenSans-Regular.ttf";
	}

	namespace constants
	{
		extern Font font;

		const unsigned int cameraMovementSpeed = 800;

		constexpr uint8_t playerColorsLength = 8;
		const Color playerColors[playerColorsLength] = {
			{255, 42, 42, 255},		// red
			{0, 155, 0, 255},		// green
			{42, 42, 255, 255},		// blue
			{255, 255, 42, 255},	// yellow
			{148, 42, 255, 255},	// purple
			{255, 148, 42, 255},	// orange
			{42, 255, 255, 255},	// turkoise
			{255, 42, 255, 255},	// pink
		};


		void loadFont();
	}
}