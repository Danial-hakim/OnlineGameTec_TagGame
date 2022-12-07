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

	player.init(1);
	NOT_player.init(2);
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
	player.update();

	player.checkCollision(NOT_player.getBody());

	if (!myClient.SendString(sendPosition()))
	{
		std::cout << "Failed to send position" << std::endl;
	}


	//if (!myClient.SendString(sendCollidingStatus()))
	//{
	//	std::cout << "Failed to send collision status" << std::endl;
	//}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	NOT_player.render(m_window);
	player.render(m_window);
	m_window.display();
}

sf::Vector2f Game::getPosFromServer(std::string& opponentPos)
{
	char seperator = ',';
	split(opponentPos,seperator);
	return sf::Vector2f(std::stof(opponentPosArray[0]), std::stof(opponentPosArray[1]));
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

void Game::split(std::string string, char seperator)
{
	int currIndex = 0, i = 0;
	int startIndex = 0, endIndex = 0;
	while (i <= len(string))
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
}
