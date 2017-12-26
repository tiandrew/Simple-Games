//
//  chess.hpp
//  Simple Games
//
//  Created by Andrew Jonathan Tian on 5/11/17.
//  Copyright © 2017 Andrew Tian. All rights reserved.
//

#ifndef chess_hpp
#define chess_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

#endif /* chess_hpp */

struct Space {
    bool empty = true;
    bool black = false; // contains black piece
    bool white = false; // contains white piece
    int x;
    int y;
    string piece = "x"; // p = pawn; r = rook; h = knight; b = bishop
                        // q = queen; k = king; x = empty
                        // Ex: wp = white pawn
                        //     bk = black king
};

class Chess {
    vector<vector<Space>> board;
    
    void initialize_board();
    
    bool in_bound(const Space dest);
    
    bool valid_move(const Space origin, const Space dest);
    
    bool pawn_valid(const Space origin, const Space dest);
    
    bool rook_valid(const Space origin, const Space dest);
    
    bool knight_valid(const Space origin, const Space dest);
    
    bool bishop_valid(const Space origin, const Space dest);
    
    bool queen_valid(const Space origin, const Space dest);
    
    bool king_valid(const Space origin, const Space dest);
    
    void print_board();
    
public:
    void play_chess();
};

