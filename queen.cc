#include <string>
#include "queen.h"
#include "piece.h"
#include "move.h"
#include "defaultBoard.h"
#include <iostream>
using namespace std;

Queen::Queen(char name, int curX, int curY, std::string teamName, bool blockable, DefaultBoard* theBoard, string captureDir) : Piece(name, curX, curY, teamName, captureDir, 9, blockable), b{theBoard}  {}

/*bool isCoordEmpty(DefaultBoard* b, int x, int y) {
    if (b->getPiece(x, y)->getName() != ' ' || b->getPiece(x, y)->getName() != '_') {
        return false;
    }
    return true;
}*/

bool Queen::isValidMove(int xMove, int yMove) {
    // check if the move doesn't actually move anywhere lol
    if (xMove == x && yMove == y) {
        return false;
    }

    // check if the intended destination already has a piece of same team there, and if its not empty piece
    if (b->getPiece(xMove, yMove)->getTeamName() == teamName && !(b->isCoordEmpty(xMove, yMove))) {
        return false;
    } 

    // check if it's not a valid diagonal bishop move ***
    int xDist = xMove - x;
    int yDist = yMove - y;

    if (xDist != 0 && yDist != 0) {
        if (abs(xDist) != abs(yDist)) {
            return false;
        }

        // moving up and diagonal right
        if (xDist > 0 and yDist > 0) {
            // checking all spots in path up to but not including destination (must be empty)
            for (int i = 1; i < abs(xDist); ++i) {
                if(!(b->isCoordEmpty(x + i,y + i))) {
                    return false;
                }
            }
        //moving down and diagonal right
        } else if (xDist > 0 && yDist < 0) {
            // same as above for loop
            for (int i = 1; i < abs(xDist); ++i) {
                if(!(b->isCoordEmpty(x + i,y - i))) {
                    return false;
                }
            }
        // moving down and diagonal left
        } else if (xDist < 0 and yDist < 0) {
            // same as above for loop
            for (int i = 1; i < abs(xDist); ++i) {
                if(!(b->isCoordEmpty(x - i,y - i))) {
                    //cout << x-i << " " << y-i << endl;
                    return false;
                }
            }
        //moving up and diagonal left
        } else if (xDist < 0 && yDist > 0) {
            // same as above for loop
            for (int i = 1; i < abs(xDist); ++i) {
                if(!(b->isCoordEmpty(x - i,y + i))) {
                    return false;
                }
            }
        }
    } else {
        if (xMove != x && yMove != y) {
            return false;
        }
        // moving vertical case
        if (xDist == 0) {
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
                for (int i = y - 1; i > yMove; --i) {
                    if(!(b->isCoordEmpty(x,i))) {
                        return false;
                    }
                }
            }
            
        // moving horiz
        } else if (yDist == 0) { 
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
    }

    return true;
}

bool Queen::isValidCaptureMove(int xMove, int yMove) {
    return this->isValidMove(xMove, yMove);
}

bool Queen::inLineOfSight(int xMove, int yMove) {
    // bounds checking
    if (yMove >= b->getBoardSizeY() || yMove < 0) {
        return false;
    } else if (xMove >= b->getBoardSizeX() || xMove < 0) {
        return false;
    }

    if (xMove == x && yMove == y) {
        return false;
    }

    //diagonal case
    int xDist = xMove - x;
    int yDist = yMove - y;

    if (xDist != 0 && yDist != 0) {
        if (abs(xDist) != abs(yDist)) {
            return false;
        }

        // moving up and diagonal right
        if (xDist > 0 and yDist > 0) {
            // checking all spots in path up to but not including destination (must be empty)
            for (int i = 1; i < abs(xDist); ++i) {
                if(!(b->isCoordEmpty(x + i,y + i))) {
                    return false;
                }
            }
        //moving down and diagonal right
        } else if (xDist > 0 && yDist < 0) {
            // same as above for loop
            for (int i = 1; i < abs(xDist); ++i) {
                if(!(b->isCoordEmpty(x + i,y - i))) {
                    return false;
                }
            }
        // moving down and diagonal left
        } else if (xDist < 0 and yDist < 0) {
            // same as above for loop
            for (int i = 1; i < abs(xDist); ++i) {
                if(!(b->isCoordEmpty(x - i,y - i))) {
                    //cout << x-i << " " << y-i << endl;
                    return false;
                }
            }
        //moving up and diagonal left
        } else if (xDist < 0 && yDist > 0) {
            // same as above for loop
            for (int i = 1; i < abs(xDist); ++i) {
                if(!(b->isCoordEmpty(x - i,y + i))) {
                    return false;
                }
            }
        }
    } else {
        if (xMove != x && yMove != y) {
            return false;
        }
        // moving vertical case
        if (xDist == 0) {
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
                for (int i = y - 1; i > yMove; --i) {
                    if(!(b->isCoordEmpty(x,i))) {
                        return false;
                    }
                }
            }
            
        // moving horiz
        } else if (yDist == 0) { 
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
    }

    return true;
    
}

/*
xMove + 1 yMove //right of king
xMove -1 yMove // left of king
yMove + 1 xMove // above king
yMove -1 xMove // below king

xMove + 1 yMove + 1 diag right up
xMOve + 1 yMove - 1 diag right down
xMove -1 yMove + 1 diag up left
xMove - 1 yMove - 1 diag down left


// Does isvalid move take  into account ranges or did we do that in the main method?
*/


vector<shared_ptr<Move>> Queen::allValidMoves() {
    vector<shared_ptr<Move>> moves{};

    // Bishop valid moves
    int xMove = x + 1;
    int yMove = y + 1;

    while (xMove < b->getBoardSizeX() && yMove < b->getBoardSizeY()) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        } else {
            break;
        }

        ++xMove;
        ++yMove;
    }

    xMove = x - 1;
    yMove = y + 1;

    while (xMove >= 0 && yMove < b->getBoardSizeY()) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        } else {
            break;
        }

        --xMove;
        ++yMove;
    }

    xMove = x + 1;
    yMove = y - 1;

    while (xMove < b->getBoardSizeX() && yMove >= 0) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        } else {
            break;
        }

        ++xMove;
        --yMove;
    }

    xMove = x - 1;
    yMove = y - 1;

    while (xMove >= 0 && yMove >= 0) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        } else {
            break;
        }

        --xMove;
        --yMove;
    }
    
    // Rook valid moves

    xMove = x;
    yMove = y + 1;

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
