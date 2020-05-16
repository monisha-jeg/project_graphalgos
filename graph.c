#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Graph implementation
typedef struct graph
{
	int vertices;
	Lhead **g_arr;
}Graph;

//Create new graph
Graph *graph_new(int vertices)
{
	Graph *g;
	g = (Graph *)malloc(sizeof(Graph));
	g->vertices = vertices;

	int i;
	g->g_arr = (Lhead **)malloc(vertices * sizeof(Lhead *));
	for(i = 0; i < g->vertices; i++)
		(g->g_arr)[i] = list_new();	

	return g;
}

//Print the graph
void print_graph(Graph *g)
{
	int i;
	for(i = 0; i < g->vertices; i++)
	{
		printf("%d -> ", i);
		list_print((g->g_arr)[i]);
	}
}

//Add edge to graph
void add_edge(Graph *g, int from, int to, int capacity)
{
	Node *cur = (g->g_arr)[from]->head;
	Node *edge = node_new(to, capacity);
	
	if(cur == NULL)
		(g->g_arr)[from]->head = edge;
	else
	{
		while(cur->next != NULL && cur->next->vertex < to)
			cur = cur->next;
		if(cur->next != NULL && cur->next->vertex == to)
			cur->next->weight += capacity;
		else
		{
			edge->next = cur->next;
			cur->next = edge;	
		}		
	}	
}

//Modify weight of an edge
void modify_weight(Graph *g, int from, int to, int change_capacity)
{
	Node *cur;
	cur = (Node *)malloc(sizeof(Node));
	cur->next = (g->g_arr)[from]->head;

	while(cur->next != NULL)
	{
		cur = cur->next;
		if(cur->vertex == to)
		{
			cur->weight +=  change_capacity;
			break;
		}

	}
}

//Return weight of an edge
int get_capacity(Graph *g, int from, int to)
{
	Node *cur;
	cur = (Node *)malloc(sizeof(Node));
	cur->next = (g->g_arr)[from]->head;

	while(cur->next != NULL)
	{
		cur = cur->next;
		if(cur->vertex == to)
		{
			return cur->weight;
		}
	}
}


