/*
#include "BoardGraphic.h"
#include <iostream>
#include <string>

using namespace std;

BoardGraphic::BoardGraphic(std::shared_ptr<Board> b): b{b} {}

void BoardGraphic::graphicInitialBoard(int x, int y) {
    for (int i = y; i >= 0; i--) {
        for (int j = 0; j <= x; ++j) {
            if (i == 0 && j >= 1) {
                w.drawString(j*20, i*20, 'A' + j); 
            }

            if (j == 0 && i >= 1) {
                w.drawString(j*20, i*20, i);
            }
            if (i >= 0 && j >= 0) {
                if ((i % 2) == 0 && (j % 2) == 0) {
                    w.fillRectangle(j*20, i*20, 20, 20, Xwindow::Black);
                } else if ((i % 2) == 0 && (j % 2) == 1) {
                    w.fillRectangle(j*20, i*20, 20, 20, Xwindow::White);
                } else if ((i % 2) == 1 && (j % 2) == 0) {
                    w.fillRectangle(j*20, i*20, 20, 20, Xwindow::White);
                } else {
                    w.fillRectangle(j*20, i*20, 20, 20, Xwindow::Black);
                }
            }

            string c(1, b->getPiece(i, j)->getName());

            w.drawString(j*20+2, i*20+2, c);
        }
    }
}

void BoardGraphic::updateBoard(int x, int y, int newX, int newY) {
    string c(1, b->getPiece(x, y)->getName());
    string d(1, b->getPiece(newX, newY)->getName());

    w.drawString(x*20+2, y*20+2, c);
    w.drawString(newX*20+2, newY*20+2, d);
}
*/
