#pragma once

#include "State.h"
#include "../Tools/Objects/ScalingText.h"

class Start : public State
{
public:

	Start() : State(START) {}

	bool init(std::shared_ptr<sf::RenderWindow> window) override;
	void update(float dt) override;
	void render() override;

	void mousePressed(const sf::Mouse::Button& key) override;

private:

	sf::Font m_font;

	ScalingText m_menu_text;
	ScalingText m_play_text;
	ScalingText m_quit_text;

};