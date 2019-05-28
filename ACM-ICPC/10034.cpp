#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#define	MAXV		100		/* maximum number of vertices */
#define MAXINT  	100000
#define TREE		0		/* tree edge */
#define BACK		1		/* back edge */
#define CROSS		2		/* cross edge */
#define FORWARD		3		/* forward edge */

using namespace std;

typedef struct edgenode {
	int y;					/* adjancency info */
	double weight;			/* edge weight, if any */
	struct edgenode *next;	/* next edge in list */
} edgenode;

typedef struct {
	edgenode *edges[MAXV+1];	/* adjacency info */
	int degree[MAXV+1];		/* outdegree of each vertex */
	int nvertices;			/* number of vertices in the graph */
	int nedges;				/* number of edges in the graph */
	int directed;			/* is the graph directed? */
} graph;

void initialize_graph(graph *g, bool directed)
{
	int i;				/* counter */

	g -> nvertices = 0;
	g -> nedges = 0;
	g -> directed = directed;

	for (i=1; i<=MAXV; i++) g->degree[i] = 0;
	for (i=1; i<=MAXV; i++) g->edges[i] = NULL;
}

void insert_edge(graph *g, int x, int y, double w, bool directed)
{
	edgenode *p = new edgenode();			/* temporary pointer */

	//p = malloc(sizeof(edgenode));	/* allocate storage for edgenode */

	p->weight = w;
	p->y = y;
	p->next = g->edges[x];

	g->edges[x] = p;		/* insert at head of list */

	g->degree[x] ++;

	if (directed == false)
		insert_edge(g, y, x, w, true);
	else
		g->nedges ++;
}

void print_graph(graph *g)
{
	int i;				/* counter */
	edgenode *p;			/* temporary pointer */

	for (i=1; i<=g->nvertices; i++) {
		printf("%d: ",i);
		p = g->edges[i];
		while (p != NULL) {
			printf(" %d",p->y);
			p = p->next;
		}
		printf("\n");
	}
}

void prim(graph *g, int start)
{
	int parent[MAXV + 1];
	edgenode *p; 			/* temporary pointer */
	bool intree[MAXV+1]; 	/* is the vertex in the tree yet? */
	double distance[MAXV+1]; 	/* cost of adding to tree */
	int v; 					/* current vertex to process */
	int w; 					/* candidate next vertex */
	double weight; 			/* edge weight */
	double dist; 				/* best current distance from start */
	
	for (int i = 1; i <= g-> nvertices; i++) 
	{
		intree[i] = false;
		distance[i] = MAXINT;
		parent[i] = -1;
	}
	
	distance[start] = 0;
	v = start;

	while (intree[v] == false) 
	{
		intree[v] = true;
		p = g->edges[v];
		while (p != NULL) 
		{
			w = p->y;
			weight = p->weight;
			if ((distance[w] > weight) && (intree[w] == false)) 
			{
				distance[w] = weight;
				parent[w] = v;
			}
			p = p->next;
		}
		
		v = 1;
		dist = MAXINT;
	
		for (int i = 1; i <= g->nvertices; i++)
			if ((intree[i] == false) && (dist > distance[i])) 
			{
				dist = distance[i];
				v = i;
			}
	}
	
	double totaldist = 0;
	for (int i = 1; i <= g->nvertices; i++)
	{
		if(distance[i] != MAXINT)
			totaldist = totaldist + distance[i]; // calculate the total dist of the MST
	}
	
	cout << showpoint << setprecision(2) << fixed << totaldist << endl;
}

int main()
{
	graph *g = new graph();
	
	int test;
	cin >> test;
	
	while (test > 0)
	{
		int point;
		vector <pair <double, double> > v;
		cin >> point;
		initialize_graph(g, false);
		g->nvertices = point;
		for (int i = 0; i < point; i++)
		{
			double x, y;
			cin >> x >> y;
			v.push_back(make_pair(x, y));
		}
		
		for (int i = 1; i <= point; i++)
		{
			for (int j = i + 1; j <= point; j++)
			{
				insert_edge(g, i, j, sqrt(pow(v[i - 1].first - v[j - 1].first, 2.0) + pow(v[i - 1].second - v[j - 1].second, 2.0)), false);
			}
		}
		//print_graph(g);
		prim(g, 1);
		test--;
		if (test != 0)
			cout << endl;
	}
	return 0;
}
