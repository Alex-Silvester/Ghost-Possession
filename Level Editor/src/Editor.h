#pragma once

#include <iostream>
#include <fstream>

#include "Objects/Objects.h"

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

private:
	
	sf::RenderWindow m_window = sf::RenderWindow(sf::VideoMode({ 720,540 }), "");

	std::vector<Visual> blocks;

	sf::RectangleShape m_outline_rect;

	std::shared_ptr<sf::Texture> m_texture = std::make_shared<sf::Texture>(sf::Texture("Data/Stone Tile Map.png"));

	bool mouse_held = false;

	std::string m_path;

};