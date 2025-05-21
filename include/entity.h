#pragma once
#include "dataTypes.h"
#include "raylib.h"

namespace BoardGame
{
	class Entity
	{
	private:
		Texture2D m_Texture;
		int m_X;
		int m_Y;
		int m_Width;
		int m_Height;
		
	public:
		Entity() = default;
		Entity(Texture2D imagePath, int x, int y);
		Entity(GameEntityData entityData);

		void draw();

	};
}