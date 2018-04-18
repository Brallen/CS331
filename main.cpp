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
bool enoughAnimals(State, int);
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

    file_to_state(initial, goal, init_f, goal_f);

    return 0;
}

void file_to_state(State& i_state, State& g_state, ifstream& init, ifstream& goal)
{
    char a, b; //Dummy variables
    init >> i_state.left.num_chickens>> a >> i_state.left.num_wolves >> b >> i_state.left.boat;
    init >> i_state.right.num_chickens >> a >> i_state.right.num_wolves >> b >> i_state.right.boat;

    goal >> g_state.left.num_chickens >> a >> g_state.left.num_wolves >> b >> g_state.left.boat;
    goal >> g_state.right.num_chickens >> a >> g_state.right.num_wolves >> b >> g_state.right.boat;
}

void show_state(State s)
{
    cout << s.left.num_chickens << s.left.num_wolves << s.left.boat << 
    "," << s.right.num_chickens << s.right.num_wolves << s.right.boat << endl;
}

void write_state_to_file(State s)
{
    out_f << s.left.num_chickens << "," << s.left.num_wolves << "," << s.left.boat << '\n'
    << s.right.num_chickens << "," << s.right.num_wolves << "," << s.right.boat << '\n' << endl;
}

bool isValid(State s)
{
    return ((s.left.num_chickens >= s.left.num_wolves) && (s.right.num_chickens >= s.right.num_wolves));
}
//pass in the number of animals on the bank and the amount to try to put on the boat
//to see if this is a valid move
bool enoughAnimals(int numAnimals, int amountToMove)
    return numAnimals > amountToMove;
}
