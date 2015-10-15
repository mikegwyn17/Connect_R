#include "Board_2.h"
// method used to move around the board which is vector of chars
int move (int index, const int columns, int rows, string type)
{
	if (type == "down")
	{
		index += columns;
		if (index >= columns * rows)
			return -1;
		return index;
	}
	else if (type == "up")
	{
		index -= columns;
		if (index >= columns * rows)
			return -1;
		return index;
	}
	else if (type == "left")
	{
		if (index / columns == index-1 / columns)
			return index-1;
		else
			return -1;
	}
	else if (type == "up_left_diagnol")
	{
		index -= (columns-1);
		if (index < 0)
			return-1;
		else
			return index;
	}
	else if (type == "up-right-diagnol")
	{
		index -= (columns+1);
		if (index < 0)
			return -1;
		else
			return index;
	}
	else if (type == "down-right-diagnol")
	{
		index += (columns+1);
		if (index >= columns*rows)
			return -1;
		else
			return index;
	}
	else if (type == "down-left-diagnol")
	{
		index += (columns+1);
		if (index >= columns*rows)
			return-1;
		else
			return index;
	}
	else 
		return -1;
}

int Board_2::get_columns ()
{
	return columns;
}

int Board_2::get_rows ()
{
	return rows;
}

int Board_2::get_r ()
{
	return r;
}

void Board_2::set_board (const vector<char> passed_board )
{
	board = passed_board;
}

Board_2::Board_2 ()
{
	columns = 7;
	rows = 6;
	r = 4;
}

Board_2::~Board_2 ()
{
	cout << "destructor" << endl;
}

void Board_2::Build_Board(const int number_of_columns, const int number_of_rows, const int win_condition)
{
	columns = number_of_columns;
	rows = number_of_rows;
	r = win_condition;
	board.resize(columns*rows,'-');
}

string Board_2::to_string () const
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

vector<char> Board_2::play(const int column, const char player_piece)
{
	int to_play = column;
	if (board[to_play] != '-')
		cout << "cannot play here" << endl;
	else
	{
		to_play = ((rows*columns) - columns) + column;
		while (board[to_play] != '-')
		{
			to_play = move(to_play, columns, rows, "up");
		}
		board[to_play] = player_piece;
	}
	return board;
}

void Board_2::check_board () const
{
	int current_index = ((rows*columns) - columns) + (columns/2);
	cout << current_index << endl;
}