////////////////////////////////////////////////////////////////////////////
//  Jonathan Jones (jonesjon) and Brett Case (casebr)
//  Programming Assignment 1
//  CS331 Intro to Artificial Intelligence Spring2018
////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

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

void bfs();
void dfs();
void iddfs();
void astar();

void file_to_state(State&, State&, ifstream&, ifstream&);
void show_state(State);
void write_state_to_file(State);
bool isValid(State);

//Globals
ofstream out_f;

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
    out_f.open(output_file.c_str());
    if(!(init_f.is_open() && goal_f.is_open() && out_f.is_open())) //Check if files were opened correctly
    {
        cout << "ERROR: Invalid filenames provided" << endl;
        return 1;
    }

    //Fill initial and goal states
    file_to_state(initial, goal, init_f, goal_f);

    return 0;
}

/***************************************************************
 * Function: file_to_state
 * Description: Reads from provided input streams into the initial and goal states
 * Params: initial state, goal state, initial file stream, goal file stream
 * Returns: none
 * Pre-Conditions: Streams are open
 * Post-Conditions: States are filled
 **************************************************************/
void file_to_state(State& i_state, State& g_state, ifstream& init, ifstream& goal)
{
    char a, b; //Dummy variables
    init >> i_state.left.num_chickens>> a >> i_state.left.num_wolves >> b >> i_state.left.boat;
    init >> i_state.right.num_chickens >> a >> i_state.right.num_wolves >> b >> i_state.right.boat;

    goal >> g_state.left.num_chickens >> a >> g_state.left.num_wolves >> b >> g_state.left.boat;
    goal >> g_state.right.num_chickens >> a >> g_state.right.num_wolves >> b >> g_state.right.boat;
}

/***************************************************************
 * Function: show_state
 * Description: Prints the state to stdout
 * Params: State to be printed
 * Returns: None
 * Pre-Conditions: State contains data
 * Post-Conditions: None
 **************************************************************/
void show_state(State s)
{
    cout << s.left.num_chickens << s.left.num_wolves << s.left.boat << 
    "," << s.right.num_chickens << s.right.num_wolves << s.right.boat << endl;
}

/***************************************************************
 * Function: write_state_to_file
 * Description: Writes the contents of the state in a formatted manner into the output stream
 * Params: State to be written to file
 * Returns: None
 * Pre-Conditions: State contains data
 * Post-Conditions: None
 **************************************************************/
void write_state_to_file(State s)
{
    out_f << s.left.num_chickens << "," << s.left.num_wolves << "," << s.left.boat << '\n'
    << s.right.num_chickens << "," << s.right.num_wolves << "," << s.right.boat << '\n' << endl;
}

/***************************************************************
 * Function: isValid
 * Description: Determines the validity of the current state. If there are more wolves than chickens on either bank, the state is invalid.
 * Params: State to be validated
 * Returns: True if valid state, false if invalid state
 * Pre-Conditions: State contains data
 * Post-Conditions: None
 **************************************************************/
bool isValid(State s)
{
    return ((s.left.num_chickens >= s.left.num_wolves) && (s.right.num_chickens >= s.right.num_wolves));
}