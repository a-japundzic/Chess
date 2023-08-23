#include <string>
#include "knight.h"
#include "piece.h"
#include "move.h"
#include "defaultBoard.h"

using namespace std;
Knight::Knight(char name, int curX, int curY, std::string teamName, bool blockable, DefaultBoard* theBoard, string captureDir) : Piece(name, curX, curY, teamName, captureDir, 3, blockable), b{theBoard}  {}

/*bool isCoordEmpty(DefaultBoard* b, int x, int y) {
    if (b->getPiece(x, y)->getName() != ' ' || b->getPiece(x, y)->getName() != '_') {
        return false;
    }
    return true;
}*/

bool Knight::isValidMove(int xMove, int yMove) {
    // check if the move doesn't actually move anywhere lol
    if (xMove == x && yMove == y) {
        return false;
    }

    // check if the intended destination already has a piece of same team there, and if its not empty piece
    if (b->getPiece(xMove, yMove)->getTeamName() == teamName && !(b->isCoordEmpty(xMove, yMove))) {
        return false;
    } 
    
    int xDist = xMove - x;
    int yDist = yMove - y;

    // mmm a bit weird but i think its valid
    //nah this feels fine
    if (!((abs(xDist) == 1 && abs(yDist) == 2) || (abs(xDist) == 2 && abs(yDist) == 1))) {
        return false; 
    }

    return true;
}

bool Knight::isValidCaptureMove(int xMove, int yMove) {
    return this->isValidMove(xMove, yMove);
}

bool Knight::inLineOfSight(int xMove, int yMove) {
    // bounds checking
    if (yMove >= b->getBoardSizeY() || yMove < 0) {
        return false;
    } else if (xMove >= b->getBoardSizeX() || xMove < 0) {
        return false;
    }
    if (xMove == x && yMove == y) {
        return false;
    }

    int xDist = xMove - x;
    int yDist = yMove - y;

    // mmm a bit weird but i think its valid
    //nah this feels fine
    if (!((abs(xDist) == 1 && abs(yDist) == 2) || (abs(xDist) == 2 && abs(yDist) == 1))) {
        return false; 
    }

    return true;

    //return this->isValidMove(xMove, yMove);
}

vector<shared_ptr<Move>> Knight::allValidMoves() {
    vector<shared_ptr<Move>> moves{};

    int xMove = x + 2;
    int yMove = y + 1;

    if (yMove < 8 && xMove < 8) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        }
    }

    xMove = x + 1;
    yMove = y + 2;

    if (yMove < 8 && xMove < 8) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        } 
    }

    xMove = x - 1;
    yMove = y + 2;

    if (xMove >= 0 && yMove < 8) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        }
    }

    xMove = x - 2;
    yMove = y + 1;

    if (xMove >= 0 && yMove < 8) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        }
    }

    xMove = x - 2;
    yMove = y - 1;

    if (xMove >= 0 && yMove >= 0) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        }
    }

    xMove = x - 1;
    yMove = y - 2;

    if (xMove >= 0 && yMove >= 0) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        }
    }

    xMove = x + 1;
    yMove = y - 2;

    if (xMove < 8 && yMove >= 0) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        }
    }

    xMove = x + 2;
    yMove = y - 1;

    if (xMove < 8 && yMove >= 0) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        }
    }

    return moves;
}
