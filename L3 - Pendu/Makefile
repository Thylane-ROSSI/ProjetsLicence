# Chemins
SRC_DIR := src
BIN := pendu

# Fichiers sources et objets
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:.cpp=.o)

# Compilation
CXX := g++
CXXFLAGS := -std=c++17 -Wall
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

# Règle par défaut
all: $(BIN)

# Compilation de l'exécutable
$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des fichiers .cpp en .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(BIN) $(OBJS)

.PHONY: all clean
