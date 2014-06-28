#include <stdio.h>
#include <time.h>

int main ()
{
    int ret;
    struct tm info;
    char buffer[80];

    info.tm_year;
    info.tm_mon;
    info.tm_mday;
    info.tm_hour;
    info.tm_min;
    info.tm_sec;
    info.tm_isdst;

    ret = mktime(&info);
    if( ret == -1 )
    {
	printf("Error: unable to make time using mktime\n");
    }
    else
    {
	strftime(buffer, sizeof(buffer), "%c", &info );
	printf("%s \n", buffer);
    }

    return(0);
}


