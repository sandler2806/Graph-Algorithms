#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "headers.h"

LinkedList* findNode(LinkedList* head,int id){

    while(head){
        if(head->id==id){
            return head;
        }
        head=head->next;
    }
    return NULL;

}
void newNode(Graph * g,int id, int* dest, int* weight, int size){

    if(size<1){
        return;
    }
    LinkedList* oldNodeList=findNode(g->AdjList,id);

    Node* head=(Node*)malloc(sizeof(Node));
    Node* node=head;
    node->id=dest[0];
    node->weight=weight[0];
    node->next=NULL;
    for(int i=1;i<size;i++){
        Node* t=(Node*)malloc(sizeof(Node));
        t->id=dest[i];
        t->weight=weight[i];
        t->next=NULL;
        node->next=t;
        node=node->next;
    }


    if(oldNodeList==NULL){//create new node and connect it
        LinkedList* NodeList=(LinkedList*)malloc(sizeof(LinkedList));
        NodeList->id=id;
        NodeList->head=head;
        NodeList->next=g->AdjList;
        g->AdjList=NodeList;
        g->size++;

    }
    else{//delete old node and connect new one
        Node* oldNode=oldNodeList->head;
        freeList(oldNode);
        oldNodeList->head=head;

    }

}

void createGraph(Graph * g){

    //resetting the adjacency list if it was previously assigned

    if((g->AdjList)){
        freeLinkedList(g->AdjList);
    }

    g->AdjList = (LinkedList*) malloc(sizeof(LinkedList));


    int size, id;

    g->AdjList->id=0;
    g->AdjList->head=NULL;
    g->AdjList->next=NULL;
    LinkedList* list=g->AdjList;
    scanf("%d", &size);
    g->size = size; //read size from stdin
    for (int i = 1; i < size; i++)
    {
        LinkedList* temp = (LinkedList*) malloc(sizeof(LinkedList));
        temp->next = NULL;
        temp->head=NULL;
        temp->id=i;
        list->next=temp;
        list=list->next;

    }
    int counter,check;
    int weight[size];
    int dest[size];
    char c;
    getc(stdin);
    scanf("%c",&c);

    while (1)
    {
        scanf("%d",&id);
        counter=0;

        while (1)
        {
            c = getc(stdin);
            if(c != ' ' ){
                counter++;
                break;
            }
            scanf("%d",&dest[counter]);
            check=scanf("%d",&weight[counter++]);

            if(check==0){
                c = getc(stdin);
                if(c!='n') {
                    ungetc(c, stdin);
                }
                break;
            }

        }
        newNode(g,id,dest,weight,counter -1);

        if(c!='n'){
            break;
        }

    }

}

void deleteNode(Graph * g,int id){
    LinkedList* list=g->AdjList;
    while(list){
        remove_node(&(list->head),id);
        list=list->next;
    }
    list=findNode(g->AdjList,id);
    remove_List(&(g->AdjList),id);
    g->size--;
}


void freeList(Node* head)
{
    Node* tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
void freeLinkedList(LinkedList* H)
{
    LinkedList* temp;
    while (H != NULL)
    {
        temp = H;
        H=H->next;
        freeList(temp->head);
        free(temp);
    }

}

void remove_node(Node** H, int id){
    if(!*H)
        return;
    if((*H)->id == id){
        Node *tmp = *H;
        *H = (*H)->next;
        free(tmp);
    }
    Node* tmp = *H;
    while(tmp->next && tmp->next->id != id)
        tmp = tmp->next;
    if(!tmp->next)
        return;
    Node *tmp2 = tmp->next;
    tmp->next = tmp->next->next;
    free(tmp2);
}

void remove_List(LinkedList** H, int id){
    if(!*H)
        return;
    if((*H)->id == id){
        LinkedList *tmp = *H;
        *H = (*H)->next;
        freeList(tmp->head);
        free(tmp);
    }
    LinkedList* tmp = *H;
    while(tmp->next && tmp->next->id != id)
        tmp = tmp->next;
    if(!tmp->next)
        return;
    LinkedList *tmp2 = tmp->next;
    tmp->next = tmp->next->next;
    freeList(tmp2->head);
    free(tmp2);
}


int isEmpty(int* arr, int size){

    for(int i = 0 ; i < size; i++){

        if(arr[i] != INT_MIN){ //int_min means empty cell in out implementation
            return 0;
        }
    }
    return 1;
}

int getMin(int * arr, int size, int * dist ){
    int min = INT_MAX;
    int min_id = -1;
    for(int i = 0 ; i < size; i++){

        if(arr[i] != INT_MIN && min > dist[i]){ //to ignore empty cells
            min = dist[i];
            min_id = i;
        }

    }
    return min_id;
}

int edgeLength(LinkedList *l, int ID){

    Node * H = l->head;
    while(H){

        if(H->id == ID ){
            return H->weight;
        }

        H = H->next;
    }

    return INT_MAX;

}