#pragma once

#include "Box.h"
#include "../Interfaces/IPossessable.h"

class PossessableBox : public Box, public IPossessable
{
public:

	PossessableBox() = default;
	PossessableBox(const sf::Texture& texture) : Box(texture) {}

	void keyPressed(const sf::Event& event) override;
	void keyReleased(const sf::Event& event) override;

	sf::Vector2f updateMovement(float dt) override;
};