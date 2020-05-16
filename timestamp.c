#include<stdio.h>
#include<time.h>
#include<sys/types.h>
#include<utime.h>
#include<sys/stat.h>

//清水追加分
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#define PATHNAME_SIZE 512
//


int ts_update_currenttime(char *filepath);
int ts_update_specifiedtime(char *filepath, struct utimbuf *settime);
int ts_update_specifiedYMD(char *filepath, int year,int month, int day, int hour, int min, int sec);
//清水追加分
void get_filepath(char *filepath);
//

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

//とりあえずこっち( harry58034)
)
int ts_update_specifiedYMD(char *filepath, int year,int month, int day, int hour, int min, int sec){
    
    struct tm YMD = {sec, min, hour, day, (month-1), (year-1900)};
    struct utimbuf ct;

    ct.actime = mktime(&YMD);
    ct.modtime = ct.actime;
    int r =utime(filepath, &ct);
    //utime("test.rtf", &ct);

    if(r == 0){
        printf("成功\n");
        return r;
    }else{
        printf("失敗\n");
        return r;
    }
}

//清水追加分
void get_filepath(char *filepath){

   // 変数定義
    char pathname[PATHNAME_SIZE];  // ファイルパス
    char cdp[256]; //任意のファイルパス入力用

    // 変数初期化
    memset(pathname, '\0', PATHNAME_SIZE); 

    // 任意のファイルパスの入力
    printf("Input Current Directory > ");
	scanf("%[^\n]%*c", filepath);

    // カレントディレクトリ取得
    getcwd(pathname, PATHNAME_SIZE);
    fprintf(stdout,"Before FilePath:%s\n", pathname);

    // カレントディレクトリ変更  
    chdir(filepath); // チェンジディレクトリ
    getcwd(pathname, PATHNAME_SIZE);
    fprintf(stdout,"After FilePath:%s\n", pathname);
}
//


int main(void){

    //清水追加分:任意のファイルパスを取得する関数の呼び出し
    char filepath[256];
    get_filepath(filepath);
    //

    char file[9] = "test.rtf"; 
    ts_update_specifiedYMD(file, 1986,8,1,12,10,5);

    printf("updata!");
    //ts_update_currenttime("test.rtf");
    //printf("test");

}