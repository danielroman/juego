#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int main(){

    time_t now;
    time_t fe;
    time(&now);

    struct tm beg;

    beg = *localtime(&now);

    beg.tm_sec = beg.tm_sec + 4;
    beg.tm_hour = beg.tm_hour;
    beg.tm_min = beg.tm_min;
    beg.tm_mday = beg.tm_mday;

    double sc = difftime(mktime(&beg), now);

    fe = mktime(&beg);

	//printf("now: %s \n", asctime(localtime(&now)));
printf("now: %lf \n", beg);	
	system("sleep 2");


	printf("now: %s \n", asctime(localtime(&now)));

//	printf("end: %s\n", asctime(localtime(&fe)));

//	printf("second: %lf \n", sc);
//    }
    return 0;
}
