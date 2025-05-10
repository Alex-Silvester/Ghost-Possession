#pragma once

#include "../GameObject.h"
#include "../Interfaces/Interfaces.h"
#include "../constants.h"

#include <iostream>

class Player : public GameObject, public IPhysicsObject
{
public:
	Player() = default;

	Player(const sf::Texture& texture) : GameObject(texture) {}

	~Player()
	{
		delete m_possessable_obj_ptr;
	}

	void init(sf::Vector2f gravity);
	void update(float dt);

	void isGrounded() { m_velocity.y = 0; }

	void jump(float vel = 100.f) { setVelocity(m_velocity.x, -vel); }

	void flip(int direction) 
	{
		if(direction / abs(direction) != m_sprite->getScale().x/fabsf(m_sprite->getScale().x))
		{
			m_sprite->setScale({ direction / abs(direction) * fabsf(m_sprite->getScale().x), m_sprite->getScale().y });
			move(-direction / abs(direction) * m_sprite->getGlobalBounds().size.x, 0.f);
		}
	}

	void possess(IPossessable* possessable_obj)
	{
		m_possessable_obj_ptr = possessable_obj;
	}

	void unpossess()
	{
		m_possessable_obj_ptr = nullptr;
	}

	bool isPossessingObject()
	{
		return m_possessable_obj_ptr != nullptr;
	}

	void keyPressed(const sf::Event& event);
	void keyReleased(const sf::Event& event);

	IPossessable* getPossessedObject() 
	{
		return m_possessable_obj_ptr;
	}

private:

	IPossessable* m_possessable_obj_ptr = nullptr;

	struct KeyHeld
	{
		bool A = false;
		bool D = false;
		bool Space = false;
	}keyHeld;

};