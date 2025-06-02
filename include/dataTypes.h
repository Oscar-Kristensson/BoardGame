#pragma once

#include "raylib.h"
#include <stdint.h>
#include <vector>
#include <filesystem>

namespace BoardGame
{
	struct GameInfo
	{
		uint16_t width;
		uint16_t height;
		Color backgroundColor;
	};


	struct CommonPlayerInfo
	{
		bool hasAccounts;
		int playerStartBalance;
	};

	struct PlayerInfo
	{
		int x;
		int y;
		Color color;
	};

	struct StartMenuInfo
	{
		Color backgroundColor;
	};

	struct GameEntityData
	{
		std::filesystem::path imagePath;
		int x;
		int y;
	};
	
	struct GameConfigData
	{
		GameInfo info;
		StartMenuInfo startMenuInfo;
		std::vector<BoardGame::GameEntityData> entities;
		CommonPlayerInfo commonPlayerInfo;
		std::vector<BoardGame::PlayerInfo> players;
	};



	enum EntityType {
		TypeUnkown = 0,
		TypeEntity = 1,
		TypeGameInfo = 2,
		TypeStartMenuInfo = 3,
		TypeCommonPlayerInfo = 4,
		TypePlayerInfo = 5
	};




}