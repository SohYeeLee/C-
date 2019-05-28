#include <iostream>
#include <vector>

#define MAXV 100 		/* maximum number of vertices */
#define MAXDEGREE 50 	/* maximum vertex outdegree */

using namespace std;

typedef struct {
	int edges[MAXV+1][MAXDEGREE]; 	/* adjacency info */
	int degree[MAXV+1]; 			/* outdegree of each vertex */
	int nvertices; 					/* number of vertices in graph */
	int nedges; 					/* number of edges in graph */
} graph;

void initialize_graph(graph *g)
{
	g -> nvertices = 0;
	g -> nedges = 0;
	for (int i = 1; i <= MAXV; i++) 
		g->degree[i] = 0;
}

void insert_edge(graph *g, int x, int y, bool directed)
{
	if (g->degree[x] > MAXDEGREE)
		printf("Warning: insertion(%d,%d) exceeds max degree\n", x, y);
	
	g->edges[x][g->degree[x]] = y;
	g->degree[x]++;
	if (directed == false)
		insert_edge(g, y, x, true);
	else
		g->nedges++;
}

void read_graph(graph *g, bool directed)
{
	int i; /* counter */
	int m; /* number of edges */
	int x, y; /* vertices in edge (x,y) */
	
	initialize_graph(g);
	
	scanf("%d %d",&(g->nvertices),&m);
	
	for (i = 1; i <= m; i++) 
	{
		scanf("%d %d",&x,&y);
		insert_edge(g, x, y, directed);
	}
}

void print_graph(graph *g)
{
	int i, j; 	/* counters */
	for (i = 1; i <= g->nvertices; i++) 
	{
		printf("%d: ",i);
		for (j = 0; j < g-> degree[i]; j++)
			printf(" %d",g->edges[i][j]);
			printf("\n");
	}
}

void findPath(graph* g, int startVertex)
{
	vector<int> visitedVertex;
	visitedVertex.push_back(startVertex);
	int currentVertex = startVertex;
	int steps = 1;
	bool visited = false;
	int loop = 0;

	while (g->degree[currentVertex] != 0 && visited == false)
	{
		visited = false;
		currentVertex = g->edges[currentVertex][0];
		for (int i = 0; i < visitedVertex.size() && !visited; i++)
		{
			if (currentVertex == visitedVertex[i])
			{
				loop = i;
				visited = true;
			}
		}
		if (!visited)
		{
			visitedVertex.push_back(currentVertex);
			steps++;
		}
	}
	if (!visited)
		cout << steps << " step(s) to exit" << endl;
	else
		cout << loop << " step(s) before a loop of " << steps - loop << " step(s)" << endl;
}
int main()
{
	int row, column, start;
	
	while (cin >> row >> column >> start && (row != 0 && column != 0 && start != 0))
	{
		int steps = 1;
		char a[row * column];
		
		graph *g = new graph();
		initialize_graph(g);
		g->nvertices = row * column;
		
		for (int i = 0; i < row * column; i++)
			cin >> a[i];

		for (int i = 0; i < row * column; i++)
		{
			if (a[i] == 'N' && i >= column)
			{
				//Edge temp(i + 1, i - column + 1, -100);
				insert_edge(g, i + 1, i - column + 1, true);
				//graph.add(temp);
			}
			
			else if (a[i] == 'S' && i < column * (row - 1))
			{
				//Edge temp(i + 1, i + column + 1, -100);
				//graph.add(temp);
				insert_edge(g, i + 1, i + column + 1, true);
			}
			
			else if (a[i] == 'E' && (i + 1) % column != 0)
			{
				//Edge temp(i + 1, i + 2, -100);
				//graph.add(temp);
				insert_edge(g, i + 1, i + 2, true);
			}
			
			else if (a[i] == 'W' && (i % column != 0))
			{
				//Edge temp(i + 1, i, -100);
				//graph.add(temp);
				insert_edge(g, i + 1, i, true);
			}
		}
		findPath(g, start);
	}
	return 0;
}

