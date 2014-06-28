#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
//#include "SDL.h"
#include <unistd.h>

#define FILAS 30
#define COL 50
#define ESC 27
#define SPC 32
#define ALCANCE 4 //sirve para delimitar el alcance de la bomba


//http://www.openvim.com/tutorial.html

struct Coordenadas{
    int x;
    int y;
};

struct Bomba{
    int x;
    int y;
    int end;
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

    //    clear();
    for(int fila = 0; fila < FILAS; fila++){
	for (int col = 0; col < COL; col++){
	    printw("%c", tablero[fila][col]);

	}
	printw("\n");
    }
    // refresh();

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

void explotar_bomba(char tablero[FILAS][COL], struct Bomba *bombas){

    int alcanceizq = 0;
    int alcanceder = 0;
    int alcanceaba = 0;
    int alcancearr = 0;

    while(alcanceizq < ALCANCE){ 
	if(tablero[bombas->y][bombas->x - alcanceizq] != 'T'){
	    tablero[bombas->y][bombas->x - alcanceizq] = 'x';
	    alcanceizq++;
	}else 
	    alcanceizq = ALCANCE;
    }

    while(alcanceder < ALCANCE){
	if(tablero[bombas->y][bombas->x + alcanceder] != 'T'){
	    tablero[bombas->y][bombas->x + alcanceder] = 'x';
	    alcanceder++;
	}else 
	    alcanceder = ALCANCE;
    }

    while(alcancearr < ALCANCE){
	if(tablero[bombas->y - alcancearr][bombas->x] != 'T'){
	    tablero[bombas->y - alcancearr][bombas->x] = 'x';
	    alcancearr++;
	}else 
	    alcancearr = ALCANCE;
    }

    while(alcanceaba < ALCANCE){
	if(tablero [bombas->y + alcanceaba][bombas->x] != 'T'){
	    tablero[bombas->y + alcanceaba][bombas->x] = 'x';
	    alcanceaba++;		   
	}else 
	    alcanceaba = ALCANCE;
    }     

}

int temporizador(char tablero[FILAS][COL], struct Bomba *bombas, int seg){

    if (seg == bombas->end)
	explotar_bomba(tablero, bombas);

}

void poner_bomba(char tablero[FILAS][COL], struct Coordenadas *jugador, struct Bomba *bombas, int seg){


    if (tablero[jugador->y + 1][jugador->x] != 'T' && tablero[jugador->y + 1][jugador->x] != 'I'){
	tablero[jugador->y + 1][jugador->x] = 'X';
	bombas->y = jugador->y + 1;
	bombas->x = jugador->x;
	bombas->end = seg + 4;
    }
}

void mover(int user_input, struct Coordenadas *jugador, char tablero[FILAS][COL], struct Bomba *bombas, int seg){
    switch(tolower(user_input)){
	case 'w':
	case KEY_UP:
	    if (tablero[jugador->y - 1][jugador->x] != 'T' && tablero[jugador->y - 1][jugador->x] != 'X'){
		tablero[jugador->y][jugador->x] = ' ';
		jugador->y += -1;
	    }
	    break;
	case 's':
	case KEY_DOWN:
	    if (tablero[jugador->y + 1][jugador->x] != 'T' && tablero[jugador->y + 1][jugador->x] != 'X'){
		tablero[jugador->y][jugador->x] = ' ';
		jugador->y += 1;
	    }
	    break;
	case 'a':
	case KEY_LEFT:
	    if (tablero[jugador->y][jugador->x - 1] != 'T' && tablero[jugador->y][jugador->x - 1] != 'X'){
		tablero[jugador->y][jugador->x] = ' ';
		jugador->x += -1;
	    }
	    break;
	case 'd':
	case KEY_RIGHT:
	    if (tablero[jugador->y][jugador->x + 1] != 'T' && tablero[jugador->y][jugador->x + 1] != 'X'){
		tablero[jugador->y][jugador->x] = ' ';
		jugador->x += 1;
	    }
	    break;	
	case SPC:
	    poner_bomba(tablero, jugador, bombas, seg);
	    break;
	case 'g':
	    explotar_bomba(tablero, bombas);
    }
    tablero[jugador->y][jugador->x] = 'U';
}

int main(int argc, char *argv[]){

    struct Coordenadas jugador = {1, 1}; //posicion inicial del jugador
    struct Bomba bombas;
    char tablero[FILAS][COL];
    int user_input;
    int  min, seg, miliseg;

    min = 0;
    seg = 0;
    miliseg = 0;

    initscr();
    halfdelay(1);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    mapa(tablero);
    inicializar(tablero);
    while ((user_input = getch()) != ESC){
	clear();
	miliseg++;

	if(miliseg == 11){
	    seg++;
	    miliseg = 0;
	}

	if(seg == 60){

	    min++;
	    seg = 0;
	}

	if(min == 60){

	    min = 0;
	}

	mover(user_input, &jugador, tablero, &bombas, seg);
	temporizador(tablero, &bombas, seg);
	pintar_mapa(tablero, jugador);
	mvprintw(26, 2, "%d:%d", min, seg);
	refresh();
    }
    endwin();
    return EXIT_SUCCESS;

}
