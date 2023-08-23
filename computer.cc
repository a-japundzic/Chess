#include "computer.h"
#include "player.h"
#include "move.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

Computer1::Computer1(string name): Player(name) {
   srand(time(0));
}

int Computer1::movePiece(int x, int y, int newX, int newY) {
    for (auto &p : b.lock()->playerPieces(name)) {
      if (p->enpessantable()) {
          p->setEnpessantableFalse();
      }
    }


    std::vector<std::shared_ptr<Move>> moves;

    for (auto &p : b.lock()->playerPieces(name)) {
       // cout << p->getName () << endl;
        std::vector<shared_ptr<Move>> piecesAllValidMoves = p->allValidMoves();
     //   cout << piecesAllValidMoves.size() << endl;
        moves.insert(moves.end(), piecesAllValidMoves.begin(), piecesAllValidMoves.end());
    }

    if (moves.size() == 0) {
       throw invalid_argument{"Stalemate"};
    }

    //cout << moves.size() << endl;

    int pieceTakenIndex = -1;

    while (true) {

        int chosenMove = rand() % moves.size();

       // cout << chosenMove << endl;

        x = moves[chosenMove]->x;
        y = moves[chosenMove]->y;
        newX = moves[chosenMove]->xMove;
        newY = moves[chosenMove]->yMove;

        //cout << x << " " << y << " " << newX << " " << newY << endl;
        // cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
        //cout << b.lock()->getPiece(x, y)->getName() << endl;

        pieceTakenIndex = -1;

        pieceTakenIndex = b.lock()->movePiece(x, y, newX, newY);

        //cout << b.lock()->getPiece(newX, newY)->getName() << endl;

        //cout << "im done" << endl;
        if (b.lock()->isGivingCheck(b.lock()->getOtherTeamName(name))) {
          //  cout << "Im in the if statment whaaaaaatttttt" << endl;
            b.lock()->undo(x, y, newX, newY, pieceTakenIndex);
            continue;
        }

        break;

    }


    x1 = x + 1;
    y1 = y + 1;
    x2 = newX + 1;
    y2 = newY + 1;

    // Handles promotion
    if (b.lock()->getPiece(x2-1, y2-1)->isPromotable() && (y2 == 8 || y2 == 1)) {
      b.lock()->swapPiece(x2-1, y2-1, b.lock()->getRandomPromotionPiece(name));
    }
                    

      //  cout << "im after the first if statement" << endl;

        //cout << b->getOtherKing(name)->getX() << " " << b->getOtherKing(name)->getY() << endl;
    if(b.lock()->isGivingCheck(name)) {
      givingCheck = true;
    }


    return pieceTakenIndex;

       // cout << "im after the second if statement" << endl;
    
}


Computer2::Computer2(string name): Player(name) {
   srand(time(0));
}

int Computer2::movePiece(int x, int y, int newX, int newY) {
    for (auto &p : b.lock()->playerPieces(name)) {
      if (p->enpessantable()) {
          p->setEnpessantableFalse();
      }
    }

    std::vector<std::shared_ptr<Move>> moves;

    // Put all possible moves in vector
    for (auto &p : b.lock()->playerPieces(name)) {
       // cout << p->getName () << endl;
        std::vector<shared_ptr<Move>> piecesAllValidMoves = p->allValidMoves();
     //   cout << piecesAllValidMoves.size() << endl;
        moves.insert(moves.end(), piecesAllValidMoves.begin(), piecesAllValidMoves.end());
    }

    if (moves.size() == 0) {
       throw invalid_argument{"Stalemate"};
    }

    int maxMoveValue = 0;

    // Find the max move value
    for (auto p : moves) {
      if (p->value1 > maxMoveValue) {
        maxMoveValue = p->value1;
      }
    }


    // Store all best moves in new vector
    std::vector<std::shared_ptr<Move>> bestMoves;

    for (auto &p : moves) {
      if (p->value1 == maxMoveValue) {
        bestMoves.emplace_back(p);
      }
    }


    int pieceTakenIndex = -1;
    //cout << bestMoves.size() << endl;

    while (true) {

        int chosenMove = rand() % bestMoves.size();

       // cout << chosenMove << endl;

        x = bestMoves[chosenMove]->x;
        y = bestMoves[chosenMove]->y;
        newX = bestMoves[chosenMove]->xMove;
        newY = bestMoves[chosenMove]->yMove;

        //cout << x << " " << y << " " << newX << " " << newY << endl;
        // cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
        //cout << b.lock()->getPiece(x, y)->getName() << endl;

        pieceTakenIndex = -1;

        pieceTakenIndex = b.lock()->movePiece(x, y, newX, newY);

        //cout << b.lock()->getPiece(newX, newY)->getName() << endl;

        //cout << "im done" << endl;
        if (b.lock()->isGivingCheck(b.lock()->getOtherTeamName(name))) {
          //  cout << "Im in the if statment whaaaaaatttttt" << endl;
            b.lock()->undo(x, y, newX, newY, pieceTakenIndex);
            continue;
        }

        break;

    }
    
    x1 = x + 1;
    y1 = y + 1;
    x2 = newX + 1;
    y2 = newY + 1;

     // Handles promotion
    if (b.lock()->getPiece(x2-1, y2-1)->isPromotable() && (y2 == 8 || y2 == 1)) {
      b.lock()->swapPiece(x2-1, y2-1, b.lock()->getRandomPromotionPiece(name));
    }

      //  cout << "im after the first if statement" << endl;

        //cout << b->getOtherKing(name)->getX() << " " << b->getOtherKing(name)->getY() << endl;
    if(b.lock()->isGivingCheck(name)) {
        givingCheck = true;
    }


    return pieceTakenIndex;

       // cout << "im after the second if statement" << endl;
    
}


