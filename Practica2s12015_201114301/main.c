#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include "arbolavl.h"

 #define GNUPLOT_PATH "/usr/share/gnuplot"

/* VARIABLES GLOBALES */

time_t iniciotiempo,fintiempo;
double diferencia;
double difTBurbuja, diferenciaentrada, difTQuick;

clock_t t_ini, t_fin;
double secs;


float t1, t2, t3, t4;
FILE *file;
char *path;
int numDatos=0;
node *raiz = NULL;
int tamano;

FILE *gBurbu;
FILE *gQuick;
FILE *gInser;


int op;
char nombrearch[30];

typedef struct _nodolista {
   int valor;
   struct _nodolista *siguiente;
   struct _nodolista *anterior;
} tipoNodolista;
typedef tipoNodolista *pNodol;
typedef tipoNodolista *Lista;

void diferencia_tempos (void)
{
  time_t inicio,fin;
  char texto_teclado [50];
  double diferencia;

  time (&inicio);
  time (&fin);
  //diferencia = difftime (fin,inicio);
  diferencia = fin - inicio;
  printf ("Hola %s.\n", texto_teclado);
  printf ("Levouche %.2f segundos escribir o teu nome.\n", diferencia );
}


void ingresarArbol(){
    file = fopen(path,"r");
    if (file==NULL){
        printf(" Archivo no encontrado o no existe");
    }else{
        char buf[1500]; numDatos=0;
        while (fgets(buf, sizeof buf, file) != NULL){
            int val = atoi(buf);
            raiz = insert(raiz, val);
            numDatos++;
        }
        fclose(file);
    }
}


// ---------------- PRUEBAS

void leerarchivo (Lista *l){
        char caracteres[100];
        int val;
        file = fopen(path,"r");
       	if (path == NULL){
		printf("\n Error de apertura del archivo. \n\n");
        }else{
	    while (feof(path) == 0)
	    {
                fgets(caracteres,100,path);
                val = atoi(caracteres);
                if (val != 0){
                Insertarlista(l,val);
                }
	    }
        }
        fclose(path);
}
void Insertarlista(Lista *lista, int v)
{
   pNodol nuevo, actual;
   nuevo = (pNodol)malloc(sizeof(tipoNodolista));
   nuevo->valor = v;
   actual = *lista;
   if(actual) while(actual->anterior) actual = actual->anterior;
   if(!actual || actual->valor ) {
      nuevo->siguiente = actual;
      nuevo->anterior = NULL;
      if(actual) actual->anterior = nuevo;
      if(!*lista) *lista = nuevo;
   }
   tamano=tamano+1;
}
void MostrarLista(Lista lista)
{
   pNodol nodo = lista;
   if(!lista) {printf("Lista vacía");}
   nodo = lista;
      while(nodo->anterior) nodo = nodo->anterior;
      printf("El orden Por Burbuja es: \n ");
      while(nodo) {
         printf("%d ,", nodo->valor);
         nodo = nodo->siguiente;
      }
}
void OrdenarBurbuja(Lista *lista){
    pNodol nodo=*lista;
    pNodol nodo2;
    int aux;
    while (nodo->anterior) {nodo=nodo->anterior;}
    while (nodo != NULL){
        aux=nodo->valor;
        nodo2=nodo->siguiente;
        while (nodo2 != NULL){
            if(nodo->valor > nodo2->valor){
                int temp;
                temp=nodo->valor;
                nodo->valor=nodo2->valor;
                nodo2->valor=temp;
            }
            nodo2=nodo2->siguiente;
        }
        nodo=nodo->siguiente;
    }
}

void ingresoVector(Lista lista , int t){
    int vector [t];
    int k=0;
    int c =t;
    pNodol nodo =lista;
    while (nodo->anterior) {nodo=nodo->anterior;}
    while (nodo){
        vector[k]=nodo->valor;
        k++;
        nodo=nodo->siguiente;
    }
    OrdenarSort(vector,c);
}
void MostrarVector(int v[], int d){

    printf("El orden por quicksort \n");
    int i;
    for (i=0; i < d; i++) {
	printf("%d,", v[i]);
    }
    printf("\n");
}
void  OrdenarSort(int v2[], int d){
    int insercion;
    int siguiente;
    for (siguiente=1; siguiente < d; siguiente++) {
        insercion=v2[siguiente];

        int moverElemento =siguiente;
        while (moverElemento >0 && v2[moverElemento-1]> insercion){
            v2[moverElemento]= v2[moverElemento-1];
            moverElemento--;
        }
        v2[moverElemento] =insercion;
    }
    MostrarVector(v2,d);
}
// FIN DE NUEVAS LISTAS

