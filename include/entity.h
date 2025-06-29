#pragma once
#include "dataTypes.h"
#include "raylib.h"
#include "mouseDragController.h"
#include "assetManager.h"
#include <optional>

namespace BoardGame
{
	class Entity
	{
	private:
		Texture2D* m_Texture;
		int m_X;
		int m_Y;
		int m_Width;
		int m_Height;
		bool m_IsCopyable;
		bool m_IsClone;

	public:
		std::optional<BoardGame::DragController> m_DragController;
		
	public:

		Entity() = default;
		Entity(Texture2D* image, int x, int y);
		Entity(const GameEntityData& entityData, BoardGame::TextureManager& textureManager);


		void draw();

		// Disable copying (because of textures)
		/*
		* This should work because the Texture is now a pointer
		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;
		*/


		// Copy + move constructors
		Entity(const Entity&) = default;
		Entity& operator=(const Entity&) = default;
		Entity(Entity&&) noexcept = default;
		Entity& operator=(Entity&&) noexcept = default;

		bool isMouseHovering(int x, int y);
		void move(int x, int y);
		bool getIsCopyable();
		bool getIsClone();
		void setIsClone(bool isClone);

	};
}