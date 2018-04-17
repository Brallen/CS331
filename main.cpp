#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void bfs();
void dfs();
void iddfs();
void astar();

struct Bank {
    unsigned int num_wolves, num_chickens, boat;
};

struct State {
    Bank left, right;
};

struct Node {
    State state;
    Node* prev;
    vector<Node*> succ;
};

// <initial state file> <goal state file> <mode> <output file>
int main(int argc, char** argv)
{
    //Initialize command line argument buffers
    string init_state_file, goal_state_file, mode, output_file;
    State initial;
    State goal;
    
    //Check for valid number of arguments
    if(argc == 5)
        init_state_file = argv[1], goal_state_file = argv[2], mode = argv[3], output_file = argv[4];
    else 
    {
        cout << "USAGE: Invalid argument count\n<initial state file> <goal state file> <mode> <output file>" << endl;
        return 1;
    }

    //Open files for reading and writing
    ifstream init_f(init_state_file.c_str()), goal_f(goal_state_file.c_str());
    ofstream out_f(output_file.c_str());
    if(!(init_f.is_open() && goal_f.is_open() && out_f.is_open())) //Check if files were opened correctly
    {
        cout << "ERROR: Invalid filenames provided" << endl;
        return 1;
    }

    return 0;
}