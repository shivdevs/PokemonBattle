// Author: Harshiv Mistry
// Date: 10-29-2024
//
// This file contains the implementation of Trainer class and Game class. 

/*
 * Overview:
 * - `Trainer` Class:
 *   - Manages a trainer's Pokemon team using a BST.
 *   - Provides functionality to build a team, display the team, remove all Pokemon, and retrieve a Pokemon for battle.
 *
 * - `Stadium` Class:
 *   - Facilitates battles between two trainers and manages the game flow.
 *   - Includes functionality to set up trainers, start battles, display scores, and navigate a user-friendly menu.
 *
 * Key Features:
 * - Interactive menu system for the user to engage with the simulation.
 * - Turn-based battle system where players choose actions for their Pokemon until one faints.
 * - Dynamic interaction between trainers and their Pokemon teams.
 */

#include "battle.h"

/****** TRAINER CLASS IMPLEMENTATION *****/
// Default constructor initializes the trainer's name.
Trainer::Trainer() : name("")
{}

// Destructor removes all Pokemon from the team.
Trainer::~Trainer()
{ 
	name = "";
}

//returns a random number from the given range
int Trainer::random_num(int min, int max)
{
	if (min > max) {
		throw "Invalid Range: min should be <= max.";
	}
	random_device rd;
	mt19937 gen(rd());	//gets the random num	
	uniform_int_distribution<> distrib(min,max);
	return distrib(gen);

}

//returns name for simplicity.
const string &Trainer::get_name() const
{
	return name;
}

//sets the passed in name to the this name.
int Trainer::set_name(string & toset)
{
	name = toset;
	return 1;
}
// Builds a team of Pokemon with randomly decided types.
int Trainer::build_team(int size)
{
	if (size <= 0)
	{
		cerr << "Invalid team size. Must be greater than 0." << endl;
		return -1;
	}

	for (int i = 0; i < size; ++i)
	{
		int type = random_num(1, 3); // Randomly decide Pokemon type (1 = Fire, 2 = Water, 3 = Grass)
		Pokemon *new_pokemon = nullptr;

		if (type == 1)
		{
			new_pokemon = new Fire();
		}
		else if (type == 2)
		{
			new_pokemon = new Water();
		}
		else if (type == 3)
		{
			new_pokemon = new Grass();
		}
		else
		{
			cerr << "Error: Invalid Pokemon type generated." << endl;
			continue;
		}

		add_pokemon(new_pokemon);
	}

	return 0; // Success
}

// Adds a new Pokemon to the trainer's team.
int Trainer::add_pokemon(Pokemon *new_pokemon)
{
	if (!new_pokemon)
	{
		cerr << "Invalid Pokemon pointer. Cannot add to the team." << endl;
		return -1;
	}

	// Insert into the team's 2-3 tree
	my_pokemons.insert(new_pokemon);
	cout << "\t" << new_pokemon->get_name() << " added to " << name << "'s team." << endl;
	return 0;
}

// Displays the entire team of Pokemon.
void Trainer::display_team() const
{
	cout << name << "'s Pokemon Team:" << endl;
	my_pokemons.display_all(); // Assumes `display_all()` prints the entire tree
}

// Removes all Pokemon from the trainer's team.
void Trainer::remove_all_pokemon()
{
	my_pokemons.remove_all(); // Assumes `remove_all()` clears the tree
	cout << name << "'s team has been cleared." << endl;
}

// Prompts the user to choose a Pokemon by name and retrieves it from the team.
Pokemon *&Trainer::send_to_battle()
{
	string chosen_name; // Store the Pokemon name input by the user
	cout << "\nCurrent Team: " << endl;
	display_team();
	cin.clear();
	//cin.ignore(1000, '\n');
	// Prompt the user to pick a Pokemon by name
	cout << endl << name << endl << "Choose a Pokemon to battle by its name: ";
	getline(cin, chosen_name);
	return my_pokemons.retrieve(chosen_name);	//returns the pokemon returned from retrieve function.
}

/***** END OF TRAINER CLASS *****/




/******* GAME CLASS IMPLEMENTATION ********/
// Default constructor for the Stadium
Stadium::Stadium():trainer1_wins(0), trainer2_wins(0)
{
	cout << "Welcome to the Pokemon Stadium!" << endl;
}

//Destructor
Stadium::~Stadium()
{
	trainer1_wins = 0;
	trainer2_wins = 0;
}
//sets the name for the users.
void Stadium::set_trainers()
{
	string name;
	// Trainer 1 setup
	//cin.ignore();	
	cout << "Enter Trainer 1's name: ";
	getline(cin, name);
	//cin.ignore(1000, '\n');
	trainer1 = Trainer();
	trainer1.set_name(name); // Assuming Trainer has a set_name function

	cout << "Enter the size of Trainer 1's team (max:50): ";
	int size = input(1, 50); // Assuming team size between 1 and 10
	trainer1.build_team(size);

	//clear local name
	//name = "";
	// Trainer 2 setup


	//cin.ignore();	
	cout << "Enter Trainer 2's name: ";
	getline(cin, name);
	//cin.ignore(1000, '\n');
	trainer2 = Trainer();
	trainer2.set_name(name);

	cout << "Enter the size of Trainer 2's team (max:50): ";
	size = input(1, 50);
	trainer2.build_team(size);

	cout << "Trainers and their teams are ready for battle!" << endl;
}

