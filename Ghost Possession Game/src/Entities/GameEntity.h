#pragma once

#include "../Visual.h"

class GameEntity : public Visual
{
public:

	void init(std::shared_ptr<sf::Texture>& texture, sf::Vector2f scale = { 1.f,1.f })
	{
		m_texture = texture;
		m_scale = scale;
		m_vertex_array = sf::VertexArray(sf::PrimitiveType::Triangles, 6);

		sf::Vector2f tex_size = (sf::Vector2f)m_texture->getSize();

		m_vertex_array.value()[0].position = sf::Vector2f(0,0);
		m_vertex_array.value()[1].position = sf::Vector2f( tex_size.x, 0.f );
		m_vertex_array.value()[2].position = sf::Vector2f(tex_size.x, tex_size.y);
		
		m_vertex_array.value()[3].position = sf::Vector2f(tex_size.x, tex_size.y);
		m_vertex_array.value()[4].position = sf::Vector2f(0.f, tex_size.y);
		m_vertex_array.value()[5].position = sf::Vector2f(0,0);

		m_vertex_array.value()[0].texCoords = { 0.f,0.f };
		m_vertex_array.value()[1].texCoords = { tex_size.x, 0.f };
		m_vertex_array.value()[2].texCoords = tex_size;
															
		m_vertex_array.value()[3].texCoords = tex_size;
		m_vertex_array.value()[4].texCoords = { 0.f, tex_size.y };
		m_vertex_array.value()[5].texCoords = { 0.f,0.f };
	}

private:

};