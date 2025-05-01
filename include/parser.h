#pragma once
#include "game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>


namespace BoardGame::parser {
	void ping();
	void readFile(const std::filesystem::path& path);
}