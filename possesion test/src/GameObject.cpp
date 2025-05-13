#include "GameObject.h"

GameObject::~GameObject()
{
	delete m_texture;
}

bool GameObject::intersects(const sf::FloatRect& rect)
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

const sf::FloatRect& GameObject::getFloatRect() const
{
	sf::Vector2f bounds =
	{
		m_vertex_array->getBounds().size.x * m_scale.x,
		m_vertex_array->getBounds().size.y * m_scale.y
	};
	return sf::FloatRect(m_position, bounds);
}

void GameObject::setPosition(float x, float y)
{
	if (m_vertex_array.has_value())
	{
		m_position += sf::Vector2f(x, y);
	}
}

void GameObject::setPosition(sf::Vector2f vec)
{
	if (m_vertex_array.has_value())
	{
		m_position = vec;
	}
}

sf::Vector2f GameObject::getPosition()
{
	return m_vertex_array.has_value() ? m_position : sf::Vector2f();
}

void GameObject::move(float x, float y)
{
	if (m_vertex_array.has_value())
	{
		m_position += sf::Vector2f(x, y);
	}
}

void GameObject::move(sf::Vector2f vec)
{
	if (m_vertex_array.has_value())
	{
		m_position += vec;
	}
}

void GameObject::setColour(sf::Color col)
{
	for (int i = 0; i < m_vertex_array->getVertexCount(); i++)
	{
		m_vertex_array.value()[i].color = col;
	}
}

sf::Color GameObject::getColour() 
{
	return m_vertex_array.value()[0].color; 
}

void GameObject::scale(float x, float y)
{
	m_scale = sf::Vector2f(x, y);
}

void GameObject::scale(sf::Vector2f vec)
{
	m_scale = vec;
}

void GameObject::setTransparancey(float alpha)
{
	setColour(sf::Color(
		getColour().r,
		getColour().g,
		getColour().b,
		alpha));
}

void GameObject::generateTexture(const std::vector<std::vector<unsigned int>>& data, sf::Vector2u tile_size, sf::Texture* texture)
{
	m_texture = texture;
	m_vertex_array = sf::VertexArray(sf::PrimitiveType::Triangles);

	for (int y = 0; y < data.size(); y++)
	{
		for (int x = 0; x < data[y].size(); x++)
		{
			std::array<sf::Vertex, 3> vertices_1;
			std::array<sf::Vertex, 3> vertices_2;

			//-----position-----//
			vertices_1[0].position = {  x      * (float)tile_size.x,  y      * (float)tile_size.y };
			vertices_1[1].position = {  x      * (float)tile_size.x, (y + 1) * (float)tile_size.y };
			vertices_1[2].position = { (x + 1) * (float)tile_size.x, (y + 1) * (float)tile_size.y };
																					 															 
			vertices_2[0].position = { (x + 1) * (float)tile_size.x, (y + 1) * (float)tile_size.y };
			vertices_2[1].position = { (x + 1) * (float)tile_size.x,  y      * (float)tile_size.y };
			vertices_2[2].position = {  x      * (float)tile_size.x,  y      * (float)tile_size.y };

			sf::Vector2u tex = sf::Vector2u(
				data[y][x] % (m_texture->getSize().x / tile_size.x),
				data[y][x] / (m_texture->getSize().x / tile_size.x)
			);

			//-----texture-----//
			vertices_1[0].texCoords = {  tex.x      * (float)tile_size.x,  tex.y      * (float)tile_size.y };
			vertices_1[1].texCoords = {  tex.x      * (float)tile_size.x, (tex.y + 1) * (float)tile_size.y };
			vertices_1[2].texCoords = { (tex.x + 1) * (float)tile_size.x, (tex.y + 1) * (float)tile_size.y };
																	 																								
			vertices_2[0].texCoords = { (tex.x + 1) * (float)tile_size.x, (tex.y + 1) * (float)tile_size.y };
			vertices_2[1].texCoords = { (tex.x + 1) * (float)tile_size.x,  tex.y      * (float)tile_size.y };
			vertices_2[2].texCoords = {  tex.x      * (float)tile_size.x,  tex.y      * (float)tile_size.y };

			m_vertex_array->append(vertices_1[0]);
			m_vertex_array->append(vertices_1[1]);
			m_vertex_array->append(vertices_1[2]);
																		 
			m_vertex_array->append(vertices_2[0]);
			m_vertex_array->append(vertices_2[1]);
			m_vertex_array->append(vertices_2[2]);
		}
		printf("\n");
	}
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_vertex_array.has_value())
	{
		states.transform.scale(m_scale);
		states.transform.translate({m_position.x/m_scale.x, m_position.y/m_scale.y});
		states.texture = m_texture;
		target.draw(m_vertex_array.value(), states);
	}
}
