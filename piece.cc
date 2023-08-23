#include "piece.h"
#include <string>
#include <iostream>
#include <sstream>

class DefaultBoard;

using namespace std;

Piece::Piece(char name, int curX, int curY, std::string teamName, string captureDir, int value, bool blockable) : name{name}, x{curX}, y{curY}, teamName{teamName}, captureDir{captureDir}, value{value}, blockable{blockable} {}

//virtual bool isValidMove(int xMove, int yMove) = 0;

/* returns all valid moves possible for the piece
    - each move is separated by a "|"
    - ex: 2,3|4,5|3,2|
*/
//virtual std::string Piece::allValidMoves() = 0;
/*bool isCoordEmpty(DefaultBoard* b, int x, int y) {
    if (b->getPiece(x, y)->getName() != ' ' || b->getPiece(x, y)->getName() != '_') {
        return false;
    }
    return true;
}*/

void Piece::updateNumOfMoves(char op) {
    if (op == '+') {
        ++numOfMoves;
    } else {
        --numOfMoves;
    }   
}

int Piece::getX() {
    return x;
}

int Piece::getY() {
    return y;
}

//void Piece::assignTeamName(std::string teamName) : teamName{teamName} {}

std::string Piece::getTeamName() {
    return teamName;
}

char Piece::getName() {
    return name;
}

bool Piece::isBlockable() {
    return blockable; 
}

bool Piece::isPromotable() {
    return false; 
}

void Piece::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

string Piece::getCaptureDir() {
    return captureDir;
}

bool Piece::enpessantable() {
    return false; 
}

void Piece::setEnpessantableFalse(){
    isEnpessantable = false;
}

void Piece::setEnpessantableTrue() {
    isEnpessantable = true;
}

bool Piece::isRook() {
    return false; 
}

bool Piece::notPreviouslyMoved() {
    return (numOfMoves == 0);
}


int Piece::getValue() {
    return value;
}

//bool Piece::givingCheck(std::shared_ptr<Piece> p) {
//    this->isValidMove(p->getX(), p->getY());
//}

//bool Piece::anyValidMoves() {
//    return true;
//}
