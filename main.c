#include <stdio.h>
#include "graph.h"
int main() {
    graph g= init_graph(26);
    add_node(0,3,&g,1000,130);
    add_node(0,4,&g,50000,30);
    add_node(3,2,&g,1000,130);
    add_node(2,4,&g,5000,130);
    add_node(0,6,&g,5000,30);
    add_node(6,4,&g,1000,30);
    add_node(0,4,&g,50000,130);
    print_graph(g);
    road *n=fastest_road(g,0,4);
    print_road(n);
    free_road(n);
    free_graph(g);
    return 0;
}
