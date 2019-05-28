#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <iomanip>
#include "WinConsole.hpp"			// For color.

using namespace std;

//**************************************
// Find the number of virtual page.    *
//**************************************
void virtualPage(string input, int& numVirtualPage)
{
	vector<char> temp;

	// Find distinct number of page in the string.
	for (int i = 0; i < input.size(); i++)
	{
		bool found = false;
		for (int j = 0; j < temp.size() && !found; j++)
		{
			if (input[i] == temp[j])
				found = true;
		}
		if (!found)
			temp.push_back(input[i]);
	}
	numVirtualPage = temp.size();
}

//*********************************
// Draw the page fault graph.     *
//*********************************
void drawGraph(int a[], int size)
{
	setForegroundColor(CYAN);

	// Find the maximum scale for y-axis.
	int max = a[0];
	for (int i = 0; i < size; i++)
	{
		if (a[i] > max)
			max = a[i];
	}

	cout << endl << "Number of page faults";	// Title of Y-Axis.

	// Plot the graph.
	for (int i = max; i >= 0; i--)
	{
		cout << endl;

		// Adjust the y-axis scale margin.
		if (i == 0)
			cout << setw(3) << right << i << "-+";
		else
			cout << setw(3) << right << i << "-|";

		bool sameaxis = false;		// To adjust the margin for more than 1 point with same y-value.
		int lastpoint = -1;
		for (int j = 0; j < 3; j++)
		{
			if (a[j] == i)
			{
				if (sameaxis)
				{
					cout << setw((j - lastpoint) * 5);
					lastpoint = j;
				}
				else
				{
					cout << setw((j + 3) *5);
					sameaxis = true;
					lastpoint = j;
				}
				cout << right << "x";		// Plot "x" in the graph to indicate the point.
			}
		}
	}

	// Output the X-axis.
	for (int i = 1; i <= 30 ; i++)
	{
		if (i % 5 == 0)
			cout << "+";
		else
			cout << "-";
	}
	cout << endl << "     ";
	cout << setw(5) << "1" << setw(5) << "2" << setw(5) << "3" << setw(5) << "4"
		 << setw(5) << "5" << setw(5) << "6" << endl;
	cout << setw(30)  << "Number of frames" << endl;		// X-Axis title.

	setForegroundColor(LIGHTGRAY);
}

//****************************************************
// For showing the reference string while output.    *
//****************************************************
void showReferenceString(string input)
{
	setForegroundColor(YELLOW);
	cout << endl << endl << "Reference String : ";

	for (int i = 0; i < input.size(); i++)
		cout << input[i] << " ";
	cout << endl << endl;
	setForegroundColor(CYAN);
}

//************************
// LRU algorithm.        *
//************************
void LRU (string input, int frame, int virtualPage, int& pageFault)
{
	if (virtualPage < frame)
		virtualPage = frame;

	deque <char> M;						// The internal array, M.
	vector<char> output[input.size()];	// For output purpose.

	// For every page in the input string.
	for (int i = 0; i < input.size(); i++)
	{
		bool found = false;

		// Check whether the page is inside the frame.
		for (int j = 0; j < frame && j < M.size() && !found ; j++)
		{
			if (M[j] == input[i])			// If the page is found.
			{
				found = true;
				deque<char>::iterator it = M.begin() + j;
				M.erase(it);				// Erase it in the frame.
			}
		}

		if (M.size() >= virtualPage)	// If the deque size larger than virtualPage.
			M.pop_back();		// Pop the deque for later push_front purpose.

		M.push_front(input[i]);	// Push the current page to the front of the deque.

		// Put all the pages into the vector for later output purpose.
		int k = 0;
		for (k; k < M.size(); k++)
			output[i].push_back(M[k]);

		while (k < virtualPage)		// If the page do not fill the M.
		{
			output[i].push_back(' ');
			k++;
		}

		if (!found)					// If the page is not found in frame, means page fault.
		{
			output[i].push_back('P');
			pageFault++;
		}
		
		else
			output[i].push_back(' ');
	}

	setForegroundColor(WHITE);
	cout << endl << frame << " Frames :" << endl;
	setForegroundColor(GREEN);		// Color for all pages inside frame.

	// Output.
	for (int i = 0; i < virtualPage + 1; i++)
	{
		cout << "  ";
		for (int j = 0; j < input.size(); j++)
			cout << output[j][i] << " ";
		cout << endl;

		if (i == frame - 1)
		{
			for (int k = 0; k < input.size(); k++)
				cout << "--";
			cout << "--" << endl;
		}

		if (i >= frame - 1)			// Color for pages outside frame.
			setForegroundColor(RED);
		if (i >= virtualPage - 1)
			setForegroundColor(PINK);	// Color for page fault('P').
	}

	cout << endl;
}

