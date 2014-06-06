#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include <unistd.h>

#define FILAS 25
#define COL 50
#define ESC 27
#define SPC 32

//http://www.openvim.com/tutorial.html

struct Coordenadas{
    int x;
    int y;
    int bombas;
};

struct Bomba{
    int x;
    int y;
    int explosion;
};

void mapa(char tablero[FILAS][COL]){

    FILE *fichero;

    fichero = fopen("tablero.txt", "r");
    if(fichero == NULL){
	printf("El archivo tablero.txt no se encuentra");
	//falta poner que se salga cuando esto ocurra
    }else{
	for(int fila = 0; fila < FILAS; fila++)
	    for(int col = 0; col < COL; col++)
		fscanf(fichero, " %c", &tablero[fila][col]);
	fclose(fichero);
    }
}

void pintar_mapa(char tablero[FILAS][COL], struct Coordenadas jugador){

    clear();
    for(int fila = 0; fila < FILAS; fila++){
	for (int col = 0; col < COL; col++){
	    printw("%c", tablero[fila][col]);

	}
	printw("\n");
    }
    refresh();

}

void inicializar(char tablero[FILAS][COL]){

    for (int fila = 0; fila < FILAS; fila++)
	for (int col = 0; col < COL; col++)
	    if (tablero[fila][col] == '1')
		tablero[fila][col] = 'T';
	    else
		if(tablero[fila][col] == '0')    
		    tablero[fila][col] = ' ';
		else 	    
		    if (tablero[fila][col] == '2')
			tablero[fila][col] = 'I';
		    else
			if (tablero[fila][col] == '4')
			    tablero[fila][col] = 'L';
}

//hay que mejorar el codigo chapuza momentanea
void explotar_bomba(char tablero[FILAS][COL], struct Coordenadas *jugador){

	    int alcanceizq = 0;
	    int alcanceder = 0;
	    int alcanceaba = 0;
	    int alcancearr = 0;

	    while(alcanceizq < 5){
		if(tablero[jugador->y][jugador->x - alcanceizq] != 'T'){
		    tablero[jugador->y][jugador->x - alcanceizq] = 'x';
		    alcanceizq++;
		}else 
		    alcanceizq = 5;
	    }

	    while(alcanceder < 5){
		if(tablero[jugador->y][jugador->x + alcanceder] != 'T'){
		    tablero[jugador->y][jugador->x + alcanceder] = 'x';
		    alcanceder++;
		}else 
		    alcanceder = 5;
	    }
	    
	    while(alcancearr < 5){
		if(tablero[jugador->y - alcancearr][jugador->x] != 'T'){
		    tablero[jugador->y - alcancearr][jugador->x] = 'x';
		    alcancearr++;
		}else 
		    alcancearr = 5;
	    }
		
	    while(alcanceaba < 5){
		if(tablero[jugador->y + alcanceaba][jugador->x] != 'T'){
		    tablero[jugador->y + alcanceaba][jugador->x] = 'x';
		    alcanceaba++;		   
		}else 
		    alcanceaba = 5;
	    }
}

void poner_bomba(char tablero[FILAS][COL], struct Coordenadas *jugador){ 
    if(jugador->bombas < 3)
	if(tablero[jugador->y + 1][jugador->x] != 'T'){
	     tablero[jugador->y + 1][jugador->x] = 'X'; 
	     jugador->bombas++;
	}
    //realizar temporizador

    //explotar_bomba(tablero, jugador);
}


void mover(int user_input, struct Coordenadas *jugador, char tablero[FILAS][COL]){
    switch(tolower(user_input)){
	case 'w':
	case KEY_UP:
	    if (tablero[jugador->y - 1][jugador->x] != 'T'){
		tablero[jugador->y][jugador->x] = ' ';
		jugador->y += -1;
	    }
	    break;
	case 's':
	case KEY_DOWN:
	    if (tablero[jugador->y + 1][jugador->x] != 'T'){
		tablero[jugador->y][jugador->x] = ' ';
		jugador->y += 1;
	    }
	    break;
	case 'a':
	case KEY_LEFT:
	    if (tablero[jugador->y][jugador->x - 1] != 'T'){
		tablero[jugador->y][jugador->x] = ' ';
		jugador->x += -1;
	    }
	    break;
	case 'd':
	case KEY_RIGHT:
	    if (tablero[jugador->y][jugador->x + 1] != 'T'){
		tablero[jugador->y][jugador->x] = ' ';
		jugador->x += 1;
	    }
	    break;	
	case SPC:
	    poner_bomba(tablero, jugador);
	    break;
    }
    tablero[jugador->y][jugador->x] = 'U';
}

int main(int argc, char *argv[]){

    struct Coordenadas jugador = {1, 1}; //posicion inicial del jugador
    char tablero[FILAS][COL];
    int user_input;

    initscr();
    halfdelay(1);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    mapa(tablero);
    inicializar(tablero);
    while ((user_input = getch()) != ESC){	
	mover(user_input, &jugador, tablero);
	pintar_mapa(tablero, jugador);
    }
    endwin();
    return EXIT_SUCCESS;

}
