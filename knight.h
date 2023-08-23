#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

class DefaultBoard;

class Knight : public Piece {
    private:
        DefaultBoard* b;

    public:
        Knight(char name, int curX, int curY, std::string teamName, bool blockable, DefaultBoard* theBoard, std::string captureDir);

        // checks if a given move is valid for the piece
        bool isValidMove(int xMove, int yMove) override;

        /* returns all valid moves possible for the piece
            - each move is separated by a "|"
            - ex: 2,3|4,5|3,2|
        */
        std::vector<std::shared_ptr<Move>> allValidMoves() override;

        bool isValidCaptureMove(int xMove, int yMove) override;
        bool inLineOfSight(int xMove, int yMove) override;

};

#endif
