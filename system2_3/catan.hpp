//royrachbuch@gmail.com
#ifndef CATAN_HPP
#define CATAN_HPP

#include "player.hpp"
#include "board.hpp"
#include <vector>
#include <string>

namespace ariel {

class Catan {


public:
    void setupBoard();
    int currentPlayerIndex;
    std::vector<Player> players;
    Board board;

    Catan( Player &p1,  Player &p2,  Player &p3);
    void ChooseStartingPlayer();
    Board getBoard() const;
    void printWinner() const;
};

} // namespace ariel

#endif // CATAN_HPP
