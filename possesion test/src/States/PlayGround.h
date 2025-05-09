#pragma once

#include "../Entities/Entities.h"
#include "../Objects/Objects.h"
#include "../GameObject.h"
#include "State.h"

class PlayGround : public State
{
public:

	PlayGround() {};

	bool init(std::shared_ptr<sf::RenderWindow> window) override;
	void update(float dt) override;
	void render() override;

private:

	sf::Texture m_player_texture;
	Player m_player;

	sf::Texture m_box_texture;
	Box m_box;
};