// displays menu until quitting.
void Stadium::display_menu()
{
	int choice = 0;

	do
	{
		// Display menu options
		cout << "\n--- Pokemon Stadium Menu ---" << endl;
		cout << "1. Start a Battle" << endl;
		cout << "2. Display a Trainer's Team" << endl;
		cout << "3. Show Score" << endl;
		cout << "4. Clear Team (Remove all for BST)." << endl;
			cout << "5. Quit" << endl;
		cout << "Enter your choice: ";

		choice = input(1, 5);

		// Menu handlin with if-else
		if (choice == 1)
		{
			start_battle();
		}
		else if (choice == 2)
		{
			// Display a trainer's team
			cout << "Display team for which trainer? (1 = Trainer 1, 2 = Trainer 2): ";
			int trainer_choice = input(1, 2);
			if (trainer_choice == 1)
			{
				trainer1.display_team();
			}
			else
			{
				trainer2.display_team();
			}
		}
		else if (choice == 3)
		{
			show_score();
		}
		else if (choice == 4)
		{
			cout << "Clear team for which trainer? (1 = Trainer 1, 2 = Trainer 2): ";
			int trainer_choice = input(1, 2);
			if (trainer_choice == 1)
			{
				trainer1.remove_all_pokemon();
			}
			else
			{
				trainer2.remove_all_pokemon();
			}
		}
		else if (choice == 5)
		{
			cout << "Exiting Pokemon Stadium. Goodbye!" << endl;
		}
	} while (choice != 5);
}

//starts the battle for both users.
void Stadium::start_battle()
{
	cout << "\nThe battle between " << trainer1.get_name() << " and " << trainer2.get_name() << " begins!" << endl;

	Pokemon *pokemon1 = trainer1.send_to_battle();
	cout << "\n\n";
	pokemon1->display();	
	cout << "\nReady to Battle!!!\n";
	Pokemon *pokemon2 = trainer2.send_to_battle();
	cout << "\n\n";
	pokemon1->display();	
	cout << "\nReady to Battle!!!\n";

	if (!pokemon1 || !pokemon2)
	{
		cerr << "Error: Unable to retrieve Pokemon for battle!" << endl;
		return;
	}

	// Perform the battle
	int result = battle(pokemon1, pokemon2);

	// Update scores and display the result
	if (result == 1)
	{
		trainer1_wins++;
	}
	else if (result == 2)
	{
		trainer2_wins++;
	}
}


//prompts for input and does error checking.
int Stadium::input(int min, int max) const
{
	int user_input = 0;
	bool valid = false;

	while (!valid)
	{
		cin >> user_input;
		cin.ignore(1000,'\n');
		if (cin.fail() || user_input < min || user_input > max)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
		}
		else
		{
			valid = true;
		}
	}

	return user_input;
}

//shows scores for both players.
void Stadium::show_score() const
{
	cout << "\n--- Current Score ---" << endl;
	cout << trainer1.get_name() << ": " << trainer1_wins << " wins" << endl;
	cout << trainer2.get_name() << ": " << trainer2_wins << " wins" << endl;
}

//lets the pokemons battle each other.
int Stadium::battle(Pokemon *first, Pokemon *second)
{
	if (!first || !second)
	{
		cerr << "Error: Null Pokemon pointers passed to the battle function!" << endl;
		return -1; // Indicates an error
	}

	cout << "\n--- Battle Beins ---" << endl;
	cout << first->get_name() << " (Health: " << first->get_health() << ")"
		<< " vs. "
		<< second->get_name() << " (Health: " << second->get_health() << ")" << endl;

	// Continue the battle until one Pokemon's health reaches 0
	while (first->get_health() > 0 && second->get_health() > 0)
	{
		// Player 1's turn
		cout << "\nWhat should " << first->get_name() << " do? (1 = Attack, 2 = Special Ability): ";
		int choice = input(1, 2);

		int first_action = 0;
		if (choice == 1)
		{
			first_action = first->attack();
			cout << first->get_name() << " attacks!" << endl;
		}
		else if (choice == 2)
		{
			first_action = first->special_ability();
			cout << first->get_name() << " uses its special ability!" << endl;
		}

		int damage_to_second = first_action - second->defend();
		if (damage_to_second < 0) damage_to_second = 0;

		second->reduce_health(damage_to_second);
		cout << first->get_name() << " dealt " << damage_to_second << " damage to "
			<< second->get_name() << "." << endl;
		cout << second->get_name() << " (Remaining Health: " << second->get_health() << ")" << endl;

		if (second->get_health() <= 0)
		{
			cout << second->get_name() << " fainted! " << first->get_name() << " wins the battle!" << endl;
			return 1; // First Pokemon wins
		}

		// Player 2's turn
		cout << "\nWhat should " << second->get_name() << " do? (1 = Attack, 2 = Special Ability): ";
		choice = input(1, 2);

		int second_action = 0;
		if (choice == 1)
		{
			second_action = second->attack();
			cout << second->get_name() << " attacks!" << endl;
		}
		else if (choice == 2)
		{
			second_action = second->special_ability();
			cout << second->get_name() << " uses its special ability!" << endl;
		}

		int damage_to_first = second_action - first->defend();
		if (damage_to_first < 0) damage_to_first = 0;

		first->reduce_health(damage_to_first);
		cout << second->get_name() << " dealt " << damage_to_first << " damage to "
			<< first->get_name() << "." << endl;
		cout << first->get_name() << " (Remaining Health: " << first->get_health() << ")" << endl;

		if (first->get_health() <= 0)
		{
			cout << first->get_name() << " fainted! " << second->get_name() << " wins the battle!" << endl;
			return 2; // Second Pokemon wins
		}
	}

	return 0; // Should not reach here, but added for completeness
}
