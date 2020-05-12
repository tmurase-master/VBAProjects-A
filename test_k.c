#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

#include <time.h>
#include <sys/utime.h>
#include <sys/stat.h>
#include <errno.h>

int main(void)
{
	/*指定フォルダ内を探索する*/

    DIR *dir;
    struct dirent *dp;

    dir = opendir(".");  //パスの指定が必要
    if (dir == NULL) {
        return 1;
    }

    while (1) {
        dp = readdir(dir);
        if (dp == NULL) {
            break;
        }
        printf("%s\n", dp->d_name);
    }
    closedir(dir);

    /*指定ファイルが存在するか確認する*/
    if (existFile("sample.txt")) {  //パスの指定が必要

    	printf("存在します。\n");


    	/*存在指定ファイルのの更新時間を変える*/

    	time_t tt;
    	struct utimbuf ut;
    	struct stat st;
    	struct tm *t;

    	time(&tt);
    	t = localtime(&tt);

    	//年月日
    	t->tm_year = 102; //1900年+何年で計算される（例：2002年）
    	t->tm_mon =4;    //1月を0として計算される（例：5月）
    	t->tm_mday = 20; //数字通り

    	//時間
    	t->tm_hour = 15;
    	t->tm_min = 35;
    	t->tm_sec = 25;

    	ut.actime =0; //※アクセス時間変更途中

    	ut.modtime = mktime(t);
    	utime("sample.txt",&ut);  //パスの指定が必要
    	stat("sample.txt",&st);  //パスの指定が必要
    	printf("更新:%s",ctime(&st.st_mtime)); //確認用出力

    }
    else {
    	printf("存在しません。\n");
    }

    return 0;
}

/*ファイルが存在するか確認する*/

int existFile(const char* path)
{

	FILE* fp = fopen(path, "r");
    if (fp == NULL) {
        return 0;
    }

    fclose(fp);
    return 1;
}

