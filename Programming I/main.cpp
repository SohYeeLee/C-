/*************************************
Program: TC101_ASG2_LEE_SOH_YEE.cpp 
Course:  TCP 1231
Year:    2008/09 Trimester 1
Name:    LEE SOH YEE
ID:      1081102579
Lecture: TC101
Lab:     TC202
Email:   foreversuperfishlee@yahoo.com
Phone:   012-3632249
*************************************/

#include <iostream>
#include <cstdlib>				// For exit.
#include <fstream>
#include <string>
#include "WinConsole.hpp"		// For colour.
#include <windows.h>			// For music.
#include <ctime>

using namespace std;

bool valid_input = false;
char player = 'X';
char opponent = 'O';
int colour = 0;					// Change colour for display

// Uses iostream:
// Display board.
void display ( char a[8][8], int rowinput, int columninput )
{
	setBackgroundColor(BLACK);
	
	// The colour of the board.		
	if ( colour >= 4 )
		colour = 0;	
	if ( colour % 4 == 0 )
		setForegroundColor(CYAN);
	else if ( colour % 3 == 0 )
		setForegroundColor(PINK);
	else if ( colour % 2 == 0 )
		setForegroundColor(YELLOW);		
	else 
		setForegroundColor(GREEN);
	colour++;
		
	for ( int i = 0; i < 8; i++ )
	{
		cout << "  +---+---+---+---+---+---+---+---+ " << endl;
		cout << i + 1 << " ";
		for ( int j = 0; j < 8; j++ )
		{
			if ( rowinput == i && columninput == j )
				cout << "|["  << a[i][j] << "]";		// The input will be mark [ ] after flip.
			else
				cout << "| "  << a[i][j] << " ";
		}
			
		cout << "| ";
		cout << endl;
	}
	cout << "  +---+---+---+---+---+---+---+---+ " << endl;
	cout << "    A   B   C   D   E   F   G   H   "  << endl;	
}

// Swap Player.
// Precondition : The player is playing the game.
// Postcondition : Change to his opponent to play the game.
void swap ( char& player, char& opponent )
{	
	char temp;
	temp = player;
	player = opponent;
	opponent = temp;
}

// Check column downward.
// Precondition : The input given is within the limit.
// Postcondition : If the situation is correct for column downward,player will change the opponent pieces to his one.
void down ( char a[8][8],int rowinput, int columninput, char player, char opponent, bool isUpdate = true )
{
	if ( a[rowinput + 1][columninput] == opponent )
	{
		for ( int i = rowinput + 1; i < 7; i++ )
		{
			if ( a[i][columninput] == opponent && a[i + 1][columninput] == ' ' )	// Check whether there is space between the column.
				break;
				
			else if ( a[i][columninput] == opponent && a[i + 1][columninput] == player ) // Check if fullfill the condition.
			{
				if ( isUpdate )
				{
					for ( int z = i; z >= rowinput; z-- )		// Change the opponent pieces.
						a[z][columninput] = player;						
				}
				valid_input = true;	
				break;	
			}	
		}	 
	}
}

// Check column upward.
// Precondition : The input given is within the limit.
// Postcondition : If the situation is correct for column upward,player will change the opponent pieces to his one.
void up ( char a[8][8],int rowinput, int columninput, char player, char opponent, bool isUpdate = true )
{
	if ( a[rowinput - 1][columninput] == opponent )
	{
		for ( int i = rowinput - 1; i > 0; i-- )
		{
			if ( a[i][columninput] == opponent && a[i - 1][columninput] == ' ' )	// Check whether there is space between the column.
				break; 
				
			else if ( a[i][columninput] == opponent && a[i - 1][columninput] == player ) // Check if fullfill the condition.
			{
				if ( isUpdate )
				{
					for ( int z = i; z <= rowinput; z++ )		// Change the opponent pieces.
						a[z][columninput] = player;	
				}
				valid_input = true;
				break;	
			}	
		}	 
	}
}

