// Author: Harshiv Mistry
// Date: 10-29-2024
//
// This file contains the implementation of the core hierarchy used in this project -- Pokemon; Fire; Water; Grass

// Nagivation ---- Pokemon: Line 44
// 			  ---- Fire: 	Line 197
//			  ---- Water: 	Line 425
//			  ---- Grass: 	Line 632

/**********************************************************
 * Pokemon.cpp
 * This file contains the implementation of the core Pokemon
 * base class (an Abstract Base Class) and its derived
 * specialized types: Fire, Water, and Grass.
 *
 * Class Details:
 * 1. Pokemon (Base Class):
 *    - Provides shared attributes (e.g., name, health) and
 *      common behaviors (e.g., heal, set_name).
 *    - Includes virtual methods (attack, defend, special_ability)
 *      for dynamic binding.
 *    - Overloads comparison operators for integration with 2-3
 *      tree data structures.
 *
 * 2. Fire (Derived Class):
 *    - Implements Fire-specific attributes and abilities, such as
 *      burn damage and flying power.
 *    - Overrides base class functions for Fire-type behavior.
 *
 * 3. Water (Derived Class):
 *    - Implements Water-specific attributes and abilities, such as
 *      splash resistance and Aqua Blast attacks.
 *    - Overrides base class functions for Water-type behavior.
 *
 * 4. Grass (Derived Class):
 *    - Implements Grass-specific attributes and abilities, such as
 *      the entangle ability to stop opponents from defending.
 *    - Overrides base class functions for Grass-type behavior.
 *
 **********************************************************/
#include "pokemon.h"

/* Overview Here */

/********** Pokemon Class Implementation **********/

//default constructor
Pokemon::Pokemon():name(""), health(100)
{}

//destructor
Pokemon::~Pokemon()
{
	name = "";
	health =0;
}

//displays the name and the health
void Pokemon::display()
{
	cout << "\nName: " << name << endl << "Health: " << health << endl;
}

//heals the health to a random amount.
int Pokemon::heal()
{
	health += random_num(10,20);
	return health;
}

//this function assigns a name based on passed in type.
//	(1) = Fire Based Pokemon
//	(2) = Water Based Pokemon
//	(3) = Grass Based Pokemon
int Pokemon::set_name(int type)
{
	// Create arrays of names using smart pointers
	static unique_ptr<string[]> fire_names(new string[5]{"Charmander", "Vulpix", "Flareon", "Torchic", "Ponyta"});
	static unique_ptr<string[]> water_names(new string[5]{"Squirtle", "Psyduck", "Lapras", "Vaporeon", "Totodile"});
	static unique_ptr<string[]> grass_names(new string[5]{"Bulbasaur", "Chikorita", "Leafeon", "Turtwig", "Oddish"});

	try 
	{
		int index = random_num(0, 4); // Random index from 0 to 4

		if (type == 1) { // Fire-type Pokemon
			name = fire_names[index];
		} else if (type == 2) { // Water-type Pokemon
			name = water_names[index];
		} else if (type == 3) { // Grass-type Pokemon
			name = grass_names[index];
		} else {
			throw invalid_argument("Invalid type passed to set_name!");
		}
	} 
	catch (const invalid_argument& e)
	{
		cerr << "Error: " << e.what() << endl;
		return -1;
	}

	return 0; // Success	
}

//returns a random number from the given range
int Pokemon::random_num(int min, int max)
{
	if (min > max) {
		throw "Invalid Range: min should be <= max.";
	}
	random_device rd;
	mt19937 gen(rd());	//gets the random num	
	uniform_int_distribution<> distrib(min,max);
	return distrib(gen);

}

//prompts the user for input error checks for wrong data types
//and also bound checks for the passed in range.
int Pokemon::input(int min, int max)
{
	int user_input{0};	//stores user's input
	int valid{0};	//flag used for error checking incorrect input.
	do
	{
		cin >> user_input;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid Input! Please enter an Interger\n";
		}
		else if (user_input < min || user_input > max)
		{
			cout << "\nInvalid Choice!\nTry again!!\n";
		}
		else
			valid = 1;
	}while (!valid || (user_input < min || user_input > max));
	return user_input;
}

