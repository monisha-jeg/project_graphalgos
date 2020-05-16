#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>

#include "linked_list.c"
#include "queue.c"
#include "graph.c"


//Find set of shortest augmenting paths by dividing graph into layers starting from free vertices in left hand side
int bfs_augmenting_path(Graph *g, int m, int *matching, int *distance)
{  
    int i, u; 
    Queue *q;  
    q = queue_new(); 
    distance[0] = INT_MAX;
   	for(i = 1; i <= m; i++)
   	{  
    	if(matching[i] == 0)
    	{   
       		distance[i] = 0;  
       		enqueue(q, i);  
    	}
    	else
    		distance[i] = INT_MAX;
    } 

    Node *cur;
    while(!queue_is_empty(q))
    {
    	u = dequeue(q);
    	if(u != 0)
    	{
    		cur = (g->g_arr)[u]->head;
    		while(cur != NULL)
    		{
    			if(distance[matching[cur->vertex]] == INT_MAX)
    			{
    				//Set distance at each layer and enqueue
            		distance[matching[cur->vertex]] = distance[u] + 1;
    				enqueue(q, matching[cur->vertex]);
    			}
                cur = cur->next;
    		}
    	}
    }
    //distance[0] is changed if path was found, i.e, if dummy vertex was visited    
    return !(distance[0] == INT_MAX);
}


//Find bigger matching using augmenting path starting from given vertex
int dfs_matching(Graph *g, int *matching, int *distance, int start_vertex)
{
	if(start_vertex != 0)
	{
		Node *cur = (g->g_arr)[start_vertex]->head;
  	    while(cur != NULL)
  	    {
      		if(distance[matching[cur->vertex]] == distance[start_vertex] + 1)
      		{
      			if(dfs_matching(g, matching, distance, matching[cur->vertex]) == 1)
      			{
      				matching[cur->vertex] = start_vertex;
      				matching[start_vertex] = cur->vertex;
      				return 1;
      			}
      		}
            cur = cur->next;
  	    }
      	distance[start_vertex] = INT_MAX;
      	return 0;
	}
	return 1;
}


//Find maximum matching by Hopkraft-Karp's method 
int get_max_matching(Graph *g, int m, int n, int *matching)
{
	int max_matching = 0, i; 
    for(i = 1; i <= (m+n); i++)
        matching[i] = 0;
    int *distance;
    distance = (int *)malloc((m+n+1) * sizeof(int));
   
 	//While augmenting paths w.r.t matching exist
    while(bfs_augmenting_path(g, m, matching, distance) == 1)
 	{
 		for(i = 1; i <= m; i++)
 		{
 			if(matching[i] == 0)//If 'i' is a free vertex
                //if there is an augmenting path starting from start_vertex
 				if(dfs_matching(g, matching, distance, i) == 1)
 					max_matching++;
 		}      
 	}        
    return max_matching;    
} 


//Driver Function
int main (int argc, char *argv[]) 
{
	int m, n, e, v1, v2, i;

	FILE *input_graph = fopen(argv[1], "r");  
	fscanf(input_graph, "%d %d %d", &m, &n, &e);
	Graph *g = graph_new(m+n+1);	
	for(i = 1; i <= e; i++)
	{
		fscanf(input_graph, "%d %d", &v1, &v2);	
		add_edge(g, v1, v2, 1);
	}	
	//Adding edges from all RHS vertices to dummy vertex 0 
	for(i = m+1; i <= n; i++)
		add_edge(g, i, 0, 1);
	
	//print_graph(g);
	int *matching;
	matching = (int *)malloc((m+n+1) * sizeof(int));	

	FILE *time = fopen("times-bipartite.txt", "a");
	struct timeval start,end;
	gettimeofday(&start, NULL);
	int max_matching = get_max_matching(g, m, n, matching);
	gettimeofday(&end, NULL);
	fprintf(time, "%d\t\t%d\t\t-->\t\t%.2f\n", m+n, e, (double)(end.tv_sec-start.tv_sec));

	FILE *output = fopen("output-bipartite.txt", "w");
	// fprintf(output, "Max matching : %d\n", max_matching);
	printf("Maximum Matching : %d\n", max_matching);

    for(i = 1; i <= m; i++)
        if(matching[i] != 0)
            fprintf(output, "%d --- %d\n", i, matching[i]);

    fclose(output);
    fclose(input_graph);
	return 0;
}