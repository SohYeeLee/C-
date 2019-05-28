/*************************************
Program: command.cpp
Course: Data Structures and Algorithms
Year: 2008/09 Trimester 3
Name: LEE SOH YEE
ID: 1081102579
Lecture: TC103
Lab: TC206
Email: foreversuperfishlee@yahoo.com
Phone: 012-3632249
*************************************/

#include "command.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>          // For exit.
#include <iomanip>
using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CLASS TABLE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//**************************
// Default constructor.    *
//**************************
table::table()
{
    head = new Node;
    head->next = NULL;
    head->data = new string;
    length = 0;
	NumAttribute = 1;
	tableName = "No name";
}

//***********************************************************************
// Constructor.Initialize head,length and store the attribute names.    *
//***********************************************************************
table::table(string *attribute, int NumAttribute, string name)
{
    head = new Node;
    head->data = attribute;
    head->next = NULL;
    length = 0;
	this->NumAttribute = NumAttribute;
	tableName = name;
}

//***************************************************************************************
// Copy constructor with sorting.It will copy either ascendingly(NumAttribute = 1),     *
// or descendingly(NumAttribute = 2), or no change(NumAttribute = 0) to the new table.  *
//***************************************************************************************
table::table(table& a, int b, string sortKey)
{
	length = 0;						// Set new table's length = 0.
	NumAttribute = a.NumAttribute;	// NumAttribute is same with old table.
	tableName = a.tableName;
	
	head = new Node;
	string* p = new string[NumAttribute];		
	a.retrieve(0, p);				// Copy the attributes list as a head for the new table.
	head->data = p;
	head->next = NULL;
	
	// No sorting, insert according to old table.
	if (b == 0)
	{	
		for (int i = 1; i <= a.size(); i++)
		{
			p = new string[NumAttribute];
			a.retrieve(i, p);
			insert(p);
		}
	}
	
	// Sort ascendingly or descendingly."1" is ascendingly, "2" is descendingly.
	else if (b == 1 || b == 2)
	{
		int column = -1;			// For storing the location(column) of the sort key.
		a.retrieve(0, p);			// Get attributes list out.
		for (int i = 0; i < NumAttribute; i++)		// Find location of sort key.
		{
			if (p[i] == sortKey)
				column = i;
		}
		
		// Cannot find the sort key among the attributes.
		if (column == -1)
		{
			cout << "Invalid sort key for SELECT command." << endl;
			cout << "The table will sort according to first attribute(" << p[0] << ")" << endl;
			column = 0;
		}
		
		// Insert and sort the contents of old table into new table.
		for (int i = 1; i <= a.size(); i++)
		{
			bool correct = false;				// Stop for inserting new data if the location is correct.
			p = new string[NumAttribute];		
			
			a.retrieve(i, p);					// Get the data of old table.
			string *q;
			Node* Ptr = new Node;
			Ptr->data = p;
			Node* prev = head;
			Node* cur = head->next;
					
			while (cur != NULL && !correct)
			{
				bool alldigit = true;			// For checking whether the string is all digit.
				q = cur->data;					// Point to the current data in new table.
					
				// For special case like phone number. 012-3333333 is not number,is string.	
				if (q[column][0] != '-' && !isdigit(q[column][0]))
					alldigit = false;

				if ( !isdigit(p[column][0]) && p[column][i] != '-')
						alldigit = false;
						
				for (int j = 1; j < q[column].size(); j++)		// Check whether the currect data is number.
				{
					if (!isdigit(q[column][j]) && !isspace(q[column][j]) && q[column][j] != '.' )
						alldigit = false;
				}
						
				for (int i = 1; i < p[column].size(); i++)		// Check whether the old table data is number.
				{
					if (!isdigit(p[column][i]) && !isspace(p[column][i]) && p[column][i] != '.' )
						alldigit = false;
				}
				
				if (b == 1)			// Insert ascendingly.
				{
					if (!alldigit)	// If the strings are not numbers,we can use string compare.
					{
						if (p[column] < q[column])
							correct = true;
					}

					else if (alldigit)	// If both strings are numbers,convert it to number first.
					{
						if (atof(p[column].c_str()) < atof(q[column].c_str()))
							correct = true;
					}
				}
				
				else if (b == 2)		// Insert descendingly.
				{
					if (!alldigit)		// If the strings are not numbers,we can use string compare.
					{
						if (p[column] > q[column])
							correct = true;
					}

					else if (alldigit)	// If both strings are numbers,convert it to number first.
					{
						if (atof(p[column].c_str()) > atof(q[column].c_str()))
							correct = true;
					}
				}
				
				if (!correct)
				{
					prev = cur;
					cur = cur->next;
				}
			}
			Ptr->next = cur;
			prev->next = Ptr;
			q = NULL;		// To prevent the content that it pointed to being deleted.
			length++;
		}		
		p = NULL;			// To prevent the content that it pointed to being deleted.
	}
}

//********************************************
// Destructor.Reallocate the memory          *
//********************************************
table::~table()
{
    while(!isEmpty())
        remove(1);
    delete head;        // Delete the attribute name.
    head = NULL;
}

//**************************************************************
// Return a pointer to the index-th node in the list.          *
//**************************************************************
table::Node *table::find(int index) const
{
    if (index < 0 || index > size())
        return NULL;

    else
    {
        Node *cur = head;
        for (int i = 0; i < index; i++)
            cur = cur->next;
        return cur;
    }
}

//************************************************
// Return true if the list is empty.             *
//************************************************
bool table::isEmpty() const
{
    return length == 0;
}

//************************************************
// Return the size of the table.                 *
//************************************************
int table::size() const
{
    return length;
}

