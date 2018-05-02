/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"

using std::vector;

signed int posIn = 0x7fffffff; //largest
signed int negIn = 0x80000000; //smallest

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}
// function MINIMAX-DECISION(state) returns an action
// 	inputs: state, current state in game
// 	v← MAX-VALUE(state)
// 	return the action in SUCCESSORS(state) with value v
// 
// function MAX-VALUE(state) returns a utility value
// 	if TERMINAL-TEST(state) then return UTILITY(state)
// 	v← -Infinity
// 	for a, s in SUCCESSORS(state) do 
// 		v← MAX(v, MIN-VALUE(s))
// 	return v
// 
// function MIN-VALUE(state) returns a utility value
// 	if TERMINAL-TEST(state) then return UTILITY(state)v ← Infinity
// 	for a, sin SUCCESSORS(state) do
// 		v← MIN(v, MAX-VALUE(s))
// 	return v
void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
    if(symbol == b->get_p1_symbol()){
			MaxValue(row,col,'X',b);
		}else{
			MaxValue(row,col,'O',b);
		}
}
int MinimaxPlayer::MaxValue(int& row, int &col, char player, OthelloBoard* b){
	return 0;
}
int MinimaxPlayer::MinValue(int& row, int &col, char player, OthelloBoard* b){
	return 0;
}
int MinimaxPlayer::Utility(OthelloBoard* b){
	return b->count_score('X') - b->count_score('O');
}

vector<OthelloBoard*> GetSucc(char player, OthelloBoard* b){
	vector<OthelloBoard*> board;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			if (b->is_legal_move(i, j, player)){
				board.push_back(new OthelloBoard(*b));
			}
		}
	}
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
