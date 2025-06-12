#include "mouseDragController.h"
#include <iostream>

BoardGame::DragController::DragController()
{

}


bool BoardGame::DragController::isDragged()
{
	return m_IsDragged;
}

void BoardGame::DragController::startDragging()
{
	std::cout << "Starting dragging" << std::endl;
	m_IsDragged = true;
}

void BoardGame::DragController::stopDragging()
{
	if (m_IsDragged)
		std::cout << "Ending dragging" << std::endl;
	m_IsDragged = false;
}



