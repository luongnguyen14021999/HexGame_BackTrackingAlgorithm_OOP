//
// Created by Nguyen Dinh Luong on 2/4/21.
//

#ifndef HEXGAMEASSIGNMENT_CELL_H
#define HEXGAMEASSIGNMENT_CELL_H


struct Cell {
    int x;
    int y;
    double utility;

    Cell(int xx, int yy, double hh):x(xx), y(yy), utility(hh) {}

    bool operator<(const Cell& c) const {
        return utility < c.utility;
    }
};
#endif //HEXGAMEASSIGNMENT_CELL_H