//************************************************
// Do the LRU algorithm for 3, 4 and 5 frames.   *
//************************************************
void allLRU(string input)
{
	int numVirtualPage;
	virtualPage(input, numVirtualPage);		// Get the number of virtual page.
	int pageFault[3] = {0, 0, 0};

	showReferenceString(input);
	cout << "Least-Recently-Used Algorithm (LRU)" << endl << endl;

    setForegroundColor(GREEN);
	cout << "<GREEN color represents pages that are in frame>" << endl;
	setForegroundColor(RED);
	cout << "<RED color represents pages that have been swapped out>" << endl << endl;

	LRU(input, 3, numVirtualPage, pageFault[0]);
	LRU(input, 4, numVirtualPage, pageFault[1]);
	LRU(input, 5, numVirtualPage, pageFault[2]);
	drawGraph(pageFault, 3);			// Draw the graph.
}

//************************
// FIFO algorithm.       *
//************************
void FIFO(string input, int frame, int virtualPage, int& pageFault)
{
	if (virtualPage < frame)
		virtualPage = frame;

	deque <char> M;							// The internal array, M.
	vector <char> output[input.size()];		// For output purpose.
	deque <char> queue;				// To determine which page will be swapped out.
	vector <char> showQueue[input.size()];	// For output the queue purpose.

	// For every page in the input string.
	for (int i = 0; i < input.size(); i++)
	{
		bool found = false;

		// Check whether the page is inside the frame.
		for (int j = 0; j < frame && j < M.size() && !found; j++)
		{
			if (M[j] == input[i])			// If the page is found.
			{
				found = true;
				deque<char>::iterator it = M.begin() + j;
				M.erase(it);				// Erase it in the frame.
			}
		}

		if (M.size() >= virtualPage)		// If size of M exceed number of virtual page.
			M.pop_back();					// Pop 1 page for later push purpose.

		// If the page is not found in the frame.
		if (!found)
		{
			if (queue.size() >= frame)			// If the queue is full.
			{
				char popvalue = queue.front();	// Get the front page in the queue.
				queue.pop_front();				// Pop the queue.

				// Find the page that will be swapped out.
				for (int k = 0; k < frame ; k++)
				{
					if (M[k] == popvalue)		// The page that will be swapped out found.
					{
						deque<char>::iterator it = M.begin() + k;
						M.erase(it);			// Erase the page from the frame.
					}
				}
				deque<char>::iterator it = M.begin() + frame - 1;
				M.insert(it, popvalue);			// Insert the popped out page to the bottom part of M.
			}
			queue.push_back(input[i]);			// Push the new page to the queue.
		}

		M.push_front(input[i]);	// Push the page to the front of the deque.


		// Push the elements of queue for later output purpose.
		int l = 0;
		for (l; l < queue.size(); l++)
			showQueue[i].push_back(queue[l]);

		while (l < frame)
		{
			showQueue[i].push_back(' ');
			l++;
		}

		// Put all the pages into the vector for later output purpose.
		int k = 0;
		for (k; k < M.size(); k++)
			output[i].push_back(M[k]);

		while (k < virtualPage)		// If the page do not fill the M.
		{
			output[i].push_back(' ');
			k++;
		}

		if (!found)				// If the page is not found in frame, means page fault.
		{
			output[i].push_back('P');
			pageFault++;
		}
		else
			output[i].push_back(' ');

	}

	setForegroundColor(WHITE);
	cout << endl << frame << " Frames :" << endl;
	setForegroundColor(GREEN);		// Color for all pages in frame.

	// Output.
	for (int i = 0; i < virtualPage + 1; i++)
	{
		cout << "  ";
		for (int j = 0; j < input.size(); j++)
			cout << output[j][i] << " ";
		cout << endl;

		if (i == frame - 1)
		{
			for (int k = 0; k < input.size(); k++)
				cout << "--";
			cout << "--" << endl;
		}

		if (i >= frame - 1)
			setForegroundColor(RED);	// Color for swapped out page.
		if (i >= virtualPage - 1)
			setForegroundColor(PINK);	// Color for page fault('P').
	}

	cout << endl;
	setForegroundColor(WHITE);
	cout << "In The Queue:" << endl;
	setForegroundColor(YELLOW);			// Color for page in queue.

	// Output the queue.
	for (int i = 0; i < frame; i++)
	{
		cout << "  ";
		for (int j = 0; j < input.size(); j++)
			cout << showQueue[j][i] << " ";
		cout << endl;
	}
	cout << endl << endl;
}

