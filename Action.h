//
//  Action.h
//  8 Sliding Tile Puzzle
//
//  Created by Andy Truong on 12/8/20.
//  Copyright © 2020 Andy Truong. All rights reserved.
//

#ifndef Action_h
#define Action_h

struct Action {
    //Action source and destination
    int srcRow;
    int srcCol;
    int destRow;
    int destCol;
    
    //cost of action
    int hCost;
    int fCost;
    
    // == comparison for action
    bool operator==(const Action &a) const {
        if (srcRow != a.srcRow)
            return false;
        else if (srcCol != a.srcCol)
            return false;
        else if (destRow != a.destRow)
            return false;
        else if (destCol != a.destCol)
            return false;
        else
            return true;
    }
    
    // < comparison for action
    bool operator<(const Action &a) const {return hCost > a.hCost;}
    
    //print action
    void printAction() {
        cout << "Moving (" << srcRow << ", " << srcCol << ") to (" << destRow << ", " << destCol << ")" << " with a cost of [" << fCost << ", " << hCost << "]" << endl;
    }
    
    //return GCost of action
    int getGCost() {return hCost + fCost;}
};

#endif /* Action_h */
