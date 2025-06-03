#pragma once
#include "raylib.h"
#include <stdint.h>
#include <vector>
#include <string>
#include <stdint.h>

#define USE_DEBUG_SCREEN_MACROS 1


#if _DEBUG

namespace BoardGame
{
	namespace gui
	{
		namespace DebugScreen
		{
			inline unsigned int lastUpdated = 0;
			inline bool updating = false;
			inline std::vector<std::string> strings;
			inline uint8_t fontSize = 30;
			inline uint16_t updateIntervall = 0;

			void newFrame();
			bool isUpdating();
			void postUpdate(std::string string);
			void postUpdate(const char* string);
			void draw();
		}
	}
}

#if USE_DEBUG_SCREEN_MACROS

	#define DEBUG_NEW_FRAME BoardGame::gui::DebugScreen::newFrame
	#define DEBUG_POST_UPDATE(msg) BoardGame::gui::DebugScreen::postUpdate(msg)

	#define DEBUG_DRAW BoardGame::gui::DebugScreen::draw


#endif

#else
	#define DEBUG_NEW_FRAME ((void)0)
	#define DEBUG_POST_UPDATE(msg) ((void)0)
	#define DEBUG_DRAW ((void)0)

#endif