#define MAX(a,b) (a > b) ? (a) : (b)
#define MIN(a,b) (a < b) ? (a) : (b)
#define EMPTY 0

typedef struct Node
{
    int id;
    int weight;
    struct Node* next;
}Node;

typedef struct LinkedList
{
    int id;
    Node * head;
    struct LinkedList * next;
}LinkedList;

typedef struct Graph
{
    int size;
    LinkedList * AdjList;
}Graph;

void newNode(Graph * g, int id, int* dest, int* weight, int size);

void createGraph(Graph * g);

void tsp(Graph * g,int* list,int size);

int* shp(Graph* g, int src,int dest,int printFlag);

void deleteNode(Graph * g, int id);

LinkedList* findNode(LinkedList* head,int id);

void freeList(Node* head);

void freeLinkedList(LinkedList* H);

int readInt();

void remove_node(Node** H, int data);

void remove_List(LinkedList** H,int id);

int isEmpty(int* arr, int size);

int getMin(int*arr, int size, int * dist );

int edgeLength(LinkedList *l, int ID);