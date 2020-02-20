#include "FontHolder.h"
#include <cassert>

void FontHolder::load(Fonts::Id id, const std::string& filename)
{
	std::unique_ptr<sf::Font> font(new sf::Font());
	if (!font->loadFromFile(filename))
		throw std::runtime_error("FontHolder::load - Failed to load " + filename);

	const auto font_pair = fonts_.insert(std::make_pair(id, std::move(font)));
	assert(font_pair.second);
}

sf::Font& FontHolder::get(const Fonts::Id id)
{
	const auto font_pair = fonts_.find(id);
	assert(font_pair != fonts_.end());
	return *font_pair->second;
}
