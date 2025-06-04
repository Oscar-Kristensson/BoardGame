#pragma once
#include <stdint.h>
#include "uiElement.h"
#include "raylib.h"
#include <string>
#include <chrono>


namespace BoardGame
{
	namespace gui
	{

		/**
		 * @brief Represents a dice object
		 * 
		 * This class handels the dice and its rolling behavior
		 */
		class Dice : public Element
		{
		private:
			uint8_t m_DiceMaxNumber = 6;
			uint8_t m_CurrentValue = 0;
			uint8_t m_DisplayedValue = 0;
			uint8_t m_FontSize = 64;
			std::chrono::steady_clock::time_point m_LastTimeUpdated;
			uint8_t m_TimesToRoll = 0;
			
		
		public:			
			Dice() = default;
			Dice(float x, float y, uint8_t maxNumber);

			/**
			 * @brief Rolls the dice
			 * @return the value of the rolled dice
			 * 
			 * Generates a random number (the final value) and randomly changes
			 * the value of the dice a few times. After the animation, the final 
			 * value is set. Note that this function only starts the process.
			 */
			uint8_t startRolling();
			void update(int mouseX, int mouseY);
			void draw() override;
		};
	}
}