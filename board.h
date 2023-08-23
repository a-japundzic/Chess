#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <map>
#include <string>
#include "piece.h"
//class Piece;

class Board {
    protected:
        std::string lastMove;
        std::vector<std::vector<std::shared_ptr<Piece>>> b;
        std::map<std::string, std::vector<std::shared_ptr<Piece>>> players;
        std::shared_ptr<Piece> lastPieceTaken;
        std::map<std::string, std::vector<char>> promotionPieces;
    public:
        void attach(std::vector<std::shared_ptr<Piece>>& p);
        void detach(int x, int y);
        std::shared_ptr<Piece> getPiece(int x, int y);
        virtual int movePiece(int x, int y, int newX, int newY) = 0;
        virtual bool isCoordEmpty(int x, int y) = 0;
        virtual std::string getOtherTeamName(std::string myTeamName) = 0;
        std::vector<std::shared_ptr<Piece>>& playerPieces(std::string teamName);
        char getRandomPromotionPiece(std::string myTeamName);
        virtual ~Board();
        int getBoardSizeX();
        int getBoardSizeY();
        virtual void undo(int x, int y, int newX, int newY, int index = -1) = 0;
        virtual bool isGivingCheck(std::string myTeamName) = 0;
};

#endif
