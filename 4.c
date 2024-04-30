#include <stdlib.h>
#include <string.h>


typedef struct Node 
{
    char* city_name; 
    int weight;      
    struct Node* next; 
} Node;


typedef struct 
{
    int num_vertex; 
    Node** adj_lists; 
} GraphList;


GraphList* create_graph_list(int vertex) 
{
    GraphList* graph = malloc(sizeof(GraphList));
    graph->num_vertex = vertex;
    graph->adj_lists = malloc(sizeof(Node*) * vertex);
    for (int i = 0; i < vertex; i++) 
    {
        graph->adj_lists[i] = NULL;
    }
    return graph;
}

int add_edge(GraphList* graph, int src, int dest, int weight, const char* src_city, const char* dest_city) 
{

    if (src < 0 || src >= graph->num_vertex || dest < 0 || dest >= graph->num_vertex) 
    {
        printf( "Invalid vertices\n");
        return -1;
    }

    Node* new_node_src = malloc(sizeof(Node));
    if(new_node_src==NULL)
    {
        printf("memory not allocated ");
        exit(0);
    }
    new_node_src->city_name = strdup(src_city); 
    new_node_src->weight = weight; 
    new_node_src->next = graph->adj_lists[src]; 
    graph->adj_lists[src] = new_node_src; 

    
    Node* new_node_dest = malloc(sizeof(Node));
    if(new_node_dest==NULL)
    {
        printf("memory not allocated ");
        exit(0);
    }
    new_node_dest->city_name = strdup(dest_city); 
    new_node_dest->weight = weight; 
    new_node_dest->next = graph->adj_lists[dest];
    graph->adj_lists[dest] = new_node_dest; 

    return 0;
}


void print_graph_list(GraphList* graph) 
{

    for (int i = 0; i < graph->num_vertex; i++) {
        Node* temp = graph->adj_lists[i]; 
        printf("\n vertexes %d", i);
        while (temp != NULL) 
        {
            printf(" %s (Charge: %d)", temp->city_name, temp->weight); 
            temp = temp->next; 
        }
        printf("\n");
    }
}


int main() {
    
    int vertices = 4;

    GraphList* graph = create_graph_list(vertices);


    add_edge(graph, 5, 10, 550, "Delhi", "UP");
    add_edge(graph, 0, 4, 3000, "Delhi", "Amritsar");
    add_edge(graph, 10, 4, 6000, "Bangalore", "Delhi");
    add_edge(graph, 5, 3, 7000, "Chennai", "Delhi");

    print_graph_list(graph);
    for (int i = 0; i < graph->num_vertex; i++) 
    {
        Node* current = graph->adj_lists[i];
        while (current != NULL) 
        {
            Node* next = current->next;
            free(current->city_name);
            free(current);
            current = next;
        }
        graph->adj_lists[i] = NULL;
    }
    free(graph->adj_lists);
    free(graph);

    return 0;
}