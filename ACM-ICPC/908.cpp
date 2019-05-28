#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <iomanip>
#define MAXINT 10000
#define MAXV 1000000      // maximum number of vertices 
using namespace std;

short parent[MAXV+1]; // discovery relation

typedef struct edgenode {
	int y; //adjacency info 
	int weight; // edge weight
	struct edgenode *next; // next edge in list
} ;

typedef struct graph{
	edgenode *edges[MAXV+1]; // adjacency info
	//int degree[MAXV+1]; // outdegree of each vertex 
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
		//for (i=1; i<=MAXV; i++) g->degree[i] = 0;
		for (i=1; i<=MAXV; i++) g->edges[i] = NULL;
}

void insert_edge(graph *g, int x, int y, bool directed , int z)
{
	edgenode *p; /* temporary pointer */
	p = new edgenode; /* allocate edgenode storage */
	p->weight = z;
	p->y = y;
	p->next = g->edges[x];
	g->edges[x] = p; /* insert at head of list */
	//g->degree[x]++;
	
	if (directed == false)
		insert_edge(g,y,x,true,z);
	else
		g->nedges++;
}

void prim(graph *g, int start)
{
	int i;        /* counter */
	edgenode *p; /* temporary pointer */
	bool intree[MAXV+1];  /* is the vertex in the tree yet? */
	int distance[MAXV+1]; /* cost of adding to tree */
	int v;       /* current vertex to process */
	int w;       /* candidate next vertex */
	int weight; /* edge weight */
	int dist;   /* best current distance from start */
	
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
	
	    int totaldist = 0;
		for (int i=1; i<= g->nvertices; i++){
		if(distance[i] != MAXINT)
			totaldist = totaldist + distance[i]; // calculate the total dist of the MST
	}
	cout << totaldist << endl;
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
	int vertex;
	while (cin >> vertex)
	{
		graph *g = new graph();
		g->nvertices = vertex;
		
		for (int i = 0; i < vertex - 1; i++)
		{
			int x, y, z;
			cin >> x >> y >> z;
		}
		int k;
		cin >> k;
		
		for (int i = 0; i < k; i++)
		{
			int x, y, weight;
			cin >> x >> y >> weight;
			insert_edge(g, x, y, false, weight);
		}
		
		int m;
		cin >> m;
		//graph *h = new graph();
		h->nvertices = vertex;
		for (int i = 0; i < m; i++)
		{
			int x, y, weight;
			cin >> x >> y >> weight;
			insert_edge(g, x, y, false, weight);
			//insert_edge(h, x, y, false, weight);
		}
		//prim(h, 1);
		prim(g, 1);
	}
	return 0;
}
