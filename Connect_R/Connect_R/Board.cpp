#include "Board.h"

Board::Board ()
{
	number_of_rows = 5;
	number_of_rows = 6;
	r = 4;
}

void Board::Build_Board(const int rows, const int columns, const int win_condition)
{
	number_of_rows = rows;
	number_of_columns = columns;
	r = win_condition;
	board.resize(number_of_columns, vector<char>(number_of_rows, '-'));
}

string Board::to_string () const
{
	string output = "";
	for (int row = 0; row < board.size(); row++)
	{
		output += "\n";
		for (int column = 0; column < board.at(row).size(); column++)
		{
			output += board[row][column];
			output += " ";
		}
	}
	return output;
}

void Board::play(const int column, const char character)
{
	int size = board.size()-1;
	if (board[size][column] == '-')
		board[size][column] = character;
	else if (board[0][column] != '-')
		;
	else
	{
		for (int row = 0; row < board.size(); row++)
		{
			if (board[row][column] != '-')
				board[row-1][column] = character;
		}
	}
}

void Board::check_board () const
{

}