//************************************************
// Insert data into the link.                    *
//************************************************
void table::insert(string* value)
{
    Node *newPtr = new Node;

    if (newPtr == NULL)
    {
        cout << "Memory cannot be allocated!The program will exit now!" << endl;
        exit(1);
    }

    else
    {
        Node *cur = head;
        Node *prev = NULL;

        while (cur != NULL)     // Insert to the end of the link.
        {
            prev = cur;
            cur = cur->next;
        }
        newPtr->data = value;
        newPtr->next = cur;
        prev->next = newPtr;

        length++;
    }
}

//************************************************
// Remove the node from the list.                *
//************************************************
void table::remove(int index)
{
    Node *cur = head;
    if (isEmpty())
    {
        cout << "The list is empty.The program will exit now!" << endl;
        exit(1);
    }
    else
    {
        length--;

        Node *prev = find (index - 1);
        cur = prev->next;
        prev->next = cur->next;

        cur->next = NULL;
		string *temp = cur->data;			// Delete the dynamic allocated memory for data.
		delete[] temp;
		temp = NULL;
        delete cur;
        cur = NULL;
    }
}

//************************************************
// Retrieve the data of the node from the link.  *
//************************************************
void table::retrieve (int index, string a[])
{
    if ( index < 0 || index > size())
    {
        cout << "Index out of range!The program will exit now!" << endl;
        exit(1);
    }

    Node* cur = find(index);
	for (int i = 0; i < NumAttribute; i++)
		a[i] = cur->data[i];
}

//**************************************************************
// Update the new data by inserting it's index and column.     *
//**************************************************************
void table::update (int index, int column, const string& newdata)
{
	if ( index < 0 || index > size())
    {
        cout << "Index out of range!The program will exit now!" << endl;
        exit(1);
    }

    Node* cur = find(index);
	string *p = cur->data;
	p[column] = newdata;
}

//*********************************
//Return the NumAttribute.        *
//*********************************
int table::NumDynamicData()
{
	return NumAttribute;
}

//**************************************
// Return the name of the table.       *
//**************************************
string table::name()
{
	return tableName;
}


//~~~~~~~~~~~~~~~~~~~~~~~ CLASS PROCESSCOMMAND ~~~~~~~~~~~~~~~~~~~~~~~~

//*****************************************************************
// Eliminate everything before first valid command is found.      *
//*****************************************************************
void ProcessCommand::getValidCommand(string& command, int& line)
{
    line++;
	
	string temp = command;
	upperCase(temp);
	
	size_t find1 = temp.find("INSERT");
	size_t find2 = temp.find("SELECT");
    size_t find3 = temp.find("CREATE");
    size_t find4 = temp.find("DROP");
    size_t find5 = temp.find("DELETE");
	size_t find6 = temp.find("UPDATE");

    if (line == 1)              // The first command must be "create table".
    {
		// CREATE command found.
        if (find3 != string::npos)
		{	
			checkValid(temp, find3);
            command = command.substr(find3);
		}

        else
        {
            // Check the string is just space but not other sql command.
            for (int i = 0; i < command.size(); i++)
            {
                if (!isspace(command[i]))
                {
                    cout << "No table found.The program will exit!." << endl;
					exit(1);
                }
            }
        }
    }
	
    else
    {
        // Create command found but another table is already created.
        if (find3 != string::npos)
        {
			checkValid(temp, find3);
            cout << "Maximum 1 table can be created only.The program will exit now!" << endl;
            exit(1);
        }

        // INSERT command found in the string.
        else if (find1 != string::npos)
		{
			checkValid(temp, find1);
            command = command.substr(find1);			
		}

        // SELECT command found in the string.
        else if (find2 != string::npos)
		{
			checkValid(temp, find2);
            command = command.substr(find2);		
		}

        // DROP command.
        else if (find4 != string::npos)
        {
			checkValid(temp, find4);
            command = command.substr(find4);
            line = 0;               // Reset back the line.		
        }

        // DELETE command.
        else if (find5 != string::npos)
		{
			checkValid(temp, find5);
            command = command.substr(find5);			
		}
		
		// UPDATE command.
		else if (find6 != string::npos)
		{
			checkValid(temp, find6);
			command = command.substr(find6);
		}
    }
}

//*****************************************************************
// Check whether the command contain another command or not.      *
// Specially for checking missing ';' in each command line.       *
//*****************************************************************
void ProcessCommand::checkValid(string command, size_t found)
{
	// The case where before the command there is another command.
	if (found > 0)
	{
		string a = command.substr(0, found - 1);
		allSpace(a);		// Check whether the string is all space or not.If not the program will exit.
	}
	
	// Check the case where after the command the is another command.
	command = command.substr(found + 1);
	size_t find1 = command.find("INSERT");
	size_t find2 = command.find("SELECT");
	size_t find3 = command.find("CREATE");
	size_t find4 = command.find("DROP");
	size_t find5 = command.find("DELETE");
	size_t find6 = command.find("UPDATE");
	
	if ( find1 != string::npos || find2 != string::npos || find3 != string::npos || 
	     find4 != string::npos || find5 != string::npos || find6 != string::npos )
	{
		cout << "Missing ';' among the command line" << endl;
		invalid();
	}
}

//**************************************************************
// Special method for first line in the file to                *
// eliminate everything until the first command is found.      *
//**************************************************************
void ProcessCommand::FirstLine(string& command)
{
	string a = command;
	upperCase(a);
	size_t find1 = a.find("INSERT");
	size_t find2 = a.find("SELECT");
	size_t find3 = a.find("CREATE");
	size_t find4 = a.find("DROP");
	size_t find5 = a.find("DELETE");
	size_t find6 = a.find("UPDATE");
	
	if ( find1 != string::npos || find2 != string::npos || find4 != string::npos || 
	     find5 != string::npos || find6 != string::npos)
		invalid();
	
	else if (find3 != string::npos)
		command = command.substr (find3);
}