// Check row leftward.
// Precondition : The input given is within the limit.
// Postcondition : If the situation is correct for row leftward,player will change the opponent pieces to his one.
void left ( char a[8][8],int rowinput, int columninput, char player, char opponent, bool isUpdate = true )
{
	if ( a[rowinput][columninput - 1] == opponent )
	{
		for ( int j = columninput - 1; j > 0; j-- )
		{
			if ( a[rowinput][j] == opponent && a[rowinput][j - 1] == ' ' )	// Check whether there is space between the column.
				break; 
				
			else if ( a[rowinput][j] == opponent && a[rowinput][j - 1] == player ) // Check if fullfill the condition.
			{				
				if ( isUpdate )
				{
					for ( int z = j; z <= columninput; z++ )		// Change the opponent pieces.
						a[rowinput][z] = player;	
				}
				valid_input = true;		
				break;
			}	
		}	 
	}
}

// Check row rightward.
// Precondition : The input given is within the limit.
// Postcondition : If the situation is correct for row rightward,player will change the opponent pieces to his one.
void right ( char a[8][8],int rowinput, int columninput, char player, char opponent, bool isUpdate = true )
{
	if ( a[rowinput][columninput + 1] == opponent )
	{
		for ( int j = columninput + 1; j < 7; j++ )
		{
			if ( a[rowinput][j] == opponent && a[rowinput][j + 1] == ' ' )	// Check whether there is space between the column.
				break; 
				
			else if ( a[rowinput][j] == opponent && a[rowinput][j + 1] == player ) // Check if fullfill the condition.
			{
				if ( isUpdate )
				{
					for ( int z = j; z >= columninput; z-- )		// Change the opponent pieces.
						a[rowinput][z] = player;
				}	
				valid_input = true;
				break;		
			}	
		}	 
	}
}

// Check TopLeft.
// Precondition : The input given is within the limit.
// Postcondition : If the situation is correct for TopLeft,player will change the opponent pieces to his one.
void top_left ( char a[8][8],int rowinput, int columninput, char player, char opponent, bool isUpdate = true )
{
	if ( a[rowinput - 1][columninput - 1] == opponent )
	{
		int i = rowinput - 1;
		int j = columninput - 1;
		
		while ( i > 0 && j > 0 )
		{
			if ( a[i][j] == opponent && a[i - 1][j - 1] == ' ' )	// check whether there is space between the column.
				break; 
				
			else if ( a[i][j] == opponent && a[i - 1][j - 1] == player ) // Check if fullfill the condition.
			{
				if ( isUpdate )
				{
					while ( i <= rowinput && j <= columninput )		// Change the opponent pieces. 
					{
						a[i][j] = player;	
						i++;
						j++;
					}
				}
				valid_input = true;		
				break;
			}
			i--;
			j--;
		}
	}	 
}

// Check DownRight
// Precondition : The input given is within the limit.
// Postcondition : If the situation is correct for DownRight,player will change the opponent pieces to his one.
void down_right ( char a[8][8],int rowinput, int columninput, char player, char opponent, bool isUpdate = true )
{
	if ( a[rowinput + 1][columninput + 1] == opponent )
	{
		int i = rowinput + 1;
		int j = columninput + 1;
		
		while ( i < 7 && j < 7 )
		{
			if ( a[i][j] == opponent && a[i + 1][j + 1] == ' ' )	// Check whether there is space between the column.
				break; 
				
			else if ( a[i][j] == opponent && a[i + 1][j + 1] == player ) // Check if fullfill the condition.
			{
				if ( isUpdate )
				{
					while ( i >= rowinput && j >= columninput )		// Change the opponent pieces.
					{
						a[i][j] = player;	
						i--;
						j--;
					}
				}
				valid_input = true;		
				break;
			}
			i++;
			j++;
		}
	}	 
}

// Check DownLeft.
// Precondition : The input given is within the limit.
// Postcondition : If the situation is correct for DownLeft,player will change the opponent pieces to his one.
void down_left ( char a[8][8],int rowinput, int columninput, char player, char opponent, bool isUpdate = true )
{
	if ( a[rowinput + 1][columninput - 1] == opponent )
	{
		int i = rowinput + 1;
		int j = columninput - 1;
		
		while ( i < 7 && j > 0 )
		{
			if ( a[i][j] == opponent && a[i + 1][j - 1] == ' ' )	// Check whether there is space between the column.
				break; 
				
			else if ( a[i][j] == opponent && a[i + 1][j - 1] == player ) // Check if fullfill the condition.
			{
				if ( isUpdate )
				{
					while ( i >= rowinput && j <= columninput )		// Change the opponent pieces.
					{
						a[i][j] = player;	
						i--;
						j++;
					}
				}
				valid_input = true;		
				break;
			}
			i++;
			j--;
		}
	}	 
}

