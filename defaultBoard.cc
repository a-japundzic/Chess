#include "defaultBoard.h"
#include "computer.h"
#include "rook.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "king.h"
#include "queen.h"
#include "empty.h"
#include "player.h"
#include <memory>

#include <iostream>

using namespace std;
DefaultBoard::DefaultBoard(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, char type) : p1{player1}, p2{player2} {
    string p1Name = p1.lock()->getName();
    string p2Name = p2.lock()->getName();
    int column = 0;
    bool addBlack = true;
    
    // row one of all empty pieces
    vector<shared_ptr<Piece>> rowOne(8);
    column = 0;
    addBlack = true;
    for (auto  &p : rowOne) {
        if (addBlack) {
            p = make_shared<Empty>('_', column,2, p2Name, false, this,"N");
            ++column;
            addBlack = false;
        } else {
            p = make_shared<Empty>(' ', column,2, p1Name, false, this, "N");
            ++column;
            addBlack = true;
        }
    }
    b.push_back(rowOne);

    // row two of all empty pieces
    vector<shared_ptr<Piece>> rowTwo(8);
    addBlack = false;
    column = 0;
    for (auto  &p : rowTwo) {
        if (addBlack) {
            p = make_shared<Empty>('_', column,5,p2Name,false,this,"N");
            ++column;
            addBlack = false;
        } else {
            p = make_shared<Empty>(' ', column,5,p1Name,false,this, "N");
            ++column;
            addBlack = true;
        }
    } 
    b.push_back(rowTwo);

    // row one of all empty pieces
    vector<shared_ptr<Piece>> rowThree(8);
    column = 0;
    addBlack = true;
    for (auto  &p : rowThree) {
        if (addBlack) {
            p = make_shared<Empty>('_', column,2, p2Name, false, this,"N");
            ++column;
            addBlack = false;
        } else {
            p = make_shared<Empty>(' ', column,2, p1Name, false, this, "N");
            ++column;
            addBlack = true;
        }
    }
    b.push_back(rowThree);

    // row two of all empty pieces
    vector<shared_ptr<Piece>> rowFour(8);
    addBlack = false;
    column = 0;
    for (auto  &p : rowFour) {
        if (addBlack) {
            p = make_shared<Empty>('_', column,5,p2Name,false,this,"N");
            ++column;
            addBlack = false;
        } else {
            p = make_shared<Empty>(' ', column,5,p1Name,false,this, "N");
            ++column;
            addBlack = true;
        }
    } 
    b.push_back(rowFour);

    // row one of all empty pieces
    vector<shared_ptr<Piece>> rowFive(8);
    column = 0;
    addBlack = true;
    for (auto  &p : rowFive) {
        if (addBlack) {
            p = make_shared<Empty>('_', column,2, p2Name, false, this,"N");
            ++column;
            addBlack = false;
        } else {
            p = make_shared<Empty>(' ', column,2, p1Name, false, this, "N");
            ++column;
            addBlack = true;
        }
    }
    b.push_back(rowFive);

    // row two of all empty pieces
    vector<shared_ptr<Piece>> rowSix(8);
    addBlack = false;
    column = 0;
    for (auto  &p : rowSix) {
        if (addBlack) {
            p = make_shared<Empty>('_', column,5,p2Name,false,this,"N");
            ++column;
            addBlack = false;
        } else {
            p = make_shared<Empty>(' ', column,5,p1Name,false,this, "N");
            ++column;
            addBlack = true;
        }
    } 
    b.push_back(rowSix);

    // row one of all empty pieces
    vector<shared_ptr<Piece>> rowSeven(8);
    column = 0;
    addBlack = true;
    for (auto  &p : rowSeven) {
        if (addBlack) {
            p = make_shared<Empty>('_', column,2, p2Name, false, this,"N");
            ++column;
            addBlack = false;
        } else {
            p = make_shared<Empty>(' ', column,2, p1Name, false, this, "N");
            ++column;
            addBlack = true;
        }
    }
    b.push_back(rowSeven);

    // row two of all empty pieces
    vector<shared_ptr<Piece>> rowEight(8);
    addBlack = false;
    column = 0;
    for (auto  &p : rowEight) {
        if (addBlack) {
            p = make_shared<Empty>('_', column,5,p2Name,false,this,"N");
            ++column;
            addBlack = false;
        } else {
            p = make_shared<Empty>(' ', column,5,p1Name,false,this, "N");
            ++column;
            addBlack = true;
        }
    } 
    b.push_back(rowEight);

    promotionPieces[p1Name] = {'Q','B','N','R'};
    promotionPieces[p2Name] = {'q','b','n','r'};

}
void DefaultBoard::addAtPos(char type, int x, int y){
    string p1Name = p1.lock()->getName();
    string p2Name = p2.lock()->getName();

    if (!this->isCoordEmpty(x, y)) {
        this->removeAtPos(x, y);
    }
    
    //string p1Name = p1->getTeamName();
    //string p2name = p2->getTeamName();

    //HANDLES wrong char types based on player
    /*if (nameTeam == p1->getName() && type >= 97 && type <= 122) { //white and lowercase
        type -= 32;
    } else if (nameTeam == p2->getName() && type >= 65 && type <= 90) { // black and uppercase
        type += 32; 
    }*/ 

    if (type == 'Q') {
        b[y][x] = make_shared<Queen>(type, x, y, p1Name, true, this, "VHD");
    } else if (type == 'B') {
        b[y][x] = make_shared<Bishop>(type, x, y,  p1Name, true, this, "D");
    } else if (type == 'N') {
        b[y][x] = make_shared<Knight>(type, x, y,  p1Name, false, this, "L");
    } else if (type == 'R') {
        b[y][x] = make_shared<Rook>(type, x, y,  p1Name, true, this, "VH");
    } else if (type == 'P') {
        b[y][x] = make_shared<Pawn>(type, x, y,  p1Name, true, this, "D");
    } else if (type == 'K') {
        p1King = make_shared<King>(type, x, y,  p1Name, true, this, "VHD");
        kings.emplace_back(p1King);
        b[y][x] = p1King;
    }
    

    if (type < 'a') {
        players[p1Name].emplace_back(b[y][x]);
    }

    if (type == 'q') {
        b[y][x] = make_shared<Queen>(type, x, y, p2Name, true, this, "VHD");
    } else if (type == 'b') {
        b[y][x] = make_shared<Bishop>(type, x, y,  p2Name, true, this, "D");
    } else if (type == 'n') {
        b[y][x] = make_shared<Knight>(type, x, y,  p2Name, false, this, "L");
    } else if (type == 'r') {
        b[y][x] = make_shared<Rook>(type, x, y,  p2Name, true, this, "VH");
    } else if (type == 'p') {
        b[y][x] = make_shared<Pawn>(type, x, y,  p2Name, true, this, "D");
    } else if (type == 'k') {
        p2King = make_shared<King>(type, x, y,  p2Name, true, this, "VHD");
        kings.emplace_back(p2King);
        b[y][x] = p2King;
    }
    
    // does this add shit to the player vector????? = Yes
    if (type >= 'a') {
        players[p2Name].emplace_back(b[y][x]);
    }


    /*
    switch(piece) {

        //swapPiece
        case 'K':
            p1King = make_shared<King>('K',y,x,p1Name,true, this, "VHD");
            //b.emplace_back(p1king);
            
            //rowOne.emplace_back(p1King);
            break;
        case 'Q':
    // code block
            break;
        case 'B':
    // code block
            break;
        case 'R':
    // code block
            break;
        case 'N':
    // code block
            break;
        case 'P':
    // code block
            break;
        case 'k':
    // code block
            break;
        case 'q':
    // code block
            break;
        case 'b':
    // code block
            break;
        case 'r':
    // code block
            break;
        case 'n':
    // code block
            break;
        case 'p':
    // code block
            break;         
        //default:
    // code block
}*/
}

