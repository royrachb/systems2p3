#include "player.hpp"
#include <iostream>
#include <stdexcept>
#include "board.hpp"  // Include the full definition of the Board class
using namespace std;
using namespace ariel;
#include "catan.hpp"
#include <ctime>
Player::Player(const std::string &name) : name(name), points(0), wood(0), brick(0), wheat(0), sheep(0), ore(0) {}
Player::Player(const std::string &name , int points , int wood , int ore , int wheat , int brick , int sheep) : name(name), points(points), wood(wood), brick(brick), wheat(wheat), sheep(sheep), ore(ore) {}

bool Player::areHexTileVectorsEqual(const std::vector<HexTile*>& vec1, const std::vector<HexTile*>& vec2) {

    for (const auto& tile1 : vec1) {
        bool found = false;
        for (const auto& tile2 : vec2) {
            if (tile1 == tile2) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }

    return true;
}

bool Player::isHexTileVectorNotInList(const std::vector<HexTile*>& vector, const std::vector<std::vector<HexTile*>>& listOfVectors) {
    for (const auto& vec : listOfVectors) {
        if (areHexTileVectorsEqual(vector, vec)) {
            return false;
        }
    }
    return true;
}

// Implementation of the placeSettlement function
void Player::placeSettlement(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board) {
    std::vector<HexTile*> newSettlement;

    // Ensure the sizes of places and placesNum match
    if (places.size() != placesNum.size()) {
        // Handle the error, e.g., throw an exception or return early
        throw std::invalid_argument("places and placesNum vectors must be of the same size");
    }
    
    // Iterate through the places and placesNum vectors
    for (size_t i = 0; i < places.size(); ++i) {
        HexTile* tile = board.getTile(places[i], placesNum[i]);
        if (tile) {
            newSettlement.push_back(tile);
        } else {
            // Handle the error if the tile is not found, e.g., throw an exception or return early
            throw std::runtime_error("Tile not found for place: " + places[i] + " and numberToken: " + std::to_string(placesNum[i]));
        }
    }
        std::vector<HexTile*> vector1 = {newSettlement[0], newSettlement[1]};
        std::vector<HexTile*> vector2 = {newSettlement[1], newSettlement[2]};
        std::vector<HexTile*> vector3 = {newSettlement[0], newSettlement[2]};
    // Check if the new settlement is not included in any of the other players' or this player's settlements
    for (const auto& player : board.players)
    {
        if (!isHexTileVectorNotInList(newSettlement, player->settlements)) {
            throw std::runtime_error("The settlement is already present in another player's or this player's settlements");
        }

        if (!isHexTileVectorNotInList(vector1, player->settlements)) {
            throw std::runtime_error("The settlement is to close to a nother settlement");
        }
        if (!isHexTileVectorNotInList(vector2, player->settlements)) {
            throw std::runtime_error("The settlement is to close to a nother settlement");
        }
        if (!isHexTileVectorNotInList(vector3, player->settlements)) {
            throw std::runtime_error("The settlement is to close to a nother settlement");
        }
    }
    // Add the new settlement to the settlements vector
    if (settlements.size()<2)
    {
        settlements.push_back(newSettlement);
        points += 1; // נניח שכל כרטיס פיתוח נותן נקודה אחת בונוס
    }
    else if (wood >= 1 && wheat >= 1 && brick >= 1 && sheep >= 1)
    {

        if (isHexTileVectorNotInList(vector1, roads) && (isHexTileVectorNotInList(vector2, roads)) && (isHexTileVectorNotInList(vector3, roads))) {
            throw std::runtime_error("The settlement have no roads connected to it");
        }
        else 
        {
            settlements.push_back(newSettlement);
            points += 1; // נניח שכל כרטיס פיתוח נותן נקודה אחת בונוס
            wood--;
            wheat--;
            brick--;
            sheep--;
        }

    }
    else
    {
        throw std::runtime_error("not enogh matirials to build the settlement");
    }

}


void Player::placeRoad(const std::vector<std::string>& places, const std::vector<int>& placesNum, ariel::Board& board) {
    std::vector<HexTile*> roadTiles;

    // Ensure the sizes of places and placesNum match
    if (places.size() != placesNum.size() || places.size() != 2) {
        // Handle the error, e.g., throw an exception or return early
        throw std::invalid_argument("places and placesNum vectors must be of the same size and contain exactly two elements");
    }

    // Iterate through the places and placesNum vectors
    for (size_t i = 0; i < places.size(); ++i) {
        HexTile* tile = board.getTile(places[i], placesNum[i]);
        if (tile) {
            roadTiles.push_back(tile);
        } else {
            // Handle the error if the tile is not found, e.g., throw an exception or return early
            throw std::runtime_error("Tile not found for place: " + places[i] + " and numberToken: " + std::to_string(placesNum[i]));
        }
    }
    for (const auto& player : board.players)
    {
        if (!isHexTileVectorNotInList(roadTiles, player->roads)) {
            throw std::runtime_error("The road is already present in another player's or this player's road");
        }
      
    }
    std::vector<HexTile*> vector1 = {roadTiles[0]};
    std::vector<HexTile*> vector2 = {roadTiles[1]};

    if (isHexTileVectorNotInList(roadTiles, settlements)) {
        if (isHexTileVectorNotInList(vector1, roads) && isHexTileVectorNotInList(vector2, roads)) {
            throw std::runtime_error("The road not connected to any settlement or road");
        }
    }  

    if (roads.size()<2)
    {
        roads.push_back(roadTiles);
    }
    else if (wood >= 1 && brick >= 1)
    {
        roads.push_back(roadTiles);
        wood--;
        brick--;
    }
    else
    {
        throw std::runtime_error("not enogh matirials to build the road");
    }
    // Add the new road to the roads vector
}

void Player::modifyResources(int Wood , int Ore , int Wheat , int Sheep ,int Brick) 
{
    wood = Wood;
    ore = Ore;
    wheat = Wheat;
    sheep = Sheep;
    brick = Brick;
}
void Player::rollDice(Catan& catan, ariel::Board& board) {
    // מימוש גלגול הקוביות (נניח קוביה עם מספרים מ-1 עד 12)
    if (catan.players[catan.currentPlayerIndex].name != this->name ) 
    {
        throw std::runtime_error("not the right player turn");
    }
    std::unordered_map<std::string, int*> resourceMap;
    int diceRoll = rand() % 12 + 1;
    cout << name << " rolled a " << diceRoll << endl;
    for (const auto& player : board.players)
    {
        resourceMap = {
                {"forest", &(player->wood)},
                {"hill", &(player->brick)},
                {"field", &(player->wheat)},
                {"pasture", &(player->sheep)},
                {"mountain", &(player->ore)}
            };
        for (const auto& tile1 : player->settlements) 
        {
            for (const auto& tile2 : tile1) 
            {
                if (tile2->numberToken == diceRoll && diceRoll != 7 && tile2->place != "sea") 
                {
                    (*resourceMap[tile2->place]) += 1;
                }
            }
        }
    }

    // מימוש ההשפעות של גלגול הקוביות על הלוח והשחקנים

    
}

void Player::endTurn(Catan& catan) {
    // מימוש סיום התור
    catan.currentPlayerIndex = (catan.currentPlayerIndex + 1) % catan.players.size();
    cout << name << " ends their turn." << endl;
}

void Player::trade(Player &other, const std::string &giveResource, const std::string &receiveResource, int giveAmount, int receiveAmount) {
    std::unordered_map<std::string, int*> resourceMap = {
        {"wood", &wood},
        {"brick", &brick},
        {"wheat", &wheat},
        {"sheep", &sheep},
        {"ore", &ore}
    };
    std::unordered_map<std::string, int*> oResourceMap = {
        {"wood", &(other.wood)},
        {"brick", &(other.brick)},
        {"wheat", &(other.wheat)},
        {"sheep", &(other.sheep)},
        {"ore", &(other.ore)}
    };

    if (resourceMap.find(giveResource) == resourceMap.end() || resourceMap.find(receiveResource) == resourceMap.end()) {
        std::cout << "Invalid resource.\n";
        return;
    }

    if (*resourceMap[giveResource] < giveAmount) {
        std::cout << name << " does not have enough " << giveResource << " to trade.\n";
        return;
    }

    if (*oResourceMap[receiveResource] < receiveAmount) {
        std::cout << other.getName() << " does not have enough " << receiveResource << " to trade.\n";
        return;
    }

    *resourceMap[giveResource] -= giveAmount;
    *resourceMap[receiveResource] += receiveAmount;
    *oResourceMap[giveResource] += giveAmount;
    *oResourceMap[receiveResource] -= receiveAmount;

    std::cout << name << " trades " << giveAmount << " " << giveResource << " with " << other.getName() << " for " << receiveAmount << " " << receiveResource << std::endl;
}

void Player::buyDevelopmentCard(Board& board) {
    std::unordered_map<std::string, int*> thisResourceMap= {
        {"wood", &wood},
        {"brick", &brick},
        {"wheat", &wheat},
        {"sheep", &sheep},
        {"ore", &ore}
        };
    if (ore >= 1 && sheep >= 1&& wheat >= 1)
    {
        ore--;
        sheep--;
        wheat--;
        cout << name << " buys a development card." << endl;
        // Initialize the random seed
        std::srand(static_cast<unsigned int>(std::time(0)));
        // Generate a random number in the range 1 to 5
        int random_number = std::rand() % 5 + 1;
         // Use a switch statement to handle different cases
           cout << name << random_number << endl;

        if (random_number == 1)
        {          
            std::cout << "You got a monopol card!" << std::endl;
            std::cout << "write the resource to take" << std::endl;
            std::cout << "1 wheat" << std::endl;
            std::cout << "2 ore" << std::endl;
            std::cout << "3 brick" << std::endl;
            std::cout << "4 wood" << std::endl;
            std::cout << "5 sheep" << std::endl;
            std::string input;
            // Get the input from the user
            std::cin >> input;
            std::unordered_map<std::string, int*> resourceMap;
   

            for (const auto& player : board.players)
            {
                if (player->name != name)
                {
                    resourceMap = {
                    {"wood", &(player->wood)},
                    {"brick", &(player->brick)},
                    {"wheat", &(player->wheat)},
                    {"sheep", &(player->sheep)},
                    {"ore", &(player->ore)}
                    };
                    if (*resourceMap[input] >= 1)
                    {
                        *resourceMap[input]--;
                        *thisResourceMap[input]++;
                    }
                }
            }
        }
        if (random_number == 2)
        {          
            std::string road1p1;
            std::string road1p2;
            std::string road2p1;
            std::string road2p2;
            int road1n1;
            int road1n2;
            int road2n1;
            int road2n2;

            std::cout << "You got a build card! you can place two roads" << std::endl;
            std::cout << "plese chose the the first place to put the first road" << std::endl;
            std::cin >> road1p1;
            std::cout << "plese chose the the first numberToken to put the first road" << std::endl;
            std::cin >> road1n1;
            std::cout << "plese chose the the second place to put the second road" << std::endl;
            std::cin >> road1p2;
            std::cout << "plese chose the the first numberToken to put the first road" << std::endl;
            std::cin >> road1n2;
            std::vector<int> vectorN = {road1n1, road1n2};
            std::vector<std::string> vectorS = {road1p1, road1p2};
            placeRoad(vectorS,vectorN,board);


            std::cout << "plese chose the the first place to put the second road" << std::endl;
            std::cin >> road2p1;
            std::cout << "plese chose the the first numberToken to put the second road" << std::endl;
            std::cin >> road2n1;
            std::cout << "plese chose the the second place to put the second road" << std::endl;
            std::cin >> road2p2;
            std::cout << "plese chose the the second numberToken to put the second road" << std::endl;
            std::cin >> road2n2;
            std::vector<int> vector2N = {road2n1, road2n2};
            std::vector<std::string> vector2S = {road2p1, road2p2};
            placeRoad(vector2S,vector2N,board);
        }
        if(random_number == 3)
        {   
            std::cout << "You got a matirial card!" << std::endl;
            std::string mat;
            std::cout << "plese chose the matirial you want" << std::endl;
            std::cin >> mat;
            thisResourceMap[mat] += 2;
        }
        if(random_number == 4)
        {
            std::cout << "You got a knight card!" << std::endl;
            knights += 1;
            if(knights == 3)
            {
                points += 2;
            }

        }
        if(random_number == 5)
        {
            std::cout << "You got a win point card!" << std::endl;
            points++;        
        }   

    }
    else 
    {
        throw std::runtime_error("you have not enogh meterials to buy the development card");
    }

}

void Player::printPoints() const {
    cout << name << " has " << points << " points." << endl;
}

std::string Player::getName() const {
    return name;
}

int Player::getPoints() const {
    return points;
}


void Player::printResources(){
    cout << name << " has " << wood << " wood." << endl;
    cout << name << " has " << wheat << " wheat." << endl;
    cout << name << " has " << ore << " ore." << endl;
    cout << name << " has " << sheep << " sheep." << endl;
    cout << name << " has " << brick << " brick." << endl;
}