//returns health for the battle logic in this game.
int Pokemon::get_health()
{
    return health;
}

//reduces health by the passed in damage so simulate
//fight.
void Pokemon::reduce_health(int damage)
{
    health -= damage;
    if (health < 0)
        health = 0; // Ensure health doesn't drop below 0
}

//returns name for battle logic.
const string & Pokemon::get_name() const
{
    return name;
}

/*Overloaded operators are intentionally left empty */
//real implementation is done in the derived class overloaded operators.
bool Pokemon::operator <(const Pokemon * op2)
{
	return false;
}
bool Pokemon::operator >(const Pokemon * op2)
{
	return false;
}
bool Pokemon::operator >=(const Pokemon * op2)
{
	return false;
}
bool Pokemon::operator <=(const Pokemon * op2)
{
	return false;
}
bool Pokemon::operator ==(const Pokemon * op2)
{
	return false;
}
bool Pokemon::operator !=(const Pokemon * op2)
{
	return false;
}
/*** END OF Pokemon (ABC) class ***/




/********** FIRE CLASS IMPLEMENTATION ***********/

// Constructor initializes the Fire Pokemon with default attributes and assigns a name.
Fire::Fire()
    : attack_power(50), defend_power(30), fly_power(20), burn_damage(15)
{
    try
    {
        set_name(1); // Assigns a Fire-type name using the base class function
    }
    catch (const string &e)
    {
        cerr << "Error in Fire::Fire() - " << e << endl;
        throw; // Re-throw the exception for higher-level handling if necessary
    }
}

// Destructor
Fire::~Fire()
{
	
}

// Displays all attributes of the Fire Pokemon.
void Fire::display()
{
    try
    {
        cout << "Fire Pokemon: " << name << endl;
        cout << "Health: " << health << endl;
        cout << "Attack Power: " << attack_power << endl;
        cout << "Defend Power: " << defend_power << endl;
        cout << "Fly Power: " << fly_power << endl;
        cout << "Burn Damage: " << burn_damage << endl;
    }
    catch (const string &e)
    {
        cerr << "Error in Fire::display() - " << e << endl;
    }
}

// Executes an attack and returns the total damage dealt (attack power + burn damage).
int Fire::attack()
{
    try
    {
        if (attack_power <= 0 || burn_damage <= 0)
        {
            throw string("Invalid attack or burn damage in Fire::attack()");
        }
        cout << name << " attacks with Fire Blast!" << endl;
        return attack_power + burn_damage;
    }
    catch (const string &e)
    {
        cerr << "Error in Fire::attack() - " << e << endl;
        return 0;
    }
}

// Defends against an attack and returns the defense power.
int Fire::defend()
{
    try
    {
        if (defend_power <= 0)
        {
            throw string("Invalid defend power in Fire::defend()");
        }
        cout << name << " defends against the attack!" << endl;
        return defend_power;
    }
    catch (const string &e)
    {
        cerr << "Error in Fire::defend() - " << e << endl;
        return 0;
    }
}

// Executes the special ability and returns double the burn damage.
int Fire::special_ability()
{
    try
    {
        if (burn_damage <= 0)
        {
            throw string("Invalid burn damage in Fire::special_ability()");
        }
        cout << name << " uses Inferno! Massive burn damage!" << endl;
        return burn_damage * 2;
    }
    catch (const string &e)
    {
        cerr << "Error in Fire::special_ability() - " << e << endl;
        return 0;
    }
}

// Dodges an attack by flying and returns the fly power.
int Fire::fly()
{
    try
    {
        if (fly_power <= 0)
        {
            throw string("Invalid fly power in Fire::fly()");
        }
        cout << name << " flies to dodge the attack!" << endl;
        return fly_power;
    }
    catch (const string &e)
    {
        cerr << "Error in Fire::fly() - " << e << endl;
        return 0;
    }
}

