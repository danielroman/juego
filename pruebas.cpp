#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 

struct Bombas{
    time_t now;
};

int main(){

    time_t now;
    time_t fe;
    time(&now);

    struct tm beg;

    beg = *localtime(&now);

    beg.tm_sec = beg.tm_sec;
    beg.tm_hour = beg.tm_hour;
    beg.tm_min = beg.tm_min;

    double sc = difftime(mktime(&beg), now);

    fe = mktime(&beg);

	//printf("now: %s \n", asctime(localtime(&now)));
   // printf("now: %ld \n", beg);	


	printf("now: %s \n", asctime(localtime(&now)));

	printf("end: %s\n", asctime(localtime(&fe)));

//	printf("second: %lf \n", sc);
//    }
    return 0;
}