// Check TopRight.
// Precondition : The input given is within the limit.
// Postcondition : If the situation is correct for TopRight,player will change the opponent pieces to his one.
void top_right ( char a[8][8],int rowinput, int columninput, char player, char opponent, bool isUpdate = true )
{
	if ( a[rowinput - 1][columninput + 1] == opponent )
	{
		int i = rowinput - 1;
		int j = columninput + 1;
		
		while ( i > 0 && j < 7 )
		{
			if ( a[i][j] == opponent && a[i - 1][j + 1] == ' ' )	// Check whether there is space between the column.
				break; 
				
			else if ( a[i][j] == opponent && a[i - 1][j + 1] == player ) // Check if fullfill the condition.
			{
				if ( isUpdate )
				{
					while ( i <= rowinput && j >= columninput )		// Change the opponent pieces.
					{
						a[i][j] = player;	
						i++;
						j--;
					}
				}
				valid_input = true;		
				break;
			}
			i--;
			j++;
		}
	}	 
}

// Check input valid.
// Precondition : Any input is given.
// Postcondition : If the input given is within the limit,it will continue to following steps,else the input will be rejected.
bool check_valid ( char a[8][8], int rowinput, int columninput )
{	
	if ( (rowinput < 0 || rowinput > 7) || (columninput < 0 || columninput > 7) )
		return false;
		 
	if ( a[rowinput][columninput] != ' ' )				
		return false;
		
	else
		return true;
}	

// Check whether the player still has move or not.
// Precondition : The situation of the board is given.
// Postcondition : If players still can move,it will proceed to next steps,else it will pass back to his opponent.
bool is_miss_turn( char a[8][8], char player, char opponent )
{		
	for ( int i = 0; i < 8; i++ )
	{
		for ( int j = 0; j < 8; j++ )
		{
			valid_input = check_valid ( a, i, j );
			
			if ( valid_input )
			{	
				valid_input = false;					
				down ( a, i, j, player, opponent, false );
				up (  a, i, j, player, opponent, false );
				left ( a, i, j, player, opponent, false );
				right ( a, i, j, player, opponent, false );
				top_left ( a, i, j, player, opponent, false );
				down_right ( a, i, j, player, opponent, false );
				down_left ( a, i, j, player, opponent, false );
				top_right ( a, i, j, player, opponent, false );
			}
			
			if ( valid_input )
				return false;
		}
	}
	return true;
}

// Check who is the winner.
// Precondition : The amount of the pieces on the board is given.
// Postcondition : The player that have the more pieces on the board is the winner.
void win_status ( int x, int o, ofstream& out_stream )
{
	out_stream << endl;
	
	if ( x > o )
	{
		cout << "Player (X) win!" << endl;
		out_stream << "Player (X) win!" << endl;
	}
	else if ( o > x )
	{
		cout << "Player (O) win!" << endl;
		out_stream << "Player (O) win!" << endl;
	}			
	else
	{
		cout << "Draw game!" << endl;
		out_stream << "Draw game!" << endl;
	}
	
	system ("pause");
}

// Check whether the game is end or not.
// Precondition : The situation of game is given.
// Postcondition : If do not match the end game condition,the game will continue,else the game will end.				 
bool end_game ( char a[8][8], int x, int o, int& k, int& u )
{	
	bool isPlayerMissTurn = is_miss_turn( a, player, opponent );
				
	if ( x == 0 || o == 0 )
		return true;
	else if ( x + o == 64 )
		return true;
					
	// player miss turn
	else if ( isPlayerMissTurn )
	{
		cout << "Player ("<< player << ") do not have valid move!" << endl;
		cout << "Pass back to player (" << opponent << ")" << endl;
		swap ( player, opponent );			
		u = 1;			// for write to file.
		k++;			// For write to file.
		
		// find out whether the next player also miss turn
		bool isNextPlayerMissTurn = is_miss_turn(a, player, opponent);
		
		if ( isNextPlayerMissTurn )
		{
			cout << "Player ("<< player << ") do not have valid move!" << endl;
			cout << "Both Player do not have valid move.End Game!" << endl;
		}
		if ( isPlayerMissTurn && isNextPlayerMissTurn )
			return true;
	}
	
	else
	return false;
}

