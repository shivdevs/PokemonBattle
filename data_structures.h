// Author: Harshiv Mistry
// Date: 10-29-2024
//
// This file contains the class declerations that manage the data structures for this project -- Node class, & BST class.

/*
 * BST Tree Implementation for Pokemon Battle Simulation
 * 
 * This file defines two classes: `Node` and `BST`.
 * - `Node` represents individual nodes in the BST tree. Each node holds up to two Pokémon pointers and three child pointers.
 *   It includes getters, setters, and a custom copy constructor for managing data and children pointers.
 * - `BST` is the main class managing the BST tree structure. It supports insertion, display, and removal of Pokémon nodes.
 *   It also includes a custom copy constructor and recursive functions to manage the tree structure.
 * 
 * Data organization:
 * - Pokémon data in each `Node` is stored in an array `data[2]`.
 * - Child nodes are stored in an array `child[3]` where `child[0]` is left, `child[1]` is middle, and `child[2]` is right.
 * - The tree sorts data with less values going to the left, greater values going to the right, and in-between values in the middle.
 * 
 */

#include "pokemon.h"

/* This class represents the node used for the BST in 
 * in this project. 
 */
class Node
{
	public:
		Node();                                // Default constructor
		~Node();                               // Destructor
		Node(const Node &source);              // Copy constructor
		Node & operator=(const Node & source);	//only copies data to avoid shallow copy
		Node *&get_left();                     // Returns the left child pointer
		Node *&get_right();                    // Returns the right child pointer
		Pokemon *&get_data();                  // Returns the Pokemon pointer

		void set_left(Node *new_left);         // Sets the left child pointer
		void set_right(Node *new_right);       // Sets the right child pointer
		void set_data(Pokemon *new_data);      // Sets the Pokemon pointer

	private:
		Pokemon *data;                         // Pointer to Pokemon object
		Node *left;                            // Pointer to left child
		Node *right;                           // Pointer to right child
		void copy(const Pokemon * source);			//copies data.
};


class BST
{
public:
    BST();                                 // Default constructor
    ~BST();                                // Destructor
    BST(const BST &source);                // Copy constructor
	BST & operator=(const BST & source);	//overloaded assignment operator.
    int insert(Pokemon *to_add);           // Inserts a Pokemon into the tree
    int display_all() const;               // Displays all Pokemon in the tree
    int remove_all();                      // Removes all Pokemon from the tree
    int remove_specific(const string &name_to_remove); // Removes a specific Pokemon
    Pokemon *& retrieve(const string &name_to_find); // Retrieves a Pokemon by name

private:
    Node *root;                            // Root node of the BST

    // Recursive helper functions
    int insert(Node *&root, Pokemon *to_add);
    int display_all(Node *root) const;
    int remove_all(Node *&root);
    int remove_specific(Node *&root, const string &name_to_remove);
    Pokemon *& retrieve(Node * root, const string &name_to_find);
	int copy(Node *& dest, Node * src);
    // Helper for removing a node
    Node *find_ios(Node * root) const;   // Finds the node with the minimum value in a subtree
};

