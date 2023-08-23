#include "board.h"
#include "defaultBoard.h"
#include "printBoardText.h"
#include "player.h"
#include "realPlayer.h"
#include "computer.h"
#include "piece.h"
#include "queen.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "openingMoves.h"
#include <string>
#include <memory>
#include <iostream>
#include <stdexcept>

using namespace std;

int convertMove(char move) {
    if (move == 'a') {
        return 1;
    } else if (move == 'b') {
        return 2;
    } else if (move == 'c') {
        return 3;
    } else if (move == 'd') {
        return 4;
    } else if (move == 'e') {
        return 5;
    } else if (move == 'f') {
        return 6;
    } else if (move == 'g') {
        return 7;
    } else {
        return 8;
    }
}

// setting up each player, base pieces and board setup
void getGameInput(shared_ptr<Player>& p1, shared_ptr<Player>& p2, shared_ptr<OpeningMoves>& om) {
   /* string command;
    while (true) {
        cin >> command;
        if (command != "game") {
            cin.clear();
            cin.ignore();
            cout << "Invalid input, please refer to input instructions" << endl;
        } else {
            break;
        }
    }
    
    if (command == "game") {     */
        // ensuring input validity
        string player1;
        while (true) {
            cin >> player1;
            if (player1 != "human" && player1 != "computer[1]" && player1 != "computer[2]"
            && player1 != "computer[3]" && player1 != "computer[4]" ) {
                cout << "Invalid input, please refer to input instructions" << endl;
                cin.clear();
                cin.ignore();
            } else {
                break;
            }
        }

        // setting up player1 with the correct object type
        if (player1 == "human") {
            p1 = make_shared<RealPlayer>("White");
        } else if (player1 == "computer[1]") {
            p1 = make_shared<Computer1>("White");
        } else if (player1 == "computer[2]") {
            p1 = make_shared<Computer2>("White");
        } else if (player1 == "computer[3]") {
            p1 = make_shared<Computer3>("White");
        } else if (player1 == "computer[4]") {
            p1 = make_shared<Computer4>("White", om);
        }
        
        // ensuring input validity
        string player2;
        while (true) {
            cin >> player2;
            if (player2 != "human" && player2 != "computer[1]" && player2 != "computer[2]"
            && player2 != "computer[3]" && player2 != "computer[4]" ) {
                cout << "Invalid input, please refer to input instructions" << endl;
                cin.clear();
                cin.ignore();
            } else {
                break;
            }
        }
        
        // setting up player2 with the correct object type
        if (player2 == "human") {
            p2 = make_shared<RealPlayer>("Black");
        } else if (player2 == "computer[1]") {
            p2 = make_shared<Computer1>("Black");
        } else if (player2 == "computer[2]") {
            p2 = make_shared<Computer2>("Black");
        } else if (player2 == "computer[3]") {
            p2 = make_shared<Computer3>("Black");
        } else if (player2 == "computer[4]") {
            p2 = make_shared<Computer4>("Black", om);
        }

        // building the default board with default pieces with the players
        //b  = make_shared<DefaultBoard>(p1, p2);

        // attaching the players to the board (each player has pointer to the board)
        //p1->attachBoard(b);  
        //p2->attachBoard(b);    
    //}
}

