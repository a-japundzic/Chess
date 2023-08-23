#include <string>
#include "king.h"
#include "piece.h"
#include "move.h"
#include "defaultBoard.h"
#include <iostream>

using namespace std;

King::King(char name, int curX, int curY, std::string teamName, bool blockable, DefaultBoard* theBoard, string captureDir) : Piece(name, curX, curY, teamName, captureDir, blockable), b{theBoard}  {}

/*bool isCoordEmpty(DefaultBoard* b, int x, int y) {
    if (b->getPiece(x, y)->getName() != ' ' || b->getPiece(x, y)->getName() != '_') {
        return false;
    }
    return true;
}*/

/// NOTE NOT CURRENTLY CHECKING FOR CHECKMATE OR ANYTHING LIKE THAT JUST BASIC MOVEMENT
bool King::isValidMove(int xMove, int yMove) {
    //cout << "We got to isvalid move" << endl;
    // check if the move doesn't actually move anywhere lol
    
    if (xMove == x && yMove == y) {
        return false;
    }

    //cout << "Passed first if statement" << endl;

    //cout << x << " " << xMove << " " << y << " " << yMove << endl;
    // check if the intended destination already has a piece of same team there, and if its not empty piece
    if (b->getPiece(xMove, yMove)->getTeamName() == teamName && !(b->isCoordEmpty(xMove, yMove))) {
        return false;
    } 

    // check if it's not a valid king move
    int xDist = xMove - x;
    int yDist = yMove - y;

    //cout << "Passed second if statement" << endl;

    if (abs(yDist) > 1) {
        return false;
    } else if (abs(xDist) > 2) {
        return false;
    } else if (abs(xDist) == 2 && abs(yDist) > 0) {
        return false; 
    }

    //cout << "Im before the for loop" << endl;

   // checking if the intended move is in check
    string otherTeam = b->getOtherTeamName(teamName);

    //cout << b->playerPieces(otherTeam).size() << endl;

    //cout <<  b->playerPieces(otherTeam).size() << endl;

    for (auto p : b->playerPieces(otherTeam)) {
        //cout << "yo" << endl;
        //cout << p->getName() << endl;
        if (p == b->getOtherKing(teamName)) {
            //cout << p->getName() << endl;
            if ((p->getX() == xMove) && (p->getY() + 1 == yMove)) { // above
                return false;
            } else if((p->getX() + 1 == xMove) && (p->getY() + 1 == yMove)) { //above right
                return false;
            } else if((p->getX() - 1 == xMove) && (p->getY() + 1 == yMove)) { // above left
                return false;
            } else if((p->getX() - 1  == xMove) && (p->getY() == yMove)) { // direct left
                return false;
            } else if ((p->getX() +1  == xMove) && (p->getY() == yMove)) { //direct right
                return false;
            } else if ((p->getX() == xMove) && (p->getY() - 1 == yMove)) { //direct down
                return false;
            } else if ((p->getX() -1 == xMove) && (p->getY() -1 == yMove)) { //left down
                return false;
            } else if ((p->getX() + 1  == xMove) && (p->getY() - 1 == yMove)) { //right down
                return false;
            }

            //return true
        } else if (p->isValidCaptureMove(xMove, yMove)) {
         //cout << "Im in valid capture move else if" << endl;
            return false;
        } else if (p->inLineOfSight(xMove, yMove)) {
           // cout << "I am in here for some reason" << endl;
            return false;
        }
    }

    if (abs(xDist) == 2) { // if you're castling

        cout << "IN here loool" << endl;
        if (b->getPiece(x,y)->notPreviouslyMoved()) {
        //    cout << "in the if statement" << endl;
            if (xDist < 0) {
                int curX = x - 1;

                while (b->isCoordEmpty(curX, y) && curX > 0) {
                    curX--;
                }

                if (curX >= x - 2) {
                    return false;
                }

                if (b->getPiece(curX, y)->isRook()) {
                    if (b->getPiece(curX, y)->notPreviouslyMoved()) {
                        //cout << "here in castling" << endl;
                        //b->movePiece(curX, y, x - 1, y);
                        return true; 
                    } else {
                        return false; 
                    }
                } else {
                    return false; 
                }
            } else {
              // cout << "in else statement" << endl;
                int curX = x + 1;

                while (b->isCoordEmpty(curX, y) && curX < 7) {
                    curX++;
                }
                
                if (curX <= x + 2) {
                    return false;
                }

              //  cout << "I made it in here ma" << endl;

                if (b->getPiece(curX, y)->isRook()) {
                   // cout << "????????" << endl;
                    if (b->getPiece(curX, y)->notPreviouslyMoved()) {
                        //b->movePiece(curX, y, x + 1, y);
                        return true; 
                    } else {
                        return false; 
                    }
                } else {
                    return false; 
                }
            }
        } else {
            return false; 
        }


        if (b->isGivingCheck(otherTeam)) { // if you're currently in check, invalid move
            return false; 
        }

        if (!(this->isValidMove(x + (xDist/2), y))) { //if square next to you would put u in check, invalid move 
            return false; 
        }

       //  cout << "x: " << x << "y: " << y << endl;
         b->movePiece(x, y, x + (xDist/2), y); // king moves 1 over
       //  cout << "x: " << x << "y: " << y << endl;
        
        if (!(this->isValidMove(xMove, y))) { //now when you're here, x calling if square you are moving to puts u in check, invalid move '
          //  cout << "x: " << x - (xDist/2) << endl; 
            b->undo(x - (xDist / 2), y, x, y);
            return false; 
        }

        b->undo(x - (xDist / 2), y, x, y);

      //  cout << "x: " << x << "y: " << y << endl;
    }
    
    //cout << "Im after the for loop" << endl;

    return true;
}

