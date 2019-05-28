/*************************************
Program: compress.cpp
Course:  TCP 1241
Year:    2008/09 Trimester 2
Name:    LEE SOH YEE
ID:      1081102579
Lecture: TC101
Lab:     TC201
Email:   foreversuperfishlee@yahoo.com
Phone:   012-3632249
*************************************/

#include "zip.h"
#include <iostream>
#include <cstring>		// For string compare.
#include <cstdlib>		// For exit.
using namespace std;


int main(int b, char* a[])
{	
	if (strcmp(a[1], "help") == 0)
	{
		cout << "\nYour command should be like:" << endl;
		cout << "program_name.exe compress original.txt "
			 << "compress_file.cp1 using index.idx1" << endl;
		cout << "\t =========== OR ===========" << endl;
		cout << "program_name.exe decompress compress_file.cp1 "  
			 << "decompress_file.txt using index.idx1" << endl;
	}
		
	else if (b < 6)
	{
		cout << "Wrong command entered. " << endl;
		cout << "Type \"program_name.exe help\" to view help." << endl;
		exit(1);
	}
	
	// If the second argument is not "compress" or "decompress"
	else if ( strcmp(a[1], "compress") && strcmp(a[1], "decompress") )
	{
		cout << "You must type either \"compress\" or \"decompress\" "
			 << "in second argument." << endl;
	}
		
	else if (strcmp(a[1], "compress") == 0)
	{
		compress c(a[2], a[3], a[5]);
		c.compress_file();
	}
	
	else if (strcmp(a[1], "decompress") == 0)
	{
		decompress d(a[2], a[5], a[3]);	
		d.decompress_file();
	}
	
	return 0;
}
