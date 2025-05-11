#pragma once

#include <SFML/graphics.hpp>

class GameObject : public sf::Drawable
{
public:

	GameObject() = default;
	GameObject(const sf::Texture& texture);

	void selectTextureView(sf::Vector2i size, sf::Vector2i position = sf::Vector2i());

	bool intersects(const sf::FloatRect& rect);

	sf::FloatRect getFloatRect();

	sf::Sprite& getSprite();

	//----------Position----------//
	void setPosition(float x, float y);

	void setPosition(sf::Vector2f vec);

	sf::Vector2f getPosition();

	void move(float x, float y);

	void move(sf::Vector2f vec);
	//----------Position----------//

	//----------Visuals----------//
	void setColour(sf::Color col);

	void scale(float x, float y);

	void scale(sf::Vector2f vec);

	void setTransparancey(float alpha);
	//----------Visuals----------//

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:

	std::optional<sf::Sprite> m_sprite;
};
