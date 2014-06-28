#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int hr,min,seg;
    printf("Reloj Digital\n");
    //bucle para controlar los segundos

    seg = 0;
    hr = 0;
    min = 0;

    do{
    seg++;

    if(seg == 60)
	//si los segundos llegan a 60
    {
	min++;
	//minutos aumentan a 1
	seg=0;
	//segundos se reinicia a 0
    }

    if(min == 60)
	//si los minutos llegan a 60
    {
	hr++;
	//horas aumentan a 1
	min=0;
	//minutos se reinicia a 0
    }

    if(hr==24)
    {
	seg=0;
	//segundos se reinicia a 0
	min=0;
	//minutos se reinicia a 0
	hr=0;
	//horas se reinicia a 0
    }
    usleep(1000000);
    printf("%d:%d:%d\n",hr,min,seg);
    }while(hr <= 24);
} 

