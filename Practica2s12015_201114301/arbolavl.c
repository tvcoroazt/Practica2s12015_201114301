#include "arbolavl.h"

#include<stdio.h>
#include<stdlib.h>

int i=0, d=0, fe=0;


void add(arbol *avl, int valor, nodo *padre){
    if(avl->raiz==NULL){
        nodo *n=malloc(sizeof(nodo));
        n->valor=valor;
        n->padre=NULL;
        n->Hizq=NULL;
        n->Hder=NULL;
        avl->raiz=n;
    }else if(valor<padre->valor){
        if(padre->Hizq==NULL){
            nodo *n=malloc(sizeof(nodo));
            n->valor=valor;
            n->padre=padre;
            n->Hizq=NULL;
            n->Hder=NULL;
            padre->Hizq=n;
            factorEquilibrio(avl->raiz);
        }else{
            add(avl,valor,padre->Hizq);
        }
    }else if(valor>padre->valor){
        if(padre->Hder==NULL){
            nodo *n=malloc(sizeof(nodo));
            n->valor=valor;
            n->padre=padre;
            n->Hizq=NULL;
            n->Hder=NULL;
            padre->Hder=n;
            factorEquilibrio(avl->raiz);
        }else{
            add(avl,valor,padre->Hder);
        }
    }
}

int factorEquilibrio(nodo *raiz){
    if(raiz==NULL){
        return 0;
    }else{
        i=factorEquilibrio(raiz->Hizq)+1;
        d=factorEquilibrio(raiz->Hder)+1;
    }
    raiz->i=i;
    raiz->d=d;
    fe=d-i;
    raiz->fe=fe;
    if(i>d){
        return i;
    }else{
        return d;
    }
}


node * insert(node *T,int x)
{
    if(T==NULL)
    {
        T=(node*)malloc(sizeof(node));
        T->data=x;
        T->left=NULL;
        T->right=NULL;
    }
    else
        if(x > T->data)
        {
            T->right=insert(T->right,x);
            if(FE(T)==-2){
                if(x>T->right->data){
                    T=RR(T);
                }else{
                    T=RL(T);
                }
            }
        }
        else
            if(x<T->data)
            {
                T->left=insert(T->left,x);
                if(FE(T)==2){
                    if(x < T->left->data){
                        T=LL(T);
                    }else{
                        T=LR(T);
                    }
                }
            }
        T->ht=height(T);
    return(T);
}

int height(node *T)
{
   int lh,rh;
   if(T==NULL){
    return(0);
   }
   if(T->left==NULL){
     lh=0;
   }
   else{
     lh=1+T->left->ht;
   }
   if(T->right==NULL)
      rh=0;
   else
      rh=1+T->right->ht;
   if(lh>rh)
      return(lh);
   return(rh);
}
node * rotateright(node *x)
{
    node *y;
    y=x->left;
    x->left=y->right;
    y->right=x;
    x->ht=height(x);
    y->ht=height(y);
   return(y);
}
node * rotateleft(node *x)
{
    node *y;
    y=x->right;
    x->right=y->left;
    y->left=x;
    x->ht=height(x);
    y->ht=height(y);
   return(y);
}

node *RR(node *T)
{
    T=rotateleft(T);
    return(T);
}

node * LL(node *T)
{
   T=rotateright(T);
   return(T);
}

node *LR(node *T)
{
   T->left=rotateleft(T->left);
   T=rotateright(T);
   return(T);
}

node * RL(node *T)
{
   T->right=rotateright(T->right);
   T=rotateleft(T);
   return(T);
}

int FE(node *T)
{
   int lh,rh;
   if(T==NULL){
     return(0);
   }
   if(T->left==NULL){
      lh=0;
   }
   else{
      lh=1+T->left->ht;
   }

   if(T->right==NULL)
      rh=0;
   else
      rh=1+T->right->ht;
   return(lh-rh);
}



void recorrerEnOrden(node *T)
{
    if(T)
    {
        recorrerEnOrden(T -> left);
        printf("%d,", T -> data);
        archivoDOT(T);
        recorrerEnOrden(T -> right);
    }
}

void archivoDOT(node *T)
{
    f= fopen("GraficaAVL.dot","a+");
    fprintf(f,"\"%s %d\" %s %d %s \n","node",T->data,"[label=\"<f0> | <f1>",T->data," | <f2>\"];");
    fclose(f);
    if(T -> left){
    f= fopen("GraficaAVL.dot","a+");
    fprintf(f,"\"%s %d\" %s %d %s \n","node",T->left->data,"[label=\"<f0> | <f1>",T->left->data," | <f2>\"];");
    fclose(f);
    f= fopen("GraficaAVL.dot","a+");
    fprintf(f,"\"%s %d\" %s %d %s \n","node",T->data,"[label=\"<f0> | <f1>",T->data," | <f2>\"];");
    fclose(f);
    f= fopen("GraficaAVL.dot","a+");
    fprintf(f, "\"%s %d\" %s %d\" %s \n","node",T->data,":f0 -> \"node",T->left->data,":f1;");
    fclose(f);
    }
    if(T -> right){
    f= fopen("GraficaAVL.dot","a+");
    fprintf(f, "\"%s %d\" %s %d %s \n","node",T->right->data,"[label=\"<f0> | <f1>",T->right->data," | <f2>\"];");
    fclose(f);
    f= fopen("GraficaAVL.dot","a+");
    fprintf(f, "\"%s %d\" %s %d %s \n","node",T->data,"[label=\"<f0> | <f1>",T->data," | <f2>\"];");
    fclose(f);
    f= fopen("GraficaAVL.dot","a+");
    fprintf(f, "\"%s %d\" %s %d\" %s \n","node",T->data,":f2 -> \"node",T->right->data,":f1;");
    fclose(f);
    }

}

