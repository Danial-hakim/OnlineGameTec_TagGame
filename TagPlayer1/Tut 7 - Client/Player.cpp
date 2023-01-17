#include "Player.h"

void Player::init(std::string stringID)
{
	//playerID = convertStringToID(stringID);
	//playerID = 0;
	
	setPlayerID(convertStringToID(stringID));

	setColor();

	player.setSize(sf::Vector2f(100, 100));
	player.setPosition(sf::Vector2f(500, 500));

	if (!font.loadFromFile("Assets/Fonts/alien.ttf"))
	{
		std::cout << "Unable to load font." << std::endl;
	}

	timerText.setFont(font);
	timerText.setCharacterSize(75);
	timerText.setPosition(ScreenSize::width / 2, 20);
	timerText.setFillColor(sf::Color::Green);

	stateText.setFont(font);
	stateText.setCharacterSize(150);
	stateText.setPosition((ScreenSize::width / 2) - 100, ScreenSize::height / 2);
	stateText.setFillColor(sf::Color::Magenta);

	roleText.setFont(font);
	roleText.setCharacterSize(50);
	roleText.setFillColor(sf::Color::White);
}

void Player::render(sf::RenderWindow& win)
{
	win.draw(player);
	win.draw(roleText);
	win.draw(timerText);

	if (gameOver)
	{
		win.draw(stateText);
	}
}

void Player::update()
{
	
	if (!gameOver && bothPlayerReady)
	{
		updateTimer();
	}

	if (playerID == 0)
	{
		checkInput();
	}
	else if(playerID == 1)
	{
		tempInput();
	}
	updateTextPosition();
	checkState();
	checkBoundary();
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
	if (!isInvincible)
	{
		if (player.getGlobalBounds().intersects(opponent.getGlobalBounds()))
		{
			player.setFillColor(sf::Color::White);
			isColliding = true;
		}
		else
		{
			player.setFillColor(color);
			isColliding = false;
		}
	}
}

sf::RectangleShape Player::getBody()
{
	return player;
}

std::string Player::getPos()
{
	return std::to_string(getPlayerID()) + "," + std::to_string(player.getPosition().x) + "," + std::to_string(player.getPosition().y);
}

std::string Player::getCollisionStatus()
{
	return std::to_string(isColliding); // 1 is colliding , 0 is not 
}

void Player::setPosition(sf::Vector2f newPos)
{
	player.setPosition(newPos);
}

void Player::setColor()
{
	switch (playerID)
	{
	case 1:
		color = sf::Color::Blue;
		currentRole = Role::Runner;
		roleText.setString("Runner");
		break;
	case 2:
		color = sf::Color::Yellow;
		break;
	default:
		color = sf::Color::Red;
		currentRole = Role::Chaser;
		roleText.setString("Chaser");
		break;
	}

	player.setFillColor(color);
}

void Player::setPlayerID(int ID)
{
	playerID = ID;
	setColor();
	IDSet = true;
}

int Player::getPlayerID()
{
	return playerID;
}

int Player::convertStringToID(std::string stringID)
{
	std::istringstream stream(stringID);
	int result;
	stream >> result;
	return result;
}

bool Player::isIDSet()
{
	return IDSet;
}

std::string Player::getChecked()
{
	return std::to_string(10);
}

void Player::checkState()
{
	if (isColliding)
	{
		if (currentRole == Role::Chaser)
		{
			stateText.setString("YOU WIN");
		}
		else
		{
			stateText.setString("YOU LOSE");
		}
		gameOver = true;
	}
}

void Player::updateTimer()
{
	timer = clock.getElapsedTime().asSeconds();
	
	if (timer >= 1.0f)
	{
		clock.restart();
		seconds++;
		if (seconds == 60)
		{
			minutes++;
			seconds = 0;
		}
	}

	if (isInvincible && seconds == 10)
	{
		isInvincible = false;
	}
	timerText.setString(std::to_string(minutes) + ":" + std::to_string(seconds));

}

void Player::checkBoundary()
{
	if (player.getPosition().x < 0)
	{
		player.setPosition(ScreenSize::width,player.getPosition().y);
	}

	if (player.getPosition().x > ScreenSize::width)
	{
		player.setPosition(0, player.getPosition().y);
	}
	if (player.getPosition().y < 0)
	{
		player.setPosition(player.getPosition().x,ScreenSize::height);
	}

	if (player.getPosition().y > ScreenSize::height)
	{
		player.setPosition(player.getPosition().x, 0);
	}
}

void Player::updateTextPosition()
{
	roleText.setPosition(sf::Vector2f(player.getPosition().x - 20, player.getPosition().y - 70));
}


