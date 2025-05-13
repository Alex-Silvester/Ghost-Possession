#pragma once

#include "../GameObject.h"
#include "../Interfaces/Interfaces.h"
#include "../constants.h"

#include <iostream>

class Player : public GameObject, public IPhysicsObject
{
public:
	Player() = default;

	~Player()
	{
		delete m_possessable_obj_ptr;
	}

	void init(sf::Vector2f gravity);
	void update(float dt);

	void isGrounded() { m_velocity.y = 0; m_grounded = true; }

	void jump(float vel = 100.f);

	void flip(int direction);

	void possess(IPossessable* possessable_obj);
	void unpossess();

	bool isPossessingObject();

	void keyPressed(const sf::Event& event);
	void keyReleased(const sf::Event& event);

	IPossessable* getPossessedObject() 
	{
		return m_possessable_obj_ptr;
	}

	sf::Vector2f outsideCollision(GameObject& moving_sprite, const GameObject& static_sprite) override;

private:

	IPossessable* m_possessable_obj_ptr = nullptr;
	sf::Vector2f m_prev_position;

	bool m_grounded = false;

	struct KeyHeld
	{
		bool A = false;
		bool D = false;
		bool Space = false;
	}keyHeld;

};