#include "MainGame.h"

MainGame::MainGame(sf::RenderWindow& t_window): myClient("127.0.0.1", 623)
{
	t_window.setVerticalSyncEnabled(true);
	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
	}
}

std::string MainGame::sendPosition()
{
    return player.getPos();
}

std::string MainGame::sendCollidingStatus()
{
    return player.getCollisionStatus();
}

std::string MainGame::sendNum()
{
    return player.getChecked();
}

void MainGame::processEvents()
{
}

void MainGame::processKeys(sf::Event t_event)
{
}

void MainGame::update()
{
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
		NOT_player.setPosition(getPosFromServer(myClient.getPositionMessage(), true));
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

	if (!NOT_player.isIDSet() && !opponentPosArray[0].empty())
	{
		NOT_player.init(opponentPosArray[0]);
		player.bothPlayerReady = true;
		std::cout << NOT_player.getPlayerID() << std::endl;
	}

	if (numberOfPlayer == 3 && !NOT_player_2.isIDSet() && !opponentPosArray_2[0].empty())
	{
		NOT_player_2.init(opponentPosArray_2[0]);
		std::cout << NOT_player_2.getPlayerID() << std::endl;
	}
}

void MainGame::render(sf::RenderWindow& t_window)
{
	NOT_player.render(t_window);
	NOT_player_2.render(t_window);
	player.render(t_window);
}

void MainGame::getNumberOfPlayer(std::string& string)
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

sf::Vector2f MainGame::getPosFromServer(std::string& opponentPos, bool smaller)
{
	if (smaller)
	{
		if (!opponentPos.empty())
		{
			char seperator = ',';
			split(opponentPos, seperator, smaller);
			return sf::Vector2f(std::stof(opponentPosArray[1]), std::stof(opponentPosArray[2]));
		}
	}
	else if (!smaller && numberOfPlayer == 3)
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

int MainGame::len(std::string string)
{
	int length = 0;

	for (int i = 0; string[i] != '\0'; i++)
	{
		length++;
	}
	return length;
}

void MainGame::split(std::string string, char seperator, bool smaller)
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
}
