#pragma once


#include "raylib.h"
#include "dataTypes.h"
#include "utils.h"
#include "app.h"
#include "startMenu.h"
#include "parser.h"
#include <unordered_map>
#include <string>


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

	public:
		Game(Vector2 boardSize, Color backgroundColor)
			:m_BoardSize(boardSize), m_BackgroundColor(backgroundColor)
		{
			m_MapImage = LoadTexture("assets/map.png");
			m_Camera.target = { m_BoardSize.x / 2, m_BoardSize.y / 2 };
			m_Camera.offset = Vector2( GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);
			m_Camera.rotation = 0.0f;
			m_Camera.zoom = 0.5f; 

		}
		
		void update() override;
		void render() override;
	};

};
