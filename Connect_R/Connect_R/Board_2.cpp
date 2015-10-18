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
// create a board based on the given parameters
void Board_2::Build_Board(const int number_of_columns, const int number_of_rows, const int win_condition)
{
	columns = number_of_columns;
	rows = number_of_rows;
	r = win_condition;
	board.resize(columns*rows,'-');
}

// return string representation of the board to show the user what the current board state is
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
// used to place a piece on the connect R board, starts at the bottom and works it way up
vector<char> Board_2::play(const int column, const char player_piece)
{
	// check the top of the column to see if it is full, if so it is an illeagal move
	int to_play = column;
	if (board[to_play] != '-')
		cout << "cannot play here" << endl;
	else
	{
		to_play = ((rows*columns) - columns) + column; // start at the bottom of the board in the given column
		while (board[to_play] != '-')
		{
			to_play = move(to_play, columns, rows, "up");
		}
		board[to_play] = player_piece;
		used_columns.insert(column);
		cout << to_play/columns << endl;
		
	}
	return board;
}
// function used to check each of the columns that have been played 
double check_columns (const bool is_turn, const char player_piece, set<int> used_columns, const int columns, const int rows, const int r, const vector<char> board, bool& is_limit)
{
	bool ai_last = false;
	bool player_last = false;
	double utility = 0;
	int ai_count = 0;
	int player_count = 0;
	// check the columns to see if there 
	for (auto i : used_columns)
	{
		i = ((rows*columns) - columns) + i;
		while (i != -1)
		{
			if (board[i] == player_piece)
			{
				ai_count++;
				ai_last = true;
				player_last = false;
				if (ai_count == r && is_turn) // if the winning move is found stop there and return the max value
				{
					is_limit = true;
					return numeric_limits<double>::max();
				}
				//utility -= (player_count*10);
				player_count = 0;
			}
			else if (board[i] == '-')
			{
				if(ai_last)
					utility += (ai_count*(10+ai_count));
					
				else
					utility -= (player_count*(10+player_count));
					
				player_count = 0;
				ai_count = 0;
				break;
			}
			else
			{
				player_count++;
				player_last = true;
				ai_last = false;
				if (player_count == r && !is_turn) // if the losing move is found stop there and return the min value
				{
					is_limit = true;
					return numeric_limits<double>::min();
				}
				//utility += (ai_count*10);
				ai_count = 0;
			}
			i = move(i,columns,rows,"up");
		}
	}
	return utility;
}

//double check_rows (const bool is_turn, const char player_piece, set<int> used_columns, const int columns, const int rows, const int r, const vector<char> board, bool& is_limit)
//{
//
//}

// heuristic used to determine the utility of the current board
// starts at the bottom cell and checks to see what color that piece is
// if it is the AI's color it checks all around the cell and adds ten to the the 
// utility for every cell in it that makes up a R length line of cells, and subtracts for the other players color
// if winning or loosing move is found number is set to either the largest of smallest possible int
double Board_2::check_board (const bool is_turn, const char player_piece) const
{
	bool is_limit = false;
	double utilitly = 0;
	utilitly += check_columns(is_turn,player_piece,used_columns,columns,rows,r,board,is_limit);
	if (is_limit) 
		return utilitly; // if a killer move was found return that killer move

	return utilitly;
}