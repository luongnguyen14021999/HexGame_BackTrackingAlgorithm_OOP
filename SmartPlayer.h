//
// Created by Nguyen Dinh Luong on 5/4/21.
//

#ifndef HEXGAMEASSIGNMENT_SMARTPLAYER_H
#define HEXGAMEASSIGNMENT_SMARTPLAYER_H
//
// Created by Nguyen Dinh Luong on 11/3/21.
//
using namespace std;
#include "Player.h"
#include "Board.h"
#include "Cell.h"
class SmartPlayer: public Player {
    int playType;
    int playerSymbol;
    double maxMove(Board board) {
        if (board.isFull())
            return 0.01;
        double maxUtility = -2;
        for (int i = 0; i < board.getBoardSize(); i++) {
            for (int j = 0; j < board.getBoardSize(); j++) {
                Board tempBoard(board);
                if(!tempBoard.validInput(i,j))
                    continue;
                tempBoard.addMove(playType,i, j);
                char gameStatus = tempBoard.gameStatus();
                if (gameStatus != 'C') {
                    if(playType == 1) {
                        playerSymbol = 'R';
                    } else {
                        playerSymbol = 'C';
                    }
                    if (gameStatus == playerSymbol)
                        return 1; //score 1 if wins
                    else if (gameStatus == 'D')
                        return 0; //score 0 if tie
                    else
                        return -1; //score -1 if lose
                }
                double utility;
                utility = minMove(board);

                if (utility > maxUtility) {
                    maxUtility = utility;
                }
            }
        }
//	steps--;
        return maxUtility;
    }

    double minMove(Board board) {
        //if (board.isFull())
            //return 0.01;

        double minUtility = 2;
        for (int i = 0; i < board.getBoardSize();i++) {
            for (int j = 0; j < board.getBoardSize(); j++) {
                Board tempBoard(board);
                if(!tempBoard.validInput(i,j))
                    continue;
                tempBoard.addMove(playType,i, j);
                char gameStatus = tempBoard.gameStatus();
                if (gameStatus != 'C') {
                    if(playType == 1) {
                        playerSymbol = 'R';
                    } else {
                        playerSymbol = 'C';
                    }
                    if (gameStatus == playerSymbol)
                        return 1; //score 1 if wins
                    else if (gameStatus == 'D')
                        return 0; //score 0 if tie
                    else
                        return -1; //score -1 if lose
                }
                double utility = maxMove(board);

                if (utility < minUtility) {
                    minUtility = utility;
                }
            }
        }
        // steps--;
        return minUtility;
    }

    int steps;
public:
    SmartPlayer(int t, string name = "Smart Player") :
            Player(playType, name) {}
    bool getMove(Board *board, int &x, int &y);
};

bool SmartPlayer::getMove(Board *board, int &x, int &y) {
    for(int i=0;i<board->getBoardSize();i++) {
        for(int j=0;j<board->getBoardSize();j++) {
            if(board->emptySpace(i,j) == true) {
                x = i;
                y = j;
                return true;
            }
        }
    }
}
#endif //HEXGAMEASSIGNMENT_SMARTPLAYER_H