int main () {

    // Welcome Screen Output    
    cout << "WELCOME TO CHESS" << endl;
    cout << "Commands: " << endl;
    cout << "Start a default game: game [human || computer[i]] [human || computer[i]]" << endl;
    cout << "Setup your own game: setup" << endl;

    // Core initializations for the game
    shared_ptr<Player> p1;
    shared_ptr<Player> p2;
    shared_ptr<DefaultBoard> b;

    bool whiteTurn = true; 
    int whiteWins, blackWins;

    //getting initial game setup info
    string command;
    shared_ptr<OpeningMoves> om = make_shared<OpeningMoves>();
    
    while (true) {
        cin >> command;
        if (command != "game" && command != "setup") {
            // I think this works as intended
            cin.clear();
            cin.ignore();
            cout << "Invalid input, please refer to input instructions" << endl;
            continue;
        } else if (command == "game") {
            getGameInput(p1, p2, om);
            
            //building the default board with default pieces with the players
            b  = make_shared<DefaultBoard>(p1, p2);

            // attaching the players to the board (each player has pointer to the board)
            p1->attachBoard(b);  
            p2->attachBoard(b);
            om->attachBoard(b);
            
            break;
            
        } else if (command == "setup") {

            cout << "What kind of players will be playing on this board, input same format as if making a game" << endl;

            getGameInput(p1, p2, om);
            
            b = make_shared<DefaultBoard>(p1, p2, 'e');
            p1->attachBoard(b);  
            p2->attachBoard(b);

            om->attachBoard(b);
            PrintBoardText pb{b};

            pb.printBoard(8, 8);

            string command;
            char piece;
            string colour;
            char move = ' ';
            int x;
            int y;

            while (true) {
                // ensuring a valid input character
                while (true) {
                    cin >> command;
                    if (command != "+" && command != "-" && command != "=" && command != "done") {
                        cout << "Invalid input, please refer to input instructions" << endl;
                        cin.clear();
                        cin.ignore();
                        continue;
                    } else {
                        break;
                    }
                }
                if (command == "+") {
                    cin >> piece;
                    // just check the base ones or should we do iteration of player pieces?****************************************
                    // out of range inputs how do we want to check? hardcode base data****************************************
                    cin >> move;
                    x = convertMove(move);
                    cin >> y;
                    b->addAtPos(piece, x-1, y-1);
                    
                } else if (command == "-") {
                    cin >> move; // same thing as above ****************************************
                    x = convertMove(move);
                    cin >> y;
                    b->removeAtPos(x-1, y-1);
                } else if (command == "done") {
                    // run checks on if each player has exactly one king
                    if(!b->isOneKingPerTeam()) {
                        cout << "Too many or too few kings, must fix to continue " << endl;
                        pb.printBoard(8, 8);
                        continue;
                    } else if (b->isPawnsInRowX(1)) {
                        cout << "Pawns are not allowed in bottom row, must fix to continue" << endl;
                        pb.printBoard(8, 8);
                        continue;
                    } else if (b->isPawnsInRowX(8)) {
                        cout << "Pawns are not allowed in top row, must fix to continue" << endl;
                        pb.printBoard(8, 8);
                        continue;
                    } else if (b->isGivingCheck("White")) {
                        cout << "Black king is in check, must fix to continue" << endl;
                        pb.printBoard(8, 8);
                        continue;
                    } else if (b->isGivingCheck("Black")) {
                        cout << "White king is in check, must fix to continue" << endl;
                        pb.printBoard(8, 8);
                        continue;
                    }
                    
                    // ensure find way to set enpessantable or castleable to false****************************************
                    break;
                
                } else if (command == "=") {
                    cin >> colour; //same thing here just hardcode base colours? ****************************************
                    if (colour == "White") {
                        whiteTurn = true;
                    } else {
                        whiteTurn = false;
                    }
                }
                pb.printBoard(8, 8);
                
            }

            break;
        }
    }
    
    PrintBoardText pb{b};
    //cout << " do we get to here" << endl;
    int numMoves = 0; 
    //pb.printBoard(8, 8);
    while (true) {
        string cmd; 
        char move1 = ' ';
        char move2 = ' '; 
        char newPiece; 
        int undoIndex; 

        //cout << "Im here now 5" << endl;
        
        pb.printBoard(8, 8);

       // cout << "Im here now 6" << endl;
    //cin >> cmd;
        while (true) {
            cin >> cmd;
            if (cmd != "undo" && cmd != "suggestion" && cmd != "move") {
                cout << "Not a valid input" << endl;
                cin.clear();
                cin.ignore();
            } else {
                break;
            }
        }
        //if (cin.eof()) break;

        if (whiteTurn) {
            if (cmd == "undo") {
                b->undo(p2->x1-1, p2->y1-1, p2->x2-1, p2->y2-1, undoIndex);
                whiteTurn = !whiteTurn;
                continue; 
            } else if (cmd == "suggestion") {
                cout << endl;
                cout << om->findNextMove();
                cout << endl << endl;
                continue; 
            }

            try {
                if (cin.peek() == '\n') {
                    undoIndex = p1->movePiece();
                } else {
                    cin >> move1;
                    p1->x1 = convertMove(move1);
                    cin >> p1->y1;

                    cin >> move2;
                    p1->x2 = convertMove(move2);
                    cin >> p1->y2;

                    cout << p1->x1 << " " << p1->x2 << " " << p1->y1 << " " << p1->y2 << endl;

                    undoIndex = p1->movePiece(p1->x1-1, p1->y1-1, p1->x2-1, p1->y2-1);

                   // cout << "Im here now" << endl;
                      //cout << "Im here now 2" << endl;
                }

                if (p1->getGivingCheck()) {
                    cout << p2->getName() << " is in check" << endl;
                    if(p2->inCheckmate()) {
                        cout << "Checkmate! " << p1->getName() << " wins!" << endl;
                        break;
                    } else {
                        p1->resetCheck();
                    }
                }

                  //cout << "Im here now 3" << endl;
            } catch (invalid_argument e) {
                cerr << e.what();
                cout << ": White has no possible moves" << endl;
            } catch (logic_error e) {
                cerr << e.what() << endl;
                continue;
            } 

            p1->resetCheck();
            ++numMoves;
            om->updatePastMoves(p1->x1, p1->y1, p1->x2, p1->y2);

            //cout << "Im here now 4" << endl;

        } else {
            if (cmd == "undo") {
               // cout << p1->x1 << " " << p1->y1 << " " << p1->x2 << " " << p1->y2 << endl;
                b->undo(p1->x1-1, p1->y1-1, p1->x2-1, p1->y2-1, undoIndex);
                whiteTurn = !whiteTurn;
                continue; 
            } else if (cmd == "suggestion") {
                cout << endl << endl;
                cout << om->findNextMove();
                cout << endl << endl;
                continue;
            }

            try {
                if (cin.peek() == '\n') {
                    undoIndex = p2->movePiece();
                } else {
                    cin >> move1;
                    p2->x1 = convertMove(move1);
                    cin >> p2->y1;

                    cin >> move2;
                    p2->x2 = convertMove(move2);
                    cin >> p2->y2;

                    undoIndex = p2->movePiece(p2->x1-1, p2->y1-1, p2->x2-1, p2->y2-1);

                   /* if (b->getPiece(p2->x2-1, p2->y2-1)->isPromotable() && (p2->y2 == 8 || p2->y2 == 1)) {
                        cin >> newPiece;

                        try {
                            b->swapPiece(p2->x2-1, p2->y2-1, newPiece);
                        } catch (logic_error e) {
                            b->undo(p2->x1-1, p2->y1-1, p2->x2-1, p2->y2-1);
                            cerr << e.what() << endl;
                            continue;
                        }
                    }
                    */
                }

               //  cout << "I am in main after before the first if statement" << endl;

               // cout << "I am in main after the first if statement" << endl;

                if (p2->getGivingCheck()) {
                    cout << p1->getName() << " is in check" << endl;
                    if(p1->inCheckmate()) {
                        cout << "Checkmate! " << p2->getName() << " wins!" << endl;
                        break;
                    }
                }
            
            } catch (invalid_argument e) {
                cerr << e.what();
                cout << ": Black has no possible moves" << endl;
            } catch (logic_error e) {
                cerr << e.what() << endl;
                continue;
            } 

            p2->resetCheck();
            ++numMoves;
            om->updatePastMoves(p2->x1, p2->y1, p2->x2, p2->y2);

           // cout << "im done the players turn" << endl;
        
           // cout << "im done the players turn" << endl;
        }
        
        whiteTurn = !whiteTurn;

    //}
    }
}


