#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// Estructura de datos que representa un nodo, posee un valor y un puntero al siguiente nodo.
typedef struct creaNodos
{
	char proteinas;
	struct creaNodos *sig;
}

Nodo;

// Estructura de datos que representa una lista enlazada, posee un puntero al inicio de la lista.
typedef struct lista_enlazada
{
    Nodo* puntero;
}

tListaE;

//Crea una lista enlazada vacia y la retorna.
tListaE* crear_lista()
{
    tListaE* lista0 = (tListaE*) malloc(sizeof(tListaE));
    lista0->puntero = NULL;
    return lista0;
}

//Recorre la lista desde el inicio, liberando elemento a elemento la memoria utilizada.
void destruir_lista(tListaE* lista_enlazada)
{
    Nodo* cabeza = lista_enlazada->puntero;
    while (cabeza != NULL)
    {
        lista_enlazada->puntero = cabeza->sig;
        free(cabeza);
        cabeza = lista_enlazada->puntero;
    }
    free(lista_enlazada);
}

//Crea un nodo nuevo con el elemento entregado y lo agrega al inicio de la lista.
void agregar_elemento(tListaE* lista_enlazada, char elem)
{
    Nodo* nodo = (Nodo*) malloc(sizeof(Nodo));
    nodo->proteinas = elem;
    nodo->sig = lista_enlazada->puntero;
    lista_enlazada->puntero = nodo;
}


//Analizar las condiciones de mutacion para determinar si la cadena es humana o mutante.

int detectar_mutante(tListaE* lista_enlazada)
{
    //Variables de conteo que aparecen consecutivamente
    int n_guaninas = 0;
    int n_adeninas = 0;
    int n_citosinas = 0;

    //Variable para llevar registro de que se cumplen condiciones
    int es_mutante = 0;
    Nodo* nodo = lista_enlazada->puntero;

    //Revisar si la cadena termina con timina
    if (nodo->proteinas != 't')
    {
        return 0;
    }

    while (nodo != NULL)
    {
        //Actualizar contadores
        if (nodo->proteinas == 'g')
        {
            n_guaninas++;
            n_adeninas = 0;
            n_citosinas = 0;

        }
        else if (nodo->proteinas == 'a')
        {
            n_adeninas++;
            n_guaninas = 0;
            n_citosinas = 0;
        }
        else if (nodo->proteinas == 'c')
        {
            n_citosinas++;
            n_adeninas = 0;
            n_guaninas = 0;
        }
        else
        {
            n_adeninas = 0;
            n_guaninas = 0;
            n_citosinas = 0;
        }

        //Revisar condiciones de mutacion
        if (n_guaninas == 3)
        {
            return 0;
        }
        else if (n_adeninas == 2 || n_citosinas == 2)
        {
            es_mutante = 1;
        }

        //Actualizar nodo
        nodo = nodo->sig;
    }
    if (es_mutante)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    //Solicitar nombre de archivo
    char nomArch[300];
    printf("Ingresa el nombre del archivo: ");
    gets(nomArch);

    FILE* archivo;

    //Abrir archivo
    archivo = fopen(nomArch, "r");
    if (archivo == NULL)
    {
        printf("Error, archivo invalido.");
        return 1;
    }

    //Variables para almacenar la cadena de adn en una lista
    tListaE* lista0 = crear_lista();

    //Leer caracter a caracter el archivo
    char letra;
    while ((letra = fgetc(archivo)) != EOF)
    {
    //Si el archivo no contiene caracteres correspondientes a bases nitrogenadas se indica el error y termina el programa
        if (letra != 'a' && letra != 'c' && letra != 'g' && letra != 't')
        {
            printf("Contenido invalido dentro del archivo.");
            return 1;
        }
        agregar_elemento(lista0, letra);
    }
    //Cerrar el archivo
    fclose(archivo);

    //Procesar la lista para detectar humano o mutante
    int es_mutante = detectar_mutante(lista0);
    if (es_mutante)
    {
        printf("\nMutante\n\n");
    }
    else
    {
        printf("\nHumano\n\n");
    }
    destruir_lista(lista0);
    return 0;
}
