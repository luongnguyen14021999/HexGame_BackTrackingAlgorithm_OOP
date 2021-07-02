/*
 * BaseBoard.h
 *
 *  Created on: 21/02/2021
 *      Author: dongmo
 */

#ifndef BOARD_H_
#define BOARD_H_
#include "list"
#include "stack"
#include "queue"
class Board {
private:
	int boardSize;
	int turn;
	int **grid;
	int noOfMoves;
    char playerSymbol;
public:
    list<int> emptySpaces;
	Board(int bs) {
		boardSize = bs;
		grid = new int*[boardSize];
		for (int i = 0; i < boardSize; i++)
			grid[i] = new int[boardSize];

		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++) {
				grid[i][j] = 0;
				emptySpaces.push_back(getIndex(i,j));
			}
		noOfMoves = 0;
		turn = 1;
	}

	virtual ~Board() {
		for (int i = 0; i < boardSize; i++)
			delete[] grid[i];
		delete[] grid;
	}

	Board(Board &cboard) {
		boardSize = cboard.getBoardSize();

		grid = new int*[boardSize];
		for (int i = 0; i < boardSize; i++)
			grid[i] = new int[boardSize];

		for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                grid[i][j] = 0;
            }
		}

		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++) {
				grid[i][j] = cboard.getGrid(i, j);
			}
		noOfMoves = cboard.noOfMoves;
		turn = cboard.getTurn();
		emptySpaces = cboard.emptySpaces;
	}

	int getIndex(int x,int y) {
        return x*boardSize+y;
	}

	bool emptySpace(int x,int y) {
	    if(grid[x][y] == 0) {
            return true;
	    } else {
            return false;
	    }
	}

	char getPlayerSymbol() {
        return playerSymbol;
	}

    stack<int> checkNeighbours(int player, int x, int y);

    void showStack(stack<int> s) {
        while (!s.empty())
        {
            cout <<"("<<s.top()/boardSize+1<<","<<s.top()%boardSize+1<<") ";
            s.pop();
        }
        cout << '\n';
    }

	int getBoardSize() {
		return boardSize;
	}

    int numOfMoves() {
        return noOfMoves;
	}

	int getGrid(int x, int y) {
		return grid[x][y];
	}

	int getTurn() {
		return turn;
	}

    char gameStatus() {
        //Check rows for a win
        if(checkWinningStatus(1) == 1) {
            return 'R';
        }

        if(checkWinningStatus(-1) == -1) {
            return 'B';
        }

        if (noOfMoves < boardSize*boardSize)
            return 'C';

        return 'D';
    }

	bool isFull() {
        return noOfMoves == getBoardSize()*getBoardSize();
    }

	int getRandomMove(int &x,int &y) {
        int index = rand()%(emptySpaces.size());
        list<int>::iterator it = emptySpaces.begin();
        advance(it,index);
        int cell = *it;
        x = cell/boardSize;
        y = cell%boardSize;
    }

	bool validInput(int, int);

	bool addMove(int playerType, int x, int y);

    bool straightLine() {
        int count;
        if(turn == 1)
        {
            for(int i=0;i<boardSize;i++) {
                count = 0;
                for(int j=0;j<boardSize-1;j++) {
                    if(grid[i][j] == grid[i][j+1] && grid[i][j] == -1) {
                        count++;
                    }
                }
                if(count == boardSize-1) {
                    return true;
                }
            }
        }
        else
        {
            for(int j=0;j<boardSize;j++) {
                count = 0;
                for(int i=0;i<boardSize-1;i++) {
                    if(grid[i][j] == grid[i+1][j] && grid[i][j] == 1) {
                        count++;
                    }
                }
                if(count == boardSize-1) {
                    return true;
                }
            }
        }
        return false;
    }

    bool emptyFringeRed() {
        int countRedTop = 0;
        int countRedDown = 0;
        for (int i = 0; i < boardSize; i++) {
            if(getGrid(0,i) == 1) {
                countRedTop++;
            }
        }
        for (int j = 0; j < boardSize; j++) {
            if(getGrid(boardSize-1,j) == 1) {
                countRedDown++;
            }
        }
        if((countRedTop != 0 && countRedDown != 0)) {
            return false;
        }
        return true;
    }

    bool emptyFringeBlue() {
        int countBlueTop = 0;
        int countBlueDown = 0;
        for (int i = 0; i < boardSize; i++) {
            if(getGrid(i,0) == -1) {
                countBlueTop++;
            }
        }
        for (int j = 0; j < boardSize; j++) {
            if(getGrid(j,boardSize-1) == -1) {
                countBlueDown++;
            }
        }
        if((countBlueTop != 0 && countBlueDown != 0)) {
            return false;
        }
        return true;
    }


    bool belongToList(list<int> stackOfGoals,int element) {
        list <int> :: iterator it;
        for(it = stackOfGoals.begin(); it != stackOfGoals.end(); ++it) {
            if(*it == element) {
                return true;
            }
        }
        return false;
    }

    int backtracking() {
        int checkBlue = 0;
        int checkRed = 0;
        stack<int> trackingStackRed;
        stack<int> trackingStackBlue;
        list<int> visitedListRed;
        list<int> visitedListBlue;
        list<int> goalStackOfRed;
        list<int> goalStackOfBlue;
        for(int i=0;i<boardSize;i++) {
           if(getGrid(0,i) == 1) {
               trackingStackRed.push(getIndex(0,i));
           }
           if(getGrid(i,0) == -1) {
               trackingStackBlue.push(getIndex(i,0));
           }
           if(getGrid(boardSize-1,i) == 1) {
               goalStackOfRed.push_back(getIndex(boardSize-1,i));
           }
           if(getGrid(i,boardSize-1) == -1) {
               goalStackOfBlue.push_back(getIndex(i,boardSize-1));
           }
       }
        while(emptyFringeRed() == false && trackingStackRed.empty() == false) {
            checkRed = trackingStackRed.top();
            trackingStackRed.pop();
            visitedListRed.push_back(checkRed);
            if(belongToList(goalStackOfRed,checkRed)) {
                return 1;
            } else {
                stack<int> neighborsRed = checkNeighbours(1,checkRed/boardSize,checkRed%boardSize);
                while (!neighborsRed.empty())
                {
                    if(!belongToList(visitedListRed,neighborsRed.top())) {
                        trackingStackRed.push(neighborsRed.top());
                    }
                    neighborsRed.pop();
                }
            }
        }

        while(emptyFringeBlue() == false && trackingStackBlue.empty() == false)  {
            checkBlue = trackingStackBlue.top();
            trackingStackBlue.pop();
            visitedListBlue.push_back(checkBlue);
            if (belongToList(goalStackOfBlue, checkBlue)) {
                return -1;
            } else {
                stack<int> neighborsBlue = checkNeighbours(-1, checkBlue / boardSize, checkBlue % boardSize);
                while (!neighborsBlue.empty()) {
                    if (!belongToList(visitedListBlue, neighborsBlue.top())) {
                        trackingStackBlue.push(neighborsBlue.top());
                    }
                    neighborsBlue.pop();
                }
            }
        }
        return 0;
    }

	int checkWinningStatus(int playerType);

	void printBoard();
};