//*************************************************
// Do the FIFO algorithm for 3, 4 and 5 frames.   *
//*************************************************
void allFIFO(string input)
{
	int numVirtualPage;
	virtualPage(input, numVirtualPage);		// Find the number of virtual page.
	int pageFault[3] = {0, 0, 0};

	showReferenceString(input);
	cout << "First-In-First-Out Algorithm (FIFO)" << endl << endl;
    setForegroundColor(GREEN);
	cout << "<GREEN color represents pages that are in frame>" << endl;
	setForegroundColor(RED);
	cout << "<RED color represents pages that have been swapped out>" << endl << endl;

	FIFO(input, 3, numVirtualPage, pageFault[0]);
	FIFO(input, 4, numVirtualPage, pageFault[1]);
	FIFO(input, 5, numVirtualPage, pageFault[2]);
	drawGraph(pageFault, 3);				// Draw page fault graph.
}

//***************************
// LFU algorithm.           *
//***************************
void LFU(string input, int frame, int virtualPage, int& pageFault)
{
	if (virtualPage < frame)
		virtualPage = frame;

	deque <char> M;						// The internal array, M.
	vector<char> output[input.size()];	// For output purpose.
	deque <char> queue;					// To determine which page to swapped out if counter same.
	deque <int> counter;				// To store the counter for each page in frame.

	// For every page in the input string.
	for (int i = 0; i < input.size(); i++)
	{
		bool found = false;

		// Check whether the page is inside the frame.
		for (int j = 0; j < frame && j < M.size() && !found; j++)
		{
			if (M[j] == input[i])			// If the page is found.
			{
				found = true;
				deque<char>::iterator it = M.begin() + j;
				M.erase(it);				// Erase it in the frame.
			}
		}

		if (M.size() >= virtualPage)	// If the size of M larger than number of virtualPage.
			M.pop_back();				// Pop the M for later push_front purpose.

		if (found)				// If the page is in frame.
		{
			// Find the page in the queue.
			for (int j = 0; j < queue.size(); j++)
			{
				if (input[i] == queue[j])
					counter[j]++;		// Add a counter for the page.
			}
		}

		else					// If the page is not in the frame.
		{
			if (queue.size() >= frame)			// If the queue is full.
			{
				int min = counter[0];			// Find the minumum counter in queue.
				for (int j = 0; j < counter.size(); j++)
				{
					if (min > counter[j])
						min = counter[j];
				}

				bool isRemove = false;
				char popvalue;			// Store the value of page that will be swapped out.

				// Find the first page in the queue with minumum counter and remove it.
				for (int j = 0; j < counter.size() && !isRemove; j++)
				{
					if (counter[j] == min)
					{
						popvalue = queue[j];
						isRemove = true;
						deque<char>::iterator q = queue.begin() + j;
						deque<int>::iterator c = counter.begin() + j;
						queue.erase(q);			// Remove it from queue.
						counter.erase(c);		// Remove the counter from queue.
					}
				}

				// Find the page that will be swapped out.
				for (int k = 0; k < frame ; k++)
				{
					if (M[k] == popvalue)		// The page that will be swapped out found.
					{
						deque<char>::iterator it = M.begin() + k;
						M.erase(it);			// Erase the page from the memory.
					}
				}

				deque<char>::iterator it = M.begin() + frame - 1;
				M.insert(it, popvalue);			// Insert the swapped out page to the bottom part of M.
			}
			queue.push_back(input[i]);			// Push the new page to the queue.
			counter.push_back(1);				// Push the new counter to the queue.
		}

		M.push_front(input[i]);		// Push the page to the front of the deque.

		// Put all the pages into the vector for later output purpose.
		int k = 0;
		for (k; k < M.size(); k++)
			output[i].push_back(M[k]);

		while (k < virtualPage)		// If the page do not fill the M.
		{
			output[i].push_back(' ');
			k++;
		}

		if (!found)					// If the page is not found in frame, means page fault.
		{
			output[i].push_back('P');
			pageFault++;
		}
		else
			output[i].push_back(' ');
	}

	setForegroundColor(WHITE);
	cout << endl << frame << " Frames :" << endl;
	setForegroundColor(GREEN);		// Color for pages in the frame.

	// Output.
	for (int i = 0; i < virtualPage + 1; i++)
	{
		cout << "  ";
		for (int j = 0; j < input.size(); j++)
			cout << output[j][i] << " ";
		cout << endl;

		if (i == frame - 1)
		{
			for (int k = 0; k < input.size(); k++)
				cout << "--";
			cout << "--" << endl;
		}

		if (i >= frame - 1)
			setForegroundColor(RED);	// Color for swapped out page.
		if (i >= virtualPage - 1)
			setForegroundColor(PINK);	// Color for page fault('P').
	}
	cout << endl;
}

