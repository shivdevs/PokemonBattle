// Author: Harshiv Mistry
// Date: 10-29-2024
//
// This file contains the class declarations for the Trainer class and Stadium class. 

/*
 * Trainer and Stadium Classes for Pokemon Battle Simulation
 * 
 * This file defines the `Trainer` and `Stadium` classes, which together simulate Pokémon battles between trainers.
 * 
 * - `Trainer` Class:
 *   - Manages a Pokémon team using a 2-3 tree (`my_pokemons`), allowing the trainer to build a team, add Pokémon, 
 *     choose Pokémon for battle, and display or remove their entire team.
 *   - Attributes include the trainer's name and their Pokémon collection.
 * 
 * - `Stadium` Class:
 *   - Represents the battle arena where two trainers (`trainer1` and `trainer2`) compete.
 *   - Provides functionality to set trainers, start a battle, display each trainer's team, and perform individual Pokémon battles.
 * 
 * This structure facilitates battles through dynamic interactions between trainers and their Pokémon teams.
 * 
 */

#include "data_structures.h"

/* This class is represent a individual trainer, which can have 
 * multiple pokemons -- stored using a 2-3 tree. trainer also 
 * has a nickname stored.
 */
class Trainer
{
	public:
		Trainer();			//constructor
		~Trainer();			//destructor
		int build_team(int size);	//builds the team of certain size.
		int add_pokemon(Pokemon * new_pokemon);	//adds the pokemon passed in to the team.
		int choose_battle();	//choose your pokemon for batte
		int set_name(string & toset);		//prompts the user for name. 
		const string &get_name() const;    // Retrieves the trainer's name
		int random_num(int min, int max);	//random number function for ease of access.
		void display_team() const;	//displays the entire team of pokemons.
		void remove_all_pokemon();	//removes the entire team;
		Pokemon *& send_to_battle();	//sends one of the pokemons to battle.
	private:
		BST my_pokemons;	//the pokemons trainer has collected so far.
		string name;	//name of the trainer
};

/* This class is responsible for the staduim related activites needed to make 
 * this project work, such as fighting, and building the trainers.
 */
class Stadium
{
	public:
		Stadium();		// Constructor
		~Stadium();		// Destructor
		void set_trainers();	// Prompt to set trainers and their teams
		void display_menu();	// Show the game menu and handle user input
		void start_battle();	// Start a battle between the trainers
		void display_trainers() const; // Display either trainer's team
		void show_score() const;	// Display the current score for both trainers
		int battle(Pokemon * first, Pokemon * second);	//lets the passed in pokemons battle each other.
	private:
		Trainer trainer1;	// First trainer
		Trainer trainer2;	// Second trainer
		int trainer1_wins;	// Battles won by trainer 1
		int trainer2_wins;	// Battles won by trainer 2
		int input(int min, int max) const;// Helper function for input validation
};
