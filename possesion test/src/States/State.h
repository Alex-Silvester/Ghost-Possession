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

	virtual void mousePressed() {}
	virtual void mouseReleased() {}

	virtual void keyPressed() {}
	virtual void keyReleased() {}

protected:

	std::shared_ptr<sf::RenderWindow> m_window;

};