
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

	m_box = Box(m_box_texture);
	m_box.scale(24,12);
	m_box.setPosition(0, 300);

	m_possession_test = PossessableBox(m_box_texture);
	m_possession_test.scale(6, 12);
	m_possession_test.setPosition(300,10);

	return true;
}

void PlayGround::update(float dt)
{
	m_player.update(dt);

	if(!m_player.isPossessingObject())
	{
		physicsCollision(m_box);
		physicsCollision(m_possession_test);
	}
}

void PlayGround::render()
{
	m_window->draw(m_player);
	m_window->draw(m_box);
	m_window->draw(m_possession_test);
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

void PlayGround::physicsCollision(GameObject& obj)
{
	//if player intersects with a block
	if (m_player.intersects(obj.getFloatRect()) && dynamic_cast<IPhysicsObject*>(&m_box))
	{
		//if the player is moved up from the block
		if (m_player.outsideCollision(m_player.getSprite(), obj.getFloatRect()).y < 0)
		{
			//the player is on the ground (set velocity to 0 to stop adding too much velocity)
			m_player.isGrounded();
		}
	}
}