// Compares this Pokemon's name with another's (less than).
bool Fire::operator<(const Pokemon *op2)
{
    try
    {
        if (!op2)
        {
            throw string("Null pointer passed to Fire::operator<");
        }
        return this->name < op2->get_name();
    }
    catch (const string &e)
    {
        cerr << "Error in Fire::operator< - " << e << endl;
        return false;
    }
}

// Compares this Pokemon's name with another's (greater than).
bool Fire::operator>(const Pokemon* op2)
{
    try
    {
        if (!op2)
        {
            throw string("Null pointer passed to Fire::operator>");
        }
        return this->name > op2->get_name();
    }
    catch (const string& e)
    {
        cerr << "Error in Fire::operator> - " << e << endl;
        return false;
    }
}

// Compares this Pokemon's name with another's (less than or equal to).
bool Fire::operator<=(const Pokemon* op2)
{
    try
    {
        if (!op2)
        {
            throw string("Null pointer passed to Fire::operator<=");
        }
        return this->name <= op2->get_name();
    }
    catch (const string& e)
    {
        cerr << "Error in Fire::operator<= - " << e << endl;
        return false;
    }
}

// Compares this Pokemon's name with another's (greater than or equal to).
bool Fire::operator>=(const Pokemon* op2)
{
    try
    {
        if (!op2)
        {
            throw string("Null pointer passed to Fire::operator>=");
        }
        return this->name >= op2->get_name();
    }
    catch (const string& e)
    {
        cerr << "Error in Fire::operator>= - " << e << endl;
        return false;
    }
}

// Checks if this Pokemon's name is equal to another's.
bool Fire::operator==(const Pokemon* op2)
{
    try
    {
        if (!op2)
        {
            throw string("Null pointer passed to Fire::operator==");
        }
        return this->name == op2->get_name();
    }
    catch (const string& e)
    {
        cerr << "Error in Fire::operator== - " << e << endl;
        return false;
    }
}

// Checks if this Pokemon's name is not equal to another's.
bool Fire::operator!=(const Pokemon* op2)
{
    try
    {
        if (!op2)
        {
            throw string("Null pointer passed to Fire::operator!=");
        }
        return this->name != op2->get_name();
    }
    catch (const string& e)
    {
        cerr << "Error in Fire::operator!= - " << e << endl;
        return false;
    }
}
/*** END OF Fire Class ***/



/******* WATER CLASS IMPLEMENTATION ********/

// Constructor initializes the Water Pokemon with default attributes and assigns a name.
Water::Water()
    : attack_power(40), defend_power(35), splash_resistance(20)
{
    try
    {
        set_name(2); // Assigns a Water-type name using the base class function
    }
    catch (const string &e)
    {
        cerr << "Error in Water::Water() - " << e << endl;
        throw; // Re-throw the exception for higher-level handling if necessary
    }
}

// Destructor
Water::~Water()
{
}

// Displays all attributes of the Water Pokemon.
void Water::display()
{
    try
    {
        cout << "Water Pokemon: " << name << endl;
        cout << "Health: " << health << endl;
        cout << "Attack Power: " << attack_power << endl;
        cout << "Defend Power: " << defend_power << endl;
        cout << "Splash Resistance: " << splash_resistance << endl;
    }
    catch (const string &e)
    {
        cerr << "Error in Water::display() - " << e << endl;
    }
}

// Executes an attack and returns the total damage dealt.
int Water::attack()
{
    try
    {
        if (attack_power <= 0)
        {
            throw string("Invalid attack power in Water::attack()");
        }
        cout << name << " attacks with Aqua Blast!" << endl;
        return attack_power;
    }
    catch (const string &e)
    {
        cerr << "Error in Water::attack() - " << e << endl;
        return 0;
    }
}

