#include "startMenu.h"
#include <iostream>


BoardGame::StartMenu::StartMenu(Color backgroundColor)
	:m_BackgroundColor(backgroundColor)
{
	std::cout << "bg:" << backgroundColor.r << "," << backgroundColor.b << "," << backgroundColor.g << std::endl;
}


void BoardGame::StartMenu::update()
{

}


void BoardGame::StartMenu::render()
{
	ClearBackground(m_BackgroundColor);
	DrawText("Start menu :)", 16, 16, 32, LIGHTGRAY);
}