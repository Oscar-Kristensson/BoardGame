#include "entity.h"
#include <iostream>
#include <filesystem>


BoardGame::Entity::Entity(Texture2D texture, int x, int y)
	:m_Texture(texture), m_X(x), m_Y(y), m_Width(texture.width), m_Height(texture.height)
{
}


BoardGame::Entity::Entity(const BoardGame::GameEntityData& entityData)
	:m_X(entityData.x), m_Y(entityData.y)
{
	std::string stringPath = entityData.imagePath.string();
	if (!std::filesystem::exists(entityData.imagePath))
		throw std::runtime_error("Could not find image at " + stringPath);

	
	m_Texture = LoadTexture(stringPath.c_str());
	m_Width = m_Texture.width;
	m_Height = m_Texture.height;

	if (entityData.isDraggable)
		m_DragController = BoardGame::DragController();


}

void BoardGame::Entity::draw()
{
	DrawTexture(m_Texture, m_X, m_Y, WHITE);
}


BoardGame::Entity::~Entity()
{
	UnloadTexture(m_Texture);
}

// Move constructor
BoardGame::Entity::Entity(BoardGame::Entity&& other) noexcept
	: m_Texture(other.m_Texture), m_X(other.m_X), m_Y(other.m_Y),
	m_Width(other.m_Width), m_Height(other.m_Height)
{
	// Invalidate other's texture so destructor doesn't unload twice
	other.m_Texture = { 0, 0, 0, 0 };
	other.m_X = 0;
	other.m_Y = 0;
	other.m_Width = 0;
	other.m_Height = 0;
}


BoardGame::Entity& BoardGame::Entity::operator=(BoardGame::Entity&& other) noexcept
{
	if (this != &other)
	{
		// Free current resource
		UnloadTexture(m_Texture);

		// Steal other's resource and data
		m_Texture = other.m_Texture;
		m_X = other.m_X;
		m_Y = other.m_Y;
		m_Width = other.m_Width;
		m_Height = other.m_Height;

		// Invalidate other
		other.m_Texture = { 0, 0, 0, 0 };
		other.m_X = 0;
		other.m_Y = 0;
		other.m_Width = 0;
		other.m_Height = 0;
	}
	return *this;
}

bool BoardGame::Entity::isMouseHovering(int x, int y)
{
	// Check X-axis (false if outside)
	if (!(x > m_X && x < m_X + m_Width))
		return false;

	// Check Y-axis (true if inside)
	if (y > m_Y && y < m_Y + m_Height)
		return true;

	// Otherwise false
	return false;
}



void BoardGame::Entity::move(int x, int y)
{
	m_X += x;
	m_Y += y;
}