#include "dijkstras.h"

int main()
{
    Graph graph;
    file_to_graph("large.txt", graph);

    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(graph, source, previous);

    int destination = 4;
    print_path(distances, 0);

    return 0;
}