Computer3::Computer3(string name): Player(name) {
   srand(time(0));
}

int Computer3::movePiece(int x, int y, int newX, int newY) {
    for (auto &p : b.lock()->playerPieces(name)) {
      if (p->enpessantable()) {
          p->setEnpessantableFalse();
      }
    }

    std::vector<std::shared_ptr<Move>> moves;

    // Put all possible moves in vector
    for (auto &p : b.lock()->playerPieces(name)) {
       // cout << p->getName () << endl;
        std::vector<shared_ptr<Move>> piecesAllValidMoves = p->allValidMoves();

     //   cout << piecesAllValidMoves.size() << endl;
        moves.insert(moves.end(), piecesAllValidMoves.begin(), piecesAllValidMoves.end());
    }

    if (moves.size() == 0) {
       throw invalid_argument{"Stalemate"};
    }

    int maxMoveValue = 0;

    // Find the max move value
    for (auto p : moves) {
      if (p->value2 > maxMoveValue) {
        maxMoveValue = p->value2;
      }
    }


    // Store all best moves in new vector
    std::vector<std::shared_ptr<Move>> bestMoves;

    for (auto &p : moves) {
      if (p->value2 == maxMoveValue) {
        bestMoves.emplace_back(p);
      }
    }

    cout << bestMoves.size() << endl;
    cout << maxMoveValue << endl;

    int pieceTakenIndex = -1;

    while (true) {

        int chosenMove = rand() % bestMoves.size();

       // cout << chosenMove << endl;

        x = bestMoves[chosenMove]->x;
        y = bestMoves[chosenMove]->y;
        newX = bestMoves[chosenMove]->xMove;
        newY = bestMoves[chosenMove]->yMove;

        cout << x << " " << y << " " << newX << " " << newY << endl;
        // cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
        //cout << b.lock()->getPiece(x, y)->getName() << endl;

        pieceTakenIndex = -1;

        pieceTakenIndex = b.lock()->movePiece(x, y, newX, newY);

        //cout << b.lock()->getPiece(newX, newY)->getName() << endl;

        //cout << "im done" << endl;
        if (b.lock()->isGivingCheck(b.lock()->getOtherTeamName(name))) {
          //  cout << "Im in the if statment whaaaaaatttttt" << endl;
            b.lock()->undo(x, y, newX, newY, pieceTakenIndex);
            continue;
        }

        break;
    }

    x1 = x + 1;
    y1 = y + 1;
    x2 = newX + 1;
    y2 = newY + 1;

     // Handles promotion
    if (b.lock()->getPiece(x2-1, y2-1)->isPromotable() && (y2 == 8 || y2 == 1)) {
      b.lock()->swapPiece(x2-1, y2-1, b.lock()->getRandomPromotionPiece(name));
    }

      //  cout << "im after the first if statement" << endl;
        //cout << b->getOtherKing(name)->getX() << " " << b->getOtherKing(name)->getY() << endl;
    if(b.lock()->isGivingCheck(name)) {
        givingCheck = true;
    }

    return pieceTakenIndex;

       // cout << "im after the second if statement" << endl;
    
}


