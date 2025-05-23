#pragma once

#include <iostream>
#include <fstream>

#include "Objects/Objects.h"

#define BLOCK_DATA_POINTS 5
union BlockData
{
	struct
	{
		int width;
		int height;
		int position_x;
		int position_y;
		int block_type;
	};

	int data[BLOCK_DATA_POINTS] = {};
};

class Editor
{
public:

	bool init(std::string path);
	void run();
	void end();

private:

	void update();
	void render();

	void keyPressed   (const sf::Keyboard::Key& key);
	void keyReleased  (const sf::Keyboard::Key& key);
	void mousePressed (const sf::Mouse::Button& button);
	void mouseReleased(const sf::Mouse::Button& button);

	void createBlockArray(const std::vector<BlockData>& block_data);

private:
	
	sf::RenderWindow m_window = sf::RenderWindow(sf::VideoMode({ 720,540 }), "");

	std::vector<Visual> blocks;

	sf::RectangleShape m_outline_rect;

	std::shared_ptr<sf::Texture> m_texture = std::make_shared<sf::Texture>(sf::Texture("Data/Stone Tile Map.png"));

	bool mouse_held = false;

	std::string m_path;

	sf::Vector2f m_mouse_start;

	unsigned int m_current_type = 0;

	std::shared_ptr<sf::Font> m_font = std::make_shared<sf::Font>();

	std::unique_ptr<Visual> m_selected_visual = std::make_unique<Visual>();

};