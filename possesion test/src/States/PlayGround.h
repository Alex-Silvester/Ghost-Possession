#pragma once

#include "../Entities/Entities.h"
#include "../Objects/Objects.h"
#include "../GameObject.h"
#include "../constants.h"
#include "State.h"

#include <iostream>

class PlayGround : public State
{
public:

	PlayGround() {};

	bool init(std::shared_ptr<sf::RenderWindow> window) override;
	void update(float dt) override;
	void render() override;

	void keyPressed(const sf::Event& event);
	void keyReleased(const sf::Event& event);

	void mousePressed(const sf::Event& event);
	void mouseReleased(const sf::Event& event);

private:

	void physicsCollision(GameObject & moving_obj, GameObject& static_obj);

private:

	sf::Texture m_player_texture;
	Player m_player;

	sf::Texture m_box_texture;
	std::vector<Box> m_boxes;

	PObject m_possession_test;

};