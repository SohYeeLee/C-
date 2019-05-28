/*************************************
Program: zip.cpp
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
#include <fstream>		// For file.
#include <string>
#include <vector>
#include <cstdlib>		// For atoi, exit.
#include <cctype>		// For ispunct, isalnum
#include <ctime>		// For time function.
using namespace std;


//***********************************************************************
//   Display the size of file before and after compress and time taken. *
//***********************************************************************
void zip::size_time() const
{
	cout << "Size before (de)compression \t:" << (end1 - start1) <<" bytes" << endl;
	cout << "Size after (de)compression  \t:" << (end2 - start2) << " bytes" << endl;
	cout << "Time taken for (de)compression \t:" << (clock() - start) * 1000 / CLOCKS_PER_SEC
	 	 << " miliseconds" << endl;
}

//*************************************************
//   Get end of the file position for 2 files.    *
//*************************************************
void zip::get_position(ifstream& x, ofstream& y)
{
	x.clear();					
	x.seekg(0, ios::end);
	end1 = x.tellg();			// Get the end file position of x.
	y.seekp(0, ios::end);
	end2 = y.tellp();			// Get the end file position of y.
}

//************************************************************************
// Constructor.Open the files.                                           *
// o is original file name.c is compress file name.i is index file name. *
//************************************************************************
compress::compress(const string& o, const string& c, const string& i)
{
	in.open(o.c_str());
	com.open(c.c_str());
	index.open(i.c_str());
	
	// If 1 of the file cannot be opened.
	if (in.fail() || com.fail() || index.fail())
	{
		cout << "Cannot open 1 of the file.The program will now exit." << endl;
		exit(1);
	}	
}

//************************************
// Destructor.Close the files.       *
//************************************
compress::~compress()
{
	in.close();
	com.close();
	index.close();
}

//**************************************************************
// Get the character to form word while the condition fulfill. *
//**************************************************************
bool compress::getWord()
{
	return ( (isalnum(temp) || (word.size() < 3 && 
			 (isalnum(temp) || temp == '\'' || temp == ' ' )) ) && !in.fail() );
}

//***********************************************************************************
// Ensure all the characters in string is number or char.                           *
// To avoid adding words with 2 letters and 1 punctuation(e.g "in.")into the index. *
//***********************************************************************************
bool compress::Check()
{
	for (int i = 0; i < word.size(); i++)
	{
		if (ispunct(word[i]) && word[i] != '\'')	// Need to get word with apostrophe.
		{
			return false;
			break;
		}
	}
	return true;
}

//****************************************
// Forming word while condition fulfill. *
//****************************************
void compress::form_word()			
{
     word.clear();			// Clear all the content in string "word"
  	
  	// Ignore all the punctuation.    	
	while (!isalnum(temp) && !in.fail())
	{
		com << temp;		// Output to compress file.
		in.get(temp);
	}

	while (getWord ())
	{
		word = word + temp;
		in.get(temp);
	}
}
//*********************************************
// Output to compress file with index number. *
//*********************************************
void compress::output()
{
	// Check for the word that has more than 2 letters and it is char or number.
	if (word.size() > 2 && Check())
	{			
		bool found = false;
						
		// Check whether the word is in the array.
		for (int i = 0; i < z.size(); i++)
		{
			if (word == z[i]) 
			{
				found = true;
				com << i + 1;		// Output the index number to compress file.
			}
		}
		
		// If it is not in the array,it is added to the array.					
		if (!found)
		{
			z.push_back(word);		// Add to array.
			com << z.size();		// Output the index number to compress file.
		}
	}	
	else
		com << word;			// Output the word that cannot be replaced with index.
}

//**************************************************
// Copy the content of string into an index file.  *
//**************************************************
void compress::generate_index()
{
	for (int i = 0; i < z.size(); i++)
		index << i + 1 << '\t' << z[i] << endl;
}

//***********************
// Compress the file.   *
//***********************
void compress::compress_file()
{	
	start1 = in.tellg();		// Get the start position.
	in.get(temp);
	start2 = com.tellp();
	start = clock();			// Start counting time.
	
	while (!in.fail())
	{	
		form_word();	
		output();		
	}	
	generate_index();			// Generate index file.
	get_position(in, com);		// Get position of the end of file for in and com.
	size_time();				// Display the size of file and time taken.		
}

//*****************************************************************************
// Constructor.Open the files.                                                *
// c is compress file name, i is index file name, d is decompress file name.  *
//*****************************************************************************
decompress::decompress(const string& c, const string& i, const string& d)
{
	com.open(c.c_str());
	index.open(i.c_str());
	decom.open(d.c_str());
	
	if (com.fail() || index.fail() || decom.fail())
	{
		cout << "Cannot open one of the file.The program will now exit." << endl;
		exit(1);
	}
}

//********************************
// Destructor.Close the files.   *
//********************************
decompress::~decompress()
{
	com.close();
	index.close();
	decom.close();
}

//*********************************************************************
// Get the words in the index file and store into an array of string. *
//*********************************************************************
void decompress::generate_index()
{
	z.clear();					// Clear the array of string.
	string a, c;
	char b;
	
	while (!index.fail())
	{	
		getline(index, a, '\t');
		getline(index, c);		// Get word.
		index >> b;				// Get '\n'.
		z.push_back(c);			// Add to the array.
	}
}	

//*******************************
// Decompress the file.         *
//*******************************
void decompress::decompress_file()
{		
	generate_index();			// Copy the index into a string.
	start1 = com.tellg();		// Get the beginning position of file com.
	start2 = decom.tellp();		// Get the beginning position of file decom.
	com.get(temp);		
	start = clock();			// Start counting time.
	
	while (!com.fail())
	{
		word.clear();
		
		// Get character that other than number.
		while ( (temp < 48 || temp > 57) && !com.fail() )
		{
			decom << temp;
			com.get(temp);			
		}
		
		// Get number only.
		while ( (temp >= 48 && temp <= 57) && !com.fail() )
		{
			word = word + temp;			// Getting the number.
			com.get(temp);
		}
		
		if (word.size() > 0)		
			decom << z[atoi(word.c_str()) - 1];		
	}
	get_position(com, decom);			// Get end file position for com and decom.
	size_time();						// Display the size of file and time taken.
}
