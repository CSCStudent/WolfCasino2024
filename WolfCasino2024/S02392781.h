//
//  TwentyFortyEight.hpp
//  TwentyFortyEight
//
//  Created by Madison Wacaser on 4/30/24.
//

#ifndef TwentyFortyEight_hpp
#define TwentyFortyEight_hpp
#pragma once
#include <ctime>
#include "Casino.h"

namespace S02392781 {

class Twenty48 : public CSC2034::Casino {
    public:
    Twenty48();
    ~Twenty48();
    static Twenty48 *makeGame();
    void start();
    void moveBoard(char c);
    bool endGame();
    void addPiece();
    void print();
    void mergeTiles(char direction);
    void shiftTiles(char direction);
    
    private:
    int board[4][4];
    };
}
#endif 
