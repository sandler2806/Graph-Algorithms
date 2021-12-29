#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include "headers.h"

int factorial(int num){
    int fact=1;
    for(int i=1;i<=num;i++){
        fact=fact*i;
    }
    return fact;
}

void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int** dijkstra;

int min;

int permute(char *a, int l, int r, int size, int* list)
{
    if (l == r){

        int sum=0;
        for (int i = 0; i <size-1; i++)
        {
            int dist = dijkstra[a[i]-'0'][list[a[i+1]-'0']];
            if(dist == INT_MAX-1) {
                return dist;
            }
            sum+=dist;
        }
        return sum;

    }

    else
    {
        int temp=0;
        for (int i = l; i <= r; i++)
        {
            swap((a+l), (a+i));
            temp=permute(a, l+1, r,size,list);
            if(temp<min){
                min=temp;
            }
            swap((a+l), (a+i));
        }
        return min;
    }
}

void tsp(Graph * g,int* list,int size){

    dijkstra=(int **)malloc(sizeof(int*)*size);
    min=INT_MAX;

    for (int i = 0; i < size; i++)
    {
        dijkstra[i]=shp(g,list[i],list[i],0);
    }

    char str[size];
    for (int i = 0; i < size; i++)
    {
        str[i]=i+'0';
    }

    int ans=permute(str,0, size-1,size,list);
    if(ans==INT_MAX-1){
        ans=-1;
    }
    printf("%d \n",ans);


    //free to dijkstra and all dists
    for (int i = 0; i < size; i++)
    {
        free(dijkstra[i]);
    }
    free(dijkstra);
}

int* shp(Graph* g, int src , int dest,int printFlag){

    //create array with size equal to the biggest node ID in g
    int max_id = INT_MIN;
    //to fill with all node id's

    LinkedList * curr = g->AdjList;
    //fill the ID's and find it's max
    while(curr){
        max_id = MAX(max_id, curr->id);
        curr = curr->next;
    }
    int * que = (int*) malloc(sizeof (int) * (max_id + 1));
    int * dist = (int*) malloc(sizeof(int) * (max_id + 1));

    // int prev[max_id+1];
    //fill with initial values
    for(int i = 0 ; i < max_id +1; i++){
        dist[i] = INT_MAX-1;
        que[i] = INT_MIN;
        // prev[i] = -1;
    }
    curr = g->AdjList;

    while(curr){
        que[curr->id] = 1;
        curr = curr->next;
    }

    dist[src] = 0;

    int vertex;
    while(!isEmpty(que, (max_id + 1))){

        vertex = getMin(que, max_id + 1,dist);
        que[vertex] = INT_MIN; // remove it from que


        //get a pointer to the adjacency list of this node
        LinkedList * uNode = findNode(g->AdjList, vertex);
        Node* h = uNode->head;

        int altDist;
        //finding neighbors that still exists in que
        while (h)
        {
            if (que[h->id] != INT_MIN && dist[vertex] != INT_MAX-1) {// means it still inside que

                altDist = dist[vertex] + edgeLength(uNode , h->id);
                if (altDist < dist[h->id]){

                    dist[h->id] = altDist;
                    // prev[h->id] = vertex;
                }

            }
            h = h->next;
        }
    }

    if(printFlag){
        if(dist[dest]==INT_MAX-1){
        dist[dest]=-1;
        }
        printf("%d \n", dist[dest]);
        free(dist);
    }
    free(que);
    return dist;
}