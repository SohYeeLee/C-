#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <iomanip>
#define MAXINT 10000
#define MAXV 1000      // maximum number of vertices 
using namespace std;

bool processed[MAXV+1]; // which vertices have been processed 
bool discovered[MAXV+1]; // which vertices have been found  
int parent[MAXV+1]; // discovery relation

typedef struct edgenode {
	int y; //adjacency info 
	double weight; // edge weight
	struct edgenode *next; // next edge in list
} ;

typedef struct graph{
	edgenode *edges[MAXV+1]; // adjacency info
	int degree[MAXV+1]; // outdegree of each vertex 
	int nvertices;  // number of vertices in graph 
	int nedges;     // number of edges in graph 
	bool directed; /* is the graph directed? */
} ;

void initialize_graph(graph *g, bool directed)
{
	int i; /* counter */
	g -> nvertices = 0;
	g -> nedges = 0;
	g -> directed = directed;
		for (i=1; i<=MAXV; i++) g->degree[i] = 0;
		for (i=1; i<=MAXV; i++) g->edges[i] = NULL;
}

void insert_edge(graph *g, int x, int y, bool directed , double z)
{
	edgenode *p; /* temporary pointer */
	p = new edgenode; /* allocate edgenode storage */
	p->weight = z;
	p->y = y;
	p->next = g->edges[x];
	g->edges[x] = p; /* insert at head of list */
	g->degree[x]++;
	
	if (directed == false)
		insert_edge(g,y,x,true,z);
	else
		g->nedges++;
}

void change_weight(graph *g, int x, int y, double w, bool directed)
{
	edgenode *p;
	p = g->edges[x];
	
	bool found = false;
	while (p != NULL && !found)
	{
		if (y == p->y)
		{
			found = true;
			p->weight = w;
			
			if (!directed)
				change_weight(g, y, x, w, true);
		}
		else	
			p = p->next;
	}
}

void prim(graph *g, int start)
{
	int i;        /* counter */
	edgenode *p; /* temporary pointer */
	bool intree[MAXV+1];  /* is the vertex in the tree yet? */
	double distance[MAXV+1]; /* cost of adding to tree */
	int v;       /* current vertex to process */
	int w;       /* candidate next vertex */
	double weight; /* edge weight */
	double dist;   /* best current distance from start */
	
	for (i=1; i<=g->nvertices; i++) {
		intree[i] = false;
		distance[i] = MAXINT;
		parent[i] = -1;
	}
	
	distance[start] = 0;
	v = start;

	while (intree[v] == false) {
		intree[v] = true;
		p = g->edges[v];
		while (p != NULL) {
			w = p->y;
			weight = p->weight;
			if ((distance[w] > weight) && (intree[w] == false)) {
				distance[w] = weight;
				parent[w] = v;
			}
			p = p->next;
		}

		v = 1;
		dist = MAXINT;
		for (i=1; i<=g->nvertices; i++) 
		if ((intree[i] == false) && (dist > distance[i])) {
				dist = distance[i];
				v = i;
			}
	      }
	
	    double totaldist = 0;
		for (int i=1; i<= g->nvertices; i++){
		if(distance[i] != MAXINT)
			totaldist = totaldist + distance[i]; // calculate the total dist of the MST
	}
	cout << setprecision(2) << showpoint << fixed << totaldist << endl;
}

void print_graph(graph *g)
{
	int i; /* counter */
	edgenode *p; /* temporary pointer */ 
	for (i=1; i<=g->nvertices; i++) {
		cout << i << " ";
		p = g->edges[i];
		
		while (p != NULL) {
			cout << p->y << " weight " << p->weight << " ";
			p = p->next;
		}
	printf("\n");
	}
}//End normal graph

int main()
{	
	int building;		// Number of building.
	int exist;		// Number of existing highway.

	while (cin >> building)
	{
		graph *g = new graph();
		vector<pair <int, int> > v; 
		initialize_graph(g, false);
		g->nvertices = building;
		
		for (int i = 0; i < building; i++)
		{
			int x, y;
			cin >> x >> y;
			v.push_back(make_pair(x, y));
		}
			
		for (int i = 1; i <= building; i++)
		{
			for (int j = i + 1; j <= building; j++)
			{
				double temp = sqrt(pow(v[i - 1].first - v[j - 1].first, 2.0) + pow(v[i - 1].second - v[j - 1].second, 2.0));
				insert_edge(g, i, j, false, temp);
			}
		}
		
		cin >> exist;
		for (int i = 0; i < exist; i++)
		{
			int v1, v2;
			cin >> v1 >> v2;
			change_weight(g, v1, v2, 0, false);
		}
		//print_graph(g);
		prim(g, 1);
	}
	return 0;
}
