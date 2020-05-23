#include<stdio.h>
#include<time.h>
#include<sys/types.h>
#include<utime.h>
#include<sys/stat.h>

//清水追加分
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
int ts_update_input();
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
        printf("Success\n");
        return r;
    }else{
        printf("Failure\n");
        return r;
    }
}

int ts_update_input(){

    char filename[256];
    memset(filename, '\0', 256);

    int year = 0, month = 0, day = 0;

    //fprintf(stdout,"input file name:");
    fprintf(stdout,"Enter the file name for which you want to update the time stamp:");
    fscanf(stdin, "%s", &filename);
    fprintf(stdout,"input year\n");
    fscanf(stdin, "%d", &year);
    fprintf(stdout,"input month:");
    fscanf(stdin, "%d", &month);
    fprintf(stdout,"input day:");
    fscanf(stdin, "%d", &day);

    return ts_update_specifiedYMD(filename, year,month,day,12,0,0);
}

//清水追加分
void get_filepath(char *filepath){

   // 変数定義
    char pathname[PATHNAME_SIZE];  // ファイルパス
    int i=2;
    // 変数初期化
    memset(pathname, '\0', PATHNAME_SIZE);

    // 対象のフォルダのパスを入力、変数filepathに保管（自分の環境だと日本語が文字化けしてしまうので、英語もいれてあります）
  
    //入力のところをユーザが納得するまでループさせます。未完成。。。
    while (i != 1)
    {
    
    //printf("指定のフォルダのパスを入力してください:Input Specified FolderPath > ");
	printf("Input Specified FolderPath > ");
    //scanfは連続使用できない為、このコマンドを使用
    rewind(stdin);
    //
    scanf("%[^\n]%*c", filepath);
    
    fprintf(stdout,"Is this the filepath you specified? : %s\n", filepath);
    printf("Input 1(yes) or 2(no) > ");
    scanf("%d",&i);
    //1(yes)ならループを抜けます。

    
    }
   
   //printf("well done\n ");
    
    

    //以下カレントディレクトリ関係は必要ないのでコメントアウト
    // カレントディレクトリ取得
    //getcwd(pathname, PATHNAME_SIZE);
    //fprintf(stdout,"変更前のカレントディレクトリ:Before Current Directory:%s\n", pathname);

    //カレントディレクトリ取得（filepathへ）　by harry58034
    //getcwd(filepath, PATHNAME_SIZE);

    // カレントディレクトリ変更
    //chdir(filepath); // チェンジディレクトリ
    //getcwd(pathname, PATHNAME_SIZE);
    //fprintf(stdout,"変更後カレントディレクトリ:After Current Directory:%s\n", pathname);
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
    printf("------Displays the files in the specified folder-----\n");
    while (1) {
        dp = readdir(dir);
        if (dp == NULL) {
            break;
        }
        printf("%s\n", dp->d_name);
    }
    closedir(dir);
    printf("-----The display is up to here----- \n");
}

int main(void){

    //清水追加分:指定のフォルダパスを取得する関数の呼び出し
    char filepath[256];

     get_filepath(filepath);
    //fprintf(stdout,"debug::: main function filepath is : %s\n", filepath);
    //

    //桑原追加分
    get_filelist(filepath);
    //get_filelist("/Users/Masato/agilework/workspace/VBAProjects-A");
    //fprintf(stdout,"main-Function filename FilePath:%s\n", filepath);


    //char filename[24] = "test.rtf";
    //strcat(filepath,"\\");
    //strcat(filepath,"test.rtf");

    //fprintf(stdout,"main-Function2 filename FilePath:%s\n", filepath);

    //ts_update_specifiedYMD(filepath, 1981,8,1,12,10,5);
    ts_update_input();

    printf("updata!");
    //ts_update_currenttime("test.rtf");
    //printf("test");

}
