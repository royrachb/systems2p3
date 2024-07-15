#include "board.hpp"
#include <iostream>
#include <stdexcept>
#include <functional> // For std::hash
#include <algorithm> // For std::sort
using namespace std;
using namespace ariel;

#include <vector>
bool HexTile::operator==(const HexTile& other) const {
    return place == other.place && numberToken == other.numberToken;
}

Board::Board() 
{
    
}

void Board::addTile(std::string place, int numberToken) 
{
    HexTile* newTile = new HexTile(place, numberToken);
    tiles.push_back(newTile);
}

HexTile* Board::getTile(const std::string place, int numberToken) {
    for (HexTile* tile : tiles) {
        if (tile->place == place && tile->numberToken == numberToken) {
            return tile;
        }
    }
    return nullptr;  // Return nullptr if no matching tile is found
}

void HexTile::connectTiles(HexTile* tile) {
    neighbors.push_back(tile);
    tile->neighbors.push_back(this); // Assuming a bidirectional connection
}

void Board::connectAllTiles() {
    // Assuming the tiles are added in the correct order
    // Modify the indices to match the actual map layout

    // Example: Connecting tiles manually based on your game map
    // Connect sea tiles (example)
    tiles[0]->connectTiles(tiles[1]);
    tiles[1]->connectTiles(tiles[2]);
    tiles[2]->connectTiles(tiles[3]);
    tiles[3]->connectTiles(tiles[4]);
    tiles[4]->connectTiles(tiles[5]);
    tiles[5]->connectTiles(tiles[6]);
    tiles[6]->connectTiles(tiles[7]);
    tiles[7]->connectTiles(tiles[8]);
    tiles[8]->connectTiles(tiles[9]);
    tiles[9]->connectTiles(tiles[10]);
    tiles[10]->connectTiles(tiles[11]);
    tiles[11]->connectTiles(tiles[12]);
    tiles[12]->connectTiles(tiles[13]);
    tiles[13]->connectTiles(tiles[14]);
    tiles[14]->connectTiles(tiles[15]);
    tiles[15]->connectTiles(tiles[16]);
    tiles[16]->connectTiles(tiles[17]);
    tiles[17]->connectTiles(tiles[0]);

    // Example: Connecting resource tiles manually based on your game map
    tiles[18]->connectTiles(tiles[19]);
    tiles[18]->connectTiles(tiles[0]);
    tiles[18]->connectTiles(tiles[1]);
    tiles[18]->connectTiles(tiles[17]);

    tiles[19]->connectTiles(tiles[20]);
    tiles[19]->connectTiles(tiles[1]);
    tiles[19]->connectTiles(tiles[2]);

    tiles[20]->connectTiles(tiles[2]);
    tiles[20]->connectTiles(tiles[3]);
    tiles[20]->connectTiles(tiles[4]);
    
    tiles[21]->connectTiles(tiles[17]);
    tiles[21]->connectTiles(tiles[16]);
    tiles[21]->connectTiles(tiles[22]);
    tiles[21]->connectTiles(tiles[18]);

    tiles[22]->connectTiles(tiles[23]);
    tiles[22]->connectTiles(tiles[18]);
    tiles[22]->connectTiles(tiles[19]);

    tiles[23]->connectTiles(tiles[19]);
    tiles[23]->connectTiles(tiles[20]);
    tiles[23]->connectTiles(tiles[24]);

    tiles[24]->connectTiles(tiles[20]);
    tiles[24]->connectTiles(tiles[4]);
    tiles[24]->connectTiles(tiles[5]);

    tiles[25]->connectTiles(tiles[15]);
    tiles[25]->connectTiles(tiles[16]);
    tiles[25]->connectTiles(tiles[21]);
    tiles[25]->connectTiles(tiles[26]);

    tiles[26]->connectTiles(tiles[21]);
    tiles[26]->connectTiles(tiles[22]);
    tiles[26]->connectTiles(tiles[27]);

    tiles[27]->connectTiles(tiles[22]);
    tiles[27]->connectTiles(tiles[23]);
    tiles[27]->connectTiles(tiles[28]);

    tiles[28]->connectTiles(tiles[29]);
    tiles[28]->connectTiles(tiles[23]);
    tiles[28]->connectTiles(tiles[24]);

    tiles[29]->connectTiles(tiles[5]);
    tiles[29]->connectTiles(tiles[24]);
    tiles[29]->connectTiles(tiles[6]);

    tiles[30]->connectTiles(tiles[25]);
    tiles[30]->connectTiles(tiles[26]);
    tiles[30]->connectTiles(tiles[14]);
    tiles[30]->connectTiles(tiles[31]);

    tiles[31]->connectTiles(tiles[26]);
    tiles[31]->connectTiles(tiles[27]);
    tiles[31]->connectTiles(tiles[32]);

    tiles[32]->connectTiles(tiles[27]);
    tiles[32]->connectTiles(tiles[28]);
    tiles[32]->connectTiles(tiles[33]);

    tiles[33]->connectTiles(tiles[28]);
    tiles[33]->connectTiles(tiles[29]);
    tiles[33]->connectTiles(tiles[7]);

    tiles[34]->connectTiles(tiles[13]);
    tiles[34]->connectTiles(tiles[30]);
    tiles[34]->connectTiles(tiles[31]);
    tiles[34]->connectTiles(tiles[35]);

    tiles[35]->connectTiles(tiles[31]);
    tiles[35]->connectTiles(tiles[32]);
    tiles[35]->connectTiles(tiles[36]);

    tiles[36]->connectTiles(tiles[32]);
    tiles[36]->connectTiles(tiles[33]);
    tiles[36]->connectTiles(tiles[8]);
    
    tiles[12]->connectTiles(tiles[34]);
    tiles[11]->connectTiles(tiles[34]);
    tiles[11]->connectTiles(tiles[35]);
    tiles[10]->connectTiles(tiles[35]);
    tiles[10]->connectTiles(tiles[36]);
    tiles[9]->connectTiles(tiles[36]);
    // Add specific connections based on the provided map image
    // This is a simplified example and should be customized to fit your actual game board layout
}



void Board::addPlayer(Player& player)
{
    players.push_back(&player);  // Push the address of the player to the vector}
}

