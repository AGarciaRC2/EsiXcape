#include "jugadores.h"
#include "objetos.h"

int menu_principal(jug_vect *j) {
	int op;
	char resp;
	
	do {
		do {
			system("cls");
			printf("\n<<<ESI-SCAPE>>>\n\n");
			Sleep(1000);
			printf("1. Nueva partida\n");
			printf("2. Cargar partida\n");
			printf("3. Salir\n\n");
			scanf("%d", &op);
			fflush(stdin);
		}while (op < 1 || op > 3);
		
		switch (op) {
			case 1:
				
				break;
			
			case 2:
				
				break;
				
			case 3:
				printf("\nHasta la proxima!\n");
				exit(1);
				break;
				
			default:
				printf("Seleccione una opcion valida: ");
				break;
		}
		
		if (op != 3) {
			printf("\nDeseas hacer algo mas? (S/N): ");
			scanf("%c", &resp);
			fflush(stdin);
			while (resp != 'S' && resp != 's' && resp != 'N' && resp != 'n') {
				printf("Seleccione una opcion valida: ");
				scanf("%c", &resp);
				fflush(stdin);
			}
		}
	}while (op != 3 && (resp == 'S' || resp == 's'));
	
	return 0;
}