void DefaultBoard::removeAtPos(int x, int y) {
    string p1Name = p1.lock()->getName();
    string p2Name = p2.lock()->getName();

            
    // NEED TO ALSO REMOVE FROM THE PLAYER IF WE TAKE IT OFF THE BOARD AND KING PTR SHIT!!!!!!!!!!!!!!!!!!!
    //  Above done here
    int index = 0;
    for (auto p : players[b[y][x]->getTeamName()]) {
        if (p->getName() == b[y][x]->getName() && p->getX() == b[y][x]->getX() && p->getY() == b[y][x]->getY()) {
           // cout << "In if statement" << endl;
            break;
        }
        ++index;
    }

    players[b[y][x]->getTeamName()].erase(players[b[y][x]->getTeamName()].begin()+index);

    if (b[y][x]->getName() == 'K' || b[y][x]->getName() == 'k') {
        index = 0;
        for (auto p : kings) {
            if (p->getX() == b[y][x]->getX() && p->getY() == b[y][x]->getY()) {
                break;
            }
        ++index;
        }

        kings.erase(kings.begin()+index);

        p1King = nullptr;
        p2King = nullptr;

        for (auto p : kings) {
            if (p1.lock()->getName() == p->getTeamName()) {
                p1King = p;
            }

            if (p2.lock()->getName() == p->getTeamName()) {
                p2King = p;
            }
        }
    }

    //issues 
        // should be able to simplify adding the new piece to the player vector
        // should be able to siumplify deleting the piece in the player vector
        // implement king checking
        // implement pawn location checking

    // determining if black or white empty spot is required
    // also dont think i need 2 iterators but not pertinent
    if (x % 2 == 0  && y % 2 == 0 || x % 2 == 1 && y % 2 == 1) {
        b[y][x] = make_shared<Empty>('_', x,y,p2Name, false, this,"N");  
    } else {
        b[y][x] = make_shared<Empty>(' ', x,y,p1Name, false, this,"N"); 
    }
}

