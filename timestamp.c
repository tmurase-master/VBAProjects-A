#include<stdio.h>
#include<time.h>
#include<sys/types.h>
#include<utime.h>
#include<sys/stat.h>


int ts_update_currenttime(char *filepath);
int ts_update_specifiedtime(char *filepath, struct utimbuf *settime);
int ts_update_specifiedYMD(char *filepath, int year,int month, int day, int hour, int min, int sec);

int ts_update_currenttime(char *filepath){
    struct utimbuf ct;

    ct.actime = time(NULL);
    ct.modtime = ct.actime;
    utime(*filepath, &ct);

    return 0;
}

int ts_update_specifiedtime(char *filepath, struct utimbuf *settime){

    if(settime->actime != NULL){
        utime(*filepath, &settime);
        return 0;
    }
    else return 1;
}

int ts_update_specifiedYMD(char *filepath, int year,int month, int day, int hour, int min, int sec){
    
    struct tm YMD = {sec, min, hour, day, month, (year-1900)};
    struct utimbuf ct;

    ct.actime = mktime(&YMD);
    ct.modtime = ct.actime;
    utime(*filepath, &ct);

}


int main(void){

    printf("test");

}