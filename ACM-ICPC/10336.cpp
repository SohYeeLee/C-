#include<iostream>
#include<queue>
#include<stack>
#define MAX 1000

using namespace std;

int G[MAX][MAX];
int visit[MAX];
int V, E;

void bfs(int s, char a[], char x) 
{
	queue<int> myQueue;
    int i, j, node;
    myQueue.push(s);
     
     while(!myQueue.empty())
     {
          node = myQueue.front();
          myQueue.pop();
          if(visit[node]) continue;
          visit[node] = 1;
          //cout << node << " ";
          
          for(i = 0; i < V; i++)
               if(G[i][node] != 0 && a[i] == x) myQueue.push(i);
          for(j = 0; j < V; j++)
               if(G[node][j] != 0 && a[i] == x) myQueue.push(j);     
     }
     
}

void dfs(int s, char a[], char x) 
{
	 stack<int> myStack;
     int i, j, node;
     myStack.push(s);
     
     while(!myStack.empty())
     {
        node = myStack.top();
          
        myStack.pop();
		if(visit[node]) continue;

      	visit[node] = 1;
      	//cout << node << " ";
      
      	for(i = 0; i < V; i++)
           if(G[node][i] != 0 && a[i] == x) myStack.push(i);
     }
}
 
int main() 
{
	int test;
	
	cin >> test;

	for (int k = 0; k < test; k++)
	{
		for (int i = 0; i < MAX; i++)
			for (int j = 0; j < MAX; j++)
				G[i][j] = 0;
		int height, width;
		
		cin >> height >> width;
		
		char a[height * width];
		
		V = height * width;
		for (int j = 0; j < height * width; j++)
		{
			cin >> a[j];	
			if (j >= width)		// the topest part.
				G[j][j - width] = 1;
				
			if (j < height * width - width)		// the lowest part.
				G[j][j + width] = 1;
			
			if (j % width != 0)			// the left part.
				G[j][j - 1] = 1;
				
			if ((j + 1) % width != 0)		// the right part.
				G[j][j + 1] = 1;
		}
		
	    memset(visit, 0, sizeof(visit));
		
	    bool finish = false;
	    int next = 0;
	    int val[26] = {0};
	    
	    while (!finish)
	    {
		    finish = true;
    		bfs(next, a, a[next]);
    		bool found = false;
    		
    		for (int i = 0; i < 26; i++)
    		{
	    		if (char(i + 97) == a[next])	
		    		val[i]++;
    		}
		    
    		for (int i = 0; i < V; i++)
    		{
    			if (visit[i] != 1)
    			{
    				finish = false;
    				next = i;
    				break;
				}
			}
		}
		
		cout << "World #" << k + 1<< endl;
		int max = 0;
		int maxv = 0;
		
		do{
			maxv = 0;
	    	for (int i = 0; i < 26; i++)
	    	{
		    	if (val[i] > maxv)
		    	{
		    		max = i;
		    		maxv = val[i];
	    		}
			}
			
			if (maxv > 0)
			{
				for (int i = 0; i < 26; i++)
				{
					if (maxv == val[i])
					{
						cout << char(i + 97) << ": " << maxv << endl;
						val[i] = 0;
					}
				}
			}
		}while (maxv != 0);
	}

    return 0;
}