DefaultBoard::DefaultBoard(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2): p1{player1}, p2{player2} {
    string p1Name = p1.lock()->getName();
    string p2Name = p2.lock()->getName();
    int column = 0;
    bool addBlack = true;

    vector<shared_ptr<Piece>> rowOne;
    rowOne.emplace_back(make_shared<Rook>('R',0,0,p1Name,true, this,"VH"));
    rowOne.emplace_back(make_shared<Knight>('N',1,0,p1Name,false, this, "L"));
    rowOne.emplace_back(make_shared<Bishop>('B',2,0,p1Name,true, this, "D"));
    rowOne.emplace_back(make_shared<Queen>('Q',3,0,p1Name,true, this, "VHD"));

    // keeping track of king p1
    p1King = make_shared<King>('K',4,0,p1Name,true, this, "VHD");
    rowOne.emplace_back(p1King);
    
    rowOne.emplace_back(make_shared<Bishop>('B',5,0,p1Name,true, this,"D"));
    rowOne.emplace_back(make_shared<Knight>('N',6,0,p1Name,true, this, "L"));
    rowOne.emplace_back(make_shared<Rook>('R',7,0,p1Name,true, this, "VH"));
    b.push_back(rowOne);

    vector<shared_ptr<Piece>> rowTwo(8);
    for (auto &p : rowTwo) {
        p = make_shared<Pawn>('P',column,1,p1Name, true, this, "D");
        ++column;
    }
    b.push_back(rowTwo);

    vector<shared_ptr<Piece>> player1Pieces;
        
    for (auto &p : rowOne) {
        player1Pieces.emplace_back(p);
    }

    for (auto &p : rowTwo) {
        player1Pieces.emplace_back(p);
    }

    players[p1Name] = player1Pieces;

    vector<shared_ptr<Piece>> rowThree(8);
    column = 0;
    for (auto  &p : rowThree) {
        if (addBlack) {
            p = make_shared<Empty>('_', column,2, p2Name, false, this,"N");
            ++column;
            addBlack = false;
        } else {
            p = make_shared<Empty>(' ', column,2, p1Name, false, this, "N");
            ++column;
            addBlack = true;
        }
    }
    b.push_back(rowThree);

    vector<shared_ptr<Piece>> rowFour(8);
    addBlack = false;
    column = 0;
    for (auto  &p : rowFour) {
        if (addBlack) {
            p = make_shared<Empty>('_', column,3,p2Name, false, this,"N");
            ++column;
            addBlack = false;
        } else {
            p = make_shared<Empty>(' ', column,3,p1Name,false,this, "N");
            ++column;
            addBlack = true;
        }
    } 
    b.push_back(rowFour);

    vector<shared_ptr<Piece>> rowFive(8);
    column = 0;
    addBlack = true;
    for (auto  &p : rowFive) {
        if (addBlack) {
            p = make_shared<Empty>('_', column,2, p2Name, false, this,"N");
            ++column;
            addBlack = false;
        } else {
            p = make_shared<Empty>(' ', column,2, p1Name, false, this, "N");
            ++column;
            addBlack = true;
        }
    }
    b.push_back(rowFive);

    vector<shared_ptr<Piece>> rowSix(8);
    addBlack = false;
    column = 0;
    for (auto  &p : rowSix) {
        if (addBlack) {
            p = make_shared<Empty>('_', column,5,p2Name,false,this,"N");
            ++column;
            addBlack = false;
        } else {
            p = make_shared<Empty>(' ', column,5,p1Name,false,this, "N");
            ++column;
            addBlack = true;
        }
    } 
    b.push_back(rowSix);
    

    vector<shared_ptr<Piece>> rowSeven(8);
    column = 0;
    for (auto &p : rowSeven) {
        p = make_shared<Pawn>('p',column,6,p2Name, true, this, "D");
        ++column;
    }
    b.push_back(rowSeven);

    vector<shared_ptr<Piece>> rowEight;
    rowEight.emplace_back(make_shared<Rook>('r',0,7,p2Name,true,this,"VH"));
    rowEight.emplace_back(make_shared<Knight>('n',1,7,p2Name, false, this, "L"));
    rowEight.emplace_back(make_shared<Bishop>('b',2,7,p2Name,true,this, "D"));
    rowEight.emplace_back(make_shared<Queen>('q',3,7,p2Name,true,this, "VHD"));

    p2King = make_shared<King>('k',4,7,p2Name,true, this, "VHD");
    rowEight.emplace_back(p2King);

    rowEight.emplace_back(make_shared<Bishop>('b',5,7,p2Name,true,this, "D"));
    rowEight.emplace_back(make_shared<Knight>('n',6,7,p2Name,true,this, "L"));
    rowEight.emplace_back(make_shared<Rook>('r',7,7,p2Name,true,this,"VH"));
    b.push_back(rowEight);

    vector<shared_ptr<Piece>> player2Pieces;
        
    for (auto &p : rowEight) {
        player2Pieces.emplace_back(p);
    }

    for (auto &p : rowSeven) {
        player2Pieces.emplace_back(p);
    }

    players[p2Name] = player2Pieces;

    // Map for promotion pieces
    promotionPieces[p1Name] = {'Q','B','N','R'};
    promotionPieces[p2Name] = {'q','b','n','r'};

} //calls attach in body of ctor

