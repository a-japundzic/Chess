#include "printBoardText.h"

using namespace std;

PrintBoardText::PrintBoardText(std::shared_ptr<Board> b): b{b} {}

void PrintBoardText::printBoard(int x, int y) {
    for (int i = (y-1); i >= 0; --i) {
        cout << i+1 << " ";
        for (int j = 0; j < x; ++j) {
            cout << b->getPiece(j, i)->getName();
        }
        cout << endl;
    }
    
} // Prints board, good enough for now lol
