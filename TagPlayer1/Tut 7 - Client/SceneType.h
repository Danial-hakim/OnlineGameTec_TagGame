#pragma once

enum class Scenes
{
	MAIN_GAME,
	MENU,
	GAME_OVER,
	TUTORIAL
};

class SceneTypes
{
public:
	static Scenes currentScene;
	static Scenes previousScene;
	static void updateScene(Scenes newScene);
};