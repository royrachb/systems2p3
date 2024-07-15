#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

namespace ariel {
class HexTile;  // Forward declaration
class Board;    // Forward declaration
class Catan;
class Player {
private:
    std::string name;
    int points;
    std::vector<std::vector<HexTile*>> settlements;
    std::vector<std::vector<HexTile*>> roads;
    bool isHexTileVectorNotInList(const std::vector<HexTile*>& vector, const std::vector<std::vector<HexTile*>>& listOfVectors);
    bool areHexTileVectorsEqual(const std::vector<HexTile*>& vec1, const std::vector<HexTile*>& vec2);

public:
    Player(const std::string &name);
    Player(const std::string &name,int,int ,int ,int,int,int);
    void modifyResources(int, int , int, int, int);
    int knights;
    void placeSettlement(const std::vector<std::string> &places, const std::vector<int> &placesNum, Board &board);
    void placeRoad(const std::vector<std::string> &places, const std::vector<int> &placesNum, Board &board);
    void rollDice(Catan& catan,Board& board);
    void endTurn(Catan& catan);
    void trade(Player &other, const std::string &giveResource, const std::string &receiveResource, int giveAmount, int receiveAmount);
    void buyDevelopmentCard(Board& board);
    void printPoints() const;
    int wood;
    int brick;
    int wheat;
    int sheep;
    int ore;
    // Getters
    void printResources();
    std::string getName() const;
    int getPoints() const;
    
};

} // namespace ariel

#endif // PLAYER_HPP