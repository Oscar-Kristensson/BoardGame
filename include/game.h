#pragma once

#include "parser.h"
#include <unordered_map>
#include <string>

#define entity_index_type uint8_t

namespace BoardGame {
	enum EntityType {
		Unkown = 0,
		Entity = 1
	};


	const std::unordered_map<std::string, EntityType> entityMap =
	{
		{"Entity", Entity},
	};
};