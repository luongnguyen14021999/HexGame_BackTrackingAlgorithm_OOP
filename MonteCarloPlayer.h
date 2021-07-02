//
// Created by Nguyen Dinh Luong on 2/4/21.
//
#define HEXGAMEASSIGNMENT_AIPLAYER_H
#include "Player.h"
#include "Board.h"
#include "Cell.h"
using namespace std;
class MonteCarloPlayer: public Player {
public:
    MonteCarloPlayer(int t, string name = "Monte Carlo") : Player(t, name) {}
    bool getMove(Board *board, int &x, int &y);
    double simulation(Board board);
    double expansion(char player,Board board);
};

bool MonteCarloPlayer::getMove(Board *board, int &x, int &y) {

    priority_queue<Cell> moves;

    for (int i = 0; i < board->getBoardSize(); i++) {
        for (int j = 0; j < board->getBoardSize(); j++) {
            Board tempBoard(*board);
            if(tempBoard.getGrid(i,j) != 0)
                continue;
            tempBoard.addMove(-1,i,j);
            if(tempBoard.checkWinningStatus(-1) == -1) {
                x = i;
                y = j;
                return true;
            }
            double utility = simulation(tempBoard);
            Cell c = Cell(i, j, utility);
            moves.push(c);
        }
    }

    if(!moves.empty()) {
        x = moves.top().x;
        y = moves.top().y;
        cout << moves.size() << "Utility = " << moves.top().utility
             << " at (" << (x + 1) << "," << (y + 1) << ")" << endl;
    }

    return true;
}

double MonteCarloPlayer::simulation(Board board) {
    double winning = 0.0;
    int times = 100;
    for(int i=0;i<times;i++) {
        Board tempBoard(board);
        char player = (tempBoard.getPlayerSymbol() == 'R') ? 'B' : 'R';
        winning = winning + expansion(player, tempBoard);
    }
    cout<<winning<<endl;
    return winning/times;
}

double MonteCarloPlayer::expansion(char player,Board board) {
    if(board.gameStatus() == 'R' && type == 1 || board.gameStatus() == 'B' && type == -1) {
        return 1.0;
    } else if(board.gameStatus() != 'C') {
        return 0.0;
    }
    int x,y;
    board.getRandomMove(x,y);
    int playerType;
    if(player == 'R') {
        playerType = 1;
    } else {
        playerType = -1;
    }
    board.addMove(playerType,x,y);
    player = (player == 'R') ? 'B' : 'R';
    return expansion(player,board);
}