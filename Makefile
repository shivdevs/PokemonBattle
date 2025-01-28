# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Target Executable
TARGET = pokemon_battle

# Source Files
SOURCES = harshiv_mistry_client.cpp harshiv_mistry_pokemon.cpp harshiv_mistry_tree.cpp harshiv_mistry_battle.cpp

# Default Target
all: $(TARGET)

# Linking and Compiling in one step
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean Target
clean:
	rm -f $(TARGET)
