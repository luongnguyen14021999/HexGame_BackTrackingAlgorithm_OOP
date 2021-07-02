/*
 * HexGame.h
 *
 *  Created on: 21/02/2021
 *      Author: dongmo
 */

#ifndef HEXGAME_H_
#define HEXGAME_H_

#include "Player.h"

class HexGame {
private:
    Board *board;
	Player *player[2];
public:
	HexGame(Board *b, Player *p1, Player *p2) {
		board = b;
		player[0] = p1;
		player[1] = p2;
	}
	void play();
};

void HexGame::play() {
	int won = 0;
	board->printBoard();

	while (won == 0) {
        stack<int> neighborCell;
		int playerType = board->getTurn();
        int playerIndex;
		if(playerType == player[0]->getType()) {
		    playerIndex = 0;
		} else {
		    playerIndex = 1;
		}
		int x = -1;
		int y = -1;

		if (!player[playerIndex]->getMove(board, x, y)) {
			cout << "No available move" << endl;
			return;
		}

		cout << player[playerIndex]->getPlayerName() << " plays " << " ("
				<< x + 1 << ", " << y + 1 << "):" << endl;

		if (!board->addMove(playerType, x, y))
			return;

		board->printBoard();
        won = board->checkWinningStatus(playerType);
        if(won == playerType) {
            cout << player[playerIndex]->getPlayerName() << " player wins!" << endl;
        }
		if(board->numOfMoves() == board->getBoardSize()*board->getBoardSize()) {
            won = board->checkWinningStatus(playerType);
            if(won == playerType) {
                cout << player[playerIndex]->getPlayerName() << " player wins!" << endl;
            } else {
                cout<<"Your board is full!"<<endl;
            }
            return;
		}
	}
}

#endif /* HEXGAME_H_ */
