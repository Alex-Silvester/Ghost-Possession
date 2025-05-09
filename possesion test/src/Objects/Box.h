#pragma once

#include "../Interfaces/Interfaces.h"
#include "../GameObject.h"

class Box : public GameObject, public IPhysicsObject
{
public:

	Box() 
	{
		e_collision_type = CollisionType::OUTSIDE;
	}

	Box(const sf::Texture& texture) : GameObject(texture)
	{
		e_collision_type = CollisionType::OUTSIDE;
	}

private:

};