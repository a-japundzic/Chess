#include "board.h"

void Board::attach(std::vector<std::shared_ptr<Piece>>& p) {
    b.emplace_back(p);
}

void Board::detach(int x, int y) {
    b[y].erase(b[y].begin()+(x-1));
}

std::shared_ptr<Piece> Board::getPiece(int x, int y) {
    return b[y][x];
}

std::vector<std::shared_ptr<Piece>>& Board::playerPieces(std::string teamName) {
    return players[teamName];
}

Board::~Board() {}

int Board::getBoardSizeX() {
    return b.size();
}

int Board::getBoardSizeY() {
    return (b[1]).size(); // check this if bugs
}

char Board::getRandomPromotionPiece(std::string myTeamName) {
    srand(time(0));

    int chosenPiece = rand() % promotionPieces[myTeamName].size();

    return promotionPieces[myTeamName].at(chosenPiece);
}


