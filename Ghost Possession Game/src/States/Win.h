#pragma once

#include "State.h"

#include "../Tools/Objects/ScalingText.h"

class Win : public State
{
public:

	Win() :State(WIN) {};

	bool init(std::shared_ptr<sf::RenderWindow> window) override;

	void update(float dt) override;
	void render() override;

	void mousePressed(const sf::Mouse::Button& button) override;

private:

	ScalingText m_return_text;

	sf::Font m_font;

};