//
//  8Puzzle.h
//  8 Sliding Tile Puzzle
//
//  Created by Andy Truong on 12/8/20.
//  Copyright © 2020 Andy Truong. All rights reserved.
//

#ifndef _Puzzle_h
#define _Puzzle_h

class Puzzle {
private:
    //Hold initial and goal state for printing
    State initialState;
    State goalState;
public:
    Puzzle() {
        Solver s;
        
        //These give specific values for the goal state and initial state
        int initial_Board[BOARD_SIZE][BOARD_SIZE] = {{2, 8, 3}, {1, 6, 4}, {7, 0, 5}};
        int goal_Board[BOARD_SIZE][BOARD_SIZE] = {{1, 2, 3}, {8, 0, 4}, {7, 6, 5}};
        State initial_State(initial_Board);
        State goal_State(goal_Board);
        
        
        //These randomise the initial state and goal state, NOTE: breaks after 100 steps, goal may not be reached.
        /*State initial_State;
        initial_State.randomiseState();
        State goal_State;
        goal_State.randomiseState();*/
        
        cout << "*************************" << endl;
        cout << "GOAL STATE: " << endl;
        cout << "*************************" << endl;
        goal_State.printState();
        
        cout << "*************************" << endl;
        cout << "INITIAL STATE: " << endl;
        cout << "*************************" << endl;
        initial_State.printState();
        
        s.AStarSolver(initial_State, goal_State);
    }
};

#endif /* _Puzzle_h */