/*
int main() {
    shared_ptr<Player> p1;
    shared_ptr<Player> p2;
        
    shared_ptr<DefaultBoard> b;

    bool whiteTurn = true; 
    int whiteWins, blackWins;

    while (true) {
        string input;

        if (cin.eof()) break;

        cin >> input;

        if (input == "game") {
            string player1;
            cin >> player1;

            if (player1 == "human") {
                p1 = make_shared<RealPlayer>("White");
            } else if (player1 == "computer[1]") {
                p1 = make_shared<Computer1>("White");
            } else if (player1 == "computer[2]") {
                p1 = make_shared<Computer2>("White");
            } else if (player1 == "computer[3]") {
                p1 = make_shared<Computer3>("White");
            }

            string player2;
            cin >> player2;

            if (player2 == "human") {
                p2 = make_shared<RealPlayer>("Black");
            } else if (player2 == "computer[1]") {
                p2 = make_shared<Computer1>("Black");
            } else if (player2 == "computer[2]") {
                p2 = make_shared<Computer2>("Black");
            } else if (player2 == "computer[3]") {
                p2 = make_shared<Computer3>("Black");
            }
        
            b  = make_shared<DefaultBoard>(p1, p2);

            p1->attachBoard(b);  
            p2->attachBoard(b);

            break;
        } else if (input == "setup") {
            p1 = make_shared<RealPlayer>("White");
            p2 = make_shared<RealPlayer>("Black");

            b = make_shared<DefaultBoard>(p1, p2, 'e');
            PrintBoardText pb{b};

            pb.printBoard(8, 8);

            p1->attachBoard(b);  
            p2->attachBoard(b);

            string command;
            char piece;
            string colour;
            char move = ' ';
            int x;
            int y;

            while (true) {
                cin >> command;
                if (command == "+") {
                    cin >> piece;
                    cin >> move;
                    x = convertMove(move);
                    cin >> y;
                    b->addAtPos(piece, x-1, y-1);
                    
                } else if (command == "-") {
                    cin >> move;
                    x = convertMove(move);
                    cin >> y;
                    b->removeAtPos(x-1, y-1);
                } else if (command == "done") {
                    // run checks on if each player has exactly one king
                    if(!b->isOneKingPerTeam()) {
                        cout << "Too many or too few kings, must fix to continue " << endl;
                        pb.printBoard(8, 8);
                        continue;
                    } else if (b->isPawnsInRowX(1)) {
                        cout << "Pawns are not allowed in bottom row, must fix to continue" << endl;
                        pb.printBoard(8, 8);
                        continue;
                    } else if (b->isPawnsInRowX(8)) {
                        cout << "Pawns are not allowed in top row, must fix to continue" << endl;
                        pb.printBoard(8, 8);
                        continue;
                    } else if (b->isGivingCheck("White")) {
                        cout << "Black king is in check, must fix to continue" << endl;
                        pb.printBoard(8, 8);
                        continue;
                    } else if (b->isGivingCheck("Black")) {
                        cout << "White king is in check, must fix to continue" << endl;
                        pb.printBoard(8, 8);
                        continue;
                    }
                    
                    // ensure find way to set enpessantable or castleable to false
                    break;
                
                } else if (command == "=") {
                    cin >> colour;
                    if (colour == "White") {
                        whiteTurn = true;
                    } else {
                        whiteTurn = false;
                    }
                }
                pb.printBoard(8, 8);
                
            }

            break;
    //b2->addAtPos('K', 4, 6);
        }   
    }

   // cout << "im outside the loop" << endl;

    PrintBoardText pb{b};
    int numMoves = 0; 
    shared_ptr<OpeningMoves> om = make_shared<OpeningMoves>();

    while (true) {
        string cmd; 
        char move1 = ' ';
        char move2 = ' '; 
        char newPiece; 
        int undoIndex; 
        
        pb.printBoard(8, 8);

        cin >> cmd;

        if (cin.eof()) break;

        if (whiteTurn) {
            if (cmd == "undo") {
                b->undo(p2->x1-1, p2->y1-1, p2->x2-1, p2->y2-1, undoIndex);
                whiteTurn = !whiteTurn;
                continue; 
            } else if (cmd == "suggestion") {
                cout << om->findNextMove();
                continue; 
            }

            try {
                if (cin.peek() == '\n') {
                    undoIndex = p1->movePiece();
                } else {
                    cin >> move1;
                    p1->x1 = convertMove(move1);
                    cin >> p1->y1;

                    cin >> move2;
                    p1->x2 = convertMove(move2);
                    cin >> p1->y2;

                    undoIndex = p1->movePiece(p1->x1-1, p1->y1-1, p1->x2-1, p1->y2-1);

                    if (b->getPiece(p1->x2-1, p1->y2-1)->isPromotable() && (p1->y2 == 8 || p1->y2 == 1)) {
                        cin >> newPiece;

                        try {
                            b->swapPiece(p1->x2-1, p1->y2-1, newPiece);
                        } catch (logic_error e) {
                            b->undo(p1->x1-1, p1->y1-1, p1->x2-1, p1->y2-1);
                            cerr << e.what() << endl;
                            continue;
                        }
                    }
                }

                if (p1->getGivingCheck()) {
                    cout << p2->getName() << " is in check" << endl;
                    if(p2->inCheckmate()) {
                        cout << "Checkmate! " << p1->getName() << " wins!" << endl;
                        break;
                    } else {
                        p1->resetCheck();
                    }
                }
            } catch (invalid_argument e) {
                cerr << e.what();
                cout << ": White has no possible moves" << endl;
            } catch (logic_error e) {
                cerr << e.what() << endl;
                continue;
            } 

            p1->resetCheck();
            ++numMoves;
            om->updatePastMoves(p1->x1, p1->y1, p1->x2, p1->y2);

        } else {
            if (cmd == "undo") {
               // cout << p1->x1 << " " << p1->y1 << " " << p1->x2 << " " << p1->y2 << endl;
                b->undo(p1->x1-1, p1->y1-1, p1->x2-1, p1->y2-1, undoIndex);
                whiteTurn = !whiteTurn;
                continue; 
            } else if (cmd == "suggestion") {
                cout << om->findNextMove();
                continue;
            }

            try {
                if (cin.peek() == '\n') {
                    undoIndex = p2->movePiece();
                } else {
                    cin >> move1;
                    p2->x1 = convertMove(move1);
                    cin >> p2->y1;

                    cin >> move2;
                    p2->x2 = convertMove(move2);
                    cin >> p2->y2;

                    undoIndex = p2->movePiece(p2->x1-1, p2->y1-1, p2->x2-1, p2->y2-1);

                    if (b->getPiece(p2->x2-1, p2->y2-1)->isPromotable() && (p2->y2 == 8 || p2->y2 == 1)) {
                        cin >> newPiece;

                        try {
                            b->swapPiece(p2->x2-1, p2->y2-1, newPiece);
                        } catch (logic_error e) {
                            b->undo(p2->x1-1, p2->y1-1, p2->x2-1, p2->y2-1);
                            cerr << e.what() << endl;
                            continue;
                        }
                    }
                }

               //  cout << "I am in main after before the first if statement" << endl;

               // cout << "I am in main after the first if statement" << endl;

                if (p2->getGivingCheck()) {
                    cout << p1->getName() << " is in check" << endl;
                    if(p1->inCheckmate()) {
                        cout << "Checkmate! " << p2->getName() << " wins!" << endl;
                        break;
                    }
                }
            } catch (invalid_argument e) {
                cerr << e.what();
                cout << ": Black has no possible moves" << endl;
            } catch (logic_error e) {
                cerr << e.what() << endl;
                continue;
            } 

            p2->resetCheck();
            ++numMoves;
            om->updatePastMoves(p2->x1, p2->y1, p2->x2, p2->y2);

           // cout << "im done the players turn" << endl;
        }
        
        whiteTurn = !whiteTurn;

        
    } 

}
*/
// ensure find way to set enpessantable or castleable to false



 //// END OF TEH ACTUAL STUFF BELOW WAS THE EVEN OLDER SHIT LIKE WAYAYAYAYAYAYAYAYAYAYAYAYAYAYAYAYAYAYAYAYAYAYAYAYAYAYAY

