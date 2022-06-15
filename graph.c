#include "graph.h"


graph init_graph(int size){
    graph g;
    g.size=size;
    g.list= malloc(size * sizeof(nodevalue*));
    for (int i = 0; i < size; i++) {
        g.list[i]=malloc(size * sizeof(nodevalue));
        for(int k=0 ; k < size;k++){
            g.list[i][k].dist=0;
            g.list[i][k].speed=2;
        }
    }
    return g;
}
void free_graph(graph g){
    for (int i = 0; i < g.size; i++)
        free(g.list[i]);
    free(g.list);
}
void free_road(road *r){
    if(r==NULL)
        return;
    free_road(r->next);
    free(r);
}
void add_node(int id,int to_id,graph *the_graph,int distance,int speed){
    the_graph->list[id][to_id].dist=distance;
    the_graph->list[id][to_id].speed=speed;
}

void print_graph(graph the_graph){
    for (int i = 0; i< the_graph.size; ++i) {
        printf("id : %c neighboor(",i+65);
        for (int k = 0; k<the_graph.size; ++k) {
            if(the_graph.list[i][k].dist>0)
                printf("(%c,%d,%d)",k+65,the_graph.list[i][k].dist,the_graph.list[i][k].speed);
        }
        printf(")\n");
    }
}
int road_lenght(road *r,graph g){
    int lenght=0;
    while (r!=NULL) {
        if(r->next!=NULL)
            lenght+=g.list[r->id][r->next->id].dist/g.list[r->id][r->next->id].speed;
        r=r->next;
    }
    return lenght;
}
int in_road(road *r,int value){
    while (r!=NULL) {
        if(r->id==value)
            return 1;
        r=r->next;
    }
    return 0;
}
road *add_road(int id ,road*next){
    road *r=malloc(sizeof(road));
    r->next=next;
    r->id=id;
    return r;
}
int in_road_e(road * r,int value,int e){
    if(r==NULL)
        return 0;
    while (r!=NULL) {
        if(r->id==value && r->id!=e)
            return 1;
        r=r->next;
    }
    return 0;
}
road* fastest_road(graph the_graph,int start,int stop){
    if(start==stop)
        return add_road(stop,NULL);
    road *min=NULL;
    for (int i = 0; i < the_graph.size; ++i) {
        if(the_graph.list[start][i].dist>0 && !in_road_e(min,i,stop)){
            if(min==NULL){
                road *r1 = fastest_road(the_graph, i, stop);
                if(r1!=NULL) {
                    free_road(min);
                    min = add_road(r1->id, r1->next);
                    free(r1);
                }else {
                    free_road(r1);
                }
            }else{
                road *r1 = fastest_road(the_graph, i, stop);
                road *tmp=add_road(start,r1);
                road *tmp2=add_road(start,min);
                if (r1!=NULL && road_lenght(tmp2, the_graph) > road_lenght(tmp, the_graph)) {
                    free_road(min);
                    min = add_road(r1->id, r1->next);
                    free(r1);
                }else {
                    free_road(r1);
                }
                free(tmp);
                free(tmp2);
            }
        }
    }
    if( in_road(min,stop))
        return add_road(start,min);
    else
        return NULL;
}

void print_road(road *r){
    printf("road : ");
    for (int i = 0;r!=NULL; ++i) {
        printf("%c ",r->id+65);
        r=r->next;
    }
    printf("\n");
}