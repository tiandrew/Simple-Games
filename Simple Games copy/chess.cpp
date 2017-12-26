//
//  chess.cpp
//  Simple Games
//
//  Created by Andrew Jonathan Tian on 5/11/17.
//  Copyright © 2017 Andrew Tian. All rights reserved.
//

#include "chess.hpp"

void Chess::play_chess() {
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "~~~~~~~~~~ CHESS ~~~~~~~~~~" << endl;
    initialize_board();
    bool white_turn = true;
    int origin;
    int dest;
    int i = 0;
    int o_x;
    int o_y;
    int d_x;
    int d_y;
    string input_1;
    string input_2;
    
    while (true) {
        print_board();
        if (i % 2 == 0) {
            white_turn = true;
            cout << "White's Move (XY XY): ";
        } // if
        else {
            white_turn = false;
            cout << "Black's Move (XY XY): ";
        } // else
        
        cin >> input_1;
        
        while (input_1.front() == 'h' || input_1.front() == 'H') {
            cout << "H for help\nQ for quit\nNext input: ";
            cin >> input_1;
        } // while
        
        if (input_1.front() == 'q' || input_1.front() == 'Q')
            exit(0);
        
        cin >> input_2;

        origin = stoi(input_1);
        dest = stoi(input_2);
        cout << endl << endl;
        ++i;
        
        o_y = 9-(origin % 10);
        d_y = 9-(dest % 10);
        o_x = origin / 10;
        d_x = origin / 10;
        Space& o = board[o_y][o_x];
        Space& d = board[d_y][d_x];
        
        while (origin > 88 || origin < 10 || dest > 88 || dest < 10 ||
               o_x == 0 || o_x == 9 || o_y == 0 || o_y == 9 ||
               d_x == 0 || d_x == 9 || d_y == 0 || d_y == 9 ||
               origin == dest || board[o_x][o_y].empty || !valid_move(o, d)) {
            cout << "Invalid move, try again (XY XY): ";
            cin >> origin >> dest;
            cout << endl << endl;
            o_y = 9-(origin % 10);
            d_y = 9-(dest % 10);
            o_x = origin / 10;
            d_x = origin / 10;
            o = board[o_y][o_x];
            d = board[d_y][d_x];
        } // while
        
        o.empty = true;
        o.black = false;
        o.white = false;
        d.empty = false;
        d.piece = o.piece;
        o.piece = "x";
        
        if (white_turn) {
            if (d.piece == "bk") {
                cout << "White Won!" << endl;
                exit(0);
            } // if
            d.white = true;
            d.black = false;
        } // if
        
        else {
            if (d.piece == "wk") {
                cout << "Black Won!" << endl;
                exit(0);
            } // if
            d.white = false;
            d.black = true;
        } // else
    } // while
} // play_chess

void Chess::initialize_board() {
    board.resize(9);
    for (int i = 1; i <= 8; ++i) {
        board[i].resize(9);
        switch (i) {
            case 2: // white pawns
                for (int j = 1; j <= 8; ++j) {
                    Space &current = board[i][j];
                    current.empty = false;
                    current.piece = "wp";
                    current.x = j;
                    current.y = 9-i;
                } // for
                break;
                
            case 7: // black pawns
                for (int j = 1; j <= 8; ++j) {
                    Space &current = board[i][j];
                    current.empty = false;
                    current.piece = "bp";
                    current.x = j;
                    current.y = 9-i;
                } // for
                break;
                
            case 1: // other whites
                for (int j = 1; j <= 8; ++j) {
                    Space &current = board[i][j];
                    current.empty = false;
                    current.x = j;
                    current.y = 9-i;
                    switch (j) {
                        case 1:
                            current.piece = "wr";
                            break;
                        case 2:
                            current.piece = "wh";
                            break;
                        case 3:
                            current.piece = "wb";
                            break;
                        case 4:
                            current.piece = "wq";
                            break;
                        case 5:
                            current.piece = "wk";
                            break;
                        case 6:
                            current.piece = "wb";
                            break;
                        case 7:
                            current.piece = "wh";
                            break;
                        case 8:
                            current.piece = "wr";
                            break;
                    } // switch
                } // for
                break;
                
            case 8: // other blacks
                for (int j = 1; j <= 8; ++j) {
                    Space &current = board[i][j];
                    current.empty = false;
                    current.x = j;
                    current.y = 9-i;
                    switch (j) {
                        case 1:
                            current.piece = "br";
                            break;
                        case 2:
                            current.piece = "bh";
                            break;
                        case 3:
                            current.piece = "bb";
                            break;
                        case 4:
                            current.piece = "bq";
                            break;
                        case 5:
                            current.piece = "bk";
                            break;
                        case 6:
                            current.piece = "bb";
                            break;
                        case 7:
                            current.piece = "bh";
                            break;
                        case 8:
                            current.piece = "br";
                            break;
                    } // switch
                } // for
                break;
                
            default:
                for (int j = 1; j <= 8; ++j) {
                    board[i][j].x = j;
                    board[i][j].y = 9-i;
                } // for
                break;
        } // switch
    } // for
} // initialize_board

bool Chess::in_bound(const Space dest) {
    if (dest.x < 1 || dest.x > 8 || dest.y < 1 || dest.y > 8)
        return false;
    return true;
} // bound_checker

