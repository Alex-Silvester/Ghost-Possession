#pragma once

#include <iostream>

#include "../Tools/Objects/ScalingText.h"

#include "State.h"

class LevelSelect : public State
{
public:

	LevelSelect() : State(LEVEL_SELECT) {}

	~LevelSelect()
	{
		delete level_ptr;
	}

	bool init(std::shared_ptr<sf::RenderWindow> window) override;
	void update(float dt) override;
	void render() override;

	void mousePressed(const sf::Mouse::Button& button) override;

	void keyPressed(const sf::Keyboard::Key& key) override;

	void setLevelPtr(int* lvl) { level_ptr = lvl; }

private:

	sf::Font m_font;
	std::vector<ScalingText> m_level_select_text;

	ScalingText m_return_text;

	int* level_ptr = nullptr;

};