Computer4::Computer4(string name, shared_ptr<OpeningMoves> om): Player(name), om{om} {
   srand(time(0));
}

int Computer4::movePiece(int x, int y, int newX, int newY) {
    for (auto &p : b.lock()->playerPieces(name)) {
      if (p->enpessantable()) {
          p->setEnpessantableFalse();
      }
    }

    string openingMoves = om->findNextMove(); 
    
  //  cout << openingMoves << endl;

    if (openingMoves != "") { 
      cout << openingMoves.length() << endl;
      cout << (openingMoves.length() / 5) + 1 << endl;

      int randMoveIndex = rand() % ((openingMoves.length() / 5) + 1);

    //  cout << randMoveIndex << endl;

      string chosenMove = openingMoves.substr(randMoveIndex * 5, 4);

      //cout << chosenMove << endl;

      chosenMove[0] = chosenMove[0] - 49; 
      chosenMove[2] = chosenMove[2] - 49;

     // cout << chosenMove << endl;

      x = chosenMove[0] - '0';
      y = chosenMove[1] - '0';
      --y;
      newX = chosenMove[2] - '0';
      newY = chosenMove[3] - '0';
      --newY;
      
    } else {
    
      std::vector<std::shared_ptr<Move>> moves;

      // Put all possible moves in vector
      for (auto &p : b.lock()->playerPieces(name)) {
          // cout << p->getName () << endl;
          std::vector<shared_ptr<Move>> piecesAllValidMoves = p->allValidMoves();

        //   cout << piecesAllValidMoves.size() << endl;
          moves.insert(moves.end(), piecesAllValidMoves.begin(), piecesAllValidMoves.end());
      }

      if (moves.size() == 0) {
          throw invalid_argument{"Stalemate"};
      }

      int maxMoveValue = 0;

      // Find the max move value
      for (auto p : moves) {
        if (p->value2 > maxMoveValue) {
          maxMoveValue = p->value2;
        }
      }


      // Store all best moves in new vector
      std::vector<std::shared_ptr<Move>> bestMoves;

      for (auto &p : moves) {
        if (p->value2 == maxMoveValue) {
          bestMoves.emplace_back(p);
        }
      }

      cout << bestMoves.size() << endl;
      cout << maxMoveValue << endl;

      int chosenMove = rand() % bestMoves.size();

       // cout << chosenMove << endl;

      x = bestMoves[chosenMove]->x;
      y = bestMoves[chosenMove]->y;
      newX = bestMoves[chosenMove]->xMove;
      newY = bestMoves[chosenMove]->yMove;
    }

    int pieceTakenIndex = -1;

    while (true) {
        cout << x << " " << y << " " << newX << " " << newY << endl;
        // cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
        //cout << b.lock()->getPiece(x, y)->getName() << endl;

        pieceTakenIndex = -1;

        pieceTakenIndex = b.lock()->movePiece(x, y, newX, newY);

        //cout << b.lock()->getPiece(newX, newY)->getName() << endl;

        //cout << "im done" << endl;
        if (b.lock()->isGivingCheck(b.lock()->getOtherTeamName(name))) {
          //  cout << "Im in the if statment whaaaaaatttttt" << endl;
            b.lock()->undo(x, y, newX, newY, pieceTakenIndex);
            continue;
        }

        break;
    }

    x1 = x + 1;
    y1 = y + 1;
    x2 = newX + 1;
    y2 = newY + 1;

     // Handles promotion
    if (b.lock()->getPiece(x2-1, y2-1)->isPromotable() && (y2 == 8 || y2 == 1)) {
      b.lock()->swapPiece(x2-1, y2-1, b.lock()->getRandomPromotionPiece(name));
    }

      //  cout << "im after the first if statement" << endl;
        //cout << b->getOtherKing(name)->getX() << " " << b->getOtherKing(name)->getY() << endl;
    if(b.lock()->isGivingCheck(name)) {
        givingCheck = true;
    }

    return pieceTakenIndex;

       // cout << "im after the second if statement" << endl;
    
}



