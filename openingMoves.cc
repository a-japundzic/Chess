#include "openingMoves.h"
#include <sstream>
#include "board.h"

using namespace std; 

OpeningMoves::OpeningMoves(): pastMoves{""} {
    sequences.push_back("e2e4 c7c5");
    sequences.push_back("e2e4 d7d5");
    sequences.push_back("e2e4 e7e5 g1f3 b8c6 f1b5");
    sequences.push_back("d2d4 d7d5 c2c4");
    sequences.push_back("e2e4 e7e5 e1e2 e8e7");
    numSequences = sequences.size(); 
}

void OpeningMoves::attachBoard(std::shared_ptr<Board> theBoard) {
    b = theBoard;
}

string OpeningMoves::findNextMove() {
    vector<string> seqFilter = sequences;

    /*
    string s = "";
    cout << "Enter space separated moves (Ex: e2e4 e7e5 e1e2) or press enter for all suggestions." << endl;
    in.clear();
    in.ignore();
    getline(in, s); 
    */

  // cout << pastMoves << endl;

    for (int i = 0; i < numSequences; i++) {
        if (seqFilter[i].length() <= pastMoves.length()) {
            seqFilter[i] = " "; 
        } else if (seqFilter[i].substr(0, pastMoves.length()) != pastMoves) {
           // cout << seqFilter[i].substr(0, pastMoves.length()) << endl;
            seqFilter[i] = " "; 
        }
    }

    ostringstream oss;
    int numInvalid = 0; 
    string s; 

    for (int i = 0; i < numSequences; i++) {
        if (seqFilter[i] != " ") {
            if (pastMoves.length() == 0) {
                if (oss.str().find(seqFilter[i].substr(0, 4)) == string::npos) {
                    if (oss.str().length() > 0) {
                         oss << " ";
                    }

                    s = seqFilter[i].substr(0, 4); 
                   // cout << s[0];
                   // cout << s[1];
                   // cout << s[0] - 49 - '0' << endl; 
                   // cout << s[1] - '0' << endl;
                   //cout << b->getPiece(s[0] - 49 - '0', s[1] - '0' - 1)->getName() << endl;
                   
                    if ((b->getPiece(s[0] - 49 - '0', s[1] - '0' - 1)->getName() != ' ') && (b->getPiece(s[0] - 49 - '0', s[1] - '0' - 1)->getName() != '_')) {
                        oss << s;
                    } else {
                        numInvalid++; 
                    }
                }
            } else {
                if (oss.str().find(seqFilter[i].substr(pastMoves.length() + 1, 4)) == string::npos) {
                    if (oss.str().length() > 0) {
                         oss << " ";
                    }

                    s = seqFilter[i].substr(pastMoves.length() + 1, 4); 

                    //cout << b->getPiece(s[0] - 49 - '0', s[1] - '0' - 1)->getName() << endl;

                    if ((b->getPiece(s[0] - 49 - '0', s[1] - '0' - 1)->getName() != ' ') && (b->getPiece(s[0] - 49 - '0', s[1] - '0' - 1)->getName() != '_')) {
                        oss << s;
                    } else {
                        numInvalid++; 
                    }
                }
            }
        } else {
            numInvalid++; 
        }
    }
    if (numInvalid == numSequences) {
        return "";
    }

    /*
    string s = oss.str();
    if (s[0] == ' ') {
        s = oss.str().substr(1,oss.str().length() - 1);
    }
    */

    return oss.str();
} 

void OpeningMoves::updatePastMoves(int x1, int y1, int x2, int y2) {
    ostringstream oss;
  //  cout << "In update past moves" << endl;

    char move1 = 'a' + x1 - 1;
    char move2 = 'a' + x2 - 1;

    oss << move1 << y1 << move2 << y2;

    if (pastMoves.length() == 0) {
        pastMoves = oss.str();
    } else {
        pastMoves = pastMoves + " " + oss.str();
    }

   // cout << pastMoves << endl;
}