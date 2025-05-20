#include "IPhysicsObject.h"

sf::Vector2f IPhysicsObject::outsideCollision(Visual& moving_obj, const Visual& static_obj)
{
	sf::FloatRect r1 = moving_obj.getFloatRect();
	sf::FloatRect r2 = static_obj.getFloatRect();

	sf::Vector2f offset = shortestOffset(r1, r2);

	moving_obj.move(offset);

	return offset;
}

sf::Vector2f IPhysicsObject::shortestOffset(const sf::FloatRect& rect_1, const sf::FloatRect& rect_2)
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
		offset *= rect_1.position.x <= rect_2.position.x ? -1.f : 1.f;
	}
	else
	{
		offset = sf::Vector2f(0, size.y);
		offset *= rect_1.position.y <= rect_2.position.y ? -1.f : 1.f;
	}

	return offset;
}
