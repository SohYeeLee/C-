// zip.h
#ifndef ZIP_H
#define ZIP_H

#include <iostream>
#include <fstream>		// For file.
#include <string>
#include <vector>
#include <ctime>		// For time function.
using namespace std;

class zip
{
	protected:
		vector<string> z;			// Store the words in the text file.
		string word;				// Word in the text file.
		char temp;					// Get all letters and number.
		long start1, start2;		// For get the size of the file.
		long end1, end2;			// For get the size of the file.
		clock_t start, end;			// Display the time to complete task.			
		void size_time() const;		// Display the size and time taken
									// before and after compress.
		void get_position(ifstream& x, ofstream& y);   // Get position of end of file.
		virtual void generate_index() = 0;			
};

class compress : public zip
{
	private:
		ifstream in;				// Input file(original file).
		ofstream com;				// Compress file.
		ofstream index;				// Index file.
		bool getWord();				// Get the character while condition fulfill.
		bool Check();				// Ensure all the characters in string 
									// is number or alphabet.
		void form_word();			// Form word until condition fulfill.
		void output();				// Output to the compress file.
		void generate_index();		// Generate the index file.		
	public:
		// Constructor.Open the files.
		compress(const string& o, const string& c, const string& i);
		~compress();				// Destructor.Close the files.
		void compress_file();		// Compress the file.			
};

class decompress : public zip
{
	private:
		ifstream com;				// Compress file.
		ifstream index;				// Index file.
		ofstream decom;				// Decompress file.
		void generate_index();		// Save the index into an array of string.
	public:
		// Constructor.Open the files.
		decompress(const string& c, const string& i, const string& d);
		~decompress();				// Destructor.Close the files.		
		void decompress_file();		// Decompress the file.
};

#endif
