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
		if (index / columns == (index-1) / columns)
			return index-1;
		else
			return -1;
	}
	else if (type == "right")
	{
		if (index / columns == (index+1) / columns)
			return index+1;
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

int Board_2::get_columns () const
{
	return columns;
}

int Board_2::get_rows () const
{
	return rows;
}

int Board_2::get_r () const
{
	return r;
}

int Board_2::get_placed_column () const
{
	return placed_column;
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
	board_size = columns*rows;
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
	board_size = columns*rows;
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
bool Board_2::play(const int column, const char player_piece)
{
	// check the top of the column to see if it is full, if so it is an illeagal move
	int to_play = column;
	if (board[to_play] != '-')
		return false;
	else
	{
		to_play = ((rows*columns) - columns) + column; // start at the bottom of the board in the given column
		while (board[to_play] != '-')
		{
			to_play = move(to_play, columns, rows, "up");
		}
		board[to_play] = player_piece;
		used_columns.insert(column);
		used_rows.insert(to_play/columns);
		
	}
	return true;
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
	for (auto column : used_columns)
	{
		column = ((rows*columns) - columns) + column;
		while (column != -1)
		{
			if (board[column] == player_piece)
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
			else if (board[column] == '-')
			{
				if(ai_last)
					utility += (ai_count*(10+(ai_count*ai_count)));
					
				else
					utility -= (player_count*(10+(player_count*player_count)));
					
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
			column = move(column,columns,rows,"up");
		}
	}
	return utility;
}
 
// check each of the rows that were played in and score the peices acordingly
double check_rows (const bool is_turn, const char player_piece, set<int> used_rows, const int columns, const int rows, const int r, const vector<char> board, bool& is_limit)
{
	bool ai_last = false;
	bool player_last = false;
	double utility = 0;
	int ai_count = 0;
	int player_count = 0;
	int space_count = 0;
	int check_down = 0;

	for (auto row : used_rows)
	{
		row *= (columns);
		while (row != -1)
		{
			if (board[row] == player_piece)
			{
				if (player_last)
					utility -= (player_count*(10+(player_count*player_count)));
				ai_count++;
				ai_last = true;
				player_last = false;
				if (ai_count == r && is_turn && space_count == 0) // if the winning move is found stop there and return the max value
				{
					is_limit = true;
					return numeric_limits<double>::max();
				}
				player_count = 0;
				space_count = 0;
			}
			else if (board[row] == '-')
			{
				if (ai_last)
				{
					check_down = move(row, columns, rows, "down");
					if (check_down != -1)
					{
						if (board[check_down] != '-')
							utility += 10;
					}
				}
				else if (player_last)
				{
					check_down = move(row, columns, rows, "down");
					if (check_down != -1)
					{
						if (board[check_down] != '-')
							utility -= 10;
					}
				}
				else
					;
				space_count++;
				if (space_count > 1)
				{
					if(ai_last)
						utility += (ai_count*(10+(ai_count*ai_count)));
					
					else if (player_last)
						utility -= (player_count*(10+(player_count*player_count)));
					player_count = 0;
					ai_count = 0;
				}
			}
			else
			{
				if (ai_last)
					utility += (ai_count*(10+(ai_count*ai_count)));
				player_count++;
				player_last = true;
				ai_last = false;
				if (player_count == r && !is_turn && space_count == 0) // if the losing move is found stop there and return the min value
				{
					is_limit = true;
					return numeric_limits<double>::min();
				}
				ai_count = 0;
				space_count = 0;
			}
			row = move(row, columns, rows, "right");
		}
	}
	return utility;
}

double check_diagonals (const bool is_turn, const char player_piece, const int columns, const int rows, const int r, const vector<char> board, bool& is_limit)
{
	bool ai_last = false;
	bool player_last = false;
	double utility = 0;
	int ai_count = 0;
	int player_count = 0;
	int space_count = 0;
	int check_down = 0;
	int diaganol = 0;

	// check the down right diagonals 
	for (int i = 0; i < columns - r; i++)
	{
		diaganol = i;
		while (diaganol != -1)
		{
			if (board[diaganol] == player_piece)
			{
				if (player_last)
					utility -= (player_count*(10+(player_count*player_count)));
				ai_count++;
				ai_last = true;
				player_last = false;
				if (ai_count == r && is_turn && space_count == 0) // if the winning move is found stop there and return the max value
				{
					is_limit = true;
					return numeric_limits<double>::max();
				}
				player_count = 0;
				space_count = 0;
			}
			else if (board[diaganol] == '-')
			{
				if (ai_last)
				{
					check_down = move(diaganol, columns, rows, "down");
					if (check_down != -1)
					{
						if (board[check_down] != '-')
							utility += 10;
					}
				}
				else if (player_last)
				{
					check_down = move(diaganol, columns, rows, "down");
					if (check_down != -1)
					{
						if (board[check_down] != '-')
							utility -= 10;
					}
				}
				else
					;
				space_count++;
				if (space_count > 1)
				{
					if(ai_last)
						utility += (ai_count*(10+(ai_count*ai_count)));
					
					else if (player_last)
						utility -= (player_count*(10+(player_count*player_count)));
					player_count = 0;
					ai_count = 0;
				}
			}
			else
			{
				if (ai_last)
					utility += (ai_count*(10+(ai_count*ai_count)));
				player_count++;
				player_last = true;
				ai_last = false;
				if (player_count == r && !is_turn && space_count == 0) // if the losing move is found stop there and return the min value
				{
					is_limit = true;
					return numeric_limits<double>::min();
				}
				ai_count = 0;
				space_count = 0;
			}
			diaganol = move(diaganol, columns, rows, "down-right-diagnol");
		}	
	}

	for (int i = 0; i/columns < (columns-r)-1; i+=columns)
	{
		diaganol = i;
		while (diaganol != -1)
		{
			if (board[diaganol] == player_piece)
			{
				if (player_last)
					utility -= (player_count*(10+(player_count*player_count)));
				ai_count++;
				ai_last = true;
				player_last = false;
				if (ai_count == r && is_turn && space_count == 0) // if the winning move is found stop there and return the max value
				{
					is_limit = true;
					return numeric_limits<double>::max();
				}
				player_count = 0;
				space_count = 0;
			}
			else if (board[diaganol] == '-')
			{
				if (ai_last)
				{
					check_down = move(diaganol, columns, rows, "down");
					if (check_down != -1)
					{
						if (board[check_down] != '-')
							utility += 10;
					}
				}
				else if (player_last)
				{
					check_down = move(diaganol, columns, rows, "down");
					if (check_down != -1)
					{
						if (board[check_down] != '-')
							utility -= 10;
					}
				}
				else
					;
				space_count++;
				if (space_count > 1)
				{
					if(ai_last)
						utility += (ai_count*(10+(ai_count*ai_count)));
					
					else if (player_last)
						utility -= (player_count*(10+(player_count*player_count)));
					player_count = 0;
					ai_count = 0;
				}
			}
			else
			{
				if (ai_last)
					utility += (ai_count*(10+(ai_count*ai_count)));
				player_count++;
				player_last = true;
				ai_last = false;
				if (player_count == r && !is_turn && space_count == 0) // if the losing move is found stop there and return the min value
				{
					is_limit = true;
					return numeric_limits<double>::min();
				}
				ai_count = 0;
				space_count = 0;
			}
			diaganol = move(diaganol, columns, rows, "down-right-diagnol");
		}	
	}
	return utility;
}


double Board_2::check_board (const bool is_turn, const char player_piece) const
{
	bool is_limit = false;
	double utilitly = 0;
	double temp = 0;
	temp = check_columns(is_turn,player_piece,used_columns,columns,rows,r,board,is_limit);
	if (is_limit) 
		return temp; // if a killer move was found return that killer move
	else
		utilitly += temp;
	temp = check_rows(is_turn, player_piece, used_rows, columns, rows, r, board, is_limit);
	if (is_limit)
		return temp;
	else 
		utilitly += temp;
	temp = check_diagonals(is_turn,player_piece, columns, rows, r, board, is_limit);
	if (is_limit)
		return temp;
	else
		utilitly += temp;

	return utilitly;
}