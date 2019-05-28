#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

int main()
{
	string b;
	string c;
	
	bool ok[12];	// [0] = C, [1] = C#, [2] = D, ...
	
	while (getline(cin, c) && c != "END")
	{
		memset(ok, true, sizeof(ok));
		
		stringstream a;
		a << c;
		while (a >> b)
		{
			// C
			if (b != "C" && b != "D" && b != "E" && b != "F" &&  b != "G" && b != "A" && b != "B")
				ok[0] = false;
			
			// C#
			if (b != "C#" && b != "D#" && b != "F" && b != "F#" &&  b != "G#" && b != "A#" && b != "C")
				ok[1] = false;
			
			// D
			if (b != "D" && b != "E" && b != "F#" && b != "G" &&  b != "A" && b != "B" && b != "C#")
				ok[2] = false;
						
			// D#
			if (b != "D#" && b != "F" && b != "G" && b != "G#" &&  b != "A#" && b != "C" && b != "D")
				ok[3] = false;
			
			// E
			if (b != "E" && b != "F#" && b != "G#" && b != "A" &&  b != "B" && b != "C#" && b != "D#")
				ok[4] = false;
			
			// F
			if (b != "F" && b != "G" && b != "A" && b != "A#" &&  b != "C" && b != "D" && b != "E")
				ok[5] = false;
			
			// F#
			if (b != "F#" && b != "G#" && b != "A#" && b != "B" &&  b != "C#" && b != "D#" && b != "F")
				ok[6] = false;
			
			// G
			if (b != "G" && b != "A" && b != "B" && b != "C" &&  b != "D" && b != "E" && b != "F#")
				ok[7] = false;
			
			// G#
			if (b != "G#" && b != "A#" && b != "C" && b != "C#" &&  b != "D#" && b != "F" && b != "G")
				ok[8] = false;
			//A
			if (b != "A" && b != "B" && b != "C#" && b != "D" &&  b != "E" && b != "F#" && b != "G#")
				ok[9] = false;
			
			// A#
			if (b != "A#" && b != "C" && b != "D" && b != "D#" &&  b != "F" && b != "G" && b != "A")
				ok[10] = false;
			
			// B
			if (b != "B" && b != "C#" && b != "D#" && b != "E" &&  b != "F#" && b != "G#" && b != "A#")
				ok[11] = false;
		}	
		bool space = false;
		
		if (ok[0])
		{
			cout << "C";
			space = true;
		}
		
		if (ok[1])
		{
			if (space)
				cout << " ";
			
			cout << "C#";
			space = true;
		}		
		
		if (ok[2])
		{
			if (space)
				cout << " ";
			
			cout << "D";
			space = true;
		}		
		
		if (ok[3])
		{
			if (space)
				cout << " ";
			
			cout << "D#";
			space = true;
		}		
		
		if (ok[4])
		{
			if (space)
				cout << " ";
			
			cout << "E";
			space = true;
		}		
		
		if (ok[5])
		{
			if (space)
				cout << " ";
			
			cout << "F";
			space = true;
		}		
		
		if (ok[6])
		{
			if (space)
				cout << " ";
			
			cout << "F#";
			space = true;
		}	
		
		if (ok[7])
		{
			if (space)
				cout << " ";
			
			cout << "G";
			space = true;
		}		
		if (ok[8])
		{
			if (space)
				cout << " ";
			
			cout << "G#";
			space = true;
		}		
		if (ok[9])
		{
			if (space)
				cout << " ";
			
			cout << "A";
			space = true;
		}		
		if (ok[10])
		{
			if (space)
				cout << " ";
			
			cout << "A#";
			space = true;
		}		
		if (ok[11])
		{
			if (space)
				cout << " ";
			
			cout << "B";
		}				
		cout << endl;
	}
	
	return 0;
}
