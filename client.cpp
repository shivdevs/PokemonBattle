// Author: Harshiv Mistry
// Date: 10-29-2024
//
// This file acts as the client for this project. 

#include "battle.h"

int main()
{
	try
    {
        // Initial Setup
        cout << "Welcome to the Pokemon Battle Simulation!" << endl;

        // Create the Stadium (game manager)
        Stadium new_game;

        // Set up trainers and their teams
        new_game.set_trainers();
		//testing mode.	
		//new_game.start_battle();
        // Display the main menu to start the gameplay loop
        new_game.display_menu();
    }
    catch (const string &e)
    {
        cerr << "Error: " << e << endl;
    }
    catch (...)
    {
        cerr << "An unknown error occurred!" << endl;
    }

    return 0;
}