bool DefaultBoard::isCoordEmpty(int x, int y) {
    if (b[y][x]->getName() != ' ' && b[y][x]->getName() != '_') {
        return false;
    }
    return true;
}

int DefaultBoard::movePiece(int x, int y, int newX, int newY) {
    // move piece to new location
    // if enemy piece at new location, detach enemy piece from board

    // need to know which player owns piece to be moved?
    // player has pointer to board with detach func
    // attach func that adds player at x,y?

    //pseudocode

    //cout << lastPieceTaken->getName() << " In movePiece function" << endl;
    lastPieceTaken = b[newY][newX];
    b[y][x]->setPosition(newX, newY);
    b[y][x]->updateNumOfMoves('+');

   // cout << b[y][x]->getName() << endl;

    b[newY][newX].swap(b[y][x]);
    
    if (((this->getPiece(newX, newY)->getName() == p1King->getName()) || (this->getPiece(newX, newY)->getName() == p2King->getName()))) {
        if (newX - x == 2) {
            cout << b[y][7]->getName() << "In first else if" << endl;
            b[y][7]->setPosition(x+1, y);
            b[y][7]->updateNumOfMoves('+');
            b[y][x+1].swap(b[y][7]);
        } else if (newX - x == -2) {
            cout << b[y][0]->getName() << "In else if"  << endl;
            b[y][0]->setPosition(x-1, y);
            b[y][0]->updateNumOfMoves('+');
            b[y][x-1].swap(b[y][0]);
        }
    }

    int index = 0;
    if (!this->isCoordEmpty(x, y)) {
        for (auto p : players[b[y][x]->getTeamName()]) {
            if (p->getName() == b[y][x]->getName() && p->getX() == b[y][x]->getX() && p->getY() == b[y][x]->getY()) {
                break;
            }
            ++index;
        }

        players[b[y][x]->getTeamName()].erase(players[b[y][x]->getTeamName()].begin()+index);
    } else {
        index = -1;
    }

    if (y % 2 == 0 && x % 2 == 0 || y % 2 == 1 && x % 2 == 1) {
        b[y][x] = make_shared<Empty>('_', x, y, p2.lock()->getName(), false, this,"N");
    } else {
        b[y][x] = make_shared<Empty>(' ', x, y, p1.lock()->getName(), false, this, "N");
    }



    //cout << b[newY][newX]->getName() << " After If statements" << endl;

    return index;

}

