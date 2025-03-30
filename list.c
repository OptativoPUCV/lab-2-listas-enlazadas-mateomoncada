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

void * firstList(List * list) 
{
    if(list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data; 
}

void * nextList(List * list) 
{
    if(list->current == NULL) return NULL;
    if(list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) 
{
    if(list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) 
{
    if(list->current == NULL) return NULL;
    if(list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) 
{
    Node * newNode = createNode(data);
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if(list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }

}

void pushBack(List * list, void * data) 
{
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
    Node * newNode = createNode(data);
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if(list->current->next != NULL)
    {
        newNode->next = list->current->next;
        list->current->next->prev = newNode;
    }
    else
    {
        list->tail = newNode;
    }
    newNode->prev = list->current;
    list->current->next = newNode;
}

void * popFront(List * list) 
{
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) 
{
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list)
{
        if (list->current == NULL) 
        {
            return NULL;  
        }
    
        Node * auxiliar = list->current;
        void*data = auxiliar->data;
        if (auxiliar->prev != NULL) 
        {
            auxiliar->prev->next = auxiliar->next;  
        } 
        else 
        {
            list->head = auxiliar->next;  
        }
    
        if (auxiliar->next != NULL) 
        {
            auxiliar->next->prev = auxiliar->prev;  
        } 
        else 
        {
            list->tail = auxiliar->prev;  
        }
    
        list->current = auxiliar->next;  
    
        free(auxiliar);  
        return data;  
    }
    
void cleanList(List * list) 
{
    while (list->head != NULL) 
    {
        popFront(list);
    }
}