#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdio.h>

using namespace std;

class Board
{
	private:
		vector< vector<char> > board;
		int number_of_rows;
		int number_of_columns;
		int r;

	public:
		Board ();
		~Board();
		void Build_Board(const int rows,const int columns, const int win_condition);
		string to_string () const;
		void play (const int column, const char character);
		void check_board () const;
};
#endif 