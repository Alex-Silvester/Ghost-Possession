
#include "PossessableBox.h"

void PossessableBox::keyPressed(const sf::Event& event)
{
	sf::Keyboard::Key code = event.getIf<sf::Event::KeyPressed>()->code;
	using namespace sf::Keyboard;
	
	if (code == Key::D && !keyHeld.D)
	{
		keyHeld.D = true;
		m_velocity += {100.f, 0};
	}
}

void PossessableBox::keyReleased(const sf::Event& event)
{
	sf::Keyboard::Key code = event.getIf<sf::Event::KeyReleased>()->code;
	using namespace sf::Keyboard;

	if (code == Key::D && keyHeld.D)
	{
		keyHeld.D = false;
		m_velocity += {-100.f, 0};
	}
}

sf::Vector2f PossessableBox::updateMovement(float dt)
{
	m_sprite->move(m_velocity * dt);

	return m_sprite->getPosition();
}
