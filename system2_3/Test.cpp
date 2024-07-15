//royrachbuch@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "board.hpp"
#include "catan.hpp"
#include "player.hpp"

using namespace std;
using namespace ariel;
// Example test cases
TEST_CASE("Testing Player::placeSettlement function") 
{    
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);
    // Starting of the game. Every player places two settlements and two roads.
    Board board = catan.getBoard(); // get the board of the game.
    SUBCASE("place the settlement in a invalid place") 
    {
    std::vector<std::string> places = {"place1", "place2", "place3"};
    std::vector<int> placesNum = {1, 2, 3};
    CHECK_THROWS_AS(p1.placeSettlement(places, placesNum, board), std::runtime_error);
    CHECK(p1.getPoints() == 0); // Example check, adjust based on actual point logic
    }

    SUBCASE("many kind of checks on the place settlement function") 
    {
    std::vector<std::string> places = {"pasture", "pasture", "hill"};
    std::vector<int> placesNum = {2, 4, 6};
    CHECK_NOTHROW(p1.placeSettlement(places, placesNum, board));
    CHECK(p1.getPoints() == 1); // Example check, adjust based on actual point logic

    CHECK_THROWS_AS(p1.placeSettlement(places, placesNum, board), std::runtime_error);//put the settlement in the same place as before
    places = {"mountain", "pasture", "hill"};
    placesNum = {10, 2, 6};
    CHECK_THROWS_AS(p1.placeSettlement(places, placesNum, board), std::runtime_error);//place the settlement to close to the previous one 

    places = {"mountain", "field", "hill"};
    placesNum = {10, 12, 6};
    CHECK_NOTHROW(p1.placeSettlement(places, placesNum, board));//place the settlement in a valid place

    p1.modifyResources(10, 10 , 10 ,10 ,10);
    p1.printResources();
    places = {"mountain", "field", "hill"};
    placesNum = {3, 6, 5};
    CHECK_THROWS_AS(p1.placeSettlement(places, placesNum, board), std::runtime_error);//place the settlement in place that no roads connected to it
    
    places = {"field", "hill"};
    placesNum = {12, 6};
    CHECK_NOTHROW(p1.placeRoad(places, placesNum , board));

    places = {"field", "forest"};
    placesNum = {12, 11};
    CHECK_NOTHROW(p1.placeRoad(places, placesNum , board));

    places = {"field", "forest", "field"};
    placesNum = {12, 11, 9};
    CHECK_NOTHROW(p1.placeSettlement(places, placesNum, board));//place the settlement in a valid place

    }
}
TEST_CASE("Testing Player::buydeveplomentcard") 
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);
    Board board = catan.getBoard(); // get the board of the game.
    CHECK_THROWS_AS(p1.buyDevelopmentCard(board), std::runtime_error);
    p1.modifyResources(10, 10 , 10 ,10 ,10);
    CHECK_NOTHROW(p1.buyDevelopmentCard(board));

}


