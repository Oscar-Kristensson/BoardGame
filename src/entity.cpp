#include "entity.h"
#include <iostream>
#include <filesystem>


BoardGame::Entity::Entity(Texture2D* texture, int x, int y)
	:m_Texture(texture), m_X(x), m_Y(y), m_Width(texture->width), m_Height(texture->height), m_IsCopyable(false), m_IsClone(false)
{
	
}


BoardGame::Entity::Entity(const BoardGame::GameEntityData& entityData, BoardGame::TextureManager& textureManager)
	:m_X(entityData.x), m_Y(entityData.y), m_IsCopyable(entityData.isCopyable), m_IsClone(false)
{
	std::string stringPath = entityData.imagePath.string();


	// If the path is a shared texture
	uint16_t textureID;
	if (stringPath.at(0) == '#')
	{
		textureID = textureManager.getID(stringPath);
	}
	else
	{
		if (!std::filesystem::exists(entityData.imagePath))
			throw std::runtime_error("Could not find image at " + stringPath);
		
        // NOTE: There is a suspected bug with loading directly from a path 
		std::cout << "There may be issues when loading images without shared textures. This should be fixed in future" << std::endl;
		textureID = textureManager.load(stringPath, entityData.imagePath.string());
	}

	m_Texture = textureManager.getTexture(textureID);
	m_Width = m_Texture->width;
	m_Height = m_Texture->height;

	if (entityData.isDraggable)
		m_DragController = BoardGame::DragController();


}

void BoardGame::Entity::draw()
{
	DrawTexture(*m_Texture, m_X, m_Y, WHITE);
}

// TBD Clean up this mess
// Move constructor
/*
BoardGame::Entity::Entity(BoardGame::Entity&& other) noexcept
	: m_Texture(other.m_Texture), m_X(other.m_X), m_Y(other.m_Y),
	m_Width(other.m_Width), m_Height(other.m_Height), m_DragController()
{
	/* This code is not necessary if the texture manager is used
	// Invalidate other's texture so destructor doesn't unload twice
	other.m_Texture = { 0, 0, 0, 0 };
	other.m_X = 0;
	other.m_Y = 0;
	other.m_Width = 0;
	other.m_Height = 0;
	
	
}
*/


	/*
BoardGame::Entity& BoardGame::Entity::operator=(BoardGame::Entity&& other) noexcept
{
	if (this != &other)
	{
		// Free current resource
		UnloadTexture(*m_Texture);

		// Steal other's resource and data
		m_Texture = other.m_Texture;
		m_X = other.m_X;
		m_Y = other.m_Y;
		m_Width = other.m_Width;
		m_Height = other.m_Height;

		// Invalidate other
		/* This code is not necessary if the texture manager is used
		other.m_Texture = { 0, 0, 0, 0 };
		other.m_X = 0;
		other.m_Y = 0;
		other.m_Width = 0;
		other.m_Height = 0;
		
	}

	return *this;
}
	*/
/*
BoardGame::Entity::Entity(const BoardGame::Entity& other)
	:m_Texture(other.m_Texture), m_X(other.m_X), m_Y(other.m_Y),
	m_Height(other.m_Height), m_Width(other.m_Width)
{
	if (other.m_DragController.has_value())
		m_DragController = DragController();
}
*/

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

bool BoardGame::Entity::getIsCopyable()
{
	return m_IsCopyable;
}

bool BoardGame::Entity::getIsClone()
{
	return m_IsClone;
}

void BoardGame::Entity::setIsClone(bool isClone)
{
	m_IsClone = isClone;
}
