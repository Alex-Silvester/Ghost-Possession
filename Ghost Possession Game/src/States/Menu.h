#pragma once

#include "State.h"
#include "../Tools/Objects/ScalingText.h"

class Menu : public State
{
public:

	Menu() : State(MENU) {}

	bool init(std::shared_ptr<sf::RenderWindow> window) override;
	void update(float dt) override;
	void render() override;

	void keyPressed(const sf::Keyboard::Key& key) override;

	void mousePressed(const sf::Mouse::Button& button) override;

private:

	sf::Font m_cormorant_Bold;
	ScalingText m_return_text;
};