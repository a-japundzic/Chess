#ifndef BOARDGRAPHIC_H
#define BOARDGRAPHIC_H

#include <iostream>
#include <memory>
#include "board.h"
#include "piece.h"

class BoardGraphic {
    private:
        std::shared_ptr<Board> b;
        //Xwindow w
    public:
        BoardGraphic(std::shared_ptr<Board> b);
        void graphicInitialBoard(int x, int y); // Prints board, good enough for now lol
        void updateBoard(int x, int y, int newX, int newY);
};

#endif  