// Defends against an attack and returns the defense power.
int Water::defend()
{
    try
    {
        if (defend_power <= 0)
        {
            throw string("Invalid defend power in Water::defend()");
        }
        cout << name << " defends against the attack!" << endl;
        return defend_power;
    }
    catch (const string &e)
    {
        cerr << "Error in Water::defend() - " << e << endl;
        return 0;
    }
}

// Executes the special ability and reduces burn damage by half.
int Water::special_ability()
{
    try
    {
        if (splash_resistance <= 0)
        {
            throw string("Invalid splash resistance in Water::special_ability()");
        }
        cout << name << " uses Splash Shield! Reduces burn damage by half!" << endl;
        return splash_resistance;
    }
    catch (const string &e)
    {
        cerr << "Error in Water::special_ability() - " << e << endl;
        return 0;
    }
}

// Compares this Pokemon's name with another's (less than).
bool Water::operator<(const Pokemon *op2)
{
    try
    {
        if (!op2)
        {
            throw string("Null pointer passed to Water::operator<");
        }
        return this->name < op2->get_name();
    }
    catch (const string &e)
    {
        cerr << "Error in Water::operator< - " << e << endl;
        return false;
    }
}

// Compares this Pokemon's name with another's (greater than).
bool Water::operator>(const Pokemon *op2)
{
    try
    {
        if (!op2)
        {
            throw string("Null pointer passed to Water::operator>");
        }
        return this->name > op2->get_name();
    }
    catch (const string &e)
    {
        cerr << "Error in Water::operator> - " << e << endl;
        return false;
    }
}

// Compares this Pokemon's name with another's (less than or equal to).
bool Water::operator<=(const Pokemon *op2)
{
    try
    {
        if (!op2)
        {
            throw string("Null pointer passed to Water::operator<=");
        }
        return this->name <= op2->get_name();
    }
    catch (const string &e)
    {
        cerr << "Error in Water::operator<= - " << e << endl;
        return false;
    }
}

// Compares this Pokemon's name with another's (greater than or equal to).
bool Water::operator>=(const Pokemon *op2)
{
    try
    {
        if (!op2)
        {
            throw string("Null pointer passed to Water::operator>=");
        }
        return this->name >= op2->get_name();
    }
    catch (const string &e)
    {
        cerr << "Error in Water::operator>= - " << e << endl;
        return false;
    }
}

// Checks if this Pokemon's name is equal to another's.
bool Water::operator==(const Pokemon *op2)
{
    try
    {
        if (!op2)
        {
            throw string("Null pointer passed to Water::operator==");
        }
        return this->name == op2->get_name();
    }
    catch (const string &e)
    {
        cerr << "Error in Water::operator== - " << e << endl;
        return false;
    }
}

// Checks if this Pokemon's name is not equal to another's.
bool Water::operator!=(const Pokemon *op2)
{
    try
    {
        if (!op2)
        {
            throw string("Null pointer passed to Water::operator!=");
        }
        return this->name != op2->get_name();
    }
    catch (const string &e)
    {
        cerr << "Error in Water::operator!= - " << e << endl;
        return false;
    }
}
/*** END OF Water Class ***/



/******* GRASS CLASS IMPLEMENTATION ********/
// Constructor initializes the Grass Pokemon with default attributes and assigns a name.
Grass::Grass()
    : attack_power(45), defend_power(25), entangle(15)
{
    try
    {
        set_name(3); // Assigns a Grass-type name using the base class function
    }
    catch (const std::string &e)
    {
        std::cerr << "Error in Grass::Grass() - " << e << std::endl;
        throw; // Re-throw the exception for higher-level handling if necessary
    }
}

// Destructor
Grass::~Grass()
{
}

// Displays all attributes of the Grass Pokemon.
void Grass::display()
{
    try
    {
        std::cout << "Grass Pokemon: " << name << std::endl;
        std::cout << "Health: " << health << std::endl;
        std::cout << "Attack Power: " << attack_power << std::endl;
        std::cout << "Defend Power: " << defend_power << std::endl;
        std::cout << "Entangle Power: " << entangle << std::endl;
    }
    catch (const std::string &e)
    {
        std::cerr << "Error in Grass::display() - " << e << std::endl;
    }
}

