#pragma once

#include <vector>
#include "raylib.h"


namespace BoardGame
{

	class DragController
	{
	private:
		bool m_IsDragged = false;
	public:
		DragController();
		bool isDragged();
		void startDragging();
		void stopDragging();
	};





}