bool Board::validInput(int x, int y) {
	if (x < 0 || y < 0 || x >= boardSize || y >= boardSize) {
		cout << "Move (" << x + 1 << ", " << y + 1 << ") out of range!" << endl;
		return false;
	}

	if (grid[x][y] != 0) {
		cout << "Invalid move. The cell has been occupied." << endl;
		return false;
	}

	return true;
}

stack<int> Board::checkNeighbours(int player, int x, int y)
{
    stack<int> neighbours;
    if (x - 1 >= 0 && grid[x - 1][y] == player)
        neighbours.push(getIndex(x - 1, y));
    if (x + 1 < boardSize && grid[x + 1][y] == player)
    neighbours.push(getIndex(x + 1, y));
    if (y - 1 >= 0 && grid[x][y - 1] == player)
    neighbours.push(getIndex(x, y - 1));
    if (y + 1 < boardSize && grid[x][y + 1] == player)
    neighbours.push(getIndex(x, y + 1));
    //if (x - 1 >= 0 && y - 1 >= 0 && grid[x - 1][y - 1] == player)
    //neighbours.push(getIndex(x - 1, y - 1));
    if (x - 1 >= 0 && y + 1 < boardSize && grid[x - 1][y + 1] == player)
    neighbours.push(getIndex(x - 1, y + 1));
    if (x + 1 < boardSize && y - 1 >= 0 && grid[x + 1][y - 1] == player)
    neighbours.push(getIndex(x +1, y-1));
    //if (x + 1 < boardSize && y + 1 < boardSize && grid[x + 1][y + 1] == player)
    //neighbours.push(getIndex(x + 1, y + 1));

    return neighbours;
}

bool Board::addMove(int playerType, int x, int y) {
	if (playerType != turn) {
		cout << "It is not the player's turn!" << endl;
		return false;
	}

	if (grid[x][y] != 0) {
		cout << "Invalid move. The cell has been occupied." << endl;
		return false;
	}
	noOfMoves++;
	grid[x][y] = playerType;
    emptySpaces.remove(getIndex(x,y));
	turn = -1 * turn;
    playerSymbol = (playerSymbol == 'R') ? 'B' : 'R';
	return true;
}
// work hard
int Board::checkWinningStatus(int playerType) {
    if(backtracking() == playerType) {
        return playerType;
    }
    return 0;
};

void Board::printBoard() {
	cout << "   ";
	for (int j = 0; j < boardSize; j++) {
		if (j < 9)
			cout << j + 1 << "   ";
		else
			cout << j + 1 << "  ";
	}
	cout << endl;

	cout << "   ";
	for (int j = 0; j < boardSize; j++) {
		cout << "----";
	}
	cout << endl;

	for (int i = 0; i < boardSize; i++) {
		for (int k = 0; k < i; k++)
            cout << "  ";

		if (i < 9)
			cout <<" " <<i + 1<<" ";
		else
			cout <<i + 1<<" ";

        for (int j = 0; j < boardSize; j++) {
            if (grid[i][j] == 0) {
                if (j == 0) {
                    cout <<"|   |";
                } else {
                    cout <<"   |";
                }
            } else if (grid[i][j] == 1) {
                if (j == 0) {
                    cout << "| R |";
                } else {
                    cout << " R |";
                }
            } else {
                if (j == 0) {
                    cout << "| B |";
                } else {
                    cout << " B |";
                }
            }
        }

		cout << endl;
	}

	for (int k = 0; k <= boardSize; k++)
		cout << "  ";

	for (int j = 0; j < boardSize; j++) {
		cout << "----";
	}

	cout << endl;
	cout << endl;
}

#endif /* BOARD_H_ */
