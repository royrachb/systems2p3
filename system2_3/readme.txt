# Catan Game Simulation

This project simulates the popular board game Catan. The simulation includes classes and methods to manage the board, players, and game logic.

## Files

- `board.hpp` & `board.cpp`: Defines the `Board` class, which manages the game board, including settlements, roads, and resources.
- `player.hpp` & `player.cpp`: Defines the `Player` class, which manages player actions, resources, and strategies.
- `catan.hpp` & `catan.cpp`: Contains the main game logic, integrating the `Board` and `Player` classes to simulate the game.
- `Demo.cpp`: A demonstration file to show how the game classes can be used.
- `Test.cpp`: Contains tests to verify the functionality of the game classes.

## Classes

### Board
The `Board` class is responsible for:
- Managing the game board structure.
- Keeping track of settlements and roads.
- Handling resource distribution.

### Player
The `Player` class is responsible for:
- Managing player resources.
- Handling player actions such as building settlements and roads.
- Implementing player strategies.

### Catan
The `Catan` class integrates the `Board` and `Player` classes and contains the main game loop and logic.

## Compilation and Execution

To compile the project, you can use the following command:

```sh
g++ -std=c++11 -o catan Demo.cpp board.cpp player.cpp catan.cpp
