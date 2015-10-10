#include "Board_2.h"

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
		index += columns;
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
	else
	{
		index += (columns+1);
		if (index >= columns*rows)
			return-1;
		else
			return index;
	}
}

//int move_down (int index, const int columns, const int rows)
//{
//	index += columns;
//	if (index >= columns * rows)
//		return -1;
//	return index;
//}
//
//int move_up (int index, const int columns)
//{
//	index -= columns;
//	if (index < 0)
//		return -1;
//	return index;
//}
//
//int move_left (int index, const int columns)
//{
//	if (index / columns == index-1 / columns)
//		return index-1;
//	else
//		return -1;
//}
//
//int move_right (int index, const int columns)
//{
//	if (index / columns == index+1 / columns)
//		return index+1;
//	else
//		return -1;
//}
//
//int move_left_diagnol (int index, const int columms)
//{
//	index -= (columms-1);
//	if (index < 0)
//		return-1;
//	else
//		return index;
//}
//
//int move_left_diagnol (int index, const int columns)
//{
//	index -= (columns+1);
//	if (index < 0)
//		return -1;
//	else
//		return index;
//}
//
//int move_left_diagnol (int index, const int columns)
//{
//
//}

Board_2::Board_2 ()
{
	columns = 7;
	rows = 6;
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



void Board_2::play(const int column, const char player_piece)
{
	int index = column;
	if (board[(index+1)*rows] == '-')
		board[index*rows] == player_piece;
	while (index != -1)
	{
		if (board[index] != '-')
			board[move(index,columns,rows,"up")] = player_piece;
		index = move(index,columns,rows,"down");
	}
}

//void Board_2::check_board () const
//{
//
//}