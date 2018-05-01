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
    
}
struct Move MinimaxPlayer::MinMaxDecision(OthelloBoard* b){

	
	return MaxValue(b);
}
struct Move MinimaxPlayer::MaxValue(OthelloBoard* b){
	struct Move move;
	if (TerminalState(b)) return move;
	return move;
}
struct Move MinimaxPlayer::MinValue(OthelloBoard* b){
	struct Move move;
	return move;
}
bool MinimaxPlayer::TerminalState(OthelloBoard* b){
	return b->has_legal_moves_remaining('X') || b->has_legal_moves_remaining('O');
}
MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
