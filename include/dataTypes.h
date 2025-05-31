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


	struct PlayerInfo
	{
		bool hasAccounts;
		int playerStartBalance;
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
		PlayerInfo playerInfo;
	};



	enum EntityType {
		TypeUnkown = 0,
		TypeEntity = 1,
		TypeGameInfo = 2,
		TypeStartMenuInfo = 3,
		TypePlayerInfo = 4
	};




}