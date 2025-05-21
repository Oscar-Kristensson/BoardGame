#pragma once


#include "raylib.h"
#include "dataTypes.h"
#include "entity.h"
#include "utils.h"
#include "app.h"
#include "startMenu.h"
#include "parser.h"
#include <unordered_map>
#include <string>
#include <vector>


namespace BoardGame 
{


	const std::unordered_map<std::string, EntityType> entityMap =
	{
		{"Entity", TypeEntity},
		{"GameInfo", TypeGameInfo},
		{"StartMenu", TypeStartMenuInfo}
	};






	class Game : public App
	{
	private:
		Rectangle m_Player = { 2000, 2000, 40, 40 };
		Texture2D m_MapImage;
		Camera2D m_Camera = { 0 };
        Vector2 m_BoardSize;
		Color m_BackgroundColor;
		std::vector<BoardGame::Entity> m_Entities;

	public:
		Game(Vector2 boardSize, Color backgroundColor, std::vector<BoardGame::GameEntityData> entityData);
		
		void update() override;
		void render() override;
	};

};