//**************************************************
// Do the LFU algorithm for 3, 4 and 5 frames.     *
//**************************************************
void allLFU(string input)
{
	int numVirtualPage;
	virtualPage(input, numVirtualPage);		// Find the number of virtual page.
	int pageFault[3] = {0, 0, 0};

	showReferenceString(input);
	cout << "Least-Frequently-Used Algorithm (LFU)" << endl << endl;
    setForegroundColor(GREEN);
	cout << "<GREEN color represents pages that are in frame>" << endl;
	setForegroundColor(RED);
	cout << "<RED color represents pages that have been swapped out>" << endl << endl;
	LFU(input, 3, numVirtualPage, pageFault[0]);
	LFU(input, 4, numVirtualPage, pageFault[1]);
	LFU(input, 5, numVirtualPage, pageFault[2]);
	drawGraph(pageFault, 3);		// Draw the page fault graph.
}

//********************************************
// Menu for user to choose an algorithm.     *
//********************************************
void chooseAlgorithm(string s)
{
	char choice;
	do {
		cout << endl;
		cout << "See the page replacement algorithm for" << endl;
		cout << "1. Least-Recently-Used (LRU)" << endl;
		cout << "2. Least-Frequently-Used (LFU)" << endl;
		cout << "3. First-In-First-Out (FIFO)" << endl;
		cout << "<< OTHER KEYS, return to main menu >>" << endl << endl;
		cout << "Please enter a choice: ";
		cin >> choice;
		cin.ignore(1000, '\n');

		if (choice == '1')
			allLRU(s);
		else if (choice == '2')
			allLFU(s);
		else if (choice == '3')
			allFIFO(s);

	} while (choice == '1' || choice == '2' || choice == '3');
}

int main()
{
	system("cls");
	char choice;
	string sample[3];
	sample[0] = "023121456245323857206413";
	sample[1] = "145326436";
	sample[2] = "01234567899876543210";
	string refer;

	do{
		cout << endl;
		cout << "+++++++++++++++++++++++++++++++" << endl;
		cout << "+ Paging Algorithm Simulation +" << endl;
		cout << "+++++++++++++++++++++++++++++++" << endl << endl;
		do {
			cout << "Choose a sample reference string : " << endl;
			cout << "1. " << sample[0] << endl;
			cout << "2. " << sample[1] << endl;
			cout << "3. " << sample[2] << endl;
			cout << "========= OR ==========" << endl;
			cout << "4. Enter your own reference string." << endl;
			cout << "9. Exit program." << endl << endl;
			cout << "Please enter a choice : ";
			cin >> choice;
			cin.ignore(1000, '\n');
			cout << endl;
		} while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '9');

		if (choice == '1')
			refer = sample[0];

		else if (choice == '2')
			refer = sample[1];

		else if (choice == '3')
			refer = sample[2];

		else if (choice == '4')
		{
			cout << "Enter a reference string: ";
			cin >> refer;
		}

		if (choice != '9')
			chooseAlgorithm(refer);

	} while (choice != '9');

	return 0;
}
