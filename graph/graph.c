#include <stdio.h>
#include <stdlib.h>

struct graphNode {
	int vertex;
	struct graphNode *next;
};

struct Graph {
	int vertex_num;
	struct graphNode **neigh;
	int *visited;
};

struct graphNode *createNode(int vertex)
{
	struct graphNode *node = malloc(sizeof(struct graphNode));
	node->vertex = vertex;
	node->next = NULL;
}

struct Graph *createGraph(int num)
{
	struct Graph *graph = malloc(sizeof(struct Graph));
	graph->vertex_num = num;
	graph->neigh = malloc(num * sizeof(struct graphNode));
	graph->visited = malloc(num * sizeof(int));
	for (int i=0; i<num; i++) {
		graph->neigh[i] = NULL;
		graph->visited[i] = 0;
	}
	return graph;
}

int add_edge(struct Graph *graph, int src, int dst) 
{
	struct graphNode *newNode = createNode(dst);
	newNode->next = graph->neigh[src];
	graph->neigh[src] = newNode;

	newNode = createNode(src);
	newNode->next = graph->neigh[dst];
	graph->neigh[dst] = newNode;

	return 0;
}

void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->vertex_num; v++) {
        struct graphNode* temp = graph->neigh[v];
        printf("\n顶点 %d 的邻接表: ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void dfs(struct Graph* graph, int vertex)
{
	struct graphNode *n = graph->neigh[vertex];
	graph->visited[vertex] = 1;
	printf("visit %d\n", vertex);
	while(n) {
		int a = n->vertex;
		if(graph->visited[a] == 0) {
			dfs(graph,  a);
		}
		n = n->next;
	}
}


int main()
{
	struct Graph *graph = createGraph(6);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 2, 4);
    add_edge(graph, 3, 4);
	add_edge(graph, 4, 5);
	printGraph(graph);
	dfs(graph, 0);

    free(graph->visited);
    for (int i = 0; i < graph->vertex_num; i++) {
        struct graphNode* temp = graph->neigh[i];
        while (temp) {
            struct graphNode* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->neigh);
    free(graph);

	return 0;
}
