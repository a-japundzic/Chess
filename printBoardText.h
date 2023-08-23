#ifndef PRINT_BOARD_TEXT_H
#define PRINT_BOARD_TEXT_H

#include <iostream>
#include <memory>
#include "board.h"
#include "piece.h"


class PrintBoardText {
    private:
        std::shared_ptr<Board> b;
    public:
        PrintBoardText(std::shared_ptr<Board> b);
        void printBoard(int x, int y); // Prints board, good enough for now lol
};

#endif
