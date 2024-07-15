#include "catan.hpp"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace ariel;

Catan::Catan(Player &p1, Player &p2, Player &p3) : currentPlayerIndex(0) {
    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);
    srand(static_cast<unsigned int>(time(0)));
    setupBoard();
    this->board.addPlayer(p1);
    this->board.addPlayer(p2);
    this->board.addPlayer(p3);
}
void Catan::setupBoard() {
    // Add sea tiles (numbering as per your specification)
    board.addTile("sea", 1);
    board.addTile("sea", 2);
    board.addTile("sea", 3);
    board.addTile("sea", 4);
    board.addTile("sea", 5);
    board.addTile("sea", 6);
    board.addTile("sea", 7);
    board.addTile("sea", 8);
    board.addTile("sea", 9);
    board.addTile("sea", 10);
    board.addTile("sea", 11);
    board.addTile("sea", 12);
    board.addTile("sea", 13);
    board.addTile("sea", 14);
    board.addTile("sea", 15);
    board.addTile("sea", 16);
    board.addTile("sea", 17);
    board.addTile("sea", 18);

    // Add resource tiles based on the provided image
    board.addTile("mountain", 10);
    board.addTile("pasture", 2);
    board.addTile("forest", 9);
    board.addTile("field", 12);
    board.addTile("hill",6);
    board.addTile("pasture", 4);
    board.addTile("hill", 10);
    board.addTile("field", 9);
    board.addTile("forest", 11);
    board.addTile("desert", 7);
    board.addTile("forest", 3);
    board.addTile("mountain", 8);
    board.addTile("forest", 8);
    board.addTile("mountain", 3);
    board.addTile("field", 4);
    board.addTile("pasture", 5);
    board.addTile("hill", 5);
    board.addTile("field", 6);
    board.addTile("pasture", 11);
    // Set up neighbors based on the map
    board.connectAllTiles();

}
void Catan::ChooseStartingPlayer() {
    currentPlayerIndex = rand() % players.size();
    cout << "Starting player: " << players[currentPlayerIndex].getName() << endl;
}

Board Catan::getBoard() const {
    return board;
}

void Catan::printWinner() const {
    Player winner = players[0];
    for (const auto &player : players) {
        if (player.getPoints() > winner.getPoints()) {
            winner = player;
        }
    }

    if (winner.getPoints() >= 10) {
        cout << "Winner: " << winner.getName() << endl;
    } else {
        cout << "No winner yet." << endl;
    }
}



