#ifndef PUZLE_H
#define PUZLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "salas.h"

#define max_id_puzle 4
#define max_nombre_puzle 16
#define max_tipo_puzle 10
#define max_descripcion_puzle 151
#define max_solucion_puzle 51

typedef struct{
    char id_puzle[max_id_puzle];
    char nombre[max_nombre_puzle];
    int id_sala;
    char tipo[max_tipo_puzle];
    char descripcion[max_descripcion_puzle];
    char solucion[max_solucion_puzle];
}puzle;

//precondicion: Entra un array de puzles vacio.
//postcondicion: carga todos los datos en las estructuras/registros, desde el archivo de texto "puzles.txt".
void cargar_puzles(puzle **);

//precondicion: Entra un array de puzles y un id de un puzle existente.
//postcondicion: Imprime por pantalla el puzle a averiguar.
void mostrar_puzle(puzle *, int);

//precondicion: Entra el puzle.
//postcondicion: Imprime por pantalla la solucion del puzle dado.
void mostrar_solucion_puzle(puzle *, int);

//precondicion: Entra un array de puzles y un id de puzle.
//postcondicion: Devuelve el indice del puzle en el array o -1 si no se encuentra.
int buscar_puzle(puzle *, char *);

//Precondicion: Entra un array de puzles, un id de puzle y una respuesta dada por el jugador.
//Postcondicion: Devuelve 1 si la respuesta es correcta, 0 si es incorrecta y -1 si el puzle no existe o la respuesta es invalida.
int comprobar_solucion_puzle(puzle *, char *, char *);

//precondicion: Entra una cadena de caracteres.
//postcondicion: Elimina los caracteres \r y \n, reemplazandolos por el caracter nulo, para que funcione el strcmp.   
void limpiar_cadena(char *);


#endif