// Count the move and the pieces on the board.
// Precondition : The situation on the board is given.
// Postcondition : The move and the pieces of each player will be counted and show to player.
void count ( char a[8][8], int& x, int& o, int move, int rowinput, int columninput )
{
	x = 0, o = 0;
	for ( int i = 0; i < 8; i++ )
	{
		for ( int j = 0; j < 8; j++ )
		{
			if ( a[i][j] == 'X' )
				x++;
			if ( a[i][j] == 'O' )
				o++;
		}
	}		
	system("cls");
	display ( a, rowinput, columninput );
	
	setBackgroundColor(LIGHTGRAY);
	setForegroundColor(BLACK);
	
	cout << endl;			
	cout << "Moves: " << move << endl;
	cout << "Status:" << "\t" << "X:" << x << "\t" << " O:" << o << endl;
}

// Write to the file.
// Precondition : The valid input is given.
// Postcondition : valid input will be written to the file.
void file_output (int& k, ofstream& out_stream, string input, int& u )
{
	if ( k == 0 )
		out_stream << "player (X)" << "\t" << "player (O)" << endl << "==========\t==========" << endl;
	
	if ( u == 1 )				// If the player do not have valid move.
	{
		if ( k % 2 == 0 )
		{
			out_stream << endl;
			out_stream << input[0] << input[1];
		}		
		else
			out_stream << "\t\t" << input[0] << input[1] << endl;
	}	
	
	else
	{
		if ( k % 2 == 0 )
			out_stream << input[0] << input[1];	
		else
			out_stream << "\t\t" << input[0] << input[1] << endl;
	}			
	k++;
	u = 0;
}

// Clean the garbage value in array and reset the game.
// Precondition : The board is filled with garbage value.
// Postcondition : The board is clear and ready for new game.
void clean_and_set ( char a[8][8] )
{
	// Clean all the garbage value in array.
	for ( int i = 0; i < 8; i++ )
	{
		for ( int j = 0; j < 8; j++ )
		a[i][j] = ' ';
	}
	
	a[3][3] = a[4][4] = 'X';
	a[3][4] = a[4][3] = 'O';
}

