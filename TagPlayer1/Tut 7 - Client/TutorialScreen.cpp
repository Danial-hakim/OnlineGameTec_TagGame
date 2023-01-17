#include "TutorialScreen.h"

TutorialScreen::TutorialScreen(sf::RenderWindow& t_window) : Screen(t_window)
{
}

void TutorialScreen::init()
{
	sf::String Texts[] = { "Instruction","Back" };
	initialise(1, Texts);

	buttonSprites[0].setPosition(ScreenSize::width * 0.83f, ScreenSize::height * 0.83f);
	buttonText[0].setPosition(buttonSprites[0].getPosition() + sf::Vector2f(0, BUTTON_TEXT_OFFSET));
}

void TutorialScreen::firstButtonPress(int& t_lvlChecker)
{
	SceneTypes::updateScene(Scenes::MENU);
}