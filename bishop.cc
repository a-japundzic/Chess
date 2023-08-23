#include <string>
#include "bishop.h"
#include "piece.h"
#include "defaultBoard.h"
#include "move.h"
using namespace std;
Bishop::Bishop(char name, int curX, int curY, std::string teamName, bool blockable, DefaultBoard* theBoard, string captureDir) : Piece(name, curX, curY, teamName, captureDir, 3, blockable), b{theBoard}  {}

/*bool isCoordEmpty(DefaultBoard* b, int x, int y) {
    if (b->getPiece(x, y)->getName() != ' ' || b->getPiece(x, y)->getName() != '_') {
        return false;
    }
    return true;
}*/

bool Bishop::isValidMove(int xMove, int yMove) {
    // check if the move doesn't actually move anywhere lol
    if (xMove == x && yMove == y) {
        return false;
    }

    // check if it's not a valid diagonal bishop move ***
    int xDist = xMove - x;
    int yDist = yMove - y;
    if (abs(xDist) != abs(yDist)) {
        return false;
    }

    // check if the intended destination already has a piece of same team there, and if its not empty piece
    if (b->getPiece(xMove, yMove)->getTeamName() == teamName && !(b->isCoordEmpty(xMove, yMove))) {
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
    
    return true;
}

bool Bishop::isValidCaptureMove(int xMove, int yMove) {
    return this->isValidMove(xMove, yMove);
}

vector<shared_ptr<Move>> Bishop::allValidMoves() {
    vector<shared_ptr<Move>> moves{};
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

    return moves;

}

bool Bishop::inLineOfSight(int xMove, int yMove) {
    // bounds checking
    if (yMove >= b->getBoardSizeY() || yMove < 0) {
        return false;
    } else if (xMove >= b->getBoardSizeX() || xMove < 0) {
        return false;
    }
    int xDist = xMove - x;
    int yDist = yMove - y;

    if (abs(xDist) != abs(yDist)) {
        return false;
    }

    if (xMove == x && yMove == y) {
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
    
    return true;
    
}
