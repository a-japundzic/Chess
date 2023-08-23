#include "realPlayer.h"
#include "player.h"
#include <stdexcept>

#include <iostream>

using namespace std;

RealPlayer::RealPlayer(string name): Player(name) {}

int RealPlayer::movePiece(int x, int y, int newX, int newY) {
    for (auto &p : b.lock()->playerPieces(name)) {
        if (p->enpessantable()) {
            p->setEnpessantableFalse();
        }
    }

    std::vector<shared_ptr<Move>> moves{};

    //cout << "Im here lol 1" << endl;
    

    // Check for stalemate
    for (auto &p : b.lock()->playerPieces(name)) {
      //  cout << "Im here lol 2" << endl;
        cout << p->getName() << endl;
       // cout << p->getName () << endl;
        std::vector<shared_ptr<Move>> piecesAllValidMoves = p->allValidMoves();
     //   cout << piecesAllValidMoves.size() << endl;
        moves.insert(moves.end(), piecesAllValidMoves.begin(), piecesAllValidMoves.end());
    }

   // cout << "Im here lol 3" << endl;

    if (moves.size() == 0) {
        throw invalid_argument{"Stalemate"};
    } 
    
    if (b.lock()->getPiece(x, y)->getTeamName() != name) {
        throw logic_error{"Not your turn"};
    }

    //cout << b.lock()->getPiece(x, y)->getName() << endl;
   // cout << b.lock()->getPiece(x, y)->isValidMove(newX, newY) << endl;

    if (!b.lock()->getPiece(x, y)->isValidMove(newX, newY)) {
        throw logic_error{"Invalid move"};
    } else {
        int pieceTakenIndex = -1;

        pieceTakenIndex = b.lock()->movePiece(x, y, newX, newY);

       // cout << b->getPiece(newX, newY)->getName() << endl;
       cout << name << endl;

        //cout << "im done" << endl;
        if (b.lock()->isGivingCheck(b.lock()->getOtherTeamName(name))) {
          //  cout << "Im in the if statment whaaaaaatttttt" << endl;
            b.lock()->undo(x, y, newX, newY, pieceTakenIndex);
            throw logic_error{"Invalid move: in check or would be in check"};
        }

        // Promotion Logic
        char newPiece = ' ';
        if (b.lock()->getPiece(newX, newY)->isPromotable() && (newY == 7 || newY == 0)) {
            while (!cin.eof()) {
                cin >> newPiece;

                try {
                    b.lock()->swapPiece(newX, newY, newPiece);
                } catch (logic_error e) {
                    cerr << e.what() << ": Please enter a valid piece" << endl;
                    continue;
                }

                break;
            }
        }


        //cout << b->getOtherKing(name)->getX() << " " << b->getOtherKing(name)->getY() << endl;
        if(b.lock()->isGivingCheck(name)) {
            givingCheck = true;
        }

        return pieceTakenIndex;
    }
}
