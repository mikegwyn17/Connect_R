#include "Board_2.h"
#include "Board_Tree.h"
#include <time.h>
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

	cout << "Enter number of columns ";
	number_of_columns = read_int();
	cout << endl;

	cout << "Enter the number of rows ";
	number_of_rows = read_int();
	cout << endl;

	cout << "Enter the number required to win ";
	r = read_int();
	cout << endl;

	srand (time(NULL));
	Board_Tree* tree = new Board_Tree();
	Board_2* board = new Board_2();
	board->Build_Board(number_of_columns,number_of_rows,r);
	/*tree->build(*board);*/
	string output = board->to_string();
	cout << output << '\n';
	//while (cont)
	//{
		/*cout << "Choose column to play in (0 - " << number_of_columns-1 << "): ";*/
		/*player_move = read_int();*/
		int random = (rand() % number_of_columns);
		for (int i = 0; i < 3; i++)
		{
			board->play(random,'x');
			random = (rand() % number_of_columns);
			board->play(random,'o');
			random = (rand() % number_of_columns);
		}
		
		output = board->to_string();
		cout << output << endl;
		cout << board->check_board(true,'x') << endl;
		//cout << "('quit' to exit) : ";
		//getline(cin, input);
		//if (input == "quit")
		//	cont = false;
//	}
	cout << "Press ENTER to continue...";
  	cin.ignore( numeric_limits<streamsize>::max(), '\n' );
	return 1;
};