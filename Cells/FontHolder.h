#pragma once
#include <map>
#include "Fonts.h"
#include <memory>
#include <SFML/Graphics/Font.hpp>

class FontHolder
{
	std::map<Fonts::Id, std::unique_ptr<sf::Font>> fonts_;
public:
	void load(Fonts::Id id, const std::string& filename);

	sf::Font& get(Fonts::Id id);
};
