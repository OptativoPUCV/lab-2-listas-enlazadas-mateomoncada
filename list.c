#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) 
{
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() 
{
    List * lista = (List *)malloc(sizeof(List));
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    return lista;
}

void * firstList(List * lista) 
{
    if(lista->head == NULL) return NULL;
    lista->current = lista->head;
    return lista->current->data; 
}

void * nextList(List * lista) 
{
    if(lista->current == NULL) return NULL;
    if(lista->current->next == NULL) return NULL;
    lista->current = lista->current->next;
    return lista->current->data;
}

void * lastList(List * lista) 
{
    if(lista->tail == NULL) return NULL;
    lista->current = lista->tail;
    return lista->current->data;
}

void * prevList(List * lista) 
{
    if(lista->current == NULL) return NULL;
    if(lista->current->prev == NULL) return NULL;
    lista->current = lista->current->prev;
    return lista->current->data;
}

void pushFront(List * lista, void * data) 
{
    Node * newNode = createNode(data);
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if(lista->head == NULL)
    {
        lista->head = newNode;
        lista->tail = newNode;
    }
    else
    {
        newNode->next = lista->head;
        lista->head->prev = newNode;
        lista->head = newNode;
    }

}

void pushBack(List * lista, void * data) 
{
    lista->current = lista->tail;
    pushCurrent(lista,data);
}

void pushCurrent(List * lista, void * data) 
{
    Node * newNode = createNode(data);
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if(lista->current->next != NULL)
    {
        newNode->next = lista->current->next;
        lista->current->next->prev = newNode;
    }
    else
    {
        lista->tail = newNode;
    }
    newNode->prev = lista->current;
    lista->current->next = newNode;
}

void * popFront(List * lista) 
{
    lista->current = lista->head;
    return popCurrent(lista);
}

void * popBack(List * lista) 
{
    lista->current = lista->tail;
    return popCurrent(lista);
}

void * popCurrent(List * lista)
{
        if (lista->current == NULL) 
        {
            return NULL;  
        }
    
        Node * auxiliar = lista->current;
        void*data = auxiliar->data;
        if (auxiliar->prev != NULL) 
        {
            auxiliar->prev->next = auxiliar->next;  
        } 
        else 
        {
            lista->head = auxiliar->next;  
        }
    
        if (auxiliar->next != NULL) 
        {
            auxiliar->next->prev = auxiliar->prev;  
        } 
        else 
        {
            lista->tail = auxiliar->prev;  
        }
    
        lista->current = auxiliar->next;  
    
        free(auxiliar);  
        return data;  
    }
    
void cleanList(List * lista) 
{
    while (lista->head != NULL) 
    {
        popFront(lista);
    }
}