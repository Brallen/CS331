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
#include <queue>

using namespace std;

struct Bank {
    unsigned int num_wolves, num_chickens, boat;
};

struct State {
    Bank left, right;

    bool operator==(const State a) const
    {
        return ((left.num_chickens == a.left.num_chickens)
                && (left.num_wolves == a.left.num_wolves)
                && (left.boat == a.left.boat)
                && (right.num_chickens == a.right.num_chickens)
                && (right.num_wolves == a.right.num_wolves)
                && (right.boat == a.right.boat));
    }
};

struct Node {
    State state;
    Node* prev;
    vector<Node*> succ;
};


vector<State> bfs(State, State);
void dfs();
void iddfs();
void astar();

void file_to_state(State&, State&, ifstream&, ifstream&);
void show_state(State);
void write_state_to_file(State);
bool isValid(State);
bool enoughAnimals(State, int);
void moveAnimals(State, State*,  int, int);


//Globals
ofstream out_f;

// <initial state file> <goal state file> <mode> <output file>
int main(int argc, char** argv){
    //Initialize command line argument buffers
    string init_state_file, goal_state_file, mode, output_file;
    State initial;
    State goal;
    Node* tree = NULL;
    
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

    tree = new Node();
    tree->state = initial;
    tree->prev = NULL;

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
    return ((s.left.num_chickens >= s.left.num_wolves && s.left.num_chickens > 0) && (s.right.num_chickens >= s.right.num_wolves && s.right.num_chickens > 0));
}

//pass in the number of animals on the bank and the amount to try to put on the boat
//to see if this is a valid move
bool enoughAnimals(int numAnimals, int amountToMove)
{
    return numAnimals > amountToMove;
}
//find out what side boat is on and move specificed number of animals across
void moveAnimals(State s, State* newNode, int chicks, int wolves){
    if(s.left.boat == 1){ //left side has boat
        //move number of chickens
        if(enoughAnimals(s.left.num_chickens, chicks)){
            newNode->left.num_chickens = s.left.num_chickens - chicks;
            newNode->right.num_chickens = s.right.num_chickens + chicks;
        }else newNode = NULL; //if cant make move return NULL

        //move number of wolves
        if(enoughAnimals(s.left.num_wolves, wolves)){
            newNode->left.num_wolves = s.left.num_wolves - wolves;
            newNode->right.num_wolves = s.right.num_wolves + wolves;
        }else newNode = NULL; //if cant make move return NULL
 
        //move boat
        newNode->left.boat = 0;
        newNode->right.boat = 1;

    }else{ //right side has boat
        //move number of chickens
        if(enoughAnimals(s.right.num_chickens, chicks)){
            newNode->right.num_chickens = s.right.num_chickens - chicks;
            newNode->left.num_chickens = s.left.num_chickens + chicks;
        }else newNode = NULL; //if cant make move return NULL

        //move number of wolves
        if(enoughAnimals(s.right.num_wolves, wolves)){
            newNode->right.num_wolves = s.right.num_wolves - wolves;
            newNode->left.num_wolves = s.left.num_wolves + wolves;
        }else newNode = NULL; //if cant make the move return NULL
        
        //move boat
        newNode->right.boat = 0;
        newNode->left.boat = 1;
    }
}

vector<State> bfs(State start, State goal)
{
    queue<State> elems;
    vector<State> children;
    vector<State> path;

    elems.push(start);//add the start state to the queue
    
    while(!elems.empty()){ //while elements are still in queue keep going
        State test = elems.front(); //the new node to test is the one at front of queue
        path.push_back(test); //add this state to the end of the path

        elems.pop(); //remove front of queue
        
        if(test == goal){ //if were at the goal then return the path
            return path;
        }
        
        //generate children and add them to queue
        for(int i = 0; i < 5; i++){
            if(i = 0){ //move one chicken
                State next; //make a new state for the next move
                moveAnimals(test, &next 1, 0); //move animals around
                if(next != NULL  && isValid(next)){ //see if this is a valid move (needs help)
                    elems.push(next); //if good add it to the queue to check later
                }  
            //add rest of the cases here
            }
        }
    }
    return path; //this will need to change cause void function    
}
