#pragma once

#include <SFML/graphics.hpp>

enum CollisionType
{
	NONE,
	INSIDE,
	OUTSIDE
};

class IPhysicsObject
{
public:

	void updateGravity()
	{
		m_velocity += m_gravity;
	}

	void haltX() { m_velocity.x = 0; }

	void haltY() { m_velocity.y = 0; }

	void setVelocity(float x, float y)
	{
		m_velocity = { x, y };
	}
	void setVelocity(sf::Vector2f vec)
	{
		m_velocity = vec;
	}

	void setGravity(float x, float y)
	{
		m_gravity = { x, y };
	}
	void setGravity(sf::Vector2f vec)
	{
		m_gravity = vec;
	}

	void insideCollision(sf::Sprite& moving_sprite, const sf::FloatRect& static_sprite);

	sf::Vector2f outsideCollision(sf::Sprite& moving_sprite, const sf::FloatRect& static_sprite)
	{
		sf::Vector2f offset = shortestOffset(moving_sprite.getGlobalBounds(), static_sprite);

		moving_sprite.move(offset);

		return offset;
	}

private:

	sf::Vector2f shortestOffset(const sf::FloatRect& rect_1, const sf::FloatRect& rect_2)
	{
		std::optional<sf::FloatRect> rect = rect_1.findIntersection(rect_2);

		if (rect == std::nullopt)
		{
			return sf::Vector2f();
		}

		sf::Vector2f size = rect.value().size;
		sf::Vector2f offset;

		if (fabsf(size.x) <= fabsf(size.y))
		{
			offset = sf::Vector2f(size.x, 0);
			offset *= rect_1.getCenter().x <= rect_2.getCenter().x ? -1.f : 1.f;
		}
		else
		{
			offset = sf::Vector2f(0, size.y);
			offset *= rect_1.getCenter().y <= rect_2.getCenter().y ? -1.f : 1.f;
		}

		return offset;
	}

public:

	CollisionType e_collision_type = NONE;

protected:

	sf::Vector2f m_velocity = {0,0};
	sf::Vector2f m_gravity = {0,0};
};