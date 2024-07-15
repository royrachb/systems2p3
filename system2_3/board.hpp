#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include "player.hpp"

namespace ariel {

class HexTile {
public:
    std::string place;  
    int numberToken;       // Number token (e.g., 6, 8, etc.)
    std::vector<HexTile*> neighbors;  // Pointers to neighboring tiles

    HexTile(std::string res, int num) : place(res), numberToken(num) {}

    void connectTiles(HexTile* tile);  // Function to set up neighbors

    bool operator==(const HexTile& other) const;
};

class Board {
private:
    std::vector<HexTile*> tiles;

public:
    std::vector<Player*> players;  // Ensure the correct type

    Board();
    void addTile(std::string place, int numberToken);
    void addPlayer(Player& player);  // Ensure the correct type

    HexTile* getTile(std::string place, int numberToken);
    void connectAllTiles();
};

}

#endif // BOARD_HPP