int main ()
{
	char a[8][8]; 
	int rowinput, columninput;			// Input given will be convert to rowinput and columninput 
	int x, o;							// X and O is the number of the pieces on the board.
	int move;							// The moves of the game.
	int k, u ;							// k and u is for file_output function.
	char choice;						// Choice of the main menu.
	int second_delay;					// The second delay for the replay.
	char save_file[20], open_file[20];	// Read and Write file name.
	string dummy;						// Get the input that is useless from file.
	string input;						// Input from user.
	time_t time1, time2;				// For time delay in replay.
	ifstream in_stream;
	ofstream out_stream;
	
	setConsoleTitle("Reversi Game");
	setConsoleSize(60, 30);			
	
	do
	{	
		setBackgroundColor(BLUE);		
		setForegroundColor(CYAN);
		system("cls");
		cout << "Welcome to Reversi Board Game!" << endl;	
		cout << "1. Play a two player game" << endl;
		cout << "2. Load a game record file" << endl;
		cout << "3. Quit" << endl;
		cout << "Enter your choice ( 1 - 3 ) : ";
		cin >> choice;
		cin.ignore(1000,'\n');			
		
		if ( choice == '1' )
		{
			k = 0;				// For write into file.
			move = 1;
			cout << "File name for game record file (maximum 20 characters) :";
			cin >> save_file;		
			
			out_stream.open ( save_file );
			
			if ( out_stream.fail())
			{
				cout << "Output file opening failed." << endl;
				cout << "The program will exit now." << endl;
				exit(1);
			}
			
			setBackgroundColor(DARKBLUE);			
			columninput = 1000, rowinput = 1000;				// To clear the [ ] on the previous board. 
			
			// Initialize the game.	
			clean_and_set ( a );
			count ( a, x, o, move, rowinput, columninput );		// Show the start game condition.
			cout << endl;
			
			// Reset game data.
            player = 'X';					
            opponent = 'O';
            
            // Play music.
            PlaySound("music.wav", NULL,  SND_LOOP | SND_ASYNC);
	    	for (int i = 0; i < 50000; i++)
	   	 	{
	        // does nothing.
	    	}
            			
			do
			{																																												
				do
				{														
					cout << "Player ("<< player << ") enter input ( A1 - H8 ) --> ";
					cin >> input;					
					input[0] = toupper(input[0]); 		// Accept small or big capital as input.
					columninput = input[0] - 65;
					rowinput = input[1] - 49;
					
					valid_input = check_valid ( a, rowinput, columninput );	// Check whether the input given is out of range.
					
					if ( valid_input )
					{								
						valid_input = false;						
						// Check 8 direction.					
						down ( a, rowinput, columninput, player, opponent );
						up (  a, rowinput, columninput, player, opponent );
						left ( a, rowinput, columninput, player, opponent );
						right ( a, rowinput, columninput, player, opponent );
						top_left ( a, rowinput, columninput, player, opponent );
						down_right ( a, rowinput, columninput, player, opponent );
						down_left ( a, rowinput, columninput, player, opponent );
						top_right ( a, rowinput, columninput, player, opponent );
					}
											
					if (!valid_input )
						cout << "Invalid input.Please reenter again." << endl;			
				
				}while (!valid_input);
				
				setBackgroundColor(DARKBLUE);															
				move++;											// Count the moves.							
				count ( a, x, o, move, rowinput, columninput );	// Show the board.
				file_output ( k, out_stream, input, u );		// Write to file.	
				swap ( player, opponent );						
						
			} while ( !end_game(a, x, o , k, u ) );
							
			//display winning status.	
			win_status(x, o, out_stream );
			
			PlaySound(NULL, NULL,  SND_LOOP);
			out_stream.close();				
		}
		
		else if ( choice == '2' )
		{
			// Reset game data.
            player = 'X';					
            opponent = 'O';
            
			columninput = 1000, rowinput = 1000;		// To clear the [ ] on the previous board. 
			move = 1;									// Initialize the move back to 1.
			cout << "File name for game record file : ";
			cin >> open_file;
			cout << "How many seconds of delay ( 1 - 10 ) : ";
			cin >> second_delay;

			in_stream.open ( open_file );
			if ( in_stream.fail())
			{
				cout << "Input file opening failed." << endl;
				cout << "The program will exit now." << endl;
				exit(1);
			}
			
			// Read first 2 dummy sentences from file
			for ( int i = 0; i < 2; ++i )
				getline(in_stream, dummy);	
						
			// Initialize the start situation of the game.
			clean_and_set ( a );
			
			setBackgroundColor(BLUE);
			
			count ( a, x, o, move, rowinput, columninput );
			
			while ( in_stream >> input )
			{				
				if ( input.size() == 2 )		// Just get the input that only 2 char.
				{	
					time(&time1);															
					if ( is_miss_turn(a, player, opponent) )
					{
						cout << "Player ("<< player << ") do not have valid move!" << endl;
						cout << "Pass back to Player (" << opponent << ")" << endl;
						swap( player, opponent );
					}	
					
					cout << "Player ("<< player << ") enter input ( A1 - H8 ) --> ";
					cout << input;										
					columninput = input[0] - 65;
					rowinput = input[1] - 49;
					
					do
					{	
						time(&time2);
					}while ( time2 - time1 < second_delay );
												
					down ( a, rowinput, columninput, player, opponent );
					up (  a, rowinput, columninput, player, opponent );
					left ( a, rowinput, columninput, player, opponent );
					right ( a, rowinput, columninput, player, opponent );
					top_left ( a, rowinput, columninput, player, opponent );
					down_right ( a, rowinput, columninput, player, opponent );
					down_left ( a, rowinput, columninput, player, opponent );
					top_right ( a, rowinput, columninput, player, opponent );
					
					setBackgroundColor(BLUE);																				
					move++;				// Count the moves.							
					count ( a, x, o, move, rowinput, columninput );
					swap ( player, opponent );			
				}
				else
					break;					
			}
			win_status(x, o, out_stream );	
			in_stream.close();				
		}
		
		else if ( choice == '3' )
			exit (0);
					
		else
		{
			cout << "Invalid input.Please enter the correct choice." << endl;
			system("pause");
		}
							
	}while ( choice != '1' || choice != '2' || choice != '3' );
			
	return 0;
}
