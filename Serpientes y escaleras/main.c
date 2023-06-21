#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define tamTablero 10
typedef char element;

typedef struct node {
  element e[4];
  element type;
  struct node* prev;
  struct node* next;
} Node;

typedef struct list {
  Node* head;
  Node* tail;
} List;

void createList(List* list) {
  list->head = NULL;
  list->tail = NULL;
}

void insertAtHead(List* list, element *e, element type) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  strcpy(newNode->e, e);
  newNode->type = type;
  newNode->next = NULL;
  newNode->prev = NULL;
  if (list->head == NULL) {
    list->head = newNode;
    list->tail = newNode;
  } else {
    list->head->prev = newNode;
    newNode->next = list->head;
    list->head = newNode;
  }
}

void fillList(List* list) {
  element e[4] = {' ', ' ', ' ', '\0'};
  for (int i = 0; i < tamTablero * tamTablero; i++) {
    insertAtHead(list, e , '\0');
  }
}

Node* searchNode(List* l, int pos) {
  Node* current = l->head;
  int count = 0;
  while (current != NULL) {
    if (count == pos) {
      return current;
    }
    count++;
    current = current->next;
  }
  return NULL;  // Nodo no encontrado
}

int *posSnakeorLadder(List* l) {
  srand(time(NULL));
  int* arr = (int*)malloc(sizeof(int) * tamTablero);
  for (int i = 0; i < tamTablero; i++) {
    arr[i] = (rand() % (97 - 5 + 1)) + 5;
  }

  // Reemplazar los repetidos por otro número aleatorio
  for (int i = 0; i < tamTablero; i++) {
    for (int j = 0; j < tamTablero; j++) {
      if (arr[i] == arr[j] && i != j) {
        arr[i] = (rand() % (97 - 5 + 1)) + 5;
      }
    }
  }

  // Ordenar el arreglo de forma ascendente
  for (int i = 0; i < tamTablero; i++) {
    for (int j = 0; j < tamTablero; j++) {
      if (arr[i] < arr[j]) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }

  // Asignar los valores del arreglo a la lista
  for (int i = 0; i < tamTablero; i += 2) {
    Node* temp1 = searchNode(l, arr[i]);
    Node* temp2 = searchNode(l, arr[i + 1]);
    if (arr[i] % 2 == 0) {
      temp2->prev = temp1;
      sprintf(&temp1->type, "S%d", i + 1);
      sprintf(&temp2->type, "S%d", i + 1);
    } else {
      temp1->prev = temp2;
      sprintf(&temp1->type, "L%d", i + 1);
      sprintf(&temp2->type, "L%d", i + 1);
    }
  }

  return arr;
}

void printGrid(List* l) {
  Node* current = l->head;
  int count = 0;
  while (current != NULL) {
    if (count % tamTablero == 0) {
      printf("\n");
    }
    if (current->type != '\0') {
      printf("%s\t", &current->type);
    } else {
      printf("%d\t", count + 1);
    }
    current = current->next;
    count++;
  }
  printf("\n");
}

int tirarDados(){
    int aleatorio =  (rand() % 12) + 1;
    printf("\nDados: %d \n", aleatorio);
    return aleatorio;
}

void iniciarJuego(List *l){
  int modo;
  printf("\tSERPIENTES Y ESALEDERAS\t\n\n");
  printf("Elija el modo de juego:\n");
  printf("1.\tDos jugadores\t\n");
  printf("2.\tTres jugadores\t\n");
  printf("3.\tSalir\t\n");
  scanf("%d",&modo);
  switch (modo) {
    case 1:
      printf("Modo de juego: Dos jugadores\n");
      int jugador1 = 1,jugador2 = 1,turno;
      // strcpy(&l->head->e, "AB");
      printf("Turno del jugador %d\n", turno = (rand() % 2) + 1);
      while (jugador1 < 100 && jugador2 < 100) {
        if(turno == 1){
          jugador1 += tirarDados();
          printf("Jugador 1 avanza a: %d\n", jugador1);
          if(jugador1 > 100){
            jugador1 -= tirarDados();
            printf("Jugador 1: %d\n", jugador1);
          }
          if(jugador1 == 100){
            printf("Jugador 1 ha ganado\n");
            break;
          }
          turno = 2;
      }
      break;
    case 2:
      printf("Modo de juego: Tres jugadores\n");
      break;
    case 3:
      printf("Saliendo del juego...\n");
      break;
    default:
      printf("Opcion no valida\n");
      break;
  }

}

int main() {
  List l;
  createList(&l);
  fillList(&l);
  posSnakeorLadder(&l);
  printGrid(&l);

  // Liberar memoria
  Node* current = l.head;
  while (current != NULL) {
    Node* next = current->next;
    free(current);
    current = next;
  }
  return 0;
}
