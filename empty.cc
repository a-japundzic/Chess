#include "empty.h"
#include "move.h"

using namespace std;
Empty::Empty(char name, int curX, int curY, std::string teamName, bool blockable, DefaultBoard* theBoard, std::string captureDir) : Piece(name, curX, curY, teamName, captureDir, 0, blockable), b{theBoard}  {}

bool Empty::isValidMove(int xMove, int yMove) {
    return false; 
} // throw an exception if a move is attempted?

bool Empty::isValidCaptureMove(int xMove, int yMove) {
    return false;
}

bool Empty::inLineOfSight(int xMove, int yMove) {
    return false;
}

vector<shared_ptr<Move>> Empty::allValidMoves() {
    return vector<shared_ptr<Move>>{};
}
