#include <iostream>
#include<string>

using namespace std;

#include "Board.h"
#include "HumanPlayer.h"
#include "HexGame.h"
#include "RandomPlayer.h"
#include "MonteCarloPlayer.h"
#include "SmartPlayer.h"

int main() {
    srand(time(0));
    int boardSize;
    cout<<"Input the size of board:"<<endl;
    cin >> boardSize;
    if (boardSize < 3)
        boardSize = 3;

    Board *board = new Board(boardSize);
    cout<<board<<endl;

    //Player *p1 = new HumanPlayer(1,"Human(Red)");
    Player *p1 = new RandomPlayer(1, "Human (Red)");
    //Player *p2 = new RandomPlayer(-1, "Random (Blue)");
    //Player *p2 = new MonteCarloPlayer(-1, "Monte Carlo (Monte Carlo)");
    Player *p2 = new SmartPlayer(-1,"Smart (Smart)");
    HexGame game(board,p1,p2);
    game.play();

    delete board;
    delete p1;
    delete p2;

//	system("pause");
    return 0;
};
