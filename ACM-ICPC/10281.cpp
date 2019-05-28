/* 
 * File:   main.cpp
 * Author: Lee
 *
 * Created on August 13, 2009, 11:30 PM
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main() 
{
    string input;
    int speed = 0;
    double distance = 0;
    string last = "00:00:00";
	
    while (getline(cin, input))
    {
        // Find the hour out.
        string s;
        s = s + input[0] + input[1];
        float hour = atof(s.c_str());
        s.clear();
        s = s + input[3] + input[4];
        hour = hour + atof(s.c_str()) / 60;
        s.clear();
        s = s + input[6] + input[7];
        hour = hour + atof(s.c_str()) / 3600;
		
		string s1;
        s1 = s1 + last[0] + last[1];
        float hour1 = atof(s1.c_str());
        s1.clear();
        s1 = s1 + last[3] + last[4];
        hour1 = hour1 + atof(s1.c_str()) / 60;
        s1.clear();
        s1 = s1 + last[6] + last[7];
        hour1 = hour1 + atof(s1.c_str()) / 3600;
		
		hour = hour - hour1;
        if (input.size() > 8)       // Change of speed
        {  
            string temp;      		// Storing the speed.
            int k = 8;
            
            while (input[k] == ' ')
                k++;
            for (k; k < input.size(); k++)
                temp = temp + input[k];
			
			distance = distance + hour * speed;
			speed = atoi(temp.c_str()); 
        }
        
        else                // Do not change speed
        {
            distance = distance + hour * speed;
            cout << input << " " << fixed << setprecision (2) << showpoint << distance << " km" << endl;
        }
        last = input;
    }
    return 0;
}

