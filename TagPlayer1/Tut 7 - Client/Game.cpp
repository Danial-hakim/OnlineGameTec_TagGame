/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>


/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ ScreenSize::width, ScreenSize::height, 32U }, "PLAYER 1" },
	m_exitGame{false}, myClient("127.0.0.1", 623) //when true game will exit
{
	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
	}
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps

	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

std::string Game::sendPosition()
{
	return player.getPos();
}

std::string Game::sendCollidingStatus()
{
	return player.getCollisionStatus();
}

//std::string Game::sendID()
//{
//	return std::string(std::to_string(player.getPlayerID()));
//}

std::string Game::sendNum()
{
	return player.getChecked();
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	if (!player.isIDSet())
	{
		player.init(myClient.getID_Message());
	}
	player.update();

	player.checkCollision(NOT_player.getBody());

	if (numberOfPlayer == 3)
	{
		NOT_player.setPosition(getPosFromServer(myClient.getPositionMessage(), true));
		NOT_player_2.setPosition(getPosFromServer(myClient.getPositionMessage(), false));
	}
	else
	{
		NOT_player.setPosition(getPosFromServer(myClient.getPositionMessage(),true));
	}

	if (!myClient.SendPosition(sendPosition()))
	{
		std::cout << "Failed to send position" << std::endl;
	}

	if (!myClient.SendNum(sendNum()))
	{
		std::cout << "Failed to receive number of player" << std::endl;
	}
	else
	{
		getNumberOfPlayer(myClient.getPlayerNum_Message());
	}

	//if (!myClient.Send_ID(sendID()))
	//{
	//	std::cout << "Failed to send ID" << std::endl;
	//}
	if (!NOT_player.isIDSet() && !opponentPosArray[0].empty())
	{
		NOT_player.init(opponentPosArray[0]);
		std::cout << NOT_player.getPlayerID() << std::endl;
	}

	if (numberOfPlayer == 3 && !NOT_player_2.isIDSet() && !opponentPosArray_2[0].empty())
	{
		NOT_player_2.init(opponentPosArray_2[0]);
		std::cout << NOT_player_2.getPlayerID() << std::endl;
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	NOT_player.render(m_window);
	NOT_player_2.render(m_window);
	player.render(m_window);
	m_window.display();
}

void Game::getNumberOfPlayer(std::string& string)
{
	if (!string.empty())
	{
		if (string == "1" || string == "2" || string == "3")
		{
			//std::cout << string << std::endl;
			numberOfPlayer = std::stoi(string);
		}
	}
}

sf::Vector2f Game::getPosFromServer(std::string& opponentPos, bool smaller)
{
	if (smaller)
	{
		if (!opponentPos.empty())
		{
			char seperator = ',';
			split(opponentPos, seperator,smaller);
			return sf::Vector2f(std::stof(opponentPosArray[1]), std::stof(opponentPosArray[2]));
		}
	}
	else if(!smaller && numberOfPlayer == 3)
	{
		if (!opponentPos.empty())
		{
			char seperator = ',';
			split(opponentPos, seperator, smaller);
			return sf::Vector2f(std::stof(opponentPosArray_2[1]), std::stof(opponentPosArray_2[2]));
		}
	}
	
	return sf::Vector2f(0, 0);
}

int Game::len(std::string string)
{
	int length = 0;

	for (int i = 0; string[i] != '\0'; i++)
	{
		length++;
	}
	return length;
}

void Game::split(std::string string, char seperator, bool smaller)
{
	int currIndex = 0, i = 0;
	int startIndex = 0, endIndex = 0;

	while (i <= len(string))
	{
		if (smaller)
		{
			if (string[i] == seperator || i == len(string))
			{
				endIndex = i;
				std::string subStr = "";
				subStr.append(string, startIndex, endIndex - startIndex);
				opponentPosArray[currIndex] = subStr;
				currIndex += 1;
				startIndex = endIndex + 1;
			}
			i++;
		}
		else if (!smaller && numberOfPlayer == 3)
		{
			if (string[i] == seperator || i == len(string))
			{
				endIndex = i;
				std::string subStr = "";
				subStr.append(string, startIndex, endIndex - startIndex);
				opponentPosArray_2[currIndex] = subStr;
				currIndex += 1;
				startIndex = endIndex + 1;
			}
			i++;
		}
	}

	//std::cout << "=============================" << std::endl;
	//std::cout << opponentPosArray[0] << " : " << opponentPosArray[1] << "," << opponentPosArray[2] << std::endl;
	//std::cout << opponentPosArray_2[0] << " : " << opponentPosArray_2[1] << "," << opponentPosArray_2[2] << std::endl;
	//std::cout << "=============================" << std::endl;
}
