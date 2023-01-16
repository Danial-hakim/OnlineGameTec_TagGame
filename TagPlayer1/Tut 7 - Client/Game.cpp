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
	m_exitGame{false} , mainGame(m_window), mainMenu(m_window), tutorialScreen(m_window)//when true game will exit
{
	mainMenu.init();
	tutorialScreen.init();
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
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		processEvents();

		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame.asMicroseconds() / 500);
		}

		render();
	}
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}

		processGameEvent(event);
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
void Game::update(double t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	switch (SceneTypes::currentScene)
	{
	case Scenes::MAIN_GAME:
		mainGame.update();
		break;
	case Scenes::MENU:
		mainMenu.update(m_window);
		break;
	case Scenes::TUTORIAL:
		tutorialScreen.update(m_window);
		break;
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	switch (SceneTypes::currentScene)
	{
	case Scenes::MAIN_GAME:
		mainGame.render(m_window);
		break;
	case Scenes::MENU:
		mainMenu.render(m_window);
		break;
	case Scenes::TUTORIAL:
		tutorialScreen.render(m_window);
		break;
	}
	m_window.display();
}

void Game::processGameEvent(sf::Event& event)
{
	if (sf::Event::KeyPressed == event.type || sf::Event::KeyReleased == event.type
		|| event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseMoved
		|| event.type == sf::Event::MouseButtonReleased)
	{
		switch (SceneTypes::currentScene)
		{
		case Scenes::MAIN_GAME:
			mainGame.processEvents();
			break;
		case Scenes::MENU:
			mainMenu.processGameEvents(event, m_window);
			break;
		case Scenes::TUTORIAL:
			tutorialScreen.processGameEvents(event, m_window);
			break;
		}

	}
}
