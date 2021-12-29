#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

int main(){

    Graph* g = (Graph *) malloc(sizeof(Graph));
    if(!g){return -1;} // make sure the allocation was succesfull

    g->AdjList = NULL;

    char choice;
    int flag = 1;
    while(flag){

        choice = getc(stdin);
        switch (choice)
        {
            case 'A':
                getc(stdin);// skip the space
                createGraph(g);
                break;

            case 'B':
            {

                getc(stdin);// skip the space
                int counter=0,check,id;
                int weight[g->size];
                int dest[g->size];
                scanf("%d",&id);
                char c;
                while (1){
                    c = getc(stdin);
                    if(c != ' ' ){
                        counter++;
                        break;
                    }
                    scanf("%d",&dest[counter]);
                    check=scanf("%d",&weight[counter++]);

                    if(check==0){
                        c = getc(stdin);
                        ungetc(c, stdin);
                        break;
                    }

                }
                newNode(g,id,dest,weight,counter-1);
                break;
            }

            case 'D':
                getc(stdin);// skip the space
                int id;
                scanf("%d",&id);
                deleteNode(g,id);
                break;

            case 'S': {
                int dest, src;
                scanf("%d %d", &src, &dest);
                printf("Dijsktra shortest path: ");
                shp(g, src, dest,1);
                break;
            }

            case 'T':
            {
                getc(stdin);// skip the space
                printf("TSP shortest path: ");

                int size;
                scanf("%d", &size);
                int list[size];
                for (int i = 0; i < size; ++i) {
                    scanf("%d", &list[i]);
                }
                tsp(g,list,size);
                break;
            }

            case EOF:
                flag = 0;
                break;
        }
    }
    freeLinkedList(g->AdjList);
    free(g);
}