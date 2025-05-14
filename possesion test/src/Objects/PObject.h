#pragma once

#include "Box.h"
#include "../Interfaces/IPossessable.h"

class PObject : public GameObject, public IPhysicsObject, public IPossessable
{
public:

	PObject() = default;

	void keyPressed(const sf::Event& event) override;
	void keyReleased(const sf::Event& event) override;

	sf::Vector2f updateMovement(float dt) override;

	void unpossess() override;

	void flash(sf::Color col_1, sf::Color col_2 = sf::Color::White, float rate = 1);
	void flash(sf::Color col_1, float rate);
	void resetFlash() { setColour(sf::Color::White); }
};