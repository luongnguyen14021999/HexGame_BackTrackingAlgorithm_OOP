//
// Created by Nguyen Dinh Luong on 11/3/21.
//

#ifndef HEXGAMEASSIGNMENT_RANDOMPLAYER_H
#define HEXGAMEASSIGNMENT_RANDOMPLAYER_H

#include "Player.h"
#include "Board.h"
using namespace std;

class RandomPlayer: public Player {
public:
    RandomPlayer(int t, string name = "Random") :
            Player(t, name) {
    }
    bool getMove(Board*, int&, int&);
};

bool RandomPlayer::getMove(Board *board, int &x, int &y) {
    int bs = board->getBoardSize();
    int index = rand()%(board->emptySpaces.size());
    list<int>::iterator it = board->emptySpaces.begin();
    advance(it,index);
    int cell = *it;
    x = cell/bs;
    y = cell%bs;
    return true;
}
#endif //HEXGAMEASSIGNMENT_RANDOMPLAYER_H
