
#include "Visual.h"

bool Visual::intersects(const sf::FloatRect& rect)
{
	if (m_vertex_array.has_value())
	{
		if (getFloatRect().findIntersection(rect) == std::nullopt)
		{
			return false;
		}
		return true;
	}
	return false;
}

const sf::FloatRect& Visual::getFloatRect() const
{
	sf::Vector2f bounds =
	{
		m_vertex_array->getBounds().size.x * m_scale.x,
		m_vertex_array->getBounds().size.y * m_scale.y
	};
	return sf::FloatRect(m_position, bounds);
}

void Visual::setPosition(float x, float y)
{
	if (m_vertex_array.has_value())
	{
		m_position += sf::Vector2f(x, y);
	}
}

void Visual::setPosition(sf::Vector2f vec)
{
	if (m_vertex_array.has_value())
	{
		m_position = vec;
	}
}

sf::Vector2f Visual::getPosition()
{
	return m_vertex_array.has_value() ? m_position : sf::Vector2f();
}

void Visual::move(float x, float y)
{
	if (m_vertex_array.has_value())
	{
		m_position += sf::Vector2f(x, y);
	}
}

void Visual::move(sf::Vector2f vec)
{
	if (m_vertex_array.has_value())
	{
		m_position += vec;
	}
}

void Visual::setTexture(std::shared_ptr<sf::Texture>& texture)
{
	m_texture = texture;
}

void Visual::setColour(sf::Color col)
{
	for (int i = 0; i < m_vertex_array->getVertexCount(); i++)
	{
		m_vertex_array.value()[i].color = col;
	}
}

sf::Color Visual::getColour()
{
	return m_vertex_array.value()[0].color;
}

void Visual::scale(float x, float y)
{
	m_scale = sf::Vector2f(x, y);
}

void Visual::scale(sf::Vector2f vec)
{
	m_scale = vec;
}

void Visual::setTransparancey(float alpha)
{
	setColour(sf::Color(
		getColour().r,
		getColour().g,
		getColour().b,
		alpha));
}

void Visual::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_vertex_array.has_value())
	{
		states.transform.scale(m_scale);
		states.transform.translate({ m_position.x / m_scale.x, m_position.y / m_scale.y });
		states.texture = m_texture.get();
		target.draw(m_vertex_array.value(), states);
	}
}
