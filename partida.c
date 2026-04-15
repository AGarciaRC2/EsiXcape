#include "partida.h"

void limpiar_cadena_partida(char *s){
    int i = 0;

    while(s[i] != '\0'){
        if(s[i] == '\n' || s[i] == '\r'){
            s[i] = '\0';
            break;
        }
        i++;
    }
}

int existe_jugador_partida(partida *p, int num_partidas, int id_jugador){
    int i;

    for(i = 0; i < num_partidas; i++){
        if(p[i].id_jugador == id_jugador){
            return 1;
        }
    }

    return 0;
}

int cargar_partida(partida **p){
    FILE *f = fopen("partida.txt", "r");
    char linea[100];
    int num_partidas = 0, i;

    if(f == NULL){
        printf("No se pudo abrir el fichero de partida. Se creará uno nuevo al guardar la partida.\n");
        return 0;
    }

    while(fgets(linea, sizeof(linea), f) != NULL){
        if(strncmp(linea, "JUGADOR:", 8) == 0){
            char *valor = linea + 8;
            while(*valor == ' ' || *valor == '\t'){
                valor++;
            }
            limpiar_cadena_partida(valor);
            num_partidas++;
            *p = realloc(*p, num_partidas * sizeof(partida));
            if(*p == NULL){
                printf("Error al asignar memoria para las partidas.\n");
                fclose(f);
                return 0;
            }
            (*p)[num_partidas - 1].id_jugador = atoi(valor);
            (*p)[num_partidas - 1].objetos = NULL;
            (*p)[num_partidas - 1].conexiones = NULL;
            (*p)[num_partidas - 1].puzles = NULL;
            (*p)[num_partidas - 1].id_sala_actual = 0;
        }else if(strncmp(linea, "SALA:", 5) == 0 && num_partidas > 0){
            char *valor = linea + 5;
            while(*valor == ' ' || *valor == '\t'){
                valor++;
            }
            limpiar_cadena_partida(valor);
            (*p)[num_partidas - 1].id_sala_actual = atoi(valor);
        }else if(strncmp(linea, "OBJETO:", 7) == 0 && num_partidas > 0){
            // Aquí se debería parsear el objeto y añadirlo a la partida actual
        }else if(strncmp(linea, "CONEXION:", 9) == 0 && num_partidas > 0){
            // Aquí se debería parsear la conexión y añadirla a la partida actual
        }else if(strncmp(linea, "PUZLE:", 6) == 0 && num_partidas > 0){
            // Aquí se debería parsear el puzle y añadirlo a la partida actual
        }
    }

    fclose(f);
    return num_partidas;
}

void escribir_una_partida(FILE *f, partida *p){
    int i;

    if(f == NULL || p == NULL){
        return;
    }

    fprintf(f, "JUGADOR: %02d\n", p->id_jugador);
    fprintf(f, "SALA: %02d\n", p->id_sala_actual);

    if(p->objetos != NULL){
        i = 0;
        while(p->objetos[i].id_objeto[0] != '\0'){
            fprintf(f, "OBJETO: %s-%s\n",
                    p->objetos[i].id_objeto,
                    p->objetos[i].localizacion);
            i++;
        }
    }

    if(p->conexiones != NULL){
        i = 0;
        while(p->conexiones[i].id_conexion[0] != '\0'){
            fprintf(f, "CONEXION: %s-%s\n",
                    p->conexiones[i].id_conexion,
                    p->conexiones[i].estado);
            i++;
        }
    }

    if(p->puzles != NULL){
        i = 0;
        while(p->puzles[i].id_puzle[0] != '\0'){
            fprintf(f, "PUZLE: %s-%s\n",
                    p->puzles[i].id_puzle,
                    p->puzles[i].estado);
            i++;
        }
    }
}

void guardar_partida(partida *p, int num_partidas, jugadores j){
    FILE *f = fopen("partida.txt", "w");
    int i;

    if(f == NULL){
        printf("Error al abrir el fichero partida.txt para guardar.\n");
        return;
    }

    for(i = 0; i < num_partidas; i++){
        escribir_una_partida(f, &p[i]);
    }

    fclose(f);
}

void eliminar_partida(partida **p, int *num_partidas, int id_jugador){
    int i, j, encontrado = 0;
    char confirmacion[10];
    FILE *f;

    if(p == NULL || *p == NULL || num_partidas == NULL || *num_partidas <= 0){
        printf("No hay partidas cargadas para eliminar.\n");
        return;
    }

    for(i = 0; i < *num_partidas; i++){
        if((*p)[i].id_jugador == id_jugador){
            encontrado = 1;
            break;
        }
    }

    if(!encontrado){
        printf("No existe ninguna partida del jugador %d.\n", id_jugador);
        return;
    }

    printf("¿Estás seguro de que quieres eliminar la partida del jugador con id: %d? (sí/no): ", id_jugador);
    if(fgets(confirmacion, sizeof(confirmacion), stdin) == NULL){
        printf("Error al leer la confirmación.\n");
        return;
    }
    limpiar_cadena_partida(confirmacion);

    if(strcmp(confirmacion, "sí") != 0 && strcmp(confirmacion, "si") != 0){
        printf("Eliminación cancelada.\n");
        return;
    }

    if((*p)[i].objetos != NULL){
        free((*p)[i].objetos);
    }
    if((*p)[i].conexiones != NULL){
        free((*p)[i].conexiones);
    }
    if((*p)[i].puzles != NULL){
        free((*p)[i].puzles);
    }

    for(j = i; j < *num_partidas - 1; j++){
        (*p)[j] = (*p)[j + 1];
    }

    (*num_partidas)--;

    if(*num_partidas > 0){
        partida *tmp = realloc(*p, *num_partidas * sizeof(partida));
        if(tmp != NULL){
            *p = tmp;
        } else {
            printf("Advertencia: no se pudo reducir la memoria tras eliminar la partida.\n");
        }
    } else {
        free(*p);
        *p = NULL;
    }

    f = fopen("partida.txt", "w");
    if(f == NULL){
        printf("Error al abrir el fichero partida.txt en función eliminar partida.\n");
        return;
    }

    for(j = 0; j < *num_partidas; j++){
        escribir_una_partida(f, &(*p)[j]);
    }
    fclose(f);

    printf("Partida eliminada correctamente.\n");
}