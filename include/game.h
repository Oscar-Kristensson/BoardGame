#pragma once

#include "parser.h"
#include "app.h"
#include "raylib.h"
#include <unordered_map>
#include <string>


namespace BoardGame {
	enum EntityType {
		Unkown = 0,
		Entity = 1
	};


	const std::unordered_map<std::string, EntityType> entityMap =
	{
		{"Entity", Entity},
	};






	class Game : public App
	{
	private:
		Rectangle m_Player = { 2000, 2000, 40, 40 };
		Texture2D m_MapImage;
		Camera2D m_Camera = { 0 };
        Vector2 m_BoardSize = { 4000, 4000 };

	public:
		Game()
		{
			m_MapImage = LoadTexture("assets/map.png");
			m_Camera.target = Vector2(2.0f, 2.0f);
			m_Camera.offset = Vector2( GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);
			m_Camera.rotation = 0.0f;
			m_Camera.zoom = 0.5f;

		}
		
		void update() override;
		void render() override;
	};

};
