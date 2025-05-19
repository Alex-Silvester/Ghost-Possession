#pragma once

#include <SFML/graphics.hpp>

#include "../Visual.h"

class GameObject : public Visual
{
public:

	GameObject() = default;

	~GameObject();

	void generateTexture(const std::vector<std::vector<unsigned int>>& data, sf::Vector2u tile_size, std::shared_ptr<sf::Texture> texture);

protected:

};
