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
    int r = utime(filepath, &ct);

    return r;
    
}

int ts_update_specifiedtime(char *filepath, struct utimbuf *settime){

    if(settime->actime != NULL){
        utime(*filepath, &settime);
        return 0;
    }
    else return 1;
}

int ts_update_specifiedYMD(char *filepath, int year,int month, int day, int hour, int min, int sec){
    
    struct tm YMD = {sec, min, hour, day, (month-1), (year-1900)};
    struct utimbuf ct;

    ct.actime = mktime(&YMD);
    ct.modtime = ct.actime;
    utime(filepath, &ct);
    //utime("test.rtf", &ct);


}


int main(void){

    char file[9] = "test.rtf"; 
    ts_update_specifiedYMD(file, 1986,8,1,12,10,5);
    //ts_update_currenttime("test.rtf");
    //printf("test");

}