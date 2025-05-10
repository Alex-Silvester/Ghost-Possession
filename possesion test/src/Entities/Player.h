#pragma once

#include "../GameObject.h"

#include "../Interfaces/Interfaces.h"

class Player : public GameObject, public IPhysicsObject
{
public:
	Player() = default;

	Player(const sf::Texture& texture) : GameObject(texture) {}

	void init(sf::Vector2f gravity);
	void update(float dt);

	void isGrounded() { m_velocity.y = 0; }

	void jump(float vel = 100.f) { addVelocity(0, -vel); }

private:

};