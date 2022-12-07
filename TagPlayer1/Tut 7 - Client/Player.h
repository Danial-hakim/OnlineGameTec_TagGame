#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>

class Player
{
public:
	
	void init(int ID);
	void render(sf::RenderWindow& win);
	void update();
	void checkInput();

	void tempInput();

	void checkCollision(sf::RectangleShape opponent);

	sf::RectangleShape getBody();

	std::string getPos();

	std::string getCollisionStatus();

	void setPosition(sf::Vector2f newPos);

	void setColor();

	void setPlayerID(int ID);

	int getPlayerID();

private:

	sf::RectangleShape player;

	bool isColliding = false;

	int playerID = -1;

	sf::Color color;
};

