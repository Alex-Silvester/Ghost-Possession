
#include "Visual.h"

typedef std::vector<std::vector<unsigned int>> DataMatrix;
DataMatrix Visual::generateBlockMatrix(unsigned int width, unsigned int height)
{
	DataMatrix data;

	unsigned int datum;
	for (unsigned int y = 0; y < height; y++)
	{
		data.emplace_back();
		for (unsigned int x = 0; x < width; x++)
		{
			datum = 0;
			if (y == height - 1)
			{
				datum = 6;
			}
			else if (y != 0)
			{
				datum = 3;
			}

			if (x == width - 1)
			{
				datum += 2;
			}
			else if (x != 0)
			{
				datum += 1;
			}

			data[y].emplace_back(datum);
		}
	}

	return data;
}

void Visual::generateTexture(const DataMatrix& data, sf::Vector2u tile_size)
{
	m_vertex_array = sf::VertexArray(sf::PrimitiveType::Triangles);

	if (tile_size.x > m_texture->getSize().x)
	{
		tile_size.x = m_texture->getSize().x;
	}

	if (tile_size.y > m_texture->getSize().y)
	{
		tile_size.y = m_texture->getSize().y;
	}

	size = sf::Vector2i( data.back().size(), data.size() );

	for (int y = 0; y < data.size(); y++)
	{
		for (int x = 0; x < data[y].size(); x++)
		{
			std::array<sf::Vertex, 3> vertices_1;
			std::array<sf::Vertex, 3> vertices_2;

			//-----position-----//
			vertices_1[0].position = { x * (float)tile_size.x,  y * (float)tile_size.y };
			vertices_1[1].position = { x * (float)tile_size.x, (y + 1) * (float)tile_size.y };
			vertices_1[2].position = { (x + 1) * (float)tile_size.x, (y + 1) * (float)tile_size.y };

			vertices_2[0].position = { (x + 1) * (float)tile_size.x, (y + 1) * (float)tile_size.y };
			vertices_2[1].position = { (x + 1) * (float)tile_size.x,  y * (float)tile_size.y };
			vertices_2[2].position = { x * (float)tile_size.x,  y * (float)tile_size.y };

			sf::Vector2u tex = sf::Vector2u(
				data[y][x] % (m_texture->getSize().x / tile_size.x),
				data[y][x] / (m_texture->getSize().x / tile_size.x)
			);

			//-----texture-----//
			vertices_1[0].texCoords = { tex.x * (float)tile_size.x,  tex.y * (float)tile_size.y };
			vertices_1[1].texCoords = { tex.x * (float)tile_size.x, (tex.y + 1) * (float)tile_size.y };
			vertices_1[2].texCoords = { (tex.x + 1) * (float)tile_size.x, (tex.y + 1) * (float)tile_size.y };

			vertices_2[0].texCoords = { (tex.x + 1) * (float)tile_size.x, (tex.y + 1) * (float)tile_size.y };
			vertices_2[1].texCoords = { (tex.x + 1) * (float)tile_size.x,  tex.y * (float)tile_size.y };
			vertices_2[2].texCoords = { tex.x * (float)tile_size.x,  tex.y * (float)tile_size.y };

			m_vertex_array.append(vertices_1[0]);
			m_vertex_array.append(vertices_1[1]);
			m_vertex_array.append(vertices_1[2]);
										
			m_vertex_array.append(vertices_2[0]);
			m_vertex_array.append(vertices_2[1]);
			m_vertex_array.append(vertices_2[2]);
		}
	}
}

bool Visual::intersects(const sf::FloatRect& rect)
{
	if (m_vertex_array.getVertexCount() > 0)
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
		m_vertex_array.getBounds().size.x * m_scale.x,
		m_vertex_array.getBounds().size.y * m_scale.y
	};
	return sf::FloatRect(m_position, bounds);
}

void Visual::setPosition(float x, float y)
{
	if (m_vertex_array.getVertexCount() > 0)
	{
		m_position += sf::Vector2f(x, y);
	}

	if (m_id_text.has_value())
	{
		m_id_text->setPosition(m_vertex_array.getBounds().getCenter() + m_position);
	}

	m_select_rect.setPosition({ x,y });
}

void Visual::setPosition(sf::Vector2f vec)
{
	if (m_vertex_array.getVertexCount() > 0)
	{
		m_position = vec;
	}

	if (m_id_text.has_value())
	{
		m_id_text->setPosition(m_vertex_array.getBounds().getCenter() + m_position);
	}

	m_select_rect.setPosition(vec);
}

sf::Vector2f Visual::getPosition()
{
	return m_vertex_array.getVertexCount() > 0 ? m_position : sf::Vector2f();
}

void Visual::move(float x, float y)
{
	if (m_vertex_array.getVertexCount() > 0)
	{
		m_position += sf::Vector2f(x, y);
	}

	if (m_id_text.has_value())
	{
		m_id_text->move({ x, y });
	}

	m_select_rect.move({ x,y });
}

void Visual::move(sf::Vector2f vec)
{
	if (m_vertex_array.getVertexCount() > 0)
	{
		m_position += vec;
	}

	if (m_id_text.has_value())
	{
		m_id_text->move(vec);
	}

	m_select_rect.move(vec);
}

void Visual::setColour(sf::Color col)
{
	for (int i = 0; i < m_vertex_array.getVertexCount(); i++)
	{
		m_vertex_array[i].color = col;
	}
}

sf::Color Visual::getColour()
{
	return m_vertex_array[0].color;
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
	if (m_vertex_array.getVertexCount() > 0)
	{
		states.transform.scale(m_scale);
		states.transform.translate({ m_position.x / m_scale.x, m_position.y / m_scale.y });
		states.texture = m_texture.get();
		target.draw(m_vertex_array, states);

		if(m_id_text.has_value())
			target.draw(m_id_text.value());

		if (m_draw_outline)
		{
			target.draw(m_select_rect);
		}
	}
}
