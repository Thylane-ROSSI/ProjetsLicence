# Version minimale de CMake requise
cmake_minimum_required(VERSION 3.12)
project(scrabble)

# Sources
set(test_sources
  src/board.hpp
  src/board.cpp
  src/bonus.hpp
  src/bonus.cpp
  src/spot.hpp
  src/spot.cpp
  src/etat.cpp
  src/etat.hpp
  src/gaddag.cpp
  src/gaddag.hpp
  src/jeu.cpp
  src/jeu.hpp
  src/joueur.cpp
  src/joueur.hpp
  src/lettre.hpp
  src/noeud.hpp
  src/sac.cpp
  src/sac.hpp
  src/tour.cpp
  src/tour.hpp


)

# Applications
add_executable(test_board ${test_sources} src/test_board.cpp)
