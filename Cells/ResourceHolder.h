#pragma once
#include <map>
#include <memory>
#include <SFML/Graphics/Font.hpp>
#include <cassert>
#include "Fonts.h"


/**
 * \brief Class allowing access to resources such as fonts, textures, etc.
 * \tparam Identifier Type of resource identifier
 * \tparam Resource Type of resource
 */
template <typename Identifier, typename Resource>
class ResourceHolder
{
	std::map<Identifier, std::unique_ptr<Resource>> resources_;
public:

	void load(Identifier id, const std::string& filename)
	{
		std::unique_ptr<Resource> font(new Resource);
		if (!font->loadFromFile(filename))
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

		const auto font_pair = resources_.insert(std::make_pair(id, std::move(font)));
		assert(font_pair.second);
	}

	Resource& get(const Identifier id)
	{
		const auto font_pair = resources_.find(id);
		assert(font_pair != resources_.end());
		return *font_pair->second;
	}
};

typedef ResourceHolder<Fonts::Id, sf::Font> FontHolder;