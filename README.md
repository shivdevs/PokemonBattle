# Pokémon Battle Simulation

## Overview

The **Pokémon Battle Simulation** is a C++ project designed to simulate Pokémon battles between two trainers. Players can create teams, engage in battles, and experience dynamic gameplay through a menu-driven interface. The project uses advanced object-oriented programming techniques, including inheritance, polymorphism, and custom data structures like a Binary Search Tree (BST), to manage Pokémon and simulate battles.

---

## Features

- **Trainer and Stadium Classes**:
  - Trainers can build Pokémon teams, display their rosters, and send Pokémon into battle.
  - The Stadium class manages the overall gameplay, including menu navigation and battles between trainers.

- **Core Pokémon Types**:
  - Three specialized Pokémon types: Fire, Water, and Grass.
  - Each type has unique abilities:
    - **Fire**: High attack power and special abilities like burn damage.
    - **Water**: Splash resistance and balanced stats.
    - **Grass**: Unique entangle ability to stop opponents from defending.

- **Battle System**:
  - Turn-based battles where players control Pokémon actions (e.g., attack, special ability).
  - Pokémon health dynamically decreases during battles, and the winner is determined when one Pokémon faints.

- **Data Structure**:
  - A Binary Search Tree (BST) organizes Pokémon teams for efficient retrieval and management.
  - Nodes in the BST store Pokémon objects, with deep copy and dynamic memory management for safety.

- **Menu-Driven Interface**:
  - Interactive gameplay with options to:
    - Start battles.
    - View and manage Pokémon teams.
    - Track scores.

---

## File Structure

- **`battle.h`** and **`battle.cpp`**:
  - Contains the implementation of the `Trainer` and `Stadium` classes.
  - Manages team building, menu navigation, and the battle system.

- **`pokemon.h`** and **`pokemon.cpp`**:
  - Defines the core Pokémon hierarchy:
    - Base class `Pokemon`.
    - Derived classes `Fire`, `Water`, and `Grass`.

- **`data_structures.h`** and **`tree.cpp`**:
  - Implements the Binary Search Tree (BST) for managing Pokémon teams.
  - Includes operations for insertion, retrieval, and removal of Pokémon.

- **`client.cpp`**:
  - Acts as the entry point for the program.
  - Initializes the game and displays the main menu.

- **`Makefile`**:
  - Simplifies the build process with commands to compile and link the project.

---

## How to Run

### Prerequisites

- A C++ compiler (e.g., `g++`) installed on your system.
- Make sure your environment supports C++17 or later.

### Build the Project

Use the provided `Makefile` to compile the project:

```bash
make
```
---
## Author

***Harshiv Mistry***

Project Date: 10-29-2024