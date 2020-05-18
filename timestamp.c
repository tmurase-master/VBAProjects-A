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

//桑原追記分
#include <dirent.h>
//

int ts_update_currenttime(char *filepath);
int ts_update_specifiedtime(char *filepath, struct utimbuf *settime);
int ts_update_specifiedYMD(char *filepath, int year,int month, int day, int hour, int min, int sec);
//清水追加分
void get_filepath(char *filepath);
//

//桑原追記分
void get_filelist(char *filepath);
//

int ts_update_currenttime(char *filepath){
    struct utimbuf ct;

    ct.actime = time(NULL);
    ct.modtime = ct.actime;
    int r = utime(filepath, &ct);

    return r;

}
/* コンパイルワーニングでるので一度コメントアウト  ごめんなさい（harry58034)
int ts_update_specifiedtime(char *filepath, struct utimbuf *settime){

    if(settime->actime != NULL){
        utime(*filepath, &settime);
        return 0;
    }
    else return 1;
}
*/

//とりあえずこっち( harry58034)

int ts_update_specifiedYMD(char *filepath, int year,int month, int day, int hour, int min, int sec){

    struct tm YMD = {sec, min, hour, day, (month-1), (year-1900)};
    struct utimbuf ct;

    ct.actime = mktime(&YMD);
    ct.modtime = ct.actime;
    int r =utime(filepath, &ct);
    //utime("test.rtf", &ct);

    if(r == 0){
        printf("成功:success\n");
        return r;
    }else{
        printf("失敗:Failure\n");
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

    //カレントディレクトリ取得（filepathへ）　by harry58034
    getcwd(filepath, PATHNAME_SIZE);

    // カレントディレクトリ変更
    chdir(filepath); // チェンジディレクトリ
    getcwd(pathname, PATHNAME_SIZE);
    fprintf(stdout,"After FilePath:%s\n", pathname);
}
//

//桑原追記分
void get_filelist(char *filepath){
    DIR *dir;
    struct dirent *dp;

    dir = opendir(filepath);  //パスの指定が必要
    if (dir == NULL) {
        printf("get_filelist_失敗");
    }

    while (1) {
        dp = readdir(dir);
        if (dp == NULL) {
            break;
        }
        printf("%s\n", dp->d_name);
    }
    closedir(dir);
}

int main(void){

    //清水追加分:任意のファイルパスを取得する関数の呼び出し
    char filepath[256];
    get_filepath(filepath);
    //

    //桑原追加分
    get_filelist(filepath);
    //

    fprintf(stdout,"main-Function filename FilePath:%s\n", filepath);


    char filename[24] = "test.rtf";
    strcat(filepath,"\\");
    strcat(filepath,"test.rtf");

    fprintf(stdout,"main-Function2 filename FilePath:%s\n", filepath);

    ts_update_specifiedYMD(filepath, 1981,8,1,12,10,5);

    printf("updata!");
    //ts_update_currenttime("test.rtf");
    //printf("test");

}
