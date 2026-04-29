#ifndef MENU_PARTIDA_H_
#define MENU_PARTIDA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jugadores.h"
#include "salas.h"
#include "partida.h"
#include "objetos.h"
#include "conexiones.h"
#include "puzles.h"

//PRECONDICION: id_condicion debe ser una cadena valida o NULL. Puede ser un ID de puzle (ej: "P01"), un ID de objeto (ej: "OB01") o una cadena vacia/NULL.
//POSCONDICION: Devuelve una descripcion legible de la condicion, como el nombre del puzle o del objeto, o "una condicion" si no se especifica nada.
char *obtener_nombre_condicion(const char *);

//PRECONDICION: Ninguna.
//POSCONDICION: Limpia la consola antes de pintar una nueva pantalla del menu de partida.
static void limpiar_pantalla();

//PRECONDICION: Ninguna.
//POSCONDICION: Pausa la ejecucion hasta que el usuario pulse Enter.
static void pausar_pantalla();

//PRECONDICION: s debe ser una cadena valida o NULL.
//POSCONDICION: Devuelve una copia dinamica de la cadena recibida.
static char *duplicar_cadena(const char *);

//PRECONDICION: min debe ser menor o igual que max.
//POSCONDICION: Lee un entero valido dentro del rango indicado.
static int leer_entero_rango(const char *, int, int);

//PRECONDICION: destino debe apuntar a un buffer valido.
//POSCONDICION: Lee una linea de texto eliminando el salto de linea final.
static void leer_texto_simple(const char *, char *, size_t);

//PRECONDICION: salas debe apuntar a una estructura ya cargada.
//POSCONDICION: Devuelve el nombre de la sala o "Desconocida" si no existe.
static const char *nombre_sala_por_id(vector_sala *, int);

//PRECONDICION: p debe apuntar a una partida valida.
//POSCONDICION: Muestra el nombre y la descripcion de la sala actual.
static void imprimir_descripcion_sala_actual(partida *);

//PRECONDICION: p debe apuntar a una partida valida.
//POSCONDICION: Muestra la sala actual en la parte superior del menu.
static void imprimir_cabecera_partida(partida *);

//PRECONDICION: p debe apuntar a una partida valida e id_obj debe ser una cadena valida.
//POSCONDICION: Devuelve el indice del objeto dentro de la partida o -1 si no existe.
static int buscar_indice_objeto_partida(partida *, const char *);

//PRECONDICION: p debe apuntar a una partida valida e id_conexion debe ser una cadena valida.
//POSCONDICION: Devuelve el indice del estado de esa conexion dentro de la partida o -1 si no existe.
static int buscar_indice_conexion_estado(partida *, const char *);

//PRECONDICION: p debe apuntar a una partida valida e id_puzle debe ser una cadena valida.
//POSCONDICION: Devuelve el indice del puzle dentro del estado de partida o -1 si no existe.
static int buscar_indice_puzle_estado(partida *, const char *);

//PRECONDICION: p debe apuntar a una partida valida.
//POSCONDICION: Limpia pantalla y muestra los objetos de la sala y las salidas disponibles.
static void examinar(partida *);

//PRECONDICION: p debe apuntar a una partida valida.
//POSCONDICION: Muestra las salas a las que se puede ir desde la actual y permite volver a la sala anterior aunque no exista una conexion explicita de vuelta.
static void entrar_en_otra_sala(partida *);

//PRECONDICION: La partida y el jugador deben ser validos.
//POSCONDICION: Permite coger un objeto existente en la sala y moverlo al inventario.
static void coger_objeto(partida *, jug_vect *, int);

//PRECONDICION: La partida y el jugador deben ser validos.
//POSCONDICION: Permite mover un objeto del inventario del jugador a la sala actual.
static void soltar_objeto(partida *, jug_vect *, int);

//PRECONDICION: j debe ser un vector valido y el indice del jugador debe existir.
//POSCONDICION: Limpia pantalla y muestra todos los objetos del inventario del jugador.
static void mostrar_inventario(jug_vect *, int);

//PRECONDICION: La partida y el jugador deben ser validos.
//POSCONDICION: Permite usar un objeto del inventario para abrir conexiones adyacentes de la sala actual.
static void usar_objeto(partida *, jug_vect *, int);

//PRECONDICION: p debe apuntar a una partida valida.
//POSCONDICION: Permite resolver el puzle de la sala actual y desbloquear las conexiones asociadas.
static void resolver_puzle(partida *);

//PRECONDICION: Los parametros deben referirse a estructuras validas ya cargadas.
//POSCONDICION: Guarda todas las partidas y sincroniza el inventario del jugador activo.
static void guardar_partida_menu(partida *, int, jug_vect *, int, int);

//PRECONDICION: Entran el vector de partidas, el numero de partidas, el vector de jugadores, el indice de la partida activa y el indice del jugador autenticado.
//POSCONDICION: Ejecuta el menu de partida permitiendo realizar todas las acciones del juego. Devuelve 0 si el jugador vuelve al menu principal y -1 si decide salir del programa.
int mostrar_partida(partida *, int, jug_vect *, int, int);

#endif