/*else if (cmd == "setup") {
        shared_ptr<DefaultBoard> b2  = make_shared<DefaultBoard>(p1, p2, 'e');
        PrintBoardText pb{b2}; 

        p1->attachBoard(b2);  
        p2->attachBoard(b2);

        string command;
        char piece;
        string colour;
        char move;
        int x;
        int y;

        while (true) {
            cin >> command;
            if (command == "+") {
                cin >> piece;
                cin >> move;
                x = convertMove(move);
                cin >> y;
                b2->addAtPos(piece, x-1, y-1);
                
            } else if (command == "-") {
                cin >> move;
                x = convertMove(move);
                cin >> y;
                b2->removeAtPos(x-1, y-1);
            } else if (command == "done") {
                // run checks on if each player has exactly one king
                if(!b2->isOneKingPerTeam()) {
                    cout << "Too many or too few kings, must fix to continue " << endl;
                    continue;
                } else if (b2->isPawnsInRowX(1)) {
                    cout << "Pawns are not allowed in bottom row, must fix to continue" << endl;
                    continue;
                } else if (b2->isPawnsInRowX(8)) {
                    cout << "Pawns are not allowed in top row, must fix to continue" << endl;
                    continue;
                } else if (b2->isGivingCheck("White")) {
                    cout << "Black king is in check" << endl;
                    continue;
                } else if (b2->isGivingCheck("Black")) {
                    cout << "White king is in check" << endl;
                    continue;
                }
                
                // ensure find way to set enpessantable or castleable to false
                break;
            
            } else if (command == "=") {
                cin >> colour;
                if (colour == "White") {
                    whiteTurn = true;
                } else {
                    whiteTurn = false;
                }
            }
            pb.printBoard(8, 8);
            
        }
        //b2->addAtPos('K', 4, 6);
        
    }
    
    whiteTurn = !whiteTurn;
}


    return 0;
}*/
