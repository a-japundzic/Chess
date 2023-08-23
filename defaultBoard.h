#ifndef DEFAULT_BOARD_H
#define DEFAULT_BOARD_H

#include "board.h"
#include "king.h"
#include <string>

class Player;

class DefaultBoard : public Board{
    private:
        std::weak_ptr<Player> p1;
        std::weak_ptr<Player> p2;
        std::shared_ptr<King> p1King;
        std::shared_ptr<King> p2King;
        std::vector<std::shared_ptr<King>> kings; // For board setup function
    public:
        void addAtPos(char piece, int x, int y);
        void removeAtPos(int x, int y);
        DefaultBoard(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, char type);
        DefaultBoard(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2); //calls attach in body of ctor
        bool isCoordEmpty(int x, int y) override;
        int movePiece(int x, int y, int newX, int newY) override;
        void swapPiece(int x, int y, char type);
        std::string getOtherTeamName(std::string myTeamName) override;
        std::shared_ptr<King>& getOtherKing(std::string myTeamName);
        // Add something for board translation (done in move)
        std::shared_ptr<King>& getMyKing(std::string myTeamName);
        void undo(int x, int y, int newX, int newY, int index = -1) override;
        bool isGivingCheck(std::string myTeamName) override;
        void swapPieceEmpty(int x, int y);
        bool isOneKingPerTeam();
        bool isPawnsInRowX(int i);
        
        
};

#endif
