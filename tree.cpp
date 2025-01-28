// Author: Harshiv Mistry
// Date: 10-29-2024
//
// This file contains the implementation for the node class and tree_23 class.

/*
 * Overview:
 * - `Node` Class:
 *   - Represents individual nodes in the BST.
 *   - Stores a single `Pokemon` pointer and manages left and right child pointers.
 *   - Includes functionality for deep copying and safely managing dynamic memory.
 *
 * - `BST` Class:
 *   - Implements a Binary Search Tree to store and manage Pokemon objects.
 *   - Provides functionality for insertion, retrieval, removal, and in-order traversal.
 *   - Ensures proper memory management with a destructor, copy constructor, and assignment operator.
 *
 * Key Features:
 * - Recursive implementations for all core tree operations.
 * - Dynamic memory safety with deep copies and pointer management.
 * - Integration with the Pokemon class hierarchy for battle simulation.
 */

#include "data_structures.h"

//default constructor
Node::Node(): data{nullptr}, left{nullptr}, right{nullptr}
{}

//destructor
Node::~Node()
{
	if (data)
		delete data;
	data = nullptr;
	//intentially only delete data, left and right
	//are to be handled by the BST class.
}

//custom copy constructor.
Node::Node(const Node &source)
{
	if (source.data)
	{
		try
		{
			copy(source.data);	//deep copy w/ RTTI to copy the correct data.
		}
		catch (const string &e)
		{
			cerr << "Error in Node copy constructor: " << e << endl;
			throw;
		}
	}
}

//custom overloaded operator
Node & Node::operator=(const Node & source)
{
	if (this == &source)
	{
		return *this; // Handle self-assignment
	}

	try
	{
		// Clean up existing data
		if (data)
		{
			delete data;
			data = nullptr;
		}

		// Deep copy the data
		if (source.data)
		{
			copy(source.data);	//deep copy w/ RTTI to copy the correct data.
		}

		// Child pointers remain unchanged, as they are managed by the tree structure
	}
	catch (const string &e)
	{
		cerr << "Error in Node::operator=: " << e << endl;
		throw;
	}

	return *this;
}

//returns left for recursion
Node *& Node::get_left()
{
	return left;
}

//returns right for recursion
Node *& Node::get_right()
{
	return right;
}

//returns the data for retrival.
Pokemon *& Node::get_data()
{
	return data;
}


//sets the passed in left to left.
void Node::set_left(Node *new_left)
{
	left = new_left;
}

//sets the passed in right to right.
void Node::set_right(Node *new_right)
{
	right = new_right;
}

//sets the passed in data to data.
void Node::set_data(Pokemon *new_data)
{
	data = new_data;	
}

void Node::copy(const Pokemon * source)
{
	if (!source)
	{
		throw string("Invalid source passed to Node::copy.");
	}

	try
	{
		// Attempt to dynamic_cast to each derived type
		const Fire *fire_ptr = dynamic_cast<const Fire *>(source);
		const Water *water_ptr = dynamic_cast<const Water *>(source);
		const Grass *grass_ptr = dynamic_cast<const Grass *>(source);

		// Allocate based on the type
		if (fire_ptr)
			data = new Fire(*fire_ptr); // Deep copy Fire
		else if (water_ptr)
			data = new Water(*water_ptr); // Deep copy Water
		else if (grass_ptr)
			data = new Grass(*grass_ptr); // Deep copy Grass
		else
			throw string("Unsupported Pokemon type in Node::copy.");
	}
	catch (const string &e)
	{
		cerr << "Error in Node::copy: " << e << endl;
		throw;
	}	
}
/****** END OF NODE CLASS ******/





/************************************************************/
/*					BST IMPLEMENTATION 						*/

// Default constructor
BST::BST(): root(nullptr)
{}

// Destructor
BST::~BST()
{
    try
    {
        remove_all();
    }
    catch (const string &e)
    {
        cerr << "Exception in destructor: " << e << endl;
    }
}

// Copy constructor
BST::BST(const BST &source): root(nullptr)
{
    if (source.root)
    {
        copy(root, source.root);
    }
}

