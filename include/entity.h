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
		Entity(Texture2D image, int x, int y);
		Entity(const GameEntityData& entityData);
		~Entity();


		void draw();

		// Disable copying (because of textures)
		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;

		// Move operators
		Entity(Entity&& other) noexcept;
		Entity& operator=(Entity&& other) noexcept;


	};
}