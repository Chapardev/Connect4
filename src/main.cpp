/*
 * main.cpp
 * Author: Eric-Nicolas
 * Description: Entry point of the program. Contains the game loop.
 */

#include "Game.hpp"

int main()
{
    Game game;
    
    while (game.IsRunning())
    {
        game.Update();
        game.Draw();
    }

	return 0;
}