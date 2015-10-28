#ifndef _BOARD_2_H_
#define _BOARD_2_H_
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <limits>

using namespace std;

class Board_2
{
	private:
		int columns;
		int rows;
		int r;
		set<int> used_columns;
		set<int> used_rows;
		vector<int> placed_pieces;
		int placed_column;
		int board_size;
		int last_placed;

	public:
		vector<char> board; // board state is represented as a vector of chars
		Board_2 ();
		~Board_2();
		int get_columns () const;
		int get_rows () const;
		int get_r () const;
		int get_placed_column () const;
		int size () {return board_size -1;}
		void set_board (const vector<char> passed_board);
		void Build_Board(const int rows,const int columns, const int win_condition);
		string to_string () const;
		bool play (const int column, const char character);
		double check_board (const bool is_turn, const char player_piece) const;
		void undo_move (int column);
		bool is_valid (int column) const;

};
#endif 