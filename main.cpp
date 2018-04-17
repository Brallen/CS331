#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Bank {
    unsigned int num_wolves, num_chickens;
};

struct State {
    Bank left, right;
    unsigned int boat;
};

// <initial state file> <goal state file> <mode> <output file>
int main(int argc, char** argv)
{
    //Initialize command line argument buffers
    string state_file, goal_state_file, mode, output_file;
    
    //Check for valid number of arguments
    if(argc == 5)
        state_file = argv[1], goal_state_file = argv[2], mode = argv[3], output_file = argv[4];
    else 
    {
        cout << "USAGE: Invalid argument count" << endl;
        return 1;
    }

    return 0;
}
