#pragma once

#include <SFML/Window/Keyboard.hpp>

class IControllable
{
public:

	virtual void keyPressed(const sf::Keyboard::Key& key) = 0;
	virtual void keyReleased(const sf::Keyboard::Key& key) = 0;

};