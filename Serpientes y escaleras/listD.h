
#define tamTablero 4

#define element char

typedef struct node {
  element e;
  element type;
  struct node *prev;
  struct node *next;
}Node;


typedef struct list{
  Node *head;
  Node *tail;
}List;

//Prototypes
void createList(List *l);
void insertAtHead(List *l, element e, element type);
void fillList(List *l);
Node *searchNode(List *l, int pos);
int *posSnakeorLadder(List *l);
void assignSnakeorLadder(List *l);
void printfGird(List *l);
void deleteAtHead(List *l);


#include "listD.c"