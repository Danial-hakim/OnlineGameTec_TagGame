#include "Player.h"

void Player::init(int ID)
{
	player.setSize(sf::Vector2f(100, 100));
	player.setFillColor(sf::Color::Red);
	player.setPosition(sf::Vector2f(500, 500));

	playerID = ID;
}

void Player::render(sf::RenderWindow& win)
{
	win.draw(player);
}

void Player::update()
{
	if (playerID == 1)
	{
		checkInput();
	}
	else if(playerID == 2)
	{
		tempInput();
	}
}

void Player::checkInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		player.move(0, -10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		player.move(0, 10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.move(-10, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.move(10, 0);
	}
}

void Player::tempInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player.move(0, -10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player.move(0, 10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.move(-10, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.move(10, 0);
	}
}

void Player::checkCollision(sf::RectangleShape opponent)
{
	if (player.getGlobalBounds().intersects(opponent.getGlobalBounds()))
	{
		player.setFillColor(sf::Color::White);
		isColliding = true;
	}
	else
	{
		player.setFillColor(sf::Color::Red);
		isColliding = false;
	}
}

sf::RectangleShape Player::getBody()
{
	return player;
}

std::string Player::getPos()
{
	return std::to_string(player.getPosition().x) + " , " + std::to_string(player.getPosition().y);
}

std::string Player::getCollisionStatus()
{
	return std::to_string(isColliding); // 1 is colliding , 0 is not 
}

void Player::setPosition(sf::Vector2f newPos)
{
	player.setPosition(newPos);
}


