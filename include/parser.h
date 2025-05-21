#pragma once
#include "game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <map>


namespace BoardGame::parser {
	BoardGame::GameConfigData loadGameData(const std::filesystem::path& path);

}