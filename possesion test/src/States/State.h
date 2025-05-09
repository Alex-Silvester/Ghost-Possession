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
	virtual void update() {}
	virtual void render() {}

	virtual void mousePressed() {}
	virtual void mouseReleased() {}

	virtual void keyPressed() {}
	virtual void keyReleased() {}

private:

	std::shared_ptr<sf::RenderWindow> m_window;

};