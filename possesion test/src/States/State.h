#pragma once

#include<SFML/Graphics.hpp>

class State
{
public:

	State() = default;

	virtual bool init(std::shared_ptr<sf::RenderWindow> window)
	{
		m_window = window;
		return true;
	}
	virtual void update(float dt) {}
	virtual void render() {}

	virtual void mousePressed(const sf::Event& event) {}
	virtual void mouseReleased(const sf::Event& event) {}

	virtual void keyPressed(const sf::Event& event) {}
	virtual void keyReleased(const sf::Event& event) {}

protected:

	std::shared_ptr<sf::RenderWindow> m_window;

};