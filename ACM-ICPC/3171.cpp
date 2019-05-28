#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Edge
{
	int vi, vj, w;
};

class mycomparison
{
	bool reverse;
	public:
		mycomparison(const bool& revparam = false)
		{
			reverse = revparam;
		}
		bool operator() (Edge const* lhs, Edge const* rhs) const
		{
			if (reverse) 
			return (lhs->w < rhs->w);
				
				
			else
			{
				if(lhs->w > rhs->w)
				return true;

				else if(lhs->w == rhs->w)
				{
					if(lhs->vi > rhs->vi)
					return true	;

					else
					return false;
				}
				
				else
				return false;
			}
		}
};

int kruskal(priority_queue< Edge*, vector<Edge*>, mycomparison > edges, int V, int E)
{
	vector <Edge*> mst;
	int cicles[V+1];
	int i, W, number;
	Edge *e;
	
	for (i = 0; i < V; i++)
		cicles[i] = i;
	
	while (mst.size() < (V - 1) && edges.size())
	{
		if (cicles[edges.top()->vi] != cicles[edges.top()->vj])
		{
			number = cicles[edges.top()->vj];
			
			for (i = 0; i < V; i++)
			{
				if (cicles[i] == number)
				cicles[i] = cicles[edges.top()->vi];
			}
			
			mst.push_back(edges.top());
		}
		edges.pop();
	}
	
	W = 0;
	
	for (i = 0; i < mst.size(); i++)
	{
		W += mst[i]->w;
		cout << char(mst[i]->vi + 64) << "-" << char(mst[i]->vj + 64) << " " << mst[i]->w << endl;
	}
	return W;
}

int main()
{
	
	
	int V, E;
	int test;

	cin >> test;
	int count = 0;
	while (count < test)
	{
		priority_queue< Edge*, vector<Edge*>, mycomparison > edges;
		Edge* e;
		int city;
		cin >> city;
		V = city * city;
		int a[city][city];
		
		for (int i = 0; i < city; i++)
		{
			for (int j = 0; j < city; j++)
			{
				string str;
				cin >> str;
				if (j < city - 1)
				str = str.substr(0, str.size() - 1);
				int num = atoi(str.c_str());
				a[i][j] = num;
			}
		}
		for (int i = 0; i < city; i++)
		{
			for (int j = i+1; j < city; j++)
			{
				e = new Edge();
				if (a[i][j] != 0)
				{
					e->vi = i+1;
					e->vj = j+1;
					e->w = a[i][j];
					
					edges.push(e);
				}
			}
		}
		cout << "Case " << ++count << ":" << endl;
		kruskal(edges, city, edges.size());
	}
	
	return 0;
}
