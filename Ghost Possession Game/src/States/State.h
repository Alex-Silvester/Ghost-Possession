#pragma once

#include<SFML/Graphics.hpp>

#include <functional>

enum States
{
	NULL_STATE,
	START,
	MENU,
	LEVEL_SELECT,
	PLAY,
	WIN
};

class State
{
public:

	State() : m_default_state(NULL_STATE) {}
	State(States state) : m_default_state(state)
	{
		m_current_state = state;
	}

	virtual bool init(std::shared_ptr<sf::RenderWindow> window)
	{
		m_window = window;
		return true;
	}
	virtual void update(float dt) {}
	virtual void render() {}

	virtual void mousePressed(const sf::Mouse::Button& event) {}
	virtual void mouseReleased(const sf::Mouse::Button& event) {}

	virtual void wheelScrolled(const sf::Event::MouseWheelScrolled& event) {}

	virtual void keyPressed(const sf::Keyboard::Key& event) {}
	virtual void keyReleased(const sf::Keyboard::Key& event) {}

	States getCurrentState()
	{
		States temp = m_current_state;
		m_current_state = m_default_state;
		return temp;
	}

protected:

	std::shared_ptr<sf::RenderWindow> m_window;

	States m_current_state = NULL_STATE;
	const States m_default_state;

};