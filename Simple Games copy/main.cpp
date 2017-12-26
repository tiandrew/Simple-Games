//
//  main.cpp
//  Simple Games
//
//  Created by Andrew Jonathan Tian on 5/11/17.
//  Copyright © 2017 Andrew Tian. All rights reserved.
//

#include <iostream>
#include "chess.hpp"
using namespace std;

void print_intro() {
    cout << "***************************************" << endl;
    cout << "***************************************" << endl;
    cout << "**                                   **" << endl;
    cout << "**            MINI GAMES             **" << endl;
    cout << "**                                   **" << endl;
    cout << "***************************************" << endl;
    cout << "***************************************" << endl;
    cout << endl;
    cout << "Enter:" << endl;
    cout << "1) Chess" << endl;
    cout << endl;
} // print_intro

int main(int argc, const char * argv[]) {
    print_intro();
    short choice;
    cin >> choice;
    cout << endl;
    
    Chess chess;
    chess.play_chess();
    
    while (true) {
        switch (choice) {
            case 1: {
                Chess chess;
                chess.play_chess();
                break;
            } // Chess
            default:
                cout << "Error: Game option " << choice << " not valid" << endl;
                cout << "Please reselect an option" << endl;
                cin >> choice;
                break;
        }
    }
    return 0;
} // main
