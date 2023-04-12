#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node { // estructura del nodo
  void *data;
  Node *next;
  Node *prev;
};

struct List { // estructura de la lista
  Node *head;
  Node *tail;
  Node *current;
};

typedef List List;

Node *createNode(void *data) { // crea un nodo
  Node *new = (Node *)malloc(sizeof(Node));
  assert(new != NULL);
  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

List *createList() { // crea una lista
  List *list = (List *)malloc(sizeof(List));
  assert(list != NULL); // comprueba que la memoria se haya asignado correctamente

  list->head = NULL; // inicializa los punteros a NULL
  list->tail = NULL;
  list->current = NULL;

  return list; // retorna la lista
}

void *firstList(List *list) { // retorna el primer nodo de la lista
  if (list == NULL || list->head == NULL) { // si la lista es nula o el primer nodo es nulo
    return NULL;
  }
  list->current = list->head; // el nodo actual pasa a ser el primer nodo
  return list->current->data; // retorna el dato del primer nodo
}

void *nextList(List *list) { // retorna el siguiente nodo de la lista
  if (list == NULL || list->current == NULL || list->current->next == NULL) { // si la lista es nula o el nodo actual es nulo o el nodo siguiente es nulo
    return NULL;
  }
  list->current = list->current->next; // el nodo actual pasa a ser el siguiente
  return list->current->data;
}

void *lastList(List *list) {
  if (list == NULL || list->tail == NULL) { // si la lista es nula o el ultimo nodo es nulo
    return NULL;
  }

  list->current = list->tail;// el nodo actual pasa a ser el ultimo nodo
  return list->current->data; 
}

void *prevList(List *list) { // retorna el nodo anterior de la lista
  if (list == NULL || list->current == NULL || list->current->prev == NULL) { // si la lista es nula o el nodo actual es nulo o el nodo anterior es nulo
    return NULL;
  }
  list->current = list->current->prev; // el nodo actual pasa a ser el anterior
  return list->current->data; 
}

void *pushFront(List *list, void *data) { // agrega un nodo al inicio de la lista
  if (list == NULL) { // si la lista es nula
    return NULL;
  }
  Node *new = createNode(data); // crea un nuevo nodo
  if (list->head == NULL) { // si la lista esta vacia
    list->head = new;
    list->tail = new;
  } else { // si la lista no esta vacia
    list->head->prev = new;
    new->next = list->head;
    new->prev = NULL;
    list->head = new;
  }

  return new->data;
}

void pushBack(List *list, void *data) { // agrega un nodo al final de la lista
  if (list->tail == NULL) { // si la lista esta vacia
    pushFront(list, data);
    return;
  }
  list->current = list->tail;
  pushCurrent(list, data); // agrega un nodo despues del nodo actual
}

void pushCurrent(List *list, void *data) { // agrega un nodo despues del nodo actual
  if (list == NULL) { // si la lista es nula
    return;
  }

  Node *new = createNode(data);
  if (list->current == NULL) { // si el nodo actual es nulo
    list->head = new;
    list->tail = new;
    list->current = new;
    return;
  }
  new->prev = list->current;
  if (list->current->next != NULL) { // si el nodo siguiente no es nulo
    list->current->next->prev = new;
    new->next = list->current->next;
  } else { // si el nodo siguiente es nulo
    new->next = NULL;
    list->tail = new;
  }
  list->current->next = new;
}

void *popFront(List *list) { // elimina el primer nodo de la lista
  if (list == NULL || list->head == NULL) { // si la lista es nula o el primer nodo es nulo
    return NULL;
  }
  list->current = list->head;
  popCurrent(list); // elimina el nodo actual
}

void *popBack(List *list) { // elimina el ultimo nodo de la lista
  if (list == NULL || list->tail == NULL) { // si la lista es nula o el ultimo nodo es nulo
    return NULL;
  }
  list->current = list->tail;
  popCurrent(list); // elimina el nodo actual
}

void *popCurrent(List *list) { // elimina el nodo actual
  if(list == NULL || list->current == NULL) { // si la lista es nula o el nodo actual es nulo
    return NULL;
  }
  if(list->current->prev!= NULL){ // si es que el nodo anterior no es nulo
    list->current->prev->next = list->current->next;
  } else { // si es que el nodo anterior es nulo
    list->head = list->current->next;
  }
  if(list->current->next != NULL){ // si es que el nodo siguiente no es nulo
    list->current->next->prev = list->current->prev;
  } else { // si es que el nodo siguiente es nulo
    list->tail = list->current->prev;
  }
  list->current = list->current->next; // el nodo actual pasa a ser el siguiente
  free(list->current);
  return list->current->data;


}


void cleanList(List *list) { // elimina todos los nodos de la lista
  while (list->head != NULL) {
    popFront(list);
  }
}