//*********************************************
// Get command from file and process it.      *
//*********************************************
void ProcessCommand::GetLine(ifstream& in)
{
    string command;		    // Store the command.
	string data;

	int row = 0;		    // Store the number of command line that had been process.
	
	getline(in, command, ';');
	FirstLine(command);		// Ignore everything before a first command is found.
		
	while(!in.fail())
	{
		data.clear();
		getValidCommand (command, row);		// Ignore everything until the first command found.

		// Get the first word in the command.
		for( int i = 0; isalpha(command[i]); i++)
			data = data + command[i];
			
		upperCase(data);			// Convert all the alphabets to uppercase.

		if (data == "CREATE")
		{
		    string tableName;       // Store the table name.
            int NumAttribute = 0;	// Store the number of attribute created.
		    create x;				// Create a class create object.
		    fstream dictionary;
		    dictionary.open("data dictionary.txt", ios::out);	// Data dictionary.

		    if (dictionary.fail())
            {
                cout << "Create file fail.The program will exit now!" << endl;
                exit(1);
            }
			
			// Create the table.
            string *constructor = x.createOperation(command, tableName, NumAttribute, dictionary);
            table table1(constructor, NumAttribute, tableName);
            cout << "TABLE " << tableName << " created." << endl << endl;

            dictionary.close();
			
			// After the table is created.
            while(!in.fail() && data != "DROP")
            {
                if (data == "INSERT")
                {
                    insert x;
                    x.insertOperation (command, table1, dictionary);
                }

                else if (data == "SELECT")
				{
					select x;
                    x.select_operation (command, data, table1, dictionary);
				}
				
                else if (data == "DELETE")
				{
					mydelete x;
					x.deleteOperation(dictionary, command, table1);
				}
				
				else if (data == "UPDATE")
				{
					update x;
					x.updateOperation(dictionary, command, table1);
				}
				
				else
				{
					// The command is wrong.
					if (row > 1)
						allSpace(data);		// Check whether the string is all space or not.If not the program will exit.
				}
				
                getline(in, command, ';');
				
                if (!in.fail())
                {
                    data.clear();
                    getValidCommand(command, row);

                    // Get the first word in the command.
                    for( int i = 0; isalpha(command[i]); i++)
                        data = data + command[i];
					
					upperCase(data);
                }
            }				
            if (data == "DROP")
            {
				drop x;
				x.dropTable(command, table1);
			}
        }
		else		// If the string is not a command.Invalid.
			allSpace(data);
			
		getline(in, command, ';');
	}
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CLASS CREATE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//**********************************************************************************
// Operation for create command.Return the attribute string to the constructor.    *
//**********************************************************************************
string* create::createOperation (string& command, string& tableName, int& NumAttribute, fstream& dictionary)
{
    NumAttribute = 0;			// The actual number of the attribute created.
    stringstream s;				// For checking space in the command.
	string x[4];				// For storing the data stream from string stream.
	string attribute[6];		// For temporary store the attribute name.
	string a;

	s << command;

	for(int i = 0; i < 4; i++)
	{
		s >> x[i];
        upperCase(x[i]);
	}

	if (x[0] != "CREATE" || x[1] != "TABLE" || x[3] != "(")
	{
		cout << "Wrong command for CREATE" << endl;
		invalid();
	}

    tableName = x[2];

    // Get the data inside the '(' and ')' of the command.
    size_t find1 = command.find('(');
    size_t find2 = command.rfind(')');

    if (find1 != string::npos && find2 != string::npos)
    {
        string b[4];            // Store the divided data in the string.
        find2 = find2 - find1;
        command = command.substr(find1 + 1, find2 - 1);		// Get the string between '(' and ')'.
        upperCase(command);
        command = command + ',';		// Add the colon to the last line in create function.

        find1 = command.find(',');

        while (find1 != string::npos)
        {
            a.clear();
            a = command.substr(0, find1);				// Get the string before first ','
            command = command.substr(find1 + 1);		// Get the string after ','
			
            // Check whether the command has more than 1 colon for each line.
            bool twocolon = true;
            for (int i = 0; i < a.size(); i++)
            {
                if (isalnum(a[i]))
                    twocolon = false;
            }

            if (twocolon)
			{
				cout << "There is 2 ',' or there is a ',' in the last line in CREATE command." << endl;
                invalid();
			}

            stringstream ss;
            ss << a;

            ss >> b[0] >> b[1];
			
            // To check the situation where there is no space between "STRING" and '('
            find1 = a.find("STRING(");
			
			if (b[1] == "NUMBER")
            {
                // Check the existence of PRIMARY KEY.
                if (NumAttribute == 0)
                {
					ss >> b[2] >> b[3];
					if (b[2] != "PRIMARY" || b[3] != "KEY")
						invalid();
                }
                dictionary << b[0] << "\tNUMBER\t num" << endl;		// Output to data dictionary.
				find2 = a.find("NUMBER");			// For later checking purpose.
				find2 = find2 + 5;
			}
			
            // The type of the attribute is string.
            else if (b[1] == "STRING" || find1 != string::npos)
            {
                find1 = a.find('(');
                find2 = a.find(')');

                if (find1 != string::npos && find2 != string::npos)
                {
                    string temp = a.substr(find1 + 1, find2 - find1 - 1);		// Get the size of type string between '(' and ')'.
                    int sizeofAtt = atoi(temp.c_str());

                    if (sizeofAtt < 1 || sizeofAtt > 40)
                    {
                        cout << "Invalid size for the string.The size should just between "
                             << "1 and 40.";
                        invalid();
                    }

                    // Check whether got word "PRIMARY KEY" or not.
                    if (NumAttribute == 0)
                        checkPrimaryKey (a, find2);

                    dictionary <<  b[0] << "\tSTRING\t" << sizeofAtt << endl;		// Output to data dicitonary file.
                }

                // There is no '(' and ')' to include the size of attribute.
                else
                    invalid();
            }
			
            // The type of the attribute is not string or number.
            else
			{
				cout << "The type should be either STRING type or NUMBER type only." << endl;
                invalid();
			}
			
			if (NumAttribute == 0)
			{
				find2 = a.find("KEY");		// For later checking purpose.
				find2 = find2 + 2;
			}

			// To check the case that after ',' there remain other string behind it.
			for (int i = static_cast<int>(find2 + 1); i < a.size(); i++)
			{
				if (!isspace(a[i]))
				{
					cout << "Miss 1 ',' in the create command." << endl;
					invalid();
				}
			}

            attribute[NumAttribute] = b[0];
            NumAttribute++;
            find1 = command.find(',');
        }
	
        if (NumAttribute > 6)
        {
            cout << "Invalid.Maximum 6 attributes can be supported in CREATE only." << endl;
            invalid();
        }

        // Store the attribute name to a pointer.
        string *con = new string[NumAttribute];
        for (int i = 0; i < NumAttribute; i++)
            con[i] = attribute[i];
        
		return con;
    }

    // Incorrect syntax for command "CREATE".
    else
	{
		cout << "Syntax error for CREATE command." << endl;
        invalid();
	}
}

//***********************************************************
// Check the existence of PRIMARY KEY in first attribute    *
//***********************************************************
void create::checkPrimaryKey (const string& a, size_t find2)
{
    size_t find1 = a.find ("PRIMARY");
    if (find1 == string::npos)
    {
        cout << "No primary key in the first attribute for CREATE command!";
        invalid();
    }

    string temp = a.substr(find2 + 2);
    stringstream s;
    string z[2];
    s << temp;
    s >> z[0] >> z[1];
    if ( z[0] != "PRIMARY" || z[1] != "KEY")
	{
		cout << "Spelling error for PRIMARY KEY" << endl;
        invalid();
	}
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CLASS INSERT ~~~~~~~~~~~~~~~~~~~~~~~~~~~

//******************************************************************
// Check there must a least a space between "INSERT INTO table".   *
//******************************************************************
void insert::checkSpace(const string& command, table& table1)
{
	stringstream s;
	string space[3];
	string a = command;
	size_t find1;
	
	upperCase(a);
	
	s << a;
	s >> space[0] >> space[1] >> space[2];
	find1 = space[2].find(table1.name() + ")");		// The case that there is no space between the '(' and the table name.

	if (space[0] != "INSERT" || space[1] != "INTO" || (space[2] != table1.name() && find1 == string::npos))
	{
		cout << "Invalid command for insert!" << endl;
		invalid();
	}
}

//************************************************
// Get the line of data between '(' and ')'      *
//************************************************
void insert::data_line(const string& command, string& data)
{
	size_t find1 = command.rfind('(');
	size_t find2 = command.rfind(')');
	size_t find3 = command.find('(');
	size_t find4 = command.find(')');
	
	data.clear();
	if (find1 != string::npos && find2 != string::npos)		// Get the data inside ( ).
	{
	    if (find3 == string::npos || find4 == string::npos ||
            find3 == find1 || find2 == find4)
            invalid();

        find2 = find2 - find1;
  		data = command.substr (find1 + 1, find2 - 1);		// Take out the data without ( ).
	}
}

//************************************************
// Get each data from data line and store it.    *
//************************************************
void insert::divide_data (const string& data, fstream& dictionary, table& table1)
{
    dictionary.open("data dictionary.txt", ios::in);
	string subdata;
	string *temp = new string [table1.NumDynamicData()];	// Store the insert data.
	int i = 0;
  	int z = 0;
	string d[3];			// For storing data read from file.

  	if (dictionary.fail())
  	{
  	    cout << "Open data dictionary file fail.The program will exit now!" << endl;
  	    exit(1);
  	}
	
  	while ( i < data.size())
	{
		subdata.clear();
		dictionary >> d[0] >> d[1] >> d[2];
		
		while (isspace(data[i]) && i < data.size())		// Eliminate all the space.
			i++;
		
		// The case where NULL is inserted.
		if (data[i] == 'N' || data[i] == 'n')
		{
			while (data[i] != ',' && i < data.size())
			{
				subdata = subdata + data[i];
				i++;
			}
			upperCase(subdata);
			
			if (subdata == "NULL")
				subdata = " ";
				
			else
			{
				cout << "Invalid command in INSERT" << endl;
				invalid();
			}
		}
		
		else if (d[1] == "STRING")
		{
			// If it is string type, the next character must be '"'.
			if (data[i] != '"')
			{
				cout << "No \" mark to include the string type data in INSERT." << endl;
				invalid();
			}
					
			// Get all the data inside '"'.
			else
			{
				i++;
				while (data[i] != '"' && i < data.size())		// Form the string for value.
				{
					subdata = subdata + data[i];
					i++;
				}
				
				if (data[i] != '"')			// The case where i = data.size() and no '"' to enclose the data.
				{			
					cout << "No \" mark to include the string type data in INSERT." << endl;
					invalid();
				}
				
				i++;
			}
		}
			
		// Number type
		else if (d[1] == "NUMBER")
		{
			while ((isdigit(data[i]) || data[i] == '-' || data[i] == '.') 
			        && i < data.size() && data[i] != ',')
			{
				subdata = subdata + data[i];
				i++;
			}
		}
		
		while (data[i] != ',' && i < data.size())
		{
			if (!isspace(data[i]) && data[i] != ',')
			{
				cout << "Wrong command in INSERT" << endl;
				cout << "Perhaps there is wrong type of data to be inserted" << endl;
				invalid();
			}
			i++;
		}
		i++;
				
		if (d[1] == "NUMBER")
		{
			double n = atof(subdata.c_str());

			if ( (n >= -999999.99 && n <= 999999.99 ) || subdata == " ")
				temp[z] = subdata;

			else
			{
				cout << "One of the price is out of range,it will set to null." << endl;
				temp[z] = " ";
			}
		}

		else if (d[1] == "STRING")
		{
			if (subdata.size() <= atoi(d[2].c_str()))
			{
				if (z == 0 && subdata == " ")
				{
					cout << "Primary key cannot be NULL in INSERT!" << endl;
					invalid();
				}
				temp[z] = subdata;
			}
			else
			{
				cout << "Size of data is out of range!It should not "
					 << "greater than " << d[2] << endl;
				invalid();
			}
		}
		z++;
	}

	if (z != table1.NumDynamicData())
        invalid();

    table1.insert(temp);
	dictionary.clear();		// Clear the flag.
	dictionary.close();
}

//**********************
// Insert operation.   *
//**********************
void insert::insertOperation(const string& command, table& table1, fstream& dictionary)
{
	string data;
	
	checkSpace(command, table1);		// Make sure there is a least a space between "INSERT" "INTO" "TABLE"
	data_line(command, data);			// Get the data line out.
    divide_data(data, dictionary, table1);		// Divide the data line, and insert into the table.
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CLASS SELECT ~~~~~~~~~~~~~~~~~~~~~~~~~~~

//*******************************************************
// Check whether the attribute list is valid or not.    *
// Return the number of select attribute.               *
//*******************************************************
int select::check_attribute(const string& data)
{
	int count = 0;		// For the attribute in SELECT command.
	
	// Check invalid character in the command.
	for(int i = 0; i < data.size(); i++)
	{
		if ( (!isalpha(data[i])) && (!isspace(data[i])) && 
			  data[i] != ',' && data[i] != '*' )
		{
			cout << "Wrong command for SELECT" << endl;
			invalid();
		}
		
		if (data[i] == ',')			// count how many attributes are there.
			count++;
	}
	return count + 1;
}

//****************************************************************************
// Get each selected attribute and check the attribute from SELECT command.  *
//****************************************************************************
string* select::get_attribute (string& data, int number_of_attribute, table& table1, fstream& dictionary)
{
	string *attribute = new string [number_of_attribute];		// Storing selected attributes.
	string sub;				// Storing each selected attribute.
	int i = 0;
	int j = 0;
	
	while ( i < data.size())
	{
		sub.clear();
		
		// Get all the space.
		while ( !isalpha(data[i]) && data[i] != '*' && i < data.size() )
			i++;					
		
		if (data[i] == '*')
		{
			sub = sub + data[i];
			i++;
		}
		
		// Get the word formed.
		while ( isalpha(data[i]) && i < data.size())
		{
			data[i] = toupper(data[i]);
			sub = sub + data[i];				// Form the selected attribute.
			i++;
		}		
		
		if (!sub.empty())
		{				
			// Check for repeated attribute.
			for (int k = 0; k < j; k++)
			{
				if (attribute[k] == sub)
				{
					cout << "Cannot select repeated attributes in SELECT command." << endl;
					invalid();
				}
			}
			
			// Check whether the string sub is the attribute name or not.
			if (sub != "*")
			{
				bool found = false;	
				string a[3];
				dictionary.open("data dictionary.txt", ios::in);

				for (int k = 0; k < table1.NumDynamicData(); k++)
				{
					dictionary >> a[0] >> a[1] >> a[2];
					if (sub == a[0])
						found = true;
				}
				dictionary.clear();		// Clear the flag.
				dictionary.close();
				
				if (!found)
				{
					cout << "The attribute name in SELECT command is wrong!" << endl;
					invalid();
				}
			}					
			attribute[j] = sub;									
			j++;
		}
	}
	return attribute;
}

//***************************************
// Draw line for table while display.   *
//***************************************
void select::draw_line(string* attribute, int number_of_attribute, table& table1, fstream& dictionary)
{
	string a[table1.NumDynamicData()];	// Store the attribute name.
	table1.retrieve(0, a);				// Get the attributes' name in the created table.
	dictionary.open("data dictionary.txt", ios::in);
	string d[3];						// For store the size of the attribute from file.
	
	if (dictionary.fail())
	{
		cout << "Cannot open the file.The program will exit now.";
		exit(1);
	}
	
	for(int k = 0; k < number_of_attribute; k++)
	{
		for (int l = 0; l < table1.NumDynamicData(); l++)
		{
			dictionary >> d[0] >> d[1] >> d[2];
			if (attribute[k] == a[l])
			{	
				// The type is number.
				if (d[1] == "NUMBER")
					cout << "-------------";
				
				// The type is string.
				else
				{
					for (int m = 0; m < atoi(d[2].c_str()) + 3; m++)
						cout << "-";
				}
			}
		}
		dictionary.seekp(0, ios::beg);
	}
	cout << "-" << endl;
	dictionary.clear();			// Clear the flag.
	dictionary.close();
}

//*************************************************
// Display the data for SELECT command.           *
//*************************************************
void select::display_data (int i, string* attribute, int number_of_attribute, table& table1, fstream& dictionary)
{
	string d[3];					// Store the strings that read from the file.
	string a[table1.NumDynamicData()];
	
	table1.retrieve(i, a);			// Retrieve the i-th index data and store in a.

	for (int j = 0; j < number_of_attribute; j++)
	{	
		dictionary.open("data dictionary.txt", ios::in);
		if (dictionary.fail())
		{
			cout << "Open file fail.The program will exit now!" << endl;
			exit(1);
		}
		for (int m = 0; m < table1.NumDynamicData(); m++)
		{
			dictionary >> d[0] >> d[1] >> d[2];
			if (attribute[j] == d[0] && d[1] == "STRING")	// Show attribute name & data.
				cout << "| " << left << setw(atoi(d[2].c_str())) << a[m] << " ";			
		
			else if (attribute[j] == d[0] && d[1] == "NUMBER")
			{
				if (i == 0)		// Show the attribute name.
					cout << "| " << left << setw(10) << a[m] << " ";
				else			// The data is the number which is align to right.
					cout << "| " << right << setw(10) << showpoint << setprecision(2) << fixed << atof(a[m].c_str()) << " ";
			}
		}
		dictionary.clear();
		dictionary.close();
	}
	cout << "|";
	cout << endl;
}

//*********************************************
// Operation for without WHERE condition.       *
//*********************************************
void select::without_where ( string* attribute, table& table1, int number_of_attribute, fstream& dictionary)
{
	cout << table1.name() << endl;
	
	// Display the attributes.
	if (!table1.isEmpty())
	{
		draw_line (attribute, number_of_attribute, table1, dictionary );					
		display_data (0, attribute, number_of_attribute, table1, dictionary);
		draw_line (attribute, number_of_attribute, table1, dictionary );
	}
	
	// Display the data in the table.
	for (int i = 1; i <= table1.size(); i++)						
		display_data (i, attribute, number_of_attribute, table1, dictionary);
	
	if (!table1.isEmpty())
		draw_line(attribute, number_of_attribute, table1, dictionary);

	cout << table1.size() << " rows selected." << endl << endl;
}

//*******************************************
// The operation for where condition.       *
//*******************************************
void select::with_where (string& data, const string& command, size_t find1, table& table1, string* attribute, int number_of_attribute, fstream& dictionary)
{
	bool valid = true;
	string value;			// value of the where condition part.
	string condition;		// where condition attribute.	
	string a[table1.NumDynamicData()]; 	// Store the data that read from table.
	int line = 0;						// count how many rows are displayed.
	int column = 0;						// Store the location of the attribute that fit.
	
	data.clear();
	data = command.substr(find1 + 5);		// Get the string out after "WHERE"
	get_condition_data (dictionary, data, condition, value);	// Get the condition(attribute) and its value.

	table1.retrieve(0, a);
	cout << table1.name() << endl;
	
	for (int i = 0; i < table1.NumDynamicData(); i++)
	{
		if (condition == a[i])
			column = i;
	}
	
	for (int i = 1; i <= table1.size(); i++)	// Display the data if the condition is fit.
	{
		table1.retrieve(i, a);
		if (value == a[column])
		{
			if (line == 0)
			{
				draw_line(attribute, number_of_attribute, table1, dictionary);										
				display_data (0, attribute, number_of_attribute, table1, dictionary);			
				draw_line(attribute, number_of_attribute, table1, dictionary);
			}
			display_data (i, attribute, number_of_attribute, table1, dictionary);
			
			line++;
		}
	}
	
	if (line > 0)
		draw_line(attribute, number_of_attribute, table1, dictionary);
	
	cout << line << " rows selected." << endl << endl;					
}

//*************************************************
// Get the type of the attribute.                 *
// Set Str_type = true if the type is STRING.     *
//*************************************************
void select::search_type (fstream& dictionary, const string& condition, bool& str_type)
{
	dictionary.open("data dictionary.txt");
	
	if(dictionary.fail())
	{
		cout << "File cannot be opened." << endl;
		cout << "The program will exit now! " << endl;
		exit(1);
	}
	
	string a[3];
	dictionary >> a[0] >> a[1] >> a[2];
	
	while (a[0] != condition && !dictionary.fail())
		dictionary >> a[0] >> a[1] >> a[2];
	
	if (a[0] != condition && dictionary.fail())		// The case where the attribute in WHERE is wrong.
	{
		cout << "Wrong attribute in WHERE condition." << endl;
		invalid();
	}
		
	if (a[1] == "NUM")
		str_type = false;

	else if (a[1] == "STRING")
		str_type = true;
	
	dictionary.clear();
	dictionary.close();
}

//***************************************************
// Get the attribute name and its value for WHERE   *
//***************************************************
void select::get_condition_data (fstream& dictionary, string& a, string& condition, string& value)
{
	int i = 0;
	bool str_type;			// Check the type of the attribute.
	
	while (i < a.size())
	{
		// Eliminate all the space.
		while (isspace(a[i]) && i < a.size())
			i++;
		
		// Condition(attribute) must be alphabet.
		while (isalpha(a[i]) && i < a.size())
		{
			condition = condition + a[i];
			i++;
		}
		upperCase(condition);

		while (isspace(a[i]) && i < a.size())
			i++;
		
		// The next character should be '='.If it is '=', perform following operation.
		if (a[i] == '=')
		{
			i++;			// Get next character.	
			while(isspace(a[i]) && i < a.size())
				i++;
			
			// Get the type of the attribute.
			search_type(dictionary, condition, str_type);

			// String type.
			if (str_type)
			{
				// If it is string type, the next character must be '"'.
				if (a[i] != '"')
				{
					cout << "No \" mark to include the string type data." << endl;
					invalid();
				}
				
				// Get all the data inside '"'.
				else
				{
					i++;
					while (a[i] != '"' && i < a.size())		// Form the string for value.
					{
						value = value + a[i];
						i++;
					}
					
					if (a[i] != '"')	// Check the case where i = a.size() and no another '"' to enclose the data.
					{
						cout << "No \" mark to include the string type data." << endl;
						invalid();
					}
					i++;
				}
			}
			
			// Number type
			else if (!str_type)
			{
				while ((isdigit(a[i]) || a[i] == '-' || a[i] == '.') && i < a.size())
				{
					value = value + a[i];
					i++;
				}
			}

			while (isspace(a[i]) && i < a.size())
				i++;
		}
		
		// If after operation the i is not the last index of string a, means the command is wrong.
		if ( i < a.size() || condition.empty() || value.empty())
		{
			cout << "Invalid command for command that have WHERE condition." << endl;
			cout << "Perhaps the operator for WHERE is not '=' or the data type is wrong." << endl;
			invalid();
		}
	}
}

//******************************************
// Operation for SELECT command.           *
//******************************************
void select::select_operation (string command, string data, table& table1, fstream& dictionary)
{	
	string all;
	stringstream ss;				// For checking whether selected table exist or not.
	string name;					// Check the name of table is correct or not.
	string x[4];					// For storing the "ORDER BY ATTRIBUTE ASC/DESC" string.
	int sort = 0;					// Sort number for constructor."1" is copy ascendingly,"2" is copy descendingly.
	string upper = command;			// For convert all the alphabet in command to uppercase.
	
	upperCase(upper);
	size_t find1 = upper.find("FROM");
	
	// Check whether the selected table name in command exist or not.
	ss << upper.substr(find1 + 5),
	ss >> name;

	if (name != table1.name())
	{
		cout << "Invalid SELECT command.There is no space between 'FROM' and "
		     << "table name or the selected table do not exist." << endl;
		invalid();
	}
	
	// If "FROM" is found.
	if (find1 != string::npos)
	{	
		data.clear();
		data = command.substr(7, find1 - 8);	// Get the data between SELECT and FROM.
		
		int number_of_attribute = check_attribute(data);	// Get the number of SELECTED sttributes.
						
		string *attribute; 		// Array to store those selected attributes.			
		attribute = get_attribute (data, number_of_attribute, table1, dictionary);	
		
		if ( attribute[0] == "*")		// All the attributes are selected.
		{
			all = attribute[0];
			delete[] attribute;
			number_of_attribute = table1.NumDynamicData();
			attribute = new string [number_of_attribute];
			table1.retrieve(0, attribute);			// Get all the attributes from table.
		}
		
		find1 = upper.find("ORDER");				// Find whether got "ORDER BY" or not.
		command = command.substr(0, find1 - 1); 	// Get the string before "ORDER BY".
		
		if (find1 != string::npos)
		{
			stringstream ss;
			string y[table1.NumDynamicData()];		// Store the all the attributes in table.
			bool found = false;						// For checking whether the sort key exist(correct) or not.
			ss << upper.substr(find1 - 1);
			ss >> x[0] >> x[1] >> x[2] >> x[3];
			table1.retrieve(0,y);	
			
			for (int i = 0; i < table1.NumDynamicData(); i++)		// Check whether the sort key correct or not.
			{
				if (x[2] == y[i])
					found = true;
			}
			
			// The command is correct.
			if (found && x[0] == "ORDER" && x[1] == "BY" && (x[3] == "ASC" || x[3] == "DESC"))
			{
				if (x[3] == "ASC")
					sort = 1;
					
				else if (x[3] == "DESC")
					sort = 2;	
			}
			
			// The command is incorrect.
			else
			{
				cout << "Wrong command for ORDER BY in SELECT command." << endl;
				invalid();
			}
			
		}
		
		else if (find1 == string::npos)		// Cannot find "ORDER BY" in the string.
			sort = 0;
			
		table table2(table1, sort, x[2]);	// Create a copy of the table1 for display.
		
		find1 = upper.find("WHERE");
		
		// Command with WHERE condition.
		if(find1 != string::npos)
			with_where (data, command, find1, table2, attribute, number_of_attribute, dictionary);
	
		// Command without where condition.
		else
			without_where (attribute, table2, number_of_attribute, dictionary);

		if (all != "*")
		{
			delete[] attribute;
			attribute = NULL;
		}
	}
	
	// Cannot find FROM,means the command is invalid.
	else		
		invalid();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~ CLASS DELETEROW ~~~~~~~~~~~~~~~~~~~~~~~~~~

//**************************************************************
// Check whether the delete command is valid or not.           *
//**************************************************************
void mydelete::checkDelete(const string& command, table& table1)
{
	stringstream a;
	string temp[4];
	
	a << command;
	a >> temp[0] >> temp[1] >> temp[2] >> temp[3];

	if (temp[0] != "DELETE" || temp[1] != "FROM" || temp[2] != table1.name() || temp[3] != "WHERE" )
	{
		cout << "Invalid command for delete." << endl;
		invalid();
	}
}

//***************************************************************************
// Check the attribute and the value in the table.If match,delete it.       *
//***************************************************************************
void mydelete::checkAndRemove(const string& condition, const string& value, table& table1)
{
	string a[table1.NumDynamicData()];		// For storing the data retrieve from table.
	int line = 0;
	int column;
	table1.retrieve(0, a);					// Retrieve the attribute name.
	int tablesize = table1.size();			// Store the original size of the table.
	
	for (int i = 0; i < table1.NumDynamicData(); i++)
	{
		if (condition == a[i])
			column = i;
	}
	
	for (int j = tablesize; j >=1; j--)
	{
		table1.retrieve(j, a);
		if (value == a[column])
		{
			table1.remove(j);
			line++;
		}
	}

	cout << line << " tuples deleted." << endl << endl;
}

//***********************************************
// Delete operation for the delete command.     *
//***********************************************
void mydelete::deleteOperation(fstream& dictionary, string command, table& table1)
{
	bool valid = true;
	string value;			// value of the where condition part.
	string condition;		// where condition attribute.
	string temp;
	string data;
	select dummy;			// Create dummy object to use the get_condition_data method.
	
	temp = command;
	upperCase(temp);
	checkDelete(temp, table1);				// Check the delete command.
	
	size_t find1 = temp.find("WHERE");
	data = command.substr(find1 + 5);		// Get the string out after "WHERE"
	
	dummy.get_condition_data (dictionary, data, condition, value);		// Get the condition(attribute) and value for WHERE.
	checkAndRemove(condition, value, table1);			
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~ CLASS DROP ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//************************************************
// Check whether the command is valid or not.    *
//************************************************
void drop::checkDrop (string& command, table& table1)
{
	stringstream s;
	string temp[3];
	
	upperCase(command);
	
	s << command;
	s >> temp[0] >> temp[1] >> temp[2];
	
	if (temp[0] != "DROP" || temp[1] != "TABLE" || temp[2] != table1.name())
	{
		cout << "Invalid command for DROP." << endl;
		invalid();
	}
	
	// For checking whether there is any alphabet after the table name.
	size_t find1 = command.find(temp[2]);		
	command = command.substr(find1 + temp[2].size());
	
	for (int i = 1; i < command.size(); i++)
	{
		if (!isspace(command[i]))
		{
			cout << "Invalid command for DROP." << endl;
			invalid();
		}
	}
}

//****************************************
// Operation for drop the table.         *
//****************************************	
void drop::dropTable (string& command, table& table1)
{
	checkDrop(command, table1);		// Check whether the drop command is valid.
	
	if (!table1.isEmpty())
	{
		for (int i = 0; i <= table1.size(); i++)
			table1.remove(1);
	}
	
	cout << "TABLE " << table1.name() << " dropped." << endl << endl;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~ CLASS UPDATE ~~~~~~~~~~~~~~~~~~~~~~~~

//**************************************************************
// Check whether the update command is valid or not.           *
//**************************************************************
void update::checkUpdate(const string& command, table& table1)
{
	stringstream a;
	string temp[3];
	
	a << command;
	a >> temp[0] >> temp[1] >> temp[2];

	if (temp[0] != "UPDATE" || temp[1] != table1.name() || temp[2] != "SET")
	{
		cout << "Invalid command for UPDATE." << endl;
		invalid();
	}
}

//***********************************************
// Update operation for the update command.     *
//***********************************************
void update::updateOperation(fstream& dictionary, string command, table& table1)
{
	bool valid;
	string value_w;			// To store value of the where condition part.
	string condition_w;		// To store where condition attribute.
	string value_s;			// To store the new value to be set.
	string condition_s;		// To store the condition for setting new data.
	string CDL[3];			// For storing data that read from file.
	string data;		
	select dummy;			// Create class select for usage of method "get_condition_data".
	string temp = command;
	int column = 0;			// Store the location(column) of the SET attribute for later update purpose.
	
	upperCase(temp);
	checkUpdate(temp, table1);				// Check the update command.
	
	size_t find1 = temp.find("SET");
	size_t find2 = temp.find("WHERE");
	
	data = command.substr(find1 + 3, find2 - find1 - 3);			// Get the string out after "WHERE".
	dummy.get_condition_data (dictionary, data, condition_s, value_s);	// Get SET attribute and value.
	data = command.substr(find2 + 6);								// Get the string after WHERE
	dummy.get_condition_data (dictionary, data, condition_w, value_w);	// Get WHERE attribute and value.
	
	// Search the length of the data allowed for the attribute.
	dictionary.open("data dictionary.txt");
	
	dictionary >> CDL[0] >> CDL[1] >> CDL[2];
	
	while (CDL[0] != condition_s)
	{
		dictionary >> CDL[0] >> CDL[1] >> CDL[2];
		column++;
	}
	
	// If the data(string type) to be SET is bigger the length allowed.
	if (CDL[1] == "STRING" && value_s.size() > atoi(CDL[2].c_str()))
	{
		cout << "The new data to be set is too long in UPDATE." << endl;
		cout << "It should not exceed " << CDL[2] << endl;
		cout << "The new data will be set to NULL." << endl;
		value_s = " ";
	}
	
	// If the data is number type and it exceed the range.
	else if (CDL[1] == "NUMBER" && (atof(value_s.c_str()) > 999999.99 || atof(value_s.c_str()) < -999999.99))
	{
		cout << "The new number to be set is out of range." << endl;
		cout << "It will set to 0." << endl;
		value_s = " ";
	}
	
	dictionary.close();
	
	string a[table1.NumDynamicData()];		// For storing the list of attribute.
	string d[table1.NumDynamicData()];		// For storing the list of data.
	int line = 0;
	table1.retrieve(0, a);					// Retrieve the attribute name.

	for (int i = 0; i < table1.NumDynamicData(); i++)
	{	
		for (int j = 1; j <= table1.size(); j++)
		{	
			table1.retrieve(j, d);		
			
			if(condition_w == a[i] && value_w == d[i])		// If attribute and value fit.
			{
				table1.update(j, column, value_s);
				line++;
			}
		}
	}
	cout << line << " tuples updated." << endl << endl;
}

//********************************************************
// Convert the char of the string to uppercase.          *
//********************************************************
void upperCase (string& a)
{
    for (int i = 0; i < a.size(); i++)
        a[i] = toupper(a[i]);
}

// Check whether the string is all space or not.If not the program will exit.
void allSpace (const string& a)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (!isspace(a[i]))
			invalid();
	}
}

//************************************************************
// Show error message and exit if the command is invalid.    *
//************************************************************
void invalid()
{
	cout << "Invalid command.The program will exit now!" << endl;
	exit(1);
}
