#include"MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& t_window) : Screen(t_window)
{
}

void MainMenu::init()
{
	sf::String Texts[] = { "Tag Game", "Play", "Instructions", "Exit" };
	initialise(3, Texts);
}

void MainMenu::firstButtonPress(int& t_lvlChecker)
{
	SceneTypes::updateScene(Scenes::MAIN_GAME);
}

void MainMenu::secondButtonPress(int& t_lvlChecker)
{
	SceneTypes::updateScene(Scenes::TUTORIAL);
}

void MainMenu::thirdButtonPress(int& t_lvlChecker)
{

}

void MainMenu::fourthButtonPress(int& t_lvlChecker)
{
	
}