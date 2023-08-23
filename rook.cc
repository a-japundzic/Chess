#include <string>
#include "rook.h"
#include "piece.h"
#include "move.h"
#include "defaultBoard.h"
using namespace std;
Rook::Rook(char name, int curX, int curY, std::string teamName, bool blockable, DefaultBoard* theBoard, string captureDir) : Piece(name, curX, curY, teamName, captureDir, 3, blockable), b{theBoard}{}

// checks if a given point is empty
// change later to put it into board
/*bool isCoordEmpty(DefaultBoard* b, int x, int y) {
    if (b->getPiece(x, y)->getName() != ' ' || b->getPiece(x, y)->getName() != '_') {
        return false;
    }
    return true;
}*/

bool Rook::isValidMove(int xMove, int yMove) {
    // check if the move doesn't actually move anywhere lol
    if (xMove == x && yMove == y) {
        return false;
    }

    // check if it's not a valid vertical or horiz rook move
    if (xMove != x && yMove != y) {
        return false;
    }

    // check if the intended destination already has a piece of same team there
    if (b->getPiece(xMove, yMove)->getTeamName() == teamName && !(b->isCoordEmpty(xMove, yMove))) {
        return false;
    } 

    // moving vertical case
    if (xMove == x) {
        //moving up case
        if (yMove > y) {
            // checking all spots in path up to but not including destination (must be empty)
            for (int i = y + 1; i < yMove; ++i) { //made it x+1 instead of x since it will always return false since x,y is not empty
                if(!(b->isCoordEmpty(x,i))) {
                    return false;
                }
            }
        //moving down case
        } else if (yMove < y) {
            // same as above for loop
            for (int i = y - 1; i > yMove; --i) { /// made a change here
                if(!(b->isCoordEmpty(x,i))) {
                    return false;
                }
            }
        }
    // moving horiz
    } else if (yMove == y) { 
        // moving right
        if (xMove > x) {
            // same as above for loop
            for (int i = x + 1; i < xMove; ++i) {
                if(!(b->isCoordEmpty(i,y))) {
                    return false;
                }
            }
        //moving left
        } else if (xMove < x) {
            // same as above for loop
            for (int i = x - 1; i > xMove; --i) {
                if(!(b->isCoordEmpty(i,y))) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Rook::isValidCaptureMove(int xMove, int yMove) {
    return this->isValidMove(xMove, yMove);
} 

vector<shared_ptr<Move>> Rook::allValidMoves() {
    vector<shared_ptr<Move>> moves{};
    int xMove = x;
    int yMove = y + 1;

    while (yMove < b->getBoardSizeY()) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        } else {
            break;
        }
        ++yMove;
    }

    xMove = x;
    yMove = y - 1;

    while (yMove >= 0) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        } else {
            break;
        }

        --yMove;
    }

    xMove = x + 1;
    yMove = y;

    while (xMove < b->getBoardSizeX()) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        } else {
            break;
        }

        ++xMove;
    }

    xMove = x - 1;
    yMove = y;

    while (xMove >= 0) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        } else {
            break;
        }

        --xMove;
    }

    return moves;
    
}

bool Rook::isRook() {
    return true; 
}

bool Rook::inLineOfSight(int xMove, int yMove) {
    // bounds checking
    if (yMove >= b->getBoardSizeY() || yMove < 0) {
        return false;
    } else if (xMove >= b->getBoardSizeX() || xMove < 0) {
        return false;
    }
    
    if (xMove == x && yMove == y) {
        return false;
    }

    if (xMove != x && yMove != y) {
        return false;
    }
    
    if (xMove == x) {
        //moving up case
        if (yMove > y) {
            // checking all spots in path up to but not including destination (must be empty)
            for (int i = y + 1; i < yMove; ++i) { //made it x+1 instead of x since it will always return false since x,y is not empty
                if(!(b->isCoordEmpty(x,i))) {
                    return false;
                }
            }
        //moving down case
        } else if (yMove < y) {
            // same as above for loop
            for (int i = y - 1; i > yMove; --i) { /// made a change here
                if(!(b->isCoordEmpty(x,i))) {
                    return false;
                }
            }
        }
    // moving horiz
    } else if (yMove == y) { 
        // moving right
        if (xMove > x) {
            // same as above for loop
            for (int i = x + 1; i < xMove; ++i) {
                if(!(b->isCoordEmpty(i,y))) {
                    return false;
                }
            }
        //moving left
        } else if (xMove < x) {
            // same as above for loop
            for (int i = x - 1; i > xMove; --i) {
                if(!(b->isCoordEmpty(i,y))) {
                    return false;
                }
            }
        }
    }

    return true;

    /*
    int xDist = xMove - x;
    int yDist = yMove - y;

 
    if (xDist == 0 && yDist != 0) {
        if (yMove + 1 < b->getBoardSizeY() && this->isValidMove(xMove, yMove + 1)) {
            return true;
        } else if (yMove - 1 >= 0 && this->isValidMove(xMove, yMove - 1)) {
            return true;
        }
    } else if (yDist == 0 && xDist != 0) {
        if (xMove + 1 < b->getBoardSizeX() && this->isValidMove(xMove + 1, yMove)) {
            return true;
        } else if (xMove - 1 >= 0 && this->isValidMove(xMove - 1, yMove)) {
            return true;
        }
    }

  */

  //  return false;
}