bool Chess::valid_move(Space origin, Space dest) {
    if (!in_bound(dest))
        return false;
    
    if (origin.x == dest.x && origin.y == dest.y)
        return false;
    
    char piece = origin.piece.back();
    switch (piece) {
        case 'p':
            return pawn_valid(origin, dest);
        case 'r':
            return rook_valid(origin, dest);
        case 'h':
            return knight_valid(origin, dest);
        case 'b':
            return bishop_valid(origin, dest);
        case 'q':
            return queen_valid(origin, dest);
        case 'k':
            return king_valid(origin, dest);
        default:
            return false;
    } // switch
} // valid_move

bool Chess::pawn_valid(Space origin, Space dest) {
    if (origin.piece == "wp") {
        // vertical
        if (dest.x == origin.x) {
            if (dest.y + 1 == origin.y && dest.empty)
                return true;
            
            if (origin.y == 7 && dest.y + 2 == origin.y && dest.empty)
                return true;
            
            return false;
        } // if
        
        // diagonal
        if (dest.x + 1 == origin.x && dest.y + 1 == origin.y && !dest.empty)
            return true;
        if (dest.x - 1 == origin.x && dest.y + 1 == origin.y && !dest.empty)
            return true;
        
        return false;
    } // if
    
    else {
        // vertical
        if (dest.x == origin.x) {
            if (dest.y - 1 == origin.y && dest.empty)
                return true;
            
            if (origin.y == 2 && dest.y - 2 == origin.y && dest.empty)
                return true;
            
            return false;
        } // if
        
        // diagonal
        if (dest.x + 1 == origin.x && dest.y - 1 == origin.y &&
            ((origin.black && dest.white) || (origin.white && dest.black)))
            return true;
        if (dest.x - 1 == origin.x && dest.y - 1 == origin.y &&
            ((origin.black && dest.white) || (origin.white && dest.black)))
            return true;
        
        return false;
    } // else
} // pawn_valid

bool Chess::rook_valid(const Space origin, const Space dest) {
    if ((origin.black && dest.black) || (origin.white && dest.white))
        return false;
    
//    if (dest.x == origin.x) {
//        for (int i = min(origin.y, dest.y) + 1; i < max(origin.y, dest.y); ++i)
//            if (!board[dest.x][i].empty)
//                return false;
//    } // if
//    
//    if (dest.y == origin.y) {
//        for (int i = min(origin.x, dest.x) + 1; i < max(origin.x, dest.x); ++i)
//            if (!board[i][dest.y].empty)
//                return false;
//    } // if
    
    return true;
} // rook_valid

bool Chess::knight_valid(const Space origin, const Space dest) {
    // left
    if (origin.x - dest.x == 1 && (abs(origin.y - dest.y) == 2) &&
        ((origin.black && dest.white) || (origin.white && dest.black)))
        return true;
    
    // right
    if (dest.x - origin.x == 1 && (abs(origin.y - dest.y) == 2) &&
        ((origin.black && dest.white) || (origin.white && dest.black)))
        return true;
    
    // left
    if (origin.x - dest.x == 2 && (abs(origin.y - dest.y) == 1) &&
        ((origin.black && dest.white) || (origin.white && dest.black)))
        return true;
    
    // right
    if (dest.x - origin.x == 2 && (abs(origin.y - dest.y) == 1) &&
        ((origin.black && dest.white) || (origin.white && dest.black)))
        return true;
    
    return false;
} // knight_valid

bool Chess::bishop_valid(const Space origin, const Space dest) {
    if (abs(origin.x - dest.x) != abs(origin.y - dest.y))
        return false;
    
    if ((origin.black && dest.black) || (origin.white && dest.white))
        return false;
    
//    int j = min(origin.y, dest.y) + 1;
//    for (int i = min(origin.x, dest.x) + 1; i < max(origin.x, dest.x); ++i) {
//        if (!board[i][j].empty)
//            return false;
//        ++j;
//    } // for
    
    return true;
} // bishop_valid

bool Chess::queen_valid(const Space origin, const Space dest) {
    if (bishop_valid(origin, dest))
        return true;
    
    if (rook_valid(origin, dest))
        return true;
    
    return false;
} // queen_valid

bool Chess::king_valid(const Space origin, const Space dest) {
    if (origin.black && dest.black)
        return false;
    
    if (origin.white && dest.white)
        return false;
    
    if (abs(origin.x - dest.x) > 1 || abs(origin.y - dest.y) > 1)
        return false;
    
    return true;
} // king_valid

void Chess::print_board() {
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    cout << "Y -------------------------" << endl;
    for (int i = 1; i < board.size(); ++i) {
        for (int j = 1; j < board.size(); ++j) {
            if (j == 1)
                cout << 9 - i << "| ";
            
            char first = board[i][j].piece.front();
            char second = board[i][j].piece.back();
            switch (second) {
                case 'p':
                    if (first == 'b')
                        cout << "BP ";
                    else
                        cout << "WP ";
                    break;
                case 'r':
                    if (first == 'b')
                        cout << "BR ";
                    else
                        cout << "WR ";
                    break;
                case 'h':
                    if (first == 'b')
                        cout << "BH ";
                    else
                        cout << "WH ";
                    break;
                case 'b':
                    if (first == 'b')
                        cout << "BB ";
                    else
                        cout << "WB ";
                    break;
                case 'q':
                    if (first == 'b')
                        cout << "BQ ";
                    else
                        cout << "WQ ";
                    break;
                case 'k':
                    if (first == 'b')
                        cout << "BK ";
                    else
                        cout << "WK ";
                    break;
                default:
                    cout << "[] ";
                    break;
            } // switch
            if (j == 8)
                cout << "|";
        } // for
        cout << endl;
    } // for
    cout << "  -------------------------" << endl;
    cout << "   1  2  3  4  5  6  7  8  X" << endl;
    cout << endl;
} // print_board
