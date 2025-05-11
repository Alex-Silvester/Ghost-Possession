
#include "PlayGround.h"

bool PlayGround::init(std::shared_ptr<sf::RenderWindow> window)
{
	State::init(window);

	if (!m_player_texture.loadFromFile("../possesion test/Data/Ghost.png"))
	{
		printf("[ERROR] Failed to load player texture\n");
		return false;
	}

	m_player = Player(m_player_texture);
	m_player.init({ 0,cst::s_gravity });
	m_player.scale(4, 4);

	if (!m_box_texture.loadFromFile("../possesion test/Data/yellow_block.png"))
	{
		printf("[ERROR] Failed to load player texture\n");
		return false;
	}

	for (int i = 0; i < 10; i++)
	{
		m_boxes.emplace_back(Box(m_box_texture));
		m_boxes.back().scale(4, 4);
		m_boxes.back().setPosition(sf::Vector2f( i * m_boxes.back().getSprite().getGlobalBounds().size.x, 300));
	}

	m_possession_test = PObject(m_box_texture);
	m_possession_test.scale(6, 12);
	m_possession_test.setPosition(300,10);

	return true;
}

void PlayGround::update(float dt)
{
	m_player.update(dt);

	if(!m_player.isPossessingObject())
	{
		for(auto& box : m_boxes)
		{
			physicsCollision(m_player, box);
		}
		physicsCollision(m_player, m_possession_test);
	}
	else if(PObject* obj = dynamic_cast<PObject*>(m_player.getPossessedObject()))
	{
		for(auto& box : m_boxes)
		{
			physicsCollision(*obj, box);
		}
	}
}

#define PLAYER_POS_CHECK true
void PlayGround::render()
{
#if PLAYER_POS_CHECK == false
	m_window->draw(m_player);
#endif
	for(auto& box : m_boxes)
	{
		m_window->draw(box);
	}
	m_window->draw(m_possession_test);

#if PLAYER_POS_CHECK == true
	m_window->draw(m_player);
#endif
}

void PlayGround::keyPressed(const sf::Event& event)
{
	if (m_player.isPossessingObject())
	{
		m_player.getPossessedObject()->keyPressed(event);
	}
	else
	{
		m_player.keyPressed(event);
	}
	if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::LControl)
	{
		if(!m_player.isPossessingObject())
		{
			m_player.possess(&m_possession_test);
		}
		else
		{
			m_player.unpossess();
		}
	}
}

void PlayGround::keyReleased(const sf::Event& event)
{
	if (m_player.isPossessingObject())
	{
		m_player.getPossessedObject()->keyReleased(event);
	}
	else
	{
		m_player.keyReleased(event);
	}
}

void PlayGround::mousePressed(const sf::Event& event)
{
}

void PlayGround::mouseReleased(const sf::Event& event)
{
}

void PlayGround::physicsCollision(GameObject & moving_obj, GameObject& static_obj)
{
	if (moving_obj.intersects(static_obj.getFloatRect()))
	{
		if(auto temp = dynamic_cast<IPhysicsObject*>(&moving_obj))
		{
			temp->outsideCollision(moving_obj.getSprite(), static_obj.getFloatRect());
		}
	}
}
