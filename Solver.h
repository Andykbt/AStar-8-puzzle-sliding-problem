//
//  Solver.h
//  8 Sliding Tile Puzzle
//
//  Created by Andy Truong on 12/8/20.
//  Copyright © 2020 Andy Truong. All rights reserved.
//

#ifndef Solver_h
#define Solver_h

class Solver {
public:
    bool AStarSolver(State current, State goal) {
        list<State> path;   //list to store path
        State previous; // contains previous State
        
        //Typical A* algorithm
        while (current != goal) {
            priority_queue<Action> pq;
            Action a;
            
            current.possibleActions(pq, goal);
            a = pq.top();
            
            if (current.nextState(a) == previous) {
                pq.pop();
                a = pq.top();
                pq.pop();
            } else {
                pq.pop();
            }
            
            //Quit loop if over 100 iterations
            if (current.getStep() > 100) {
                cout << "OVER 100 STEPS TAKEN AND GOAL NOT FOUND." << endl;
                break;
            }
            
            cout << "**************************************************" << endl;
            cout << "Step " << current.getStep() << " | ";
            a.printAction();
            cout << "**************************************************" << endl;
             
            previous = current;
            current.moveTile(a);
            current.printState();
        }
        
        return false;
    }
};

#endif /* Solver_h */
