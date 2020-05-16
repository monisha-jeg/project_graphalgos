#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>

#include "linked_list.c"
#include "queue.c"
#include "graph.c"


//Find shortest path using BFS
int find_shortest_path(Graph *g, int source, int sink, int *path_parent)
{
    int *visited, u, i, *flow;
    visited = (int *)malloc(g->vertices * sizeof(int));
    for(i = 0; i < g->vertices; i++)
        visited[i] = 0; 
    flow = (int *)malloc(g->vertices * sizeof(int));
    
    Queue *q;
    q = queue_new();
    enqueue(q, source);
    visited[source] = 1;
    path_parent[source] = -1;
    flow[source] = INT_MAX;
 
    Node *cur;
    while(!queue_is_empty(q))
    {
        u = dequeue(q);
        cur = (g->g_arr)[u]->head;
        
        while(cur != NULL)
        {
            if (visited[cur->vertex] == 0 && cur->weight > 0)
            {
                visited[cur->vertex] = 1;
                path_parent[cur->vertex] = u;

                //Check flow of this edge w.r.t previous edge
                if(cur->weight < flow[u])
                    flow[cur->vertex] = cur->weight;
                else
                    flow[cur->vertex] = flow[u];                

                if(cur->vertex == sink)
                    return flow[sink];

                enqueue(q, cur->vertex);
            }
            cur = cur->next;
        }
    }
    return 0;
}
    

//Find max flow
int get_max_flow(Graph *g, int source, int sink)
{
    int max_flow = 0, u, v;
    int path_found, flow_path;

    int *path_parent;
    path_parent = (int *)malloc(g->vertices * sizeof(int));   
   

    while(1)
    {
        //Find shortest augmenting path in residual graph
        flow_path = find_shortest_path(g, source, sink, path_parent);
        
        if (flow_path == 0) //Done, if there is no such path
            break;
        else
        {
            //Add to current value of max-flow
            max_flow += flow_path;
            
            //Find residual graph
            for (v = sink ; v != source; v = u)
            {
                u = path_parent[v];
                modify_weight(g, u, v, -flow_path);
                modify_weight(g, v, u, flow_path);
            }
        }
    }
    return max_flow;
}


//Driver Function
int main (int argc, char *argv[]) 
{
    int n, m, v1, v2, w, i, source, sink;

    FILE *input_graph = fopen(argv[1], "r");      
    fscanf(input_graph, "%d %d", &n, &m);

    Graph *g = graph_new(n);    
    for(i = 0; i < m; i++)
    {
        fscanf(input_graph, "%d %d %d", &v1, &v2, &w);  
        add_edge(g, v1-1, v2-1, w);
        add_edge(g, v2-1, v1-1, 0);
    }
    fscanf(input_graph, "%d %d", &source, &sink);
    //print_graph(g);

    FILE *time = fopen("times-max_flow.txt", "a");
    struct timeval start,end;
    gettimeofday(&start, NULL);
    int max_flow = get_max_flow(g, source-1, sink-1);
    gettimeofday(&end, NULL);
    fprintf(time, "%d\t\t%d\t\t-->\t\t%.2f\n", n, m, (double)(end.tv_sec-start.tv_sec));

    // FILE *output = fopen("output-max_flow.txt", "w");
    // fprintf(output, "Max flow : %d\n", max_flow);
    printf("Max flow : %d\n", max_flow);

    //fclose(output);
    //fclose(time);
    fclose(input_graph);
    return 0;
}