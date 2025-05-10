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

	void flip(int direction) 
	{
		if(direction / abs(direction) != m_sprite->getScale().x/fabsf(m_sprite->getScale().x))
		{
			m_sprite->setScale({ direction / abs(direction) * fabsf(m_sprite->getScale().x), m_sprite->getScale().y });
			move(-direction / abs(direction) * m_sprite->getGlobalBounds().size.x, 0.f);
		}
	}

private:

};