void ingresarLista(int a[]){
    file = fopen(path,"r");
    if (file==NULL){
        printf(" Archivo no encontrado o no existe");
    }else{
        char buf[15];
        int i = 0;
        while (fgets(buf, sizeof buf, file) != NULL){
            int val = atoi(buf);
            a[i] = val;
            i++;
        }
        fclose(file);
    }
}

void imprimirLista(int a[]){
    int k=0;
    printf("\n");
    for(k=0;k<numDatos;k++){
        printf("%i,",a[k]);
    }
}

void ordenamientoBurbuja(int a[]){
    int i=0, j=0, auxI=0;
    for(i=0; i<(numDatos-1) ; i++){
        for(j=0; j<(numDatos-i-1) ; j++){
            if(a[j]>a[j+1]){
                auxI = a[j];
                a[j]=a[j+1];
                a[j+1] = auxI;
            }

        }
    }
    auxI=0;
}

void burbuja(int a[], FILE *grafica3){
    int i=0, j=0, auxI=0;
    int datos = 1;
    clock_t inicio = clock();
    for(i=0; i<(numDatos-1) ; i++){
        for(j=0; j<(numDatos-i-1) ; j++){
            if(a[j]>a[j+1]){
                auxI = a[j];
                a[j]=a[j+1];
                a[j+1] = auxI;
            }
        }
        clock_t aux_f = clock();
        fprintf(grafica3, "%f %i \n", ((aux_f-inicio))/(float)CLOCKS_PER_SEC,datos);
        t3 = ((aux_f-inicio))/(float)CLOCKS_PER_SEC;
        datos++;
    }
    auxI=0;
}

