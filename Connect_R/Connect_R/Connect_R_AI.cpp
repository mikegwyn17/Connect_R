#include "Connect_R_AI.h"
#include <time.h>
// simple method used to make reading in int values from user easier
int read_int ()
{
	string input = "";
	getline(cin, input);
	int value = atoi(input.c_str());
	return value;
}

// method used to move around the board which is vector of chars
int move_ai (int index, const int columns, int rows, string type)
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

Connect_R_AI::Connect_R_AI()
{
	max_depth = 9;
	move_location = -1; 
	min_value = numeric_limits<int>::min();
	max_value = numeric_limits<int>::max();
}

Connect_R_AI::Connect_R_AI(Board_2* b)
{
	max_depth = 9;
	move_location = -1; 
	min_value = numeric_limits<int>::min();
	max_value = numeric_limits<int>::max();
	board = *b;
}

Connect_R_AI::~Connect_R_AI()
{
	// TODO implement destrcutor
	cout << "destructor" << endl;
}

void Connect_R_AI::opponent_move ()
{
	int column = 0;
	cout << "What is your move? " << endl;
	column = read_int();
	board.play(column, 'O');

}

int Connect_R_AI::result_of_game (Board_2 b) const
{
	// TODO return if game is complete and who won the game
	return 0;
}



int Connect_R_AI::check_board (Board_2 b, const bool is_turn) const
{
	// TODO implement heuristic 
	srand(time(NULL));
	return rand()%100;
}

void Connect_R_AI::maximize (board_tree& tree, int depth)
{
	// TODO method to check if the game is over

	if ( depth == max_depth)
	{
		// TODO method to run the heuristic
	}

	int m = min_value;
	int number_of_children = tree.children.size();
	for (int i = 0; i < number_of_children; i++)
	{
		;
	}
}


int Connect_R_AI::get_AI_move()
{
	return 0;
}

board_tree Connect_R_AI::play (board_tree& tree, const int column, const bool is_turn)
{
	// check the top of the column to see if it is full, if so it is an illeagal move
	int rows = tree.columns;
	int columns = tree.rows;
	int to_play = column;
	vector<char> board = tree.board.board;
	
	to_play = ((rows*columns) - columns) + column; // start at the bottom of the board in the given column
	while (board[to_play] != '-')
	{
		to_play = move_ai(to_play, columns, rows, "up");
	}
	if (is_turn)
		board[to_play] = 'X';
	else
		board[to_play] = 'O';
	board_tree new_tree (tree);
	return new_tree;
}

void Connect_R_AI::play_AI ()
{
	int player_move = -1;
	string user_choice = "";
	cout << "Would you like to play first? (y/n)" << endl;
	getline(cin, user_choice);
	if (user_choice == "y")
		opponent_move();
	board.play(3,'X');
	cout << board.to_string() << endl;
	while (true)
	{
		opponent_move();
		cout << board.to_string() << endl;
		// check to see if game is over
		get_AI_move();
		cout << board.to_string() << endl;
		// check to see if game is over
	}
}

