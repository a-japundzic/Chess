#include "move.h"
#include "board.h"
using namespace std;

Move::Move(Board* b, int x, int y, int xMove, int yMove, string teamName) : b{b}, x{x}, y{y}, xMove{xMove}, yMove{yMove}, teamName{teamName}, value1{0}, value2{0}, canCapture{false}, givesCheck{false}, capturable{false} {
    bool inCheck = false;
    
    if (b->isGivingCheck(b->getOtherTeamName(teamName))) {
        inCheck = true;
    }
    
    int index = b->movePiece(x, y, xMove, yMove);

    if (b->isGivingCheck(teamName)) {
        givesCheck = true;
        value1 += 3;
    }

    if (inCheck) {
        if (!b->isGivingCheck(b->getOtherTeamName(teamName))) {
            value1 += 50;
        }
    } else if (b->isGivingCheck(b->getOtherTeamName(teamName))) {
        value1 -= 50;
    }

    for (auto p : b->playerPieces(b->getOtherTeamName(teamName))) {
        if (p->isValidCaptureMove(xMove, yMove)) {
            capturable = true;
            value2 -= b->getPiece(xMove, yMove)->getValue();
        }
    }

    b->undo(x, y, xMove, yMove, index);
    
    if (!b->isCoordEmpty(xMove, yMove) && b->getPiece(xMove, yMove)->getTeamName() != teamName && !givesCheck) {
        canCapture = true; 
        value1 += b->getPiece(xMove, yMove)->getValue();
    }

    value2 += value1;

    for (auto p : b->playerPieces(b->getOtherTeamName(teamName))) {
        if (p->isValidCaptureMove(x, y)) {
            capturable = true;
            value2 += b->getPiece(x, y)->getValue();
        }
    }

}
