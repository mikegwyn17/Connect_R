#include "Board.h"
// simple method used to make reading in int values from user easier
int read_int ()
{
	string input = "";
	getline(cin, input);
	int value = atoi(input.c_str());
	return value;
}

int main (void)
{
	bool cont = true;
	unsigned count = 0;
	int player_move = 0;
	int number_of_columns = 0;
	int number_of_rows = 0;
	int r = 0;
	int added_row = 0;
	int added_column = 0;
	string input;

	cout << "Enter the number of rows ";
	number_of_rows = read_int();
	cout << endl;

	cout << "Enter number of columns ";
	number_of_columns = read_int();
	cout << endl;

	cout << "Enter the number required to win ";
	r = read_int();
	cout << endl;

	Board* board = new Board();
	board->Build_Board(number_of_columns,number_of_rows,r);
	string output = board->to_string();
	cout << output << '\n';
	while (cont)
	{
		cout << "Choose column to play in (0 - " << number_of_columns-1 << "): ";
		player_move = read_int();
		board->play(player_move,'x',added_column, added_row);
		count++;
		if (count >= r)
		{
			cout << board->check_board('x',added_column,added_row);
		}
		output = board->to_string();
		cout << output << endl;
		cout << "('quit' to exit) : ";
		getline(cin, input);
		if (input == "quit")
			cont = false;
	}
	system("pause");
	return 1;
};
