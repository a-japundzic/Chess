#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <memory>

#include "openingMoves.h"
#include "defaultBoard.h"
#include "board.h"

class Player {
    public:
        int x1;
        int y1;
        int x2;
        int y2;
    protected:
        std::string name;
        std::weak_ptr<DefaultBoard> b;
        bool givingCheck;
    public: 
       explicit Player(std::string name); 
       void attachBoard(std::shared_ptr<DefaultBoard> b);
      // std::string getAllValidMoves();
       bool getGivingCheck();
       std::string getName();
       virtual int movePiece(int x = 0, int y = 0, int newX = 0, int newY = 0) = 0;
       virtual ~Player();
       bool inCheckmate();
       void resetCheck();
};

#endif

/*
Basic initialization done within the client (main) method 
1. create a vector of pieces (for us just all default pieces)
2. construct a player with that vector of pieces, and a name
3. set the team names of all the pieces (setTeam method for pieces)
4. construct board with players (board will specify organization of the pieces
 from the players)
5. begin the game, make your moves (main input method)
6. after each move checking game state within the player method
7. if something notable happens, gg gl end game destruct everything
*/

/* Win Condition checking process
if (getAllValidMoves = "") return t; 

if (king is in check && valid moves exist to stop check) return check;
    - how we will do this: check if king has any valid moves, if none, is there any way to stop the check
        - to do that, we check if the blockable variable is true
            - if it is true, we check all vlaid players moves to see if we can block the check
            - if its not, then we are fucked gg no re
else if (same as above but no valid moves) return checkmate;
else keepPlaying


*/

/*
- controller has 2 players (could even be main method)
- board has move piece method

*/
