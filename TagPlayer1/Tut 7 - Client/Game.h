/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "Player.h"
#include "Client.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

	std::string sendPosition();
	std::string sendCollidingStatus();
	//std::string sendID();
	std::string sendNum();
private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void getNumberOfPlayer(std::string& string);

	sf::Vector2f getPosFromServer(std::string& opponentPos, bool smaller);
	int len(std::string string);
	void split(std::string string, char seperator, bool smaller);

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game

	Player player;
	Player NOT_player; 
	Player NOT_player_2;

	Client myClient;

	std::string opponentPosArray[3];
	std::string opponentPosArray_2[3];

	int numberOfPlayer = 0;

	std::string check;
};

#endif // !GAME_HPP