// Only call immediately after last move
void DefaultBoard::undo(int x, int y, int newX, int newY, int index) {
    // Undo casteling
   // cout << "NEW X: " << newX << endl;
  //  cout << "X: " << x << endl;
    int xDist = newX - x; 
   // cout << "NEW X - X: " << newX - x << endl;
    if (abs(xDist) == 2 && (b[newY][newX]->getName() == p1King->getName() || b[newY][newX]->getName() == p2King->getName())) {
        shared_ptr<Piece> kingLastPieceTaken = lastPieceTaken;

       cout << "Im in here jimmy" << endl;
        if (xDist < 0) {
            if (y % 2 == 0 && (x-1) % 2 == 0 || y % 2 == 1 && (x - 1) % 2 == 1) {
                lastPieceTaken = make_shared<Empty>('_', x, y, p2.lock()->getName(), false, this,"N");
            } else {
                lastPieceTaken = make_shared<Empty>(' ', x, y, p1.lock()->getName(), false, this, "N");
            }

            this->undo(0, y, x - 1, y);

            lastPieceTaken = kingLastPieceTaken;
        } else {
            cout << b[y][x+1]->getName() << endl;

            if (y % 2 == 0 && (x+1) % 2 == 0 || y % 2 == 1 && (x + 1) % 2 == 1) {
                lastPieceTaken = make_shared<Empty>('_', x, y, p2.lock()->getName(), false, this,"N");
            } else {
                lastPieceTaken = make_shared<Empty>(' ', x, y, p1.lock()->getName(), false, this, "N");
            }

            this->undo(7, y, x + 1, y);

            lastPieceTaken = kingLastPieceTaken;
        }
    }

    // Undo promotion
    if ((b[newY][newX]->getY() == 7) && b[y][x]->isPromotable()) {
        b[newY][newX] = make_shared<Pawn>('P',newX,newY,p1.lock()->getName(),true, this,"D");
    } else if (b[newY][newX]->getY() == 0 && b[y][x]->isPromotable()) {
        b[newY][newX] = make_shared<Pawn>('p',newX,newY,p2.lock()->getName(),true,this,"D");
    }


    //cout << b[newY][newX]->getName() << endl;
    b[newY][newX]->setPosition(x, y);
    b[newY][newX]->updateNumOfMoves('-');
    b[y][x].swap(b[newY][newX]);

    b[newY][newX] = lastPieceTaken;


    // Undo enpessent
    if (this->isCoordEmpty(newX, newY) && (b[y][x]->getName() == 'p') && (newX > x || newX < x)) {
        b[y][newX] = make_shared<Pawn>('P',newX,y,p1.lock()->getName(),true, this,"D");
        b[y][newX]->setEnpessantableTrue();
        b[y][newX]->updateNumOfMoves('+');
    } else if (this->isCoordEmpty(newX, newY) && (b[y][x]->getName() == 'P') && (newX > x || newX < x)) {
        b[y][newX] = make_shared<Pawn>('p',newX,y,p2.lock()->getName(),true,this,"D");
        b[y][newX]->setEnpessantableTrue();
        b[y][newX]->updateNumOfMoves('+');
    }

    //cout << "My name is: " << lastPieceTaken->getName() << endl;

    if (index >= 0) {
        //cout << "In if statement" << " " << players[b[newY][newX]->getTeamName()].size() << endl;
        players[lastPieceTaken->getTeamName()].emplace(players[lastPieceTaken->getTeamName()].begin()+index, lastPieceTaken);
        //cout << players[b[newY][newX]->getTeamName()].size() << endl;
        //cout << "My name is in players: " << players[b[newY][newX]->getTeamName()][index]->getName() << endl;
    }

}

