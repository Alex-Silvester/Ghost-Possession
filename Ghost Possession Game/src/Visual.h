#pragma once

#include <SFML/Graphics.hpp>

class Visual : public sf::Drawable
{
public:

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
	void setTexture(std::shared_ptr<sf::Texture>& texture);

	void setColour(sf::Color col);

	sf::Color getColour();

	void scale(float x, float y);

	void scale(sf::Vector2f vec);

	sf::Vector2f getScale() { return m_scale; }

	void setTransparancey(float alpha);

	//----------Visuals----------//

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:

	std::optional<sf::VertexArray> m_vertex_array;
	sf::Vector2f m_position = { 0,0 };
	std::shared_ptr<sf::Texture> m_texture = nullptr;
	sf::Vector2f m_scale = { 1,1 };
};