void quickSort(int x[numDatos], int first, int last){
    int pivot, j, temp, i;

    if(first<last){
        pivot = first;
        i = first;
        j = last;

        while(i<j){
            while(x[i]<=x[pivot]&&i<last)
                i++;
            while(x[j]>x[pivot])
                j--;
            if(i<j){
                temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
        temp = x[pivot];
        x[pivot] = x[j];
        x[j] = temp;
        quickSort(x, first, j-1);
        quickSort(x, j+1, last);
    }
}

void graficarburbu(){

}

/* AZTECA GUATEMALA   ---------------------------------- */
struct nodoArbol {
 struct nodoArbol *ptrIzq;
 int dato;
 struct nodoArbol *prtDer;
};

typedef struct nodoArbol NodoArbol;
typedef NodoArbol *ptrNodoArbol;

void insertaNodo2(ptrNodoArbol *ptrArbol, int valor)
{
    if (*ptrArbol == NULL) {
      *ptrArbol = malloc(sizeof(NodoArbol));
        if (*ptrArbol != NULL) {
             (*ptrArbol)->dato = valor;
             (*ptrArbol)->ptrIzq = NULL;
             (*ptrArbol)->prtDer = NULL;
     } else {
         printf("no se inserto %d. No hay memoria disponible. \n", valor);
       }
     } else {

     if (valor < (*ptrArbol)->dato) {
        insertaNodo2(&((*ptrArbol)->ptrIzq), valor);
     } else if (valor > (*ptrArbol)->dato) {
        insertaNodo2(&((*ptrArbol)->prtDer), valor);
     } else {
       printf("dup \n");
       }
     }
}

void archivofgets(char nombre[30]){
    int i;
    int numero;
    ptrNodoArbol ptrRaiz = NULL;
    FILE *archivolec;
  	char caracteres[10000];
  	archivolec = fopen(nombre,"r");
  	if (archivolec == NULL){
  	  printf("\n Archivo no existe - Vuelva a intentar \n");
  	  exit(1);
  	}
  	printf("\n Los numeros insertados son: \n \n");
 	while (feof(archivolec) == 0)
 	{
 		fgets(caracteres,100,archivolec);
 	/*	printf("%s",caracteres);*/

 		   /* numero = atoi(cadena);*/

     numero = atoi(caracteres);
     printf("\n %d", numero);
     insertaNodo2(&ptrRaiz, numero);
 	}

        system("PAUSE");

        fclose(archivolec);


	/*return 0;*/
}

void enOrden(ptrNodoArbol ptrArbol)
{
    if (ptrArbol != NULL) {
      enOrden(ptrArbol->ptrIzq);
      printf("\n %d", ptrArbol->dato);
      enOrden(ptrArbol->prtDer);
    }
}

void archivofgetc(char nombre[30]){
    FILE *archivolec;
  	char caracteres[100];
  	char caracter;
  	archivolec = fopen(nombre,"r");

  	if (archivolec == NULL){
  	  printf("\n Archivo no existe - Vuelva a intentar \n");
  	  exit(1);
  	}
  	printf("\n El contenido del archivo de prueba es \n\n");
 	while (feof(archivolec) == 0)
 	{
        caracter = fgetc(archivolec);
 		printf("%c",caracter);
 	}
        system("PAUSE");

        fclose(archivolec);
/*return 0;*/
}


void escribirArchivo(){
    FILE *aprueba;
    int num=1;
    aprueba = fopen ("prueba.txt", "w");
    while(num != 40000){
        fprintf(aprueba, "%d \n",num);
        num++;
    }
    fclose (aprueba);
}

void pruebaGNUPLOT(){
     FILE *gp;
     gp = popen(GNUPLOT_PATH, "w");
     if(gp == NULL){
       fprintf(stderr, "Oops, I can't find %s.", GNUPLOT_PATH);
       exit(EXIT_FAILURE);
       }
     fprintf(gp, "set term aqua title \"Function A\" \n");
     fprintf(gp, "set samples 2048 \n");
     fprintf(gp, "plot [-512:512] -abs(x*sin(sqrt(abs(x))))+400");
    fflush(gp);
     pclose(gp);


}




int main()
{
    system("clear");
    Lista lista = NULL;
    FILE *archivoGAVL;
    FILE *archivoGBURBU;

    char lectura[100];

    archivoGAVL = fopen("GraficaAVL.dot","w");
    fprintf(archivoGAVL,"%s\n","digraph G { \nnode [shape=record, height=.1];");
    fclose(archivoGAVL);

    archivoGBURBU = fopen("GraficaBURBUJA.dot","w");
    fprintf(archivoGBURBU,"%s\n","digraph G { \nnode [shape=record, height=.1];");
    fclose(archivoGBURBU);

    escribirArchivo();


    printf("\n   ------  BIENVENIDO AMIGO ------- \n \n");

   /* printf("Ingrese el nombre del archivo a leer DE PRUEBA 1\n");
    scanf("%s",nombrearch);
    archivofgets(nombrearch);


         printf("\n \n El recorrido En - orden es: \n");*/
       /*  enOrden(ptrRaiz);*/

      do{
        printf("1- Ingrese el archivo al Arbol \n");
        printf("2- Analizar e insetar al Arbol los datos \n");
        printf("3- Ordenamiento de Burbuja \n");
        printf("4- Ordenamiento Quicksort \n");
        printf("5- Reporte de Salida \n");
        printf("6- Graficar AVL \n");
        printf("7- Graficas de ejecucion \n");
        printf("8- Mostrar contenido de archivo \n");
        printf("9- Salir \n");
        printf("Seleccione:  ");
        scanf("%d",&op);
        switch(op)
        {
            case 1:

                printf("Ingrese el nombre del archivo: \n");
                path = (char *)malloc(128 *sizeof(char));
                scanf("%s", path);
               // printf("Contenido del archivo es: \n");
               // archivofgets(path);
              //  time (&iniciotiempo);
                time (&iniciotiempo);
                t_ini = clock();

                ingresarArbol();  // INGRESA AL ARBOL

                time (&fintiempo);
                t_fin = clock();
                diferenciaentrada = (double)(fintiempo - iniciotiempo) / CLOCKS_PER_SEC;
                printf("\n Ingresar Arbol - %f segundos \n \n",diferenciaentrada);
                break;
            case 2:
                time (&iniciotiempo);
                t_ini = clock();
                if(raiz==NULL){
                    printf("ARBOL SIN CONTENIDO O VACIO");
                }else{
                   printf("\n ----- METODO DE ORDENAMIENTO EN-ORDEN ---- \n");
                   recorrerEnOrden(raiz);
                }
                time (&fintiempo);
                t_fin = clock();
                diferencia = (double)(fintiempo - iniciotiempo) / CLOCKS_PER_SEC;
                printf("\n Recorrido arbol En-Orden - %f segundos \n \n",diferencia);
                system("pause");
                break;
            case 3: // ORDENAR POR METODO DE BURBUJA
                //postorden(raiz);
                if(!path){
                    printf("INGRESE UN ARBOL O UN ARCHIVO");
                }else{
                    t_ini = clock();
                    time (&iniciotiempo);
                    int listadatos[numDatos];

                    ingresarLista(&listadatos);

                   // leerarchivo(&lista);

                    ordenamientoBurbuja(&listadatos);



                    //OrdenarBurbuja(&lista);
                   //MostrarLista(lista);
                    printf("\n ----- METODO DE BURBUJA --- \n");
                    imprimirLista(listadatos);
                    t_fin = clock();
                    time (&fintiempo);
                    difTBurbuja = (double)(fintiempo - iniciotiempo) / CLOCKS_PER_SEC;
                    printf("\n Ordenamiento Burbuja - %f segundos \n \n",difTBurbuja);
                }
                system("pause");
                break;
            case 4:
                if(!path){
                    printf("INGRESE ALGO");
                }else{
                    time (&iniciotiempo);
                    int listadatos[numDatos];
                    ingresarLista(listadatos);
                    quickSort(listadatos,0,numDatos);
                    printf("\n ----- METODO DE QUICK SORFT --- \n");
                    imprimirLista(listadatos);

                    time (&fintiempo);
                    difTQuick = (double)(fintiempo - iniciotiempo) / CLOCKS_PER_SEC;
                    printf("\n Ordenamiento Quicksort - %f segundos \n \n",difTQuick);
                }
                system("pause");
                break;
            case 5:
                printf("\n ----- SALIDAS DE LOS DATOS--- \n");
                printf("Ingresar Arbol - %f segundos \n",diferenciaentrada);
                printf("Recorrido arbol - %f segundos \n",diferencia);
                printf("Ordenamiento Burbuja - %f segundos \n",difTBurbuja);
                printf("Ordenamiento Quicksort - %f segundos \n \n ",difTQuick);
                system("pause");
                break;
            case 6:
                printf("\n Espere generando grafica..............");
                archivoGAVL= fopen("GraficaAVL.dot","a+");
                fprintf(archivoGAVL,"%s\n","}");
                fclose(archivoGAVL);
                printf("\n  GRAFICA AVL GENERADA CORRECTAMENTE..........  \n \n");
                system("dot -Tpng GraficaAVL.dot -o AVL.png");
             //   system("nohup display AVL.png &" );
                break;
            case 7:
                 printf("hola mundo \n");
                 pruebaGNUPLOT();
                 //GRAFICA DE BURBUJA
                 gBurbu= fopen("gBurbuja.txt","w");
                fprintf(gBurbu,"set xlabel 'Tiempo (s)'\nset ylabel 'No. Nodos'\nset xrange[-%lf:%lf]\nset yrange[-%lf:%lf]\n plot x**2-2*x+1 title 'O(n^2) Ordenamiento Burbuja'", 1,4, 1,5);
               fclose(gBurbu);
                break;
            case 8:
                 printf("\n Contenido del archivo es: \n");
                 archivofgets(path);
                break;
            case 9:
                    time (&iniciotiempo);
                    int *listaburbuja;
                    listaburbuja = (int*)malloc(numDatos *sizeof(int));
                    ingresarLista(listaburbuja);

                    gBurbu = fopen("gBurbuja.txt", "w");
                    burbuja(listaburbuja, gBurbu);
                    fclose(gBurbu);
                    free(listaburbuja);
                    time (&fintiempo);
                    difTBurbuja = (double)(fintiempo - iniciotiempo) / CLOCKS_PER_SEC;
                    printf("\n Ordenamiento Burbuja - %f segundos \n \n",difTBurbuja);

                break;
        }// End switch
    }while(op!=0);








    return 0;
}




