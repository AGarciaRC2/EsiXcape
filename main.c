#include "salas.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    vector_sala s;

    s.vctr_sala = NULL;
    s.numreg = 0;

    if (cargar_salas(&s) == 0) {
        printf("Error al cargar salas\n");
        return 1;
    }

    describir_salas(s, 5);

    free(s.vctr_sala);

    return 0;
}