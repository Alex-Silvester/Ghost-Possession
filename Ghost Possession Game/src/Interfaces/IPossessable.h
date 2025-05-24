#pragma once

#include "IControllable.h"

class IPossessable : public IControllable
{
public:

	IPossessable() = default;

	virtual sf::Vector2f updateMovement(float dt) { return sf::Vector2f(); };

	virtual void unpossess() { m_flash_amount = 0.f; }

protected:

	struct KeyHeld
	{
		bool A = false;
		bool D = false;
		bool W = false;
		bool S = false;
		bool Space = false;
	}keyHeld;

#define PI 3.1415926f
	float m_flash_amount = 0.f;
	float m_flash_speed = 0.02f;
};