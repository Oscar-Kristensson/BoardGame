#include "startMenu.h"


void BoardGame::StartMenu::update()
{

}


void BoardGame::StartMenu::render()
{
	ClearBackground(WHITE);
	DrawText("Start menu :)", 16, 16, 32, LIGHTGRAY);
}