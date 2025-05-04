#pragma once

#include <stdint.h>

namespace BoardGame
{
	struct GameInfo
	{
		uint16_t width;
		uint16_t height;
	};


	struct GameConfigData
	{
		GameInfo info;
	};


	enum EntityType {
		TypeUnkown = 0,
		TypeEntity = 1,
		TypeGameInfo = 2
	};

}