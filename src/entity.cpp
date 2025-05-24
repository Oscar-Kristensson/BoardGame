#pragma once
#include "entity.h"
#include <iostream>


BoardGame::Entity::Entity(Texture2D texture, int x, int y)
	:m_Texture(texture), m_X(x), m_Y(y), m_Width(texture.width), m_Height(texture.height)
{
	std::cout << "Created entity at" << m_X << ", " << m_Y << std::endl;
};


BoardGame::Entity::Entity(BoardGame::GameEntityData entityData)
	:m_X(entityData.x), m_Y(entityData.y)
{
	std::string stringPath = entityData.imagePath.string();
	if (!std::filesystem::exists(entityData.imagePath))
		throw std::runtime_error("Could not find image at " + stringPath);

	std::cout << stringPath << std::endl;
	
	m_Texture = LoadTexture(stringPath.c_str());
	m_Width = m_Texture.width;
	m_Height = m_Texture.height;

};

void BoardGame::Entity::draw()
{
	DrawTexture(m_Texture, m_X, m_Y, WHITE);
};
