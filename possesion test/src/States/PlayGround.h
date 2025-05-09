#pragma once

#include "State.h"

class PlayGround : public State
{
public:

	PlayGround() {};

	bool init(std::shared_ptr<sf::RenderWindow> window) override;
	void render() override;

private:

	sf::Texture m_player_texture;
	std::optional<sf::Sprite> m_player;
};