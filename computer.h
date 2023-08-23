#include "player.h"
#include <string.h>
#include <vector>
#include <memory>

class Move;

class Computer1 : public Player {
    private:
    public: 
        Computer1(std::string name);
        int movePiece(int x = 0, int y = 0, int newX = 0, int newY = 0) override;
};

class Computer2 : public Player {
    private:
    public: 
        Computer2(std::string name);
        int movePiece(int x = 0, int y = 0, int newX = 0, int newY = 0) override;
};

class Computer3 : public Player {
    private:
    public: 
        Computer3(std::string name);
        int movePiece(int x = 0, int y = 0, int newX = 0, int newY = 0) override;
};

class Computer4 : public Player {
    private:
        std::shared_ptr<OpeningMoves> om; 
    public: 
        Computer4(std::string name, std::shared_ptr<OpeningMoves> om);
        int movePiece(int x = 0, int y = 0, int newX = 0, int newY = 0) override;
};
