#include "player.h"
#include "move.h"
#include <iostream>

using namespace std;

Player::Player(string name) : name{name}, givingCheck{false}, x1{0}, y1{0}, x2{0}, y2{0} {}

void Player::attachBoard(shared_ptr<DefaultBoard> theBoard)
{
    b = theBoard;
}

// string Player::getAllValidMoves() {
// }

bool Player::getGivingCheck()
{
    return givingCheck;
}

void Player::resetCheck()
{
    givingCheck = false;
}

string Player::getName()
{
    return name;
}

Player::~Player() {}

bool Player::inCheckmate()
{
    // cout << b.lock()->getMyKing(name)->getName() << endl;
    if (b.lock()->getMyKing(name)->anyValidMoves()) {
       // cout << "I am in here lol" << endl;
       for (auto &p : b.lock()->getMyKing(name)->allValidMoves()) {
            int pieceTakenIndex = -1;

            pieceTakenIndex = b.lock()->movePiece(p->x, p->y, p->xMove, p->yMove);

            if (b.lock()->isGivingCheck(b.lock()->getOtherTeamName(name))) {
                b.lock()->undo(p->x, p->y, p->xMove, p->yMove, pieceTakenIndex);
            } else {
                b.lock()->undo(p->x, p->y, p->xMove, p->yMove, pieceTakenIndex);
                return false;
            }
       }
        
    }
    //else
   // {
      //  cout << "In else" << endl;
        for (auto k : b.lock()->playerPieces(b.lock()->getOtherTeamName(name)))
        {
            // cout << k->isValidMove(b->getMyKing(name)->getX(), b->getMyKing(name)->getY()) << endl;
            if (k->isValidMove(b.lock()->getMyKing(name)->getX(), b.lock()->getMyKing(name)->getY()))
            {
               // cout << "in if statement" << endl;
                // if (k->getName() == 'q') {
                // cout << k->getX() << " " << k->getY() << endl;
                // }

                // cout << "Name: " << name << " " << b->playerPieces(name).size() << endl;
                for (auto p : b.lock()->playerPieces(name))
                {
                   // cout << "in this loop" << endl;
                    if (p->isValidMove(k->getX(), k->getY()))
                    {
                        return false;
                    }

                    // cout << "After the first if in the second loop" << endl;
                    // cout << "In second loop" << endl;
                    if (p->isBlockable())
                    {
                        // cout << "In blockable" << endl;
                        // if its VH
                        //  cout << "In blockable" << endl;
                        int xDist = b.lock()->getMyKing(name)->getX() - k->getX();
                        int yDist = b.lock()->getMyKing(name)->getY() - k->getY();

                        int xMove = b.lock()->getMyKing(name)->getX();
                        int x = k->getX();

                        int yMove = b.lock()->getMyKing(name)->getY();
                        int y = k->getY();
                        //  cout << "In before the VH" << endl;
                        if (k->getCaptureDir() == "VH")
                        {
                            // cout << "In VH" << endl;
                            if (xMove == x)
                            {
                                // moving up case
                                if (yMove > y)
                                {
                                    // checki ng all spots in path up to but not including destination (must be empty)
                                    for (int i = y + 1; i < yMove; ++i)
                                    { // made it x+1 instead of x since it will always return false since x,y is not empty
                                        if ((p->isValidMove(x, i)))
                                        {
                                            return false;
                                        }
                                    }
                                    // moving down case
                                }
                                else if (yMove < y)
                                {
                                    // same as above for loop
                                    for (int i = y - 1; i > yMove; --i)
                                    { /// made a change here
                                        if ((p->isValidMove(x, i)))
                                        {
                                            return false;
                                        }
                                    }
                                }
                                // moving horiz
                            }
                            else if (yMove == y)
                            {
                                // moving right
                                if (xMove > x)
                                {
                                    // same as above for loop
                                    for (int i = x + 1; i < xMove; ++i)
                                    {
                                        if ((p->isValidMove(i, y)))
                                        {
                                            return false;
                                        }
                                    }
                                    // moving left
                                }
                                else if (xMove < x)
                                {
                                    // same as above for loop
                                    for (int i = x - 1; i > xMove; --i)
                                    {
                                        if ((p->isValidMove(i, y)))
                                        {
                                            return false;
                                        }
                                    }
                                }
                            }
                        }

                        // if its D
                        if (k->getCaptureDir() == "D")
                        {
                            // cout << "In D" << endl;
                            // int xDist = k->getX() - b->getMyKing(name)->getX();
                            // int yDist = k->getY(); - b->getMyKing(name)->getY();
                            if (xDist > 0 and yDist > 0)
                            {
                                // checking all spots in path up to but not including destination (must be empty)
                                for (int i = 1; i < abs(xDist); ++i)
                                {
                                    if ((p->isValidMove(x + i, y + i)))
                                    {
                                        return false;
                                    }
                                }
                                // moving down and diagonal right
                            }
                            else if (xDist > 0 && yDist < 0)
                            {
                                // same as above for loop
                                for (int i = 1; i < abs(xDist); ++i)
                                {
                                    if ((p->isValidMove(x + i, y - i)))
                                    {
                                        return false;
                                    }
                                }
                                // moving down and diagonal left
                            }
                            else if (xDist < 0 and yDist < 0)
                            {
                                // same as above for loop
                                for (int i = 1; i < abs(xDist); ++i)
                                {
                                    if ((p->isValidMove(x - i, y - i)))
                                    {
                                        return false;
                                    }
                                }
                                // moving up and diagonal left
                            }
                            else if (xDist < 0 && yDist > 0)
                            {
                                // same as above for loop
                                for (int i = 1; i < abs(xDist); ++i)
                                {
                                    if ((p->isValidMove(x - i, y + i)))
                                    {
                                        return false;
                                    }
                                }
                            }
                        }
                        // if its VHD
                        if (k->getCaptureDir() == "VHD")
                        {
                           // cout << "Im in VHD" << endl;
                            // int xDist = k->getX() - b->getMyKing(name)->getX();
                            // int yDist =  b->getMyKing(name)->getY();k->getY()
                            //  cout << "In VHD" << endl;
                            if (xDist != 0 && yDist != 0)
                            {
                              //  cout << "In in first if statement" << endl;
                                if (abs(xDist) != abs(yDist))
                                {
                                    return false;
                                }

                                // moving up and diagonal right
                                if (xDist > 0 and yDist > 0)
                                {
                                    // checking all spots in path up to but not including destination (must be empty)
                                    for (int i = 1; i < abs(xDist); ++i)
                                    {
                                        if ((p->isValidMove(x + i, y + i)))
                                        {
                                            return false;
                                        }
                                    }
                                    // moving down and diagonal right
                                }
                                else if (xDist > 0 && yDist < 0)
                                {
                                    // same as above for loop
                                    for (int i = 1; i < abs(xDist); ++i)
                                    {
                                        if ((p->isValidMove(x + i, y - i)))
                                        {
                                            return false;
                                        }
                                    }
                                    // moving down and diagonal left
                                }
                                else if (xDist < 0 and yDist < 0)
                                {
                                    // cout << xDist << " " << yDist << endl;
                                    for (int i = 1; i < abs(xDist); ++i)
                                    {
                                        if ((p->isValidMove(x - i, y - i)))
                                        {
                                            // cout << "we got to the false" << endl;
                                            return false;
                                        }
                                    }
                                    // moving up and diagonal left
                                }
                                else if (xDist < 0 && yDist > 0)
                                {
                                    // same as above for loop
                                    for (int i = 1; i < abs(xDist); ++i)
                                    {
                                        if ((p->isValidMove(x - i, y + i)))
                                        {
                                            return false;
                                        }
                                    }
                                }
                            }
                            else
                            {
                               // cout << "Im in else" << endl;
                                // moving vertical case
                                if (xDist == 0)
                                {
                                    // moving up case
                                    if (yMove > y)
                                    {
                                        // checking all spots in path up to but not including destination (must be empty)
                                        for (int i = y + 1; i < yMove; ++i)
                                        { // made it x+1 instead of x since it will always return false since x,y is not empty
                                            if ((p->isValidMove(x, i)))
                                            {
                                                return false;
                                            }
                                        }
                                        // moving down case
                                    }
                                    else if (yMove < y)
                                    {
                                        // same as above for loop
                                        // cout << "In the yMove < y" << endl;
                                        for (int i = y - 1; i > yMove; --i)
                                        {
                                            // cout << p->getName() << endl;
                                            if ((p->isValidMove(x, i)))
                                            {
                                                return false;
                                            }
                                        }
                                    }

                                    // moving horiz
                                }
                                else if (yDist == 0)
                                {
                                    // moving right
                                    if (xMove > x)
                                    {
                                     //   cout << "In here for some reason looool" << endl;
                                        // same as above for loop
                                        for (int i = x + 1; i < xMove; ++i)
                                        {
                                            if ((p->isValidMove(i, y)))
                                            {
                                                return false;
                                            }
                                        }
                                        // moving left
                                    }
                                    else if (xMove < x)
                                    {
                                       // cout << "Im in xMove < x" << endl;
                                        // same as above for loop
                                        for (int i = x - 1; i > xMove; --i)
                                        {
                                            if ((p->isValidMove(i, y)))
                                            {
                                                return false;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    //}
    return true;
}
