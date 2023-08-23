#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <memory>
#include <vector>
//#include <stdbool.h>

class Board;
class Move;

class Piece {
    private:
        bool blockable;
        //Board* theBoard; 
    protected: // added this because subclasses need access to coordinates from parent class. prob need to do this for all fields
        const char name;
        int x, y; //coordinates
        std::string teamName;
        int numOfMoves = 0;
        std::string captureDir;
        int value;
        bool isEnpessantable = false;
    public:
        // constructor
        Piece(char name, int curX, int curY, std::string teamName, std::string captureDir, int value, bool blockable = false);
        // checks if a given move is valid for the piece
        virtual bool isValidMove(int xMove, int yMove) = 0;
        /* returns all valid moves possible for the piece
            - each move is separated by a "|"
            - ex: 2,3|4,5|3,2|
        */
        virtual bool isValidCaptureMove(int xMove, int yMove) = 0;
        virtual std::vector<std::shared_ptr<Move>> allValidMoves() = 0;
        void updateNumOfMoves(char op);
        int getX();
        int getY();
        void setPosition(int newX, int newY);
        virtual ~Piece() = default;
        //void assignTeamName(std::string teamName);
        std::string getTeamName();
        char getName();
        bool isBlockable();
        virtual bool isPromotable(); 
        virtual bool enpessantable(); 
        std::string getCaptureDir();
        virtual bool isRook();
        bool notPreviouslyMoved();
        void setEnpessantableFalse();
        void setEnpessantableTrue();
        virtual bool inLineOfSight(int xMove, int yMove) = 0;
        //bool givingCheck(std::shared_ptr<Piece>);
        //virtual bool anyValidMoves();
        int getValue();


};

#endif
