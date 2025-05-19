#include "GameObject.h"

GameObject::~GameObject()
{

}

void GameObject::generateTexture(const std::vector<std::vector<unsigned int>>& data, sf::Vector2u tile_size, std::shared_ptr<sf::Texture> texture)
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
	}
}