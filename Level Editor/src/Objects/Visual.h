#pragma once

#include <SFML/Graphics.hpp>

class Visual : public sf::Drawable
{
public:

	Visual(sf::Vector2f position, sf::Vector2i size, std::shared_ptr<sf::Texture> texture, std::shared_ptr<sf::Font> font, int type = 0)
	{
		m_type = type;
		m_texture = texture;
		generateTexture(generateBlockMatrix(size.x, size.y), { 32,32 });
		setPosition(position);

		m_id_text = sf::Text(*font, std::to_string(type));

		m_id_text->setFillColor(sf::Color::Magenta);
		m_id_text->setOrigin(m_id_text->getGlobalBounds().getCenter());
		m_id_text->setPosition(m_vertex_array.value().getBounds().getCenter() + m_position);
	}

	typedef std::vector<std::vector<unsigned int>> DataMatrix;
	static DataMatrix generateBlockMatrix(unsigned int width, unsigned int height);

	void generateTexture(const DataMatrix& data, sf::Vector2u tile_size);

	bool intersects(const sf::FloatRect& rect);

	const sf::FloatRect& getFloatRect() const;

	//----------Position----------//
	void setPosition(float x, float y);

	void setPosition(sf::Vector2f vec);

	sf::Vector2f getPosition();

	void move(float x, float y);

	void move(sf::Vector2f vec);
	//----------Position----------//

	//----------Visuals----------//
	void setColour(sf::Color col);

	sf::Color getColour();

	void scale(float x, float y);

	void scale(sf::Vector2f vec);

	sf::Vector2f getScale() { return m_scale; }

	void setTransparancey(float alpha);

	//----------Visuals----------//

	void setType(unsigned int t) { m_type = t; }

	sf::Vector2i getSize() { return size; }

	unsigned int getType() { return m_type; }

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	unsigned int m_type = 0;

	std::optional<sf::VertexArray> m_vertex_array;
	sf::Vector2f m_position = { 0,0 };
	std::shared_ptr<sf::Texture> m_texture = nullptr;
	sf::Vector2f m_scale = { 1,1 };

	sf::Vector2i size = { 0,0 };

	std::optional<sf::Text> m_id_text;
};