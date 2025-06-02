#include "debugScreen.h"
#if _DEBUG




void BoardGame::gui::DebugScreen::newFrame()
{
	updating = (GetTime() - lastUpdated > updateIntervall);

	if (!updating)
		return;

	lastUpdated = GetTime();

	strings.clear();
}

bool BoardGame::gui::DebugScreen::isUpdating() { return updating; }

void BoardGame::gui::DebugScreen::postUpdate(std::string string)
{ 
	strings.push_back(string);
}

void BoardGame::gui::DebugScreen::postUpdate(const char* string)
{
	postUpdate(std::string(string));
}


void BoardGame::gui::DebugScreen::draw()
{
	DrawRectangle(0, 0, 1000, (fontSize +4) * (1 + strings.size()), { 0, 0, 0, 128 });
	for (unsigned int i = 0; i < strings.size(); i++)
		DrawText(strings[i].c_str(), 16, (fontSize + 4) * (1 + i), fontSize, WHITE);
}


#endif