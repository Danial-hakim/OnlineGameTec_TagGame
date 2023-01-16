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
#include "MainGame.h"
#include "MainMenu.h"
#include "TutorialScreen.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(double t_deltaTime);
	void render();
	void processGameEvent(sf::Event& event);

	MainGame mainGame;
	MainMenu mainMenu;
	TutorialScreen tutorialScreen;

	sf::RenderWindow m_window; // main SFML window
	sf::Font gameFont; // font used by message
	bool m_exitGame; // control exiting game
};

#endif // !GAME_HPP