// Overloaded assignment operator
BST &BST::operator=(const BST &source)
{
    if (this != &source)
    {
        remove_all(); // Clear current tree
        copy(root, source.root); // Copy source tree
    }
    return *this;
}

// Insert a Pokemon into the tree
int BST::insert(Pokemon *to_add)
{
    if (!to_add)
    {
        throw string("Cannot insert a null Pokemon.");
    }
    return insert(root, to_add);
}

// Display all Pokemon in the tree
int BST::display_all() const
{
    if (!root)
    {
        cout << "Tree is empty." << endl;
        return 0;
    }
    return display_all(root);
}

// Remove all Pokemon from the tree
int BST::remove_all()
{
    return remove_all(root);
}

// Remove a specific Pokemon
int BST::remove_specific(const string &name_to_remove)
{
    if (name_to_remove.empty())
    {
        throw string("Name to remove cannot be empty.");
    }
    return remove_specific(root, name_to_remove);
}

// Retrieve a Pokemon by name
Pokemon *&BST::retrieve(const string &name_to_find)
{
    if (name_to_find.empty())
    {
        throw string("Name to find cannot be empty.");
    }
    return retrieve(root, name_to_find);
}

// Recursive helper for insertion
int BST::insert(Node *&root, Pokemon *to_add)
{
    if (!root)
    {
        root = new Node;
		root->set_data(to_add);
        return 1;
    }
    if (to_add->get_name() < root->get_data()->get_name())
    {
        return insert(root->get_left(), to_add);
    }
    return insert(root->get_right(), to_add);
}

// Recursive helper for displaying all nodes
int BST::display_all(Node *root) const
{
    if (!root)
    {
        return 0;
    }
    display_all(root->get_left());
	cout << "\n===================\n";
	root->get_data()->display();
	cout << "\n===================\n";
    display_all(root->get_right());
    return 1;
}

// Recursive helper to remove all nodes
int BST::remove_all(Node *&root)
{
    if (!root)
    {
        return 0;
    }
    remove_all(root->get_left());
    remove_all(root->get_right());
    //delete root->get_data(); // Free the Pokemon object
    delete root; // Free the Node
    root = nullptr;
    return 1;
}

// Recursive helper to remove a specific node
int BST::remove_specific(Node *&root, const string &name_to_remove)
{
    if (!root)
    {
        return 0;
    }

    if (name_to_remove < root->get_data()->get_name())
    {
        return remove_specific(root->get_left(), name_to_remove);
    }
    else if (name_to_remove > root->get_data()->get_name())
    {
        return remove_specific(root->get_right(), name_to_remove);
    }
    else
    {
        Node *temp = root;
        if (!root->get_left())
        {
            root = root->get_right();
        }
        else if (!root->get_right())
        {
            root = root->get_left();
        }
        else
        {
            Node *min_node = find_ios(root->get_right());
            root->get_data() = min_node->get_data();
            remove_specific(root->get_right(), min_node->get_data()->get_name());
        }
        delete temp->get_data();
        delete temp;
        return 1;
    }
}

// Recursive helper to retrieve a node by name
Pokemon *&BST::retrieve(Node *root, const string &name_to_find)
{
    if (!root)
    {
        throw string("Pokemon not found.");
    }
    if (name_to_find < root->get_data()->get_name())
    {
        return retrieve(root->get_left(), name_to_find);
    }
    else if (name_to_find > root->get_data()->get_name())
    {
        return retrieve(root->get_right(), name_to_find);
    }
    return root->get_data();
}

// Recursive helper to copy tree nodes
int BST::copy(Node *&dest, Node *src)
{
    if (!src)
    {
        return 0;
    }

    dest = new Node(*src); // Deep copy Pokemon
    copy(dest->get_left(), src->get_left());
    copy(dest->get_right(), src->get_right());
    return 1;
}

// Recursive helper to find the minimum node
Node *BST::find_ios(Node *root) const
{
    if (!root)
    {
        throw string("Tree is empty. Cannot find minimum.");
    }
    if (!root->get_left())
    {
        return root;
    }
    return find_ios(root->get_left());
}
