#include "player.h"

class Board;

class RealPlayer : public Player { 
    public: 
        RealPlayer(std::string name);
        int movePiece(int x, int y, int newX, int newY) override;
};

