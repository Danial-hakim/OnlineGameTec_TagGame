#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "Player.h"
#include "Client.h"

class MainGame
{
public:

	MainGame(sf::RenderWindow& t_window);
	std::string sendPosition();
	std::string sendCollidingStatus();
	std::string sendNum();

	void processEvents();
	void processKeys(sf::Event t_event);
	void update();
	void render(sf::RenderWindow& t_window);

private:

	void getNumberOfPlayer(std::string& string);

	sf::Vector2f getPosFromServer(std::string& opponentPos, bool smaller);
	int len(std::string string);
	void split(std::string string, char seperator, bool smaller);

	Player player;
	Player NOT_player;
	Player NOT_player_2;

	Client myClient;

	std::string opponentPosArray[3];
	std::string opponentPosArray_2[3];

	int numberOfPlayer = 0;

	std::string check;
};