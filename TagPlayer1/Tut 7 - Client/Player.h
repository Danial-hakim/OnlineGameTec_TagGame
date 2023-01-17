#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include <sstream>
#include "ScreenSize.h"

enum class Role
{
	Chaser,
	Runner
};

class Player
{
public:

	void init(std::string stringID);
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
	int convertStringToID(std::string stringID);
	bool isIDSet();

	std::string getChecked();
	void checkState();

	void updateTimer();

	bool bothPlayerReady = false;

private:

	sf::RectangleShape player;
	bool isColliding = false;

	int playerID = -1;
	sf::Color color;

	bool IDSet = false;
	Role currentRole;

	sf::Clock clock;
	int timer;

	sf::Font font;
	sf::Text timerText;
	sf::Text stateText;

	bool gameOver = false;

	int seconds = 0;
	int minutes = 0;

	bool isInvincible = true;
};

