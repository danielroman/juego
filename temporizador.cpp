#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BOMBS 3

struct Bomba{
    int x;
    int y;
    bool puesta;
    int temporizador;
    time_t fechaInicio;
};

int main(){

    struct Bomba bombas[MAX_BOMBS];

    //hacemo la inicializacion de la bomba


    for (int i = 0; i < MAX_BOMBS; i++){	
	if (bombas[i].temporizador != 0){
	    bombas[i].temporizador = 10000;
	    printf("Bomba: %i, Temporizador: %i\n", i, bombas[i].temporizador);
	}
    }

    //hacer temporizador

    for (int i = 0; i < MAX_BOMBS; i++){
	if(bombas[i].temporizador <= 0)
	    printf("bomba: %i Ha explotado \n", i + 1);
	else{
	    bombas[i].temporizador = bombas[i].temporizador - 1;
	}
//    }





    return EXIT_SUCCESS;
}
