/*************************************
Program: database.cpp
Course: Data Structures and Algorithms
Year: 2008/09 Trimester 3
Name: LEE SOH YEE
ID: 1081102579
Lecture: TC103
Lab: TC206
Email: foreversuperfishlee@yahoo.com
Phone: 012-3632249
*************************************/

#include "command.h"			// Header File.
#include <iostream>
#include <fstream>				// For file.
#include <string>
#include <cstdlib>				// For exit.
#include <cstring>

using namespace std;

int main(int b, char *a[])
{
	system("cls");
	
	if (b < 2) 			// No file name provided
	{
		cout << "No file name provided" << endl;
		cout << "Type \"program_name.exe help\" to view help." << endl;
		cout << "The program will exit now!" << endl;
		exit(1);
	}
	
	if (strcmp(a[1], "help") == 0)
	{
		cout << "\nYour command should be like:" << endl;
		cout << "program_name.exe command_file.txt " << endl;
		exit(0);
	}
	
	ifstream in;
	ProcessCommand x;
	
	in.open(a[1]);
	
	if(in.fail())
	{
		cout << "Open file failed.The program will exit now." << endl;
		exit(1);
	}
	
	x.GetLine(in);		// Execute the command in file.

	in.close();
	return 0;
}