void DefaultBoard::swapPieceEmpty(int x, int y) {
    if (y % 2 == 0 && x % 2 == 0 || y % 2 == 1 && x % 2 == 1) {
        b[y][x] = make_shared<Empty>('_', x, y, p2.lock()->getName(), false, this,"N");
    } else {
        b[y][x] = make_shared<Empty>(' ', x, y, p1.lock()->getName(), false, this, "N");
    }
}

void DefaultBoard::swapPiece(int x, int y, char type) {
    if (type != 'Q' && type != 'q' && type != 'B' && type != 'b' && type != 'N' && type != 'n' && type != 'R' && type != 'r') {
        throw logic_error{"Not a valid piece for promotion"}; 
    }

    string nameTeam = b[y][x]->getTeamName();

    //HANDLES wrong char types based on player
    if (nameTeam == p1.lock()->getName() && type >= 97 && type <= 122) { //white and lowercase
        type -= 32;
    } else if (nameTeam == p2.lock()->getName() && type >= 65 && type <= 90) { // black and uppercase
        type += 32; 
    } 

    if (type == 'Q' || type == 'q') {
        b[y][x] = make_shared<Queen>(type, x, y, nameTeam, true, this, "VHD");
    } else if (type == 'B' || type == 'b') {
        b[y][x] = make_shared<Bishop>(type, x, y, nameTeam, true, this, "D");
    } else if (type == 'N' || type == 'n') {
        b[y][x] = make_shared<Knight>(type, x, y, nameTeam, false, this, "L");
    } else if (type == 'R' || type == 'r') {
        b[y][x] = make_shared<Rook>(type, x, y, nameTeam, true, this, "VH");
    }
    
    for (auto &p : players[nameTeam]) {
        if(p->getX() == x && p->getY() == y) {
            p = b[y][x];
        }
    }
    
}

string DefaultBoard::getOtherTeamName(string myTeamName) {
    if (p1.lock()->getName() == myTeamName) {
        return p2.lock()->getName();
    } else {
        return p1.lock()->getName();
    }
}

shared_ptr<King>& DefaultBoard::getOtherKing(string myTeamName) {
    if (p1.lock()->getName() == myTeamName) {
        return p2King;
    } else {
        return p1King;
    }
}

shared_ptr<King>& DefaultBoard::getMyKing(string myTeamName) {
    if (p1.lock()->getName() == myTeamName) {
        return p1King;
    } else {
        return p2King;
    }
}

bool DefaultBoard::isGivingCheck(string myTeamName) {
  //  cout << myTeamName << endl;
    if (p1.lock()->getName() == myTeamName) {
        for (auto p : playerPieces(p1.lock()->getName())) {
               // cout << p->getName() << endl;
                if (p->isValidCaptureMove(p2King->getX(), p2King->getY())) {
                    return true;
                }
        }
    } else {
        for (auto p : playerPieces(p2.lock()->getName())) {
              //  cout << p->getName() << endl;
                if (p->isValidCaptureMove(p1King->getX(), p1King->getY())) {
                    return true;
                }
        }
    }

   // cout << "im done" << endl;
    return false;
}


bool DefaultBoard::isPawnsInRowX(int i) {
    for (int j = 0; j < 8; ++j) {
        if (b[i - 1][j]->getName() == 'P' || b[i - 1][j]->getName() == 'p') {
            return true;
        }
    }
    return false;
}

bool DefaultBoard::isOneKingPerTeam() {
    int kingCounter = 0;
    for (auto p : this->playerPieces("White")) {
        if (p->getName() == 'K') {
            kingCounter++;
        }
    }
    if (kingCounter != 1) {
        return false;
    }
    
    kingCounter = 0;

    for (auto p : this->playerPieces("Black")) {
        if (p->getName() == 'k') {
            kingCounter++;
        }
    }
    if (kingCounter != 1) {
        return false;
    }

    return true;

}



