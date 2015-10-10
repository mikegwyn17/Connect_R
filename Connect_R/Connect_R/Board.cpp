#include "Board.h"

Board::Board ()
{
	number_of_rows = 5;
	number_of_columns = 6;
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

void Board::play(const int column, const char character, int& added_column, int& added_row)
{
	int size = number_of_columns-1;
	if (board[size][column] == '-')
	{
		board[size][column] = character;
		added_column = column;
		added_row = size;
	}
	else if (board[0][column] != '-')
		;
	else
	{
		for (int row = 0; row < number_of_columns; row++)
		{
			if (board[row][column] != '-')
			{
				board[row-1][column] = character;
				added_column = column;
				added_row = row-1;
			}
		}
	}
}

bool Board::check_board (const char player_piece, int added_column, int added_row) const
{
	bool is_solved = false;
	unsigned count = 0;

	// check to see if row is solved
	if (added_row == number_of_rows)
	{
		if (board[added_column-1][added_row-1] != player_piece)
			;

		else
		{
			count++;
			for (int i = number_of_columns-1; i >= 0; i--)
			{
				if (board[added_column][i] != player_piece)
					break;
				else
					count++;
				if (count == r)
				{
					is_solved = true;
					cout << is_solved << endl;
					return is_solved;
				}
			}
		}
	}

	else
	{
		cout << is_solved << endl;
		return is_solved;
	}
	}
