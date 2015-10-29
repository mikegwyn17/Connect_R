#include "AI.h"

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
		if (index < 0)
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
		if (index <= 0)
			return-1;
		else
			return index;
	}
	else if (type == "up-right-diagnol")
	{
		index -= columns-1;
		if (index <= 0)
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

AI::AI(void)
{
	max_value = numeric_limits<int>::max();
	min_value = numeric_limits<int>::min();
	max_depth = 2;
}

AI::~AI(void)
{

}

AI::state_space AI::play (state_space& current_state, const int move_placed,
						  const bool is_turn)
{
	int rows = current_state.rows;
	int columns = current_state.columns;
	vector <char> board = current_state.board;

	int to_play = move_placed;
	if (board[to_play] != '-')
	{
		throw runtime_error ("Column Full"); 
	}

	to_play = ((rows*columns) - columns) + move_placed; // start at the bottom of the board in the given column
	while (board[to_play] != '-')
	{
		to_play = move(to_play, columns, rows, "up");
	}
	state_space new_state (current_state);
	if (is_turn)
		new_state.board[to_play] = 'X';
	else
		new_state.board[to_play] = 'O';

	return new_state;
}

int AI::minimax(state_space& current_state)
{
	maximize(current_state, 0);
	int number_of_children = current_state.children.size();
	int best_move = min_value;
	int move = 0;
	for (int i = 0; i < number_of_children; i++)
	{
		//best_move = max(current_state.children[i].utility, best_move);
		if (best_move < current_state.children[i].utility)
		{
			best_move = current_state.children[i].utility;
			move = i;
		}
	}
	cout << "Computer played in " << move << endl;
	return best_move;
}

void AI::maximize (state_space& current_state, int depth)
{
	// code to check to see if the game is over

	if (depth >= max_depth) // evaluate the leaf nodes
	{
		score_state(current_state);
		return;
	}

	int m = max_value;
	int children_number = current_state.children.size();
	for (int i = 0; i < children_number; i++)
	{
		try 
		{
			current_state.children[i] = play(current_state,i,true);
			current_state.move = i;
			minimize(current_state.children[i], ++depth);
			m = max(current_state.children[i].utility,m);
		} 	catch (const runtime_error&) {
			continue; }
	}
	current_state.utility = m;
}

void AI::minimize (state_space& current_state, int depth)
{
	if (depth >= max_depth) // evaluate the leaf nodes
	{
		score_state(current_state);
		return; 
	}

	int m = max_value;
	int children_number = current_state.children.size();
	for (int i = 0; i < children_number; i++)
	{
		try 
		{
			current_state.children[i] = play(current_state,i,false);
			current_state.move = i;
			maximize(current_state.children[i], ++depth);
			m = min(current_state.children[i].utility,m);
		} catch (const runtime_error&) {
			continue; }

	}
	current_state.utility = m;
}

// part of the heuristic, checks all of the columns of the given board
// and calculates a utility based on the placement of the pieces
int check_columns (const int columns, const int rows,
				   const int r, const vector<char> board,
				   bool& is_limit)
{
	bool ai_last = false;
	bool player_last = false;
	int utility = 0;
	int ai_count = 0;
	int player_count = 0;
	int column = 0;
	int mini = numeric_limits<int>::min();
	int maxi = numeric_limits<int>::max();
	// check the columns to see if there 
	for (int i = 0; i < columns; i++)
	{
		column = i;
		column = ((rows*columns) - columns) + column;
		while (column != -1)
		{
			if (board[column] == 'X')
			{
				ai_count++;
				ai_last = true;
				player_last = false;
				if (ai_count == r) // if the winning move is found stop there and return the max value
				{
					is_limit = true;
					return maxi;
				}

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
				if (player_count == r) // if the losing move is found stop there and return the min value
				{
					is_limit = true;
					return mini;
				}
				//utility += (ai_count*10);
				ai_count = 0;
			}
			column = move(column,columns,rows,"up");
		}
	}
	return utility;
}

// function used to check the rows and return a utility based
// on the heuristic
int check_rows (const int columns, const int rows,
				const int r, const vector<char> board,
				bool& is_limit)
{
	bool ai_last = false;
	bool player_last = false;
	int utility = 0;
	int ai_count = 0;
	int player_count = 0;
	int space_count = 0;
	int check_down = 0;
	int mini = numeric_limits<int>::min();
	int maxi = numeric_limits<int>::max();
	int row = 0;

	for (int i = 0; i < rows; i++)
	{
		row = i;
		row *= (columns);
		while (row != -1)
		{
			if (board[row] == 'X')
			{
				if (player_last)
					utility -= (player_count*(10+(player_count*player_count)));
				ai_count++;
				ai_last = true;
				player_last = false;
				if (ai_count == r && space_count == 0) // if the winning move is found stop there and return the max value
				{
					is_limit = true;
					return maxi;
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
				if (player_count == r && space_count == 0) // if the losing move is found stop there and return the min value
				{
					is_limit = true;
					return mini;
				}
				ai_count = 0;
				space_count = 0;
			}
			row = move(row, columns, rows, "right");
		}


	}
	return utility;
}

// function used to check the diagnols and return a utility
// based on the heuristic
//int check_diagonals (const int columns, 
//						const int rows, const int r, const vector<char> board,
//						bool& is_limit, const int starting_value,
//						const string direction)
//{
//	bool ai_last = false;
//	bool player_last = false;
//	int utility = 0;
//	int ai_count = 0;
//	int player_count = 0;
//	int space_count = 0;
//	int check_down = 0;
//	int diaganol = 0;
//	int mini = numeric_limits<int>::min();
//	int maxi = numeric_limits<int>::max();
//
//	// check the down right diagonals 
//	for (int i = starting_value; i <= columns - r; i++)
//	{
//		diaganol = i;
//		while (diaganol != -1)
//		{
//			if (board[diaganol] == 'X')
//			{
//				if (player_last)
//					utility -= (player_count*(10+(player_count*player_count)));
//				ai_count++;
//				ai_last = true;
//				player_last = false;
//				if (ai_count == r && space_count == 0) // if the winning move is found stop there and return the max value
//				{
//					is_limit = true;
//					return numeric_limits<double>::max();
//				}
//				player_count = 0;
//				space_count = 0;
//			}
//			else if (board[diaganol] == '-')
//			{
//				if (ai_last)
//				{
//					check_down = move(diaganol, columns, rows, "down");
//					if (check_down != -1)
//					{
//						if (board[check_down] != '-')
//							utility += 10;
//					}
//				}
//				else if (player_last)
//				{
//					check_down = move(diaganol, columns, rows, "down");
//					if (check_down != -1)
//					{
//						if (board[check_down] != '-')
//							utility -= 10;
//					}
//				}
//				else
//					;
//				space_count++;
//				if (space_count > 1)
//				{
//					if(ai_last)
//						utility += (ai_count*(10+(ai_count*ai_count)));
//					
//					else if (player_last)
//						utility -= (player_count*(10+(player_count*player_count)));
//					player_count = 0;
//					ai_count = 0;
//				}
//			}
//			else
//			{
//				if (ai_last)
//					utility += (ai_count*(10+(ai_count*ai_count)));
//				player_count++;
//				player_last = true;
//				ai_last = false;
//				if (player_count == r && space_count == 0) // if the losing move is found stop there and return the min value
//				{
//					is_limit = true;
//					return numeric_limits<double>::min();
//				}
//				ai_count = 0;
//				space_count = 0;
//			}
//			diaganol = move(diaganol, columns, rows, direction);
//		}	
//		return utility;
//	}
//}

void AI::score_state (state_space& current_state)
{
	int columns = current_state.columns;
	int rows = current_state.rows;
	int r = current_state.r;
	bool is_limit = false;
	vector<char> board  = current_state.board;
	int utility = 0;
	int temp;

	temp = check_columns(columns, rows, r, board, is_limit);
	if (is_limit)
	{
		current_state.utility = temp;
		return;
	}
	utility += temp;

	temp = check_rows(columns, rows, r, board, is_limit);
	if (is_limit)
	{
		current_state.utility = temp;
		return;
	}

	utility += temp;

	current_state.utility = utility;
}

