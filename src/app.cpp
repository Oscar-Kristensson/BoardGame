#include "app.h"

#if DEBUG
#include <iostream>

#endif


void App::update()
{
#if DEBUG
	std::cout << "Override the App::update function" << std::endl;

#endif
};