#ifndef OPENINGMOVES_H
#define OPENINGMOVES_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>

class Board;

// get next move from 
// input current moves in the game and get next one
// input no moves and get first one
class OpeningMoves {
    int numSequences;
    std::vector<std::string> sequences;
    std::string pastMoves;
    std::shared_ptr<Board> b; 

    public:
        OpeningMoves();
        void attachBoard(std::shared_ptr<Board> theBoard);
        std::string findNextMove(); 
        void updatePastMoves(int x1, int y1, int x2, int y2);
};


#endif