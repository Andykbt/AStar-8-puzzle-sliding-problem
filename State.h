//
//  State.h
//  8 Sliding Tile Puzzle
//
//  Created by Andy Truong on 12/8/20.
//  Copyright © 2020 Andy Truong. All rights reserved.
//

#ifndef State_h
#define State_h

class State {
private:
    int board[BOARD_SIZE][BOARD_SIZE];
    static int step;
public:
    //Constructor
    State() {
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE;j ++)
                 board[i][j] = 0;
    }
    
    /*
    //Copy Constructor
    State(State& s) {
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                board[i][j] = s.board[i][j];
    }*/
    
    //Copy Constructor
    State(int board[BOARD_SIZE][BOARD_SIZE]) {
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                this->board[i][j] = board[i][j];
    }
    
    // == comparison for states
    bool operator==(State& s) {
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                if (board[i][j] != s.getTile(i, j))
                    return false;
        return true;
    }
    
    // != comparison for states
    bool operator!=(State& s) {
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                if (board[i][j] != s.getTile(i, j))
                    return true;
        return false;
    }
    
    //get next state from action
    State nextState(Action a) {
        State newState(*this);
        newState.moveTile(a);
        return newState;
    }// end nextState
    
    //get heuristic in comparison with Goal state
    int getHeuristic(State goal) {
        int count = 0;
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                if (board[i][j] == goal.getTile(i, j) && board[i][j] != 0)
                    count++;
        return MAX_VAl - count;
    }// end getHeuristic
    
    //return steps
    int getStep() {return step;}
    
    //Print State
    void printState() {
        for (int i = 0; i < BOARD_SIZE; i++)
            cout << " ---";
        cout << "\n";
        
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                cout << "| " << board[i][j] << " ";
            }
            cout << "|\n";
            for (int i = 0; i < BOARD_SIZE; i++)
                cout << " ---";
            cout << "\n";
        }
    }//end printState
    
    //randomise a state
    void randomiseState() {
        for (int i = 1; i <= MAX_VAl; i++) {
            int row = rand() % BOARD_SIZE;
            int col = rand() % BOARD_SIZE;
            
            if (board[row][col] == 0)
                board[row][col] = i;
            else
                i--;
        }
    }//end randomiseState
    
    //get tile given row and column
    int getTile(int row, int col) {return board[row][col];}
    
    //returns if a specific action can be placed
    bool canMove(int row, int col, int &destR, int &destC) {
        if (board[row + 1][col] == 0 && row + 1 < BOARD_SIZE) {
            destR = row + 1;
            destC = col;
            return true;
        } else if (board[row - 1][col] == 0 && row - 1 >= 0) {
            destR = row - 1;
            destC = col;
            return true;
        } else if (board[row][col + 1] == 0 && col + 1 < BOARD_SIZE) {
            destR = row;
            destC = col + 1;
            return true;
        } else if (board[row][col - 1] == 0 && col - 1 >= 0) {
            destR = row;
            destC = col - 1;
            return true;
        }
        return false;
    }//end canMove
    
    //inserts tile at location, disregarding if move is possible or not
    bool insertTile(int row, int col, int destRow, int destCol) {
        int src = board[row][col];
        int dest = board[destRow][destCol];
        
        board[destRow][destCol] = src;
        board[row][col] = dest;
        return true;
    }//end insertTile
    
    //moveTile if move is valid
    bool moveTile(int row, int col) {
        int destR, destC;
        if (canMove(row, col, destR, destC)) {
            int temp = board[row][col];
            board[row][col] = board[destR][destC];
            board[destR][destC] = temp;
            return true;
        }
        return false;
    }//end moveTile
    
    //moveTile if move is valid
    bool moveTile(Action a) { 
        if (canMove(a.srcRow, a.srcCol, a.destRow, a.destCol)) {
            int temp = board[a.srcRow][a.srcCol];
            board[a.srcRow][a.srcCol] = board[a.destRow][a.destCol];
            board[a.destRow][a.destCol] = temp;
            return true;
        }
        return false;
    }//end moveTile
    
    //get all possible actions
    void possibleActions(priority_queue<Action> &pq, State goal) {
        Action a;
        step++;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (canMove(i, j, a.destRow, a.destCol)) {
                    a.srcRow = i;
                    a.srcCol = j;
                    a.fCost = getStep();
                    a.hCost = nextState(a).getHeuristic(goal);
                    
                    pq.push(a);
                    
                    //cout << "Move " << getTile(a.srcRow, a.srcCol) << " to " << getTile(a.destRow, a.destCol) << " with a heuristic of [" << a.fCost << ", " << a.hCost << "]" << endl;
                }
            }
        }
    }//end possibleActions
};

int State::step = 0;
#endif /* State_h */
