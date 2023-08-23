#ifndef MOVE_H
#define MOVE_H
#include "player.h"
#include <string>
#include <vector>
#include <memory>

class Board;

class Move {
    public:
        int x, y, xMove, yMove;
        std::string teamName;
        bool canCapture;
        bool givesCheck;
        bool capturable;
        int value1;
        int value2;
    private:
        Board* b;
    public:
        Move(Board* theBoard, int x, int y, int xMove, int yMove, std::string teamName);
};
#endif
