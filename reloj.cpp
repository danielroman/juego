#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int main(){
    long int i=0;
    time_t comienzo, final;
    struct tm *tiempoComienzoPtr, *tiempoFinalPtr;

    i = 0;
    comienzo = time( NULL );
    for( i=0; i < 2000000; i++ )   printf( "-" );
    final = time( NULL );

    printf( "Comienzo: %ld \n", comienzo );


    printf( "Final: %ld \n", final );
    printf( "Número de segundos transcurridos desde el comienzo del programa: %f s\n", difftime(final, comienzo) );
}

