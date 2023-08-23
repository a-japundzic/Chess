#include <string>
#include "pawn.h"
#include "piece.h"
#include "move.h"
#include "defaultBoard.h"

#include <iostream>

using namespace std;

Pawn::Pawn(char name, int curX, int curY, std::string teamName, bool blockable, DefaultBoard* theBoard, string captureDir) : Piece(name, curX, curY, teamName, captureDir, 1, blockable), b{theBoard} {}

/*bool isCoordEmpty(DefaultBoard* b, int x, int y) {
    if (b->getPiece(x, y)->getName() != ' ' || b->getPiece(x, y)->getName() != '_') {
        return false;
    }
    return true;
}*/

/// NOTE NOT CURRENTLY CHECKING FOR CHECKMATE OR ANYTHING LIKE THAT JUST BASIC MOVEMENT
    // Above should be fine
bool Pawn::isValidMove(int xMove, int yMove) {
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

    if (abs(xDist) > 1) { //cannot move x by more than 1
        return false; 
    } else if (abs(xDist) > 0 && abs(yDist) == 0 || abs(xDist) == 1 && abs(yDist) == 2) { // cant move side to side
        return false; 
    }

  //  cout << x << " " << y << " " << xMove << " " << yMove << endl;

    if (teamName == "White") {
        if (yDist <= 0) {
            return false;
        }
    } else {
        if (yDist >= 0) {
            return false; 
        }
    }

    if (numOfMoves > 0) { //Not moved yet so numofMoves is 0 
        if (abs(yDist) > 1) { // if pawn has been moved, cannot move more than 1
            return false;
        }
    } else {
        if (abs(yDist) > 2) { // if pawn has NOT been moved, cannot move more than 2
            return false; 
        }
    }

    if (abs(xDist) == 1 && b->isCoordEmpty(xMove, yMove)) { // if you're moving diagonal 
      // cout << "Im in the first if statement" << endl;
        if (!b->isCoordEmpty(xMove, y) && teamName != b->getPiece(xMove, y)->getTeamName()) {
           // cout << "Im in the second if statement" << endl;
            if (b->getPiece(xMove, y)->enpessantable()) {
                //cout << "Im here" << endl;
                b->swapPieceEmpty(xMove, y); // switch pawn to be removed with empty
                // cout << "Im here still" << endl;
                return true; //calls move function that moves enemy pawn diagonally 
            } else {
                return  false;
            }
        } else {
            return false;
        }
    } else if (abs(xDist) == 1 && b->isCoordEmpty(xMove, yMove)){
        return false;
    } else if (abs(yDist) == 1 && abs(xDist) == 0 && !b->isCoordEmpty(xMove, yMove)) {
        return false; 
    } else if (abs(yDist) == 2) {
        if (!b->isCoordEmpty(xMove, yMove)) {
            return false; 

            // if you're a black player, yDist is negative cuz youre moving to a lower index. 
            // This if statement checks the box in between the box 2 forward and the current box (checks the box 1 forward), 
            // so y + (yDist/2) would be y + -1 for black and y + 1 for white 
        } else if (!b->isCoordEmpty(xMove, y + (yDist / 2))) {
            return false; 
        }
    }

    if (abs(yDist) == 2) {
        isEnpessantable = true; 
    }

    return true;
}

bool Pawn::isValidCaptureMove(int xMove, int yMove) {
    if (this->isValidMove(xMove, yMove)) {
        int xDist = xMove - x;

        if (abs(xDist) == 1 && !b->isCoordEmpty(xMove, yMove)) {
            return true;
        }
    }

    return false;
}

bool Pawn::inLineOfSight(int xMove, int yMove) {
    // bounds checking
    if (yMove >= b->getBoardSizeY() || yMove < 0) {
        return false;
    } else if (xMove >= b->getBoardSizeX() || xMove < 0) {
        return false;
    }
    int xDist = xMove - x;
    int yDist = yMove - y;
                                                            ///// HARD CODED VALUES AS OF RIGHT NOW
    if (abs(xDist) == 1 /*&& !b->isCoordEmpty(xMove, yMove)*/) {
        if (teamName == "White" && yDist == 1) {
            return true;
        } else if (teamName == "Black" && yDist == -1) {
            return true;
        }
        
    }
    return false;
    

    //return this->isValidCaptureMove(xMove, yMove);
}

vector<shared_ptr<Move>> Pawn::allValidMoves() {
    vector<shared_ptr<Move>> moves{};

    int xMove = x;

    if (teamName == "White") {
        int yMove = y + 1; // one forward

        if (yMove < b->getBoardSizeY()) {
            if (this->isValidMove(xMove, yMove)) {
                moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
            }
        }

        ++yMove; // two forward

        if (yMove < b->getBoardSizeY()) {
            if (this->isValidMove(xMove, yMove)) {
                moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
            } 
        }

        xMove = x + 1; // diagonal
        yMove = y + 1;

        if (xMove < b->getBoardSizeX() && yMove < b->getBoardSizeY()) {
            if (this->isValidMove(xMove, yMove)) {
                moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
            }
        }

        xMove = x - 1;

        if (xMove >= 0 && yMove < b->getBoardSizeY()) {
            if (this->isValidMove(xMove, yMove)) {
                moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
            }
        }
    } else {
        int yMove = y - 1;

        if (yMove >= 0) {
            if (this->isValidMove(xMove, yMove)) {
                moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
            }
        }

        --yMove;

        if (yMove >= 0) {
            if (this->isValidMove(xMove, yMove)) {
                moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
            } 
        }

        xMove = x + 1;
        yMove = y - 1;

        if (xMove < b->getBoardSizeX() && yMove >= 0) {
            if (this->isValidMove(xMove, yMove)) {
                moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
            }
        }

        xMove = x - 1;

        if (xMove >= 0 && yMove >= 0) {
            if (this->isValidMove(xMove, yMove)) {
                moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
            }
        }
    }

    return moves;
}

bool Pawn::isPromotable() {
    return true;
}

bool Pawn::doneOneMove() {
    return (numOfMoves == 1); 
}

bool Pawn::enpessantable() {
    return (isEnpessantable && numOfMoves == 1); 
}