// Executes an attack and returns the total damage dealt.
int Grass::attack()
{
    try
    {
        if (attack_power <= 0)
        {
            throw std::string("Invalid attack power in Grass::attack()");
        }
        std::cout << name << " attacks with Leaf Blade!" << std::endl;
        return attack_power;
    }
    catch (const std::string &e)
    {
        std::cerr << "Error in Grass::attack() - " << e << std::endl;
        return 0;
    }
}

// Defends against an attack and returns the defense power.
int Grass::defend()
{
    try
    {
        if (defend_power <= 0)
        {
            throw std::string("Invalid defend power in Grass::defend()");
        }
        std::cout << name << " defends against the attack!" << std::endl;
        return defend_power;
    }
    catch (const std::string &e)
    {
        std::cerr << "Error in Grass::defend() - " << e << std::endl;
        return 0;
    }
}

// Executes the special ability and stops the opponent from defending.
int Grass::special_ability()
{
    try
    {
        if (entangle <= 0)
        {
            throw std::string("Invalid entangle power in Grass::special_ability()");
        }
        std::cout << name << " uses Vine Entangle! Stops opponent from defending!" << std::endl;
        return entangle;
    }
    catch (const std::string &e)
    {
        std::cerr << "Error in Grass::special_ability() - " << e << std::endl;
        return 0;
    }
}

// Compares this Pokemon's name with another's (less than).
bool Grass::operator<(const Pokemon *op2)
{
    try
    {
        if (!op2)
        {
            throw std::string("Null pointer passed to Grass::operator<");
        }
        return this->name < op2->get_name();
    }
    catch (const std::string &e)
    {
        std::cerr << "Error in Grass::operator< - " << e << std::endl;
        return false;
    }
}

// Compares this Pokemon's name with another's (greater than).
bool Grass::operator>(const Pokemon *op2)
{
    try
    {
        if (!op2)
        {
            throw std::string("Null pointer passed to Grass::operator>");
        }
        return this->name > op2->get_name();
    }
    catch (const std::string &e)
    {
        std::cerr << "Error in Grass::operator> - " << e << std::endl;
        return false;
    }
}

// Compares this Pokemon's name with another's (less than or equal to).
bool Grass::operator<=(const Pokemon *op2)
{
    try
    {
        if (!op2)
        {
            throw std::string("Null pointer passed to Grass::operator<=");
        }
        return this->name <= op2->get_name();
    }
    catch (const std::string &e)
    {
        std::cerr << "Error in Grass::operator<= - " << e << std::endl;
        return false;
    }
}

// Compares this Pokemon's name with another's (greater than or equal to).
bool Grass::operator>=(const Pokemon *op2)
{
    try
    {
        if (!op2)
        {
            throw std::string("Null pointer passed to Grass::operator>=");
        }
        return this->name >= op2->get_name();
    }
    catch (const std::string &e)
    {
        std::cerr << "Error in Grass::operator>= - " << e << std::endl;
        return false;
    }
}

// Checks if this Pokemon's name is equal to another's.
bool Grass::operator==(const Pokemon *op2)
{
    try
    {
        if (!op2)
        {
            throw std::string("Null pointer passed to Grass::operator==");
        }
        return this->name == op2->get_name();
    }
    catch (const std::string &e)
    {
        std::cerr << "Error in Grass::operator== - " << e << std::endl;
        return false;
    }
}

// Checks if this Pokemon's name is not equal to another's.
bool Grass::operator!=(const Pokemon *op2)
{
    try
    {
        if (!op2)
        {
            throw std::string("Null pointer passed to Grass::operator!=");
        }
        return this->name != op2->get_name();
    }
    catch (const std::string &e)
    {
        std::cerr << "Error in Grass::operator!= - " << e << std::endl;
        return false;
    }
}
/*** END OF GRASS IMPLEMENTATION ***/
