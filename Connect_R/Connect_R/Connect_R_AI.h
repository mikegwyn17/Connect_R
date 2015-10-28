#ifndef _CONNECT_R_AI_
#define _CONNECT_R_AI_
#include "Board_2.h"

using namespace std;

class Connect_R_AI
{
	private:
		Board_2 board;
		int max_depth;
		int move_location; // the location for the minimax to play
		int min_value;
		int max_value;
		
	public:
		struct board_tree // tree structure used for minimax algorithm
		{
			Board_2 board;
			vector<Board_2> children;
			int size;
			int r;
			int columns;
			int rows;
			board_tree () {}
			board_tree (const Board_2& b, const int& s, const int& r, const int& row, const int& c)
			{
				board = b;

			}
			board_tree (const board_tree& o)
			{
				children.resize(o.children.size());
				board = o.board;
				r = o.r;
				columns= o.columns;
				rows = o.rows;
			}
		};

		Connect_R_AI ();
		Connect_R_AI (Board_2* b);
		~Connect_R_AI();
		void opponent_move ();
		int result_of_game (Board_2 b) const;
		int Connect_R_AI::get_AI_move ();
		//int Minimax (int depth, bool is_turn, int alpha, int beta);
		void mimimize (board_tree& tree, int depth);
		void maximize (board_tree& tree, int depth);
		int get_move_location () {return move_location;}
		int check_board (Board_2 board, const bool is_turn) const;
		void play_AI ();
		board_tree play (board_tree& tree, const int column, const bool is_turn);

};
#endif 