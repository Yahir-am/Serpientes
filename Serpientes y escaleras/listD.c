#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

void createList(List *list) {
  list->head = NULL;
  list->tail = NULL;
}
void insertAtHead(List *list, element e, element type){
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->e = e;
  newNode->type = type;
  newNode->next = NULL;
  newNode->prev = NULL;
  if (list->head == NULL) {
    list->head = newNode;
    list->tail = newNode;
  } else {
    list->head->prev = newNode;
    list->head = newNode;
  }
}
void fillList(List *list) {
  for(int i = 0; i < tamTablero*tamTablero; i++){
    insertAtHead(list,' ',' ');
  }
}



Node *searchNode(List *l, int pos){
  Node* current = l->head;
  int count = 0;
  while (current != NULL) {
    if (count == pos) {
      return current;
    }
    count++;
    current = current->next;
  }
}

int *posSnakeorLadder(List *l){
  srand(time(NULL));
  int *arr = (int *)malloc(sizeof(int)*tamTablero);
  for(int i = 0; i < tamTablero; i++){
    arr[i] = (rand() % (13 - 3 + 1)) + 3;
  }
  //reemplazar los repetido por otro random
  for(int i = 0; i < tamTablero; i++){
    for(int j = 0; j < tamTablero; j++){
      if(arr[i] == arr[j] && i != j){
        arr[i] = (rand() % (14 - 3 + 1)) + 3;
      }
    }
  }
  //ordenar el arreglo de forma ascendente
  for(int i = 0; i < tamTablero; i++){
    for(int j = 0; j < tamTablero; j++){
      if(arr[i] < arr[j]){
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
  return arr;
}

//con los valores del arreglo se asigna la serpiente o escalera en la lista
void assignSnakeorLadder(List *l){
  int *arr = posSnakeorLadder(l);
  for(int i = 0; i < tamTablero; i++){
    Node *temp = searchNode(l, arr[i]);
    temp->type = 'S';
  }
}
void printGrid(List *l){
  Node *temp = l->head;
  for(int i = 0; i < tamTablero*tamTablero; i++){
    printf("--%d--\n", i+1);
    printf("  %c  \n", temp->e);
    printf("--%c--\n\n", temp->type);
  }
}

void deleteAtHead(List *list) {
  if (list->head == NULL) {
    return;
  } else if (list->head == list->tail) {
    free(list->head);
    list->head = NULL;
    list->tail = NULL;
  } else {
    Node *temp = list->head;
    list->head = list->head->next;
    list->head->prev = NULL;
    free(temp);
  }
}
