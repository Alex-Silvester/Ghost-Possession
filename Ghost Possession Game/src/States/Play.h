#pragma once

#include "State.h"
#include "../Objects/GameObject.h"

#include "../Tools/Level/LevelTools.h"

class Play : public State
{
public:

	Play() : State(PLAY) {}
	~Play();

	bool init(std::shared_ptr<sf::RenderWindow> window) override;
	void update(float dt) override;
	void render() override;

	void keyPressed(const sf::Keyboard::Key& key) override;

	int* getLevelPtr() { return &m_level; }

private:

	void reset();

private:

	std::shared_ptr<sf::Texture> m_box_texture = std::make_shared<sf::Texture>();
	std::vector<GameObject*> m_boxes;

	int m_level = 0;

};