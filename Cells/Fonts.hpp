#pragma once
#include <SFML/Graphics/Font.hpp>
#include "ResourceHolder.h"

namespace Fonts
{
	enum Id { Arial};
}

typedef ResourceHolder<Fonts::Id, sf::Font> FontHolder;