bool King::anyValidMoves() {
    if ((y + 1 < b->getBoardSizeY()) && this->isValidMove(x, y+1)) { // above
       return true;
    } else if((y + 1 < b->getBoardSizeY()) && (x+1 < b->getBoardSizeX()) && this->isValidMove(x+1, y+1)) { //above right
        return true;
    } else if((y + 1 < b->getBoardSizeY()) && (x-1 >= 0) && this->isValidMove(x-1, y+1)) { // above left
        return true;
    } else if((x-1 >= 0) && this->isValidMove(x - 1, y)) { // direct left
        return true;
    } else if ((x+1 < b->getBoardSizeX()) && this->isValidMove(x+1, y)) { //direct right
        return true;
    } else if ((y - 1 >= 0) && this->isValidMove(x, y-1)) { //direct down
        return true;
    } else if ((y - 1 >= 0) && (x - 1 >= 0) && this->isValidMove(x-1, y-1)) { //left down
        return true;
    } else if ((y - 1 >= 0) && (x+1 < b->getBoardSizeX()) && this->isValidMove(x+1, y-1)) { //right down
        return true;
    } 

    return false;

}

bool King::isValidCaptureMove(int xMove, int yMove) {
    return this->isValidMove(xMove, yMove);
}

bool King::inLineOfSight(int xMove, int yMove) {
    //if (xMove == x && yMove == y) {
     //   return false;
    //} BOUNDS CHECKING ADD THIS IN TO THE THING
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

    //cout << "Passed second if statement" << endl;

    if (abs(yDist) > 1) {
        return false;
    } else if (abs(xDist) > 1) {
        return false;
    }

    //cout << "Im before the for loop" << endl;

   // checking if the intended move is in check
    string otherTeam = b->getOtherTeamName(teamName);

    //cout << b->playerPieces(otherTeam).size() << endl;

    //cout <<  b->playerPieces(otherTeam).size() << endl;

    for (auto p : b->playerPieces(otherTeam)) {
        //cout << "yo" << endl;
        //cout << p->getName() << endl;
        if (p == b->getOtherKing(teamName)) {
            //cout << p->getName() << endl;
            if ((p->getX() == xMove) && (p->getY() + 1 == yMove)) { // above
                return false;
            } else if((p->getX() + 1 == xMove) && (p->getY() + 1 == yMove)) { //above right
                return false;
            } else if((p->getX() - 1 == xMove) && (p->getY() + 1 == yMove)) { // above left
                return false;
            } else if((p->getX() - 1  == xMove) && (p->getY() == yMove)) { // direct left
                return false;
            } else if ((p->getX() +1  == xMove) && (p->getY() == yMove)) { //direct right
                return false;
            } else if ((p->getX() == xMove) && (p->getY() - 1 == yMove)) { //direct down
                return false;
            } else if ((p->getX() -1 == xMove) && (p->getY() -1 == yMove)) { //left down
                return false;
            } else if ((p->getX() + 1  == xMove) && (p->getY() - 1 == yMove)) { //right down
                return false;
            }

            //return true
        } else if (p->isValidCaptureMove(xMove, yMove)) {
         //cout << "Im in valid capture move else if" << endl;
            return false;
        } else if (p->inLineOfSight(xMove, yMove)) {
            cout << p->getName() << endl;
            //cout << "I am in here for some reason" << endl;
            return false;
        }
    }

    return true;

}

vector<shared_ptr<Move>> King::allValidMoves() {
    vector<shared_ptr<Move>> moves{};

    // Bishop valid moves
    int xMove = x + 1;
    int yMove = y + 1;

    if (xMove < b->getBoardSizeX() && yMove < b->getBoardSizeY()) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        }
    }

    xMove = x - 1;
    yMove = y + 1;

    if (xMove >= 0 && yMove < b->getBoardSizeY()) {
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
    yMove = y - 1;

    if (xMove >= 0 && yMove >= 0) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        } 
    }
    
    // Rook valid moves

    xMove = x;
    yMove = y + 1;

    if (yMove < b->getBoardSizeY()) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        }
    }

    xMove = x;
    yMove = y - 1;

    if (yMove >= 0) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        }
    }

    xMove = x + 1;
    yMove = y;

    if (xMove < b->getBoardSizeX()) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        }
    }


    xMove = x - 1;
    yMove = y;

    if (xMove >= 0) {
        if (this->isValidMove(xMove, yMove)) {
            moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
        } 
    }


    // Castelling
    if (y == 0 || y == b->getBoardSizeY() - 1) {
        xMove = x + 2;
        yMove = y;

        if (xMove < b->getBoardSizeX()) {
            //cout << "In first casetling function" << endl;
            if (this->isValidMove(xMove, yMove)) {
              moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
             // b->undo(7, y, x+1, y);
            } 
        }

        xMove = x - 2;
        yMove = y;

        if (xMove >= 0) {
            //cout << "IN second casetling function" << endl;
            if (this->isValidMove(xMove, yMove)) {
              moves.emplace_back(make_shared<Move>(b, x, y, xMove, yMove, teamName));
            //  b->undo(0,y,x-1,y);
            } 
        }
    }
    

    return moves;
}
