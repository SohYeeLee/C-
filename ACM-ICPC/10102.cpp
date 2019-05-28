/* Comment : the MAXV cannot be too large, else run time error.
The MAXV define is not enough for the input.*/

#include <cstdlib>
#include <iostream>
#include <queue>
#define	MAXV		1000		/* maximum number of vertices */
#define MAXDEGREE	500 	/* maximum outdegree of a vertex */

#define MAXINT	100007

using namespace std;

typedef struct {
	int v;				/* neighboring vertex */
	int weight;			/* edge weight */
	bool in;			/* is the edge "in" the solution? */
} edge;

typedef struct {
	edge edges[MAXV+1][MAXDEGREE];	/* adjacency info */
	int degree[MAXV+1];		/* outdegree of each vertex */
	int nvertices;			/* number of vertices in the graph */
	int nedges;				/* number of edges in the graph */
} graph;

typedef struct {
        int weight[MAXV+1][MAXV+1];    	/* adjacency/weight info */
        int nvertices;                  /* number of vertices in the graph */
} adjacency_matrix;


void initialize_adjacency_matrix(adjacency_matrix *g)
{
	int i,j;			/* counters */

	g -> nvertices = 0;

	for (i=1; i<=MAXV; i++)
		for (j=1; j<=MAXV; j++)
			g->weight[i][j] = MAXINT;
}

void read_adjacency_matrix(adjacency_matrix *g, int M, char a[])
{
	int i;				/* counter */
	int m;				/* number of edges */
	int x, y, w;		/* placeholder for edge and weight */

	initialize_adjacency_matrix(g);

	g->nvertices = M * M;
		
	for (int j = 0; j < M * M; j++)
	{
		cin >> a[j];	
		if (j >= M)			// the topest part.
			g->weight[j+1][j - M+1] = 1;
			
		if (j < M * M - M)	// the lowest part.
			g->weight[j+1][j + M+1] = 1;
		
		if (j % M != 0)				// the left part.
			g->weight[j+1][j - 1+1] = 1;
			
		if ((j + 1) % M != 0)		// the right part.
			g->weight[j+1][j + 1+1] = 1;
	}
}

void print_adjacency_matrix(adjacency_matrix *g, char a[])
{
	priority_queue<int> p;
	int smallest = 100000;
	for (int i = 1; i <= g->nvertices; i++) 
	{
		for (int j = 1; j <= g->nvertices; j++)
		{
			if (a[i - 1] == '1' && a[j - 1] == '3' && g->weight[i][j] < smallest)
			{
				smallest = g->weight[i][j];
				p.push(smallest);
			}
		}
	}
	cout << p.top() << endl;
}

void floyd(adjacency_matrix *g)
{
	int i,j;			/* dimension counters */
	int k;				/* intermediate vertex counter */
	int through_k;		/* distance through vertex k */

	for (k=1; k<=g->nvertices; k++)
		for (i=1; i<=g->nvertices; i++)
			for (j=1; j<=g->nvertices; j++) 
			{
				through_k = g->weight[i][k]+g->weight[k][j];
				if (through_k < g->weight[i][j])
					g->weight[i][j] = through_k;
			}
}


main()
{
	adjacency_matrix g;
	
	int M;
	while (cin >> M)
	{
		char a[M * M];
		read_adjacency_matrix(&g, M, a);

		floyd(&g);
		print_adjacency_matrix(&g, a);

	}

}


