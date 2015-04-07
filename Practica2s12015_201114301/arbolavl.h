#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *f;


typedef struct node
{
    int data;
    struct node *left,*right;
    int ht;
}node;

typedef struct nodoAVL{
        int valor;
        int i;
        int d;
        int fe;
        struct nodoAVL *Hizq;
        struct nodoAVL *Hder;
        struct nodoAVL *padre;
}nodo;

typedef struct arbolAVL{
        nodo *raiz;
}arbol;



node *insert(node *,int);
void  inorder(node *);

node *rotateright(node *);
node *rotateleft(node *);
node *RR(node *);
node *LL(node *);
node *LR(node *);
node *RL(node *);
int FE(node *);
int   height( node *);

void add(arbol *avl, int valor, nodo *padre);
int factorEqulibrio(nodo *raiz);
void verificarEquilibrio(arbol *avl, nodo *hoja);
void equilibrar(arbol *avl, int rotacion, nodo *n, nodo *n1, nodo *n2);
void ii(arbol *avl, nodo *n, nodo *n1);
void dd(arbol *avl, nodo *n, nodo *n1);
void id(arbol *avl, nodo *n, nodo *n1, nodo *n2);
void di(arbol *avl, nodo *n, nodo *n1, nodo *n2);
void InOrden(nodo *raiz);





#endif // ARBOLAVL_H
