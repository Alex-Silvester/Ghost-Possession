#pragma once

#include "State.h"
#include "../Objects/GameObject.h"
#include "../Tools/Level/LevelTools.h"

#include "../Entities/Player.h"

class Play : public State
{
public:

	Play() : State(PLAY) {}
	~Play();

	bool init(std::shared_ptr<sf::RenderWindow> window) override;
	void update(float dt) override;
	void render() override;

	void keyPressed(const sf::Keyboard::Key& key) override;
	void keyReleased(const sf::Keyboard::Key& key) override;

	int* getLevelPtr() { return &m_level; }

private:

	void reset();

	void physicsCollision(Visual& moving_obj, const Visual& static_obj);

private:

	std::shared_ptr<sf::Texture> m_box_texture = std::make_shared<sf::Texture>();
	std::vector<GameObject*> m_boxes;

	std::shared_ptr<sf::Texture> m_player_texture = std::make_shared<sf::Texture>();
	Player m_player;

	int m_level = 0;

	using StartFlag = GameEntity;
	using EndFlag = GameEntity;

	std::optional<StartFlag> m_start;
	std::optional<EndFlag> m_end;

	std::shared_ptr<sf::Texture> m_flag_texture = std::make_shared<sf::Texture>();

};