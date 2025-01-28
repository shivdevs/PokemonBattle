// Harshiv Mistry, 11-12-2024, CS302 Fall 2024, Program #3
// FileName: pokemon.h
//
// This file contains the class declarations for the core hierarchy of pokemons used in this project. 

/*
 * Pokemon Battle Simulation
 * 
 * This file defines an Abstract Base Class (ABC) `Pokemon` and three derived classes (`Fire`, `Water`, `Grass`).
 * Each Pokemon type implements common battle actions: `attack`, `defend`, and `heal`. 
 * 
 * `Pokemon` provides shared attributes (`name` and `health`) and virtual methods for dynamic binding.
 * `Fire` includes a unique `fly` method, demonstrating RTTI usage.
 * 
 * Comparison operators (`<` and `>=`) support Binary Search Tree (BST) storage for organizing Pokemon.
 */

#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <memory>

using namespace std;

/* This class is the base class in the core hierarchy, and is also 
 * a Abstract Base Class (ABC) with only one pure virtual function -- display().
 */
class Pokemon
{
	public:
		Pokemon();			//default constructor
		int heal();					//heals health by a random amount.
		int set_name(int type);		//sets the name according the type of pokemon.
		int random_num(int min, int max);	//returns a random number from the given range.
		int input(int min, int max);		//used for input validation and error checking.
		int get_health();		//returns health for battle logic.
		void reduce_health(int damage);	//takes damage for battle logic.
		const string & get_name() const;	//returns name for battle logic.
		/* VIRTUAL METHODS -- MUST IMPLEMENT IN DERIVED CLASSES */
		virtual ~Pokemon();	//virtual destructor so the right one gets called for dervied class
		virtual void display();		//displays the name
		virtual int attack()=0;		// 1 of 3 common characteristics -- pure virtual function
		virtual int defend()=0;		// 2 of 3 common characteristics -- pure virtual function
		virtual int special_ability()=0;			// 3 of 3 common characteristics
		virtual bool operator <(const Pokemon * op2);	//needed for BST Tree implementation
		virtual bool operator >(const Pokemon * op2);	//needed for BST Tree implementation
		virtual bool operator >=(const Pokemon * op2);	//needed for BST Tree implementation
		virtual bool operator <=(const Pokemon * op2);	//needed for BST Tree implementation
		virtual bool operator ==(const Pokemon * op2);	//needed for BST Tree implementation
		virtual bool operator !=(const Pokemon * op2);	//needed for BST Tree implementation
	protected:
		string name;	//name of the pokemon.
		int health;		// health of the pokemon (from 1-100).
};

/* This class is a specialized version of Pokemon, representing the Fire
 * type of pokemons. It is implemented with the expectation of dynamic binding 
 * in the base class. 
 * NOTE: RTTI will be needed to access the Fly function. 
 */
class Fire: public Pokemon
{
	public:
		Fire();			//default constructor 
		~Fire();			//destructor
		void display();		//displays all info.
		int attack();		// 1 of 3 common characteristics
		int defend();		// 2 of 3 common characteristics
		int special_ability();			// 3 of 3 common characteristics
		int fly();			//special characteristics -- RTTI needed to call
		bool operator <(const Pokemon * op2);	//needed for BST Tree implementation
		bool operator >(const Pokemon * op2);	//needed for BST Tree implementation
		bool operator >=(const Pokemon * op2);	//needed for BST Tree implementation
		bool operator <=(const Pokemon * op2);	//needed for BST Tree implementation
		bool operator ==(const Pokemon * op2);	//needed for BST Tree implementation
		bool operator !=(const Pokemon * op2);	//needed for BST Tree implementation

	protected:
		int attack_power;	//level of damage to other player.
		int defend_power;	//level of damage to defend w/o affecting health.
		int fly_power;  	//dodge attacks by flying up.
		int burn_damage;  	//additional damage by burning.
};

/* This class is a specialized version of Pokemon, representing the Water
 * type of pokemons. It is implemented with the expectation of dynamic binding 
 * in the base class. 
 */
class Water: public Pokemon
{
	public:
		Water();			//default constructor
		~Water();			//destructor
		void display();		//displays all info
		int attack();		// 1 of 3 common characteristics
		int defend();		// 2 of 3 common characteristics
		int special_ability();			// 3 of 3 common characteristics
		bool operator <(const Pokemon * op2);	//needed for BST Tree implementation
		bool operator >(const Pokemon * op2);	//needed for BST Tree implementation
		bool operator >=(const Pokemon * op2);	//needed for BST Tree implementation
		bool operator <=(const Pokemon * op2);	//needed for BST Tree implementation
		bool operator ==(const Pokemon * op2);	//needed for BST Tree implementation
		bool operator !=(const Pokemon * op2);	//needed for BST Tree implementation

	protected:
		int attack_power;	//level of damage to other player.
		int defend_power;	//level of damage to defend w/o affecting health.
		int splash_resistance;	//reduces burn damage by half.
};

/* This class is a specialized version of Pokemon, representing the Grass
 * type of pokemons. It is implemented with the expectation of dynamic binding 
 * in the base class. 
 */
class Grass: public Pokemon
{
	public:
		Grass();			//default constructor
		~Grass();			//destructor
		void display();		// displays all info.
		int attack();		// 1 of 3 common characteristics
		int defend();		// 2 of 3 common characteristics
		int special_ability();			// 3 of 3 common characteristics
		bool operator <(const Pokemon * op2);	//needed for BST Tree implementation
		bool operator >(const Pokemon * op2);	//needed for BST Tree implementation
		bool operator >=(const Pokemon * op2);	//needed for BST Tree implementation
		bool operator <=(const Pokemon * op2);	//needed for BST Tree implementation
		bool operator ==(const Pokemon * op2);	//needed for BST Tree implementation
		bool operator !=(const Pokemon * op2);	//needed for BST Tree implementation

	protected:
		int attack_power;	//level of damage to other player.
		int defend_power;	//level of damage to defend w/o affecting health.
		int entangle;		//stops opponents from defending.
};



