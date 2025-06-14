#pragma once

#include "raylib.h"
#include <stdint.h>
#include <vector>
#include <filesystem>
#include <string>

namespace BoardGame
{
	enum TextAlignment
	{
		Left,
		Centered,
		Right
	};

	struct SharedTextureInfo
	{
		std::filesystem::path path;
		std::string stringID;
	};


	struct GameInfo
	{
		uint16_t width;
		uint16_t height;
		Color backgroundColor;
		int turnDisplayX;
		int turnDisplayY;
		int bankDisplayX;
		int bankDisplayY;
		bool requireHoverForBanks;
	};

	struct LabelInfo
	{
		std::string labelText;
		int x;
		int y;
		uint8_t fontSize;
		TextAlignment textAlignment;
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
		bool isDraggable;
		bool isCopyable;
	};

	struct DiceInfo
	{
		int x;
		int y;
		uint8_t min;
		uint8_t max;
	};
	
	struct GameConfigData
	{
		GameInfo info;
		StartMenuInfo startMenuInfo;
		std::vector<GameEntityData> entities;
		CommonPlayerInfo commonPlayerInfo;
		std::vector<PlayerInfo> players;
		std::vector<DiceInfo> die;
		std::vector<LabelInfo> labels;
		std::vector<SharedTextureInfo> sharedTextures;

	};



	enum EntityType 
	{
		TypeUnkown = 0,
		TypeEntity = 1,
		TypeGameInfo = 2,
		TypeStartMenuInfo = 3,
		TypeCommonPlayerInfo = 4,
		TypePlayerInfo = 5,
		TypeDiceInfo = 6,
		TypeLabel = 7,
		TypeSharedTextureInfo = 8
	};






}