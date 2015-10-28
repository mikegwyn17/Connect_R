#ifndef _AI_H_
#define _AI_H_
#include <vector>
#include <limits>
#include <time.h>
#include <string>
#include <iostream>

using namespace std;

class AI
{
public:

	int min_value; // used so that I don't have to retype the same thing over and over...
	int max_value; // used so that I don't have to retype the same thing over and over...
	int max_depth; // used to decide how far down the tree the minimax goes

	struct state_space // tree strcutre used for the minimax
	{
		vector<char> board;
		vector<state_space> children;
		int r;
		int columns;
		int rows;
		int move;
		int utility;
		state_space() {}
		state_space (const vector<char>& b, const int& connect_r, const int& number_of_columns, const int& number_of_rows)
		{
			board = b;
			r = connect_r;
			columns = number_of_columns;
			rows = number_of_rows;
			children.resize(columns);
		}
		state_space (const state_space& o)
		{
			board = o.board;
			r = o.r;
			columns = o.columns;
			rows = o.rows;
			children.resize(o.children.size());
		}
		string to_string ()
		{
			string output = "";
			for (int i = 0; i < columns*rows; i++)
			{
				output += board[i];
				if ((i+1) % columns == 0 )
					output += '\n';
			}
			return output;
		}
	};

	AI(void);
	~AI(void);
	//int move (int index, const int columns, int rows, string type);
	int minimax (state_space& current_state);
	void maximize (state_space& current_state, int depth);
	void minimize (state_space& current_state, int depth);
	void score_state (state_space& current_state);
	bool is_game_over (state_space& current_state); // checks to see if there is a winning move
	bool is_board_full (state_space& current_state); // checks to see if the game is draw
	state_space play (state_space& current_state, const int move, const bool is_turn); // used to add a piece to the board

	




};
#endif