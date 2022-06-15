#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H
#include "stdio.h"
#include <stdlib.h>
typedef struct s_nodevalue{
    int dist;
    int speed;
}nodevalue;
typedef struct s_graph{
    nodevalue **list;
    int size;
}graph;

typedef struct s_road{
    struct s_road *next;
    int id;
}road;

void free_graph(graph g);

void free_road(road *r);

int in_road_e(road * r,int value,int e);

road *add_road(int id ,road*next);

int in_road(road *r,int value);

graph init_graph(int size);

void add_node(int id,int to_id,graph *the_graph,int distance,int speed);

void print_graph(graph the_graph);

road* fastest_road(graph the_graph,int start,int stop);

void print_road(road *r);

int road_lenght(road *r,graph g);

#endif //GRAPH_GRAPH_H
