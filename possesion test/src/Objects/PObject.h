#pragma once

#include "Box.h"
#include "../Interfaces/IPossessable.h"

class PObject : public GameObject, public IPhysicsObject, public IPossessable
{
public:

	PObject() = default;
	PObject(const sf::Texture& texture) : GameObject(texture) {}

	void keyPressed(const sf::Event& event) override;
	void keyReleased(const sf::Event& event) override;

	sf::Vector2f updateMovement(float dt) override;
};