/*************************************
Program: command.h
Course: Data Structures and Algorithms
Year: 2008/09 Trimester 3
Name: LEE SOH YEE
ID: 1081102579
Lecture: TC103
Lab: TC206
Email: foreversuperfishlee@yahoo.com
Phone: 012-3632249
*************************************/

#ifndef TABLE_H
#define TABLE_H

#include <string>
using namespace std;

// Class for store the data and the operation on data.
class table
{
    private:
        struct Node
        {
            string* data;           // Attributes of the table.
            Node *next;
        };

        int length;					// The size of the table.
        Node *head;
        Node *find(int index) const;	//Return a pointer to the index-th node in the list.
		int NumAttribute;			// Store the number of the attribute created for data.
		string tableName;			// Store the table name.

    public:
        table();					// Default contructor.
        table(string *attribute, int NumAttribute, string tableName);		// Constructor.
        table(table& a, int b, string sortKey);			// Copy constructor with sorting.
		~table();					// Destructor.To reallocate memory.
        bool isEmpty() const;		// Return true if the table is empty.
        int size() const;			// Return the size of the table.
        void insert(string *value);	// Insert the data into the list.
        void remove(int index);		// Remove the Node that is the index from the table.
        void retrieve (int index, string a[]);		// Retrieve the content of the index-th Node
													// and store it to the array a.
		void update (int index, int column, 		// Update the data for i-th index and j-th column.
		             const string& newdata);		
		int NumDynamicData ();		// Return the NumAttribute.
		string name();				// Return the name of the table.
};

// Class for process the command in the file.
class ProcessCommand
{
	private:
		void getValidCommand(string& command, int& line);		// Ignore everything before first valid word is found.
                                                                // E.g. INSERT, SELECT...
		void checkValid(string command, size_t found);			// Check whether the command contain other command or not.
																// Specially for checking missing ';' in a command line.
		void FirstLine(string& command);						// Special method for first line in the file to eliminate everything
																// until the first command is found.
	public:
		void GetLine(ifstream& in);			// Get the command from file and process it.
};

class create
{
	private:
		void checkPrimaryKey (const string& a, size_t find2);      			// Check the existence of PRIMARY KEY in first attribute.
	public:
        string* createOperation (string& command, string& tableName,    	// Operation for create command.
								int& NumAttribute, fstream& dictionary);	// Return the attribute string to the constructor. 							  
};

class insert
{
	private:
		void checkSpace (const string& command, table& table1);		// Check there is atleast a space between "INSERT INTO table_name"
		void data_line (const string& command, string& data);       // Get the data line between '(' and ')' out from command.
		void divide_data (const string& data, fstream& dictionary,  // Get each data from the data line and store it.
                          table& table1);
	public:
		void insertOperation (const string& command, table& table1, fstream& dictionary); 
};

class select
{
	private:
		int check_attribute(const string& data);	// Check whether the attribute list is valid or not.
													// Return the number of select attribute.
		string* get_attribute (string& data, int number_of_attribute, 		// Get each selected attribute from the SELECT command.
							   table& table1, fstream&);
										   
		void draw_line (string* attribute, int number_of_attribute, 		// Draw the line for the table.
						table& table1, fstream& dictionary);
		void display_data (int i, string* attribute, 						// Display the data in table in i-th index in table.
						   int number_of_attribute, table& table1, fstream& dictionary);
		void without_where (string* attribute, table& table1, 				// The operation for without WHERE condition.
							int number_of_attribute, fstream& dictionary);	
		void with_where (string& data, const string& command, size_t find1, // The operation for with WHERE condition.
						 table& table1, string* attribute, 
						 int number_of_attribute, fstream& dictionary);
		void search_type (fstream& dictionary, 								// Get the type of the attribute.
		                  const string& condition, bool& str_type);			// (STRING or NUMBER).
	public:
		void get_condition_data (fstream& dictionary, string& a, string& condition,			// Get the condition data if it has WHERE condition.
								 string& value);	
		void select_operation (string command, string data, 				// The whole select operation.
							   table& table1, fstream& dictionary);
};

class mydelete
{
	private:
		void checkDelete(const string& command, table& table1);			// Check the delete command whether is valid or not.
		void checkAndRemove(const string& condition, 					// Remove the tuples if the condtion match.
							const string& value, table& table1);
	public:
		void deleteOperation(fstream& dictionary, string command, table& table1);			// Delete operation for the delete command.
};

class drop
{
	private:
		void checkDrop(string& command, table& table1);			// Check whether the command is valid or not.
	public:
		void dropTable(string& command, table& table1);			// Drop table operation.
};

class update
{
	private:
		void checkUpdate(const string& command, table& table1);		// Check the update command whether is valid or not.
	public:
		void updateOperation(fstream& dictionary, string command, table& table1);
		
};

// Convert the string to uppercase.
void upperCase (string& a);

// Check whether the string is all space or not.If not the program will exit.
void allSpace (const string& a);

// Show error message and exit if the command is invalid.
void invalid();

#endif
