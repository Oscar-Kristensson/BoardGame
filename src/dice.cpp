
#include "dice.h"
#include "constants.h"
#include <algorithm>
#include <iostream>


BoardGame::gui::Dice::Dice(float x, float y, uint8_t minNumber , uint8_t maxNumber, bool repeatValues)
	: Element(x, y), m_DiceMinNumber(minNumber), m_DiceMaxNumber(maxNumber), m_LastTimeUpdated(std::chrono::high_resolution_clock::now())
{
	m_Width = m_Height = m_FontSize + m_PaddingY * 2;
	
	// Sets the value of the m_NumbersLeft -> program knows it should not repeat
	if (!repeatValues)
		m_NumbersLeft.emplace();

}


uint8_t BoardGame::gui::Dice::startRolling()
{
	if (m_NumbersLeft.has_value())
	{
		if ((*m_NumbersLeft).size() == 0)
		{
			generateNumbersLeft();
			std::cout << "Regenerating numbers" << std::endl;
		}

		uint8_t indexValue = GetRandomValue(0, (*m_NumbersLeft).size() - 1);
		m_CurrentValue = (*m_NumbersLeft)[indexValue];
		std::cout << "Number:" << static_cast<int>(m_CurrentValue) << std::endl;
		(*m_NumbersLeft).erase((*m_NumbersLeft).begin() + indexValue);


	}
	else
	{
		m_CurrentValue = GetRandomValue(1, m_DiceMaxNumber);
	}

	m_LastTimeUpdated = std::chrono::high_resolution_clock::now();
	m_TimesToRoll = 14;
	return m_CurrentValue;
}

void BoardGame::gui::Dice::update(int mouseX, int mouseY)
{
	updateElement(mouseX, mouseY);

	auto now = std::chrono::high_resolution_clock::now();

	if (m_TimesToRoll == 0)
	{
		m_DisplayedValue = m_CurrentValue;
	}
	else if ((std::chrono::duration_cast<std::chrono::milliseconds>(now - m_LastTimeUpdated)).count() > 75)
	{

		uint8_t random = GetRandomValue(m_DiceMinNumber, m_DiceMaxNumber);
		if (random == m_DisplayedValue)
		{
			random++;
			if (random == m_DiceMaxNumber)
				random = m_DiceMinNumber;
		}

		m_DisplayedValue = random;
		m_TimesToRoll--;
		m_LastTimeUpdated = now;
	}


	if (m_Hovered && IsMouseButtonPressed(0))
		startRolling();
}

void BoardGame::gui::Dice::draw()
{
	DrawRectangle(m_X, m_Y, m_Width, m_Height, WHITE);
	
	
	std::string drawString = std::to_string(m_DisplayedValue);
	Vector2 textDimensions = MeasureTextEx(BoardGame::constants::font, drawString.c_str(), m_FontSize, 2);

	Vector2 drawPosition = { m_X - textDimensions.x/2 + m_Width/2, m_Y - textDimensions.y/2 + m_Height/2 };
	DrawTextEx(BoardGame::constants::font, drawString.c_str(), drawPosition, m_FontSize, 2, BLACK);
}

void BoardGame::gui::Dice::generateNumbersLeft()
{
	if (m_NumbersLeft.has_value())
	{
		m_NumbersLeft.emplace();
		(*m_NumbersLeft).reserve(m_DiceMaxNumber - m_DiceMinNumber + 1);
		for (uint8_t i = 0; i < m_DiceMaxNumber - m_DiceMinNumber + 1; i++)
		{
			(*m_NumbersLeft).emplace_back(i + 1);
			std::cout << static_cast<int>(i + 1) << std::endl;
		}
	}


	for (uint8_t i = 0; i < (*m_NumbersLeft).size(); i++)
		std::cout << static_cast<int>((*m_NumbersLeft)[i]) << ", ";

}
