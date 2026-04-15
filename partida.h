#ifndef PARTIDA_H
#define PARTIDA_H

#include "jugadores.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define max_id_objeto 5
#define max_localizacion 11
#define max_id_conexion 4
#define max_estado_conexion 11
#define max_id_puzle 4
#define max_estado_puzle 11

typedef struct{
    char id_objeto[max_id_objeto];
    char localizacion[max_localizacion];
} objeto_partida;

typedef struct{
    char id_conexion[max_id_conexion];
    char estado[max_estado_conexion];
} conexion_partida;

typedef struct{
    char id_puzle[max_id_puzle];
    char estado[max_estado_puzle];
}puzle_partida;

typedef struct{
    int id_jugador;
    int id_sala_actual;
    objeto_partida *objetos;
    conexion_partida *conexiones;
    puzle_partida *puzles;
}partida;

//cabecera: cargar_partida(partida **p)
//precondición: Entra un puntero a puntero de partida.
//postcondición: Carga los datos del fichero "partida.txt" en memoria dinámica, creando un array de partidas. Devuelve el número de partidas cargadas.
int cargar_partida(partida **p);

//cabecera: guardar_partida(partida *p)
//precondición: Entra una estructura partida con datos válidos, y ademas todos los datos de todas las partidas. Cada jugador solo puede tener una partida guardada, pero puede haber varios jugadores con su partida.
//postcondición: Guarda el estado actual de la partida en el fichero "partida.txt".
void guardar_partida(partida *p, int num_partidas, jugadores j);

//cabecera: mostrar_partida(partida *p, jug_vect *j, int id_jugador)
//precondición: Entra un puntero a partida cargada, el vector de jugadores y el id de jugador.
//postcondición: Muestra el menú de la partida y permite ejecutar acciones sobre ella.
int mostrar_partida(partida *p, jug_vect *j, int id_jugador);

//cabecera: eliminar_partida(partida **p, int *num_partidas, int id_jugador)
//precondición: Entra un puntero a puntero de partidas, un puntero al número de partidas y el id del jugador.
//postcondición: Elimina la partida del jugador tanto de la memoria dinámica como del fichero "partida.txt". Si el jugador no tiene partida guardada, no hace nada.
void eliminar_partida(partida **p, int *num_partidas, int id_jugador);

//cabecera: limpiar_cadena_partida(char *s)
//precondición: Entra una cadena.
//postcondición: Elimina los caracteres '\n' y '\r'.
void limpiar_cadena_partida(char *s);

//cabecera: existe_jugador_partida(partida *p, int num_partidas, int id_jugador)
//precondición: Entra un array de partidas, el número de partidas y un id de jugador.
//postcondición: Devuelve 1 si el jugador ya tiene una partida guardada, 0 si no.
int existe_jugador_partida(partida *p, int num_partidas, int id_jugador);

//cabecera: escribir_una_partida(FILE *f, partida *p)
//precondición: Entra un puntero a archivo abierto para escritura y una partida con datos válidos.
//postcondición: Escribe la partida en el formato adecuado en el archivo.
void escribir_una_partida(FILE *f, partida *p);

#endif