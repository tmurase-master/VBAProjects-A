/*
 * sample.c
 *
 *  Created on: 2020/05/12
 *      Author: kuwa
 */

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

    dir = opendir(".");
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
    if (existFile("sample.txt")) {

    	printf("存在します。\n");

    	time_t tt;
    	struct utimbuf ut;
    	struct stat st;
    	struct tm *t;

    	time(&tt);
    	t = localtime(&tt);

    	//年月日
    	t->tm_year = 101; //2001年
    	t->tm_mon =4;    //5月
    	t->tm_mday = 20; //20日
    	t->tm_wday = 0; //日曜日

    	//時間
    	t->tm_hour = 15;
    	t->tm_min = 35;
    	t->tm_sec = 25;

    	ut.actime =0; //※アクセス時間変更途中

    	ut.modtime = mktime(t);
    	utime("sample.txt",&ut);
    	stat("sample.txt",&st);
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


//以下、WIN32を使わないファイル探索など部品動作確認用（ゴミ）

/*
* Cドライブ直下のファイル名とディレクトリ名を表示する *
#include <stdlib.h>
#include <stdio.h>
#include <io.h>

int main( void )
{
    struct _finddata_t tFileData = { 0 };   //ファイル情報
    long   lHandle;                         // 検索ハンドル
    char   szSearchDir[] = "*.*";       // 検索ディレクトリ

    // ファイル検索開始
    lHandle = _findfirst( szSearchDir, &tFileData );

    // _findfirstが失敗した場合
    if ( lHandle == -1 )
    {
        return EXIT_FAILURE;
    }
    do
    {
        // ファイル(ディレクトリ)名を出力
        puts( tFileData.name );
    }
    // 次のファイルを検索(ない場合はループ終了)
    while ( _findnext( lHandle, &tFileData ) != -1 );

    // 検索ハンドルを閉じる
    _findclose( lHandle );

    // 終了
    return EXIT_SUCCESS;
}

/*
#include <stdio.h>
#include <sys/utime.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>


int main(void)
{
	*
	 * 更新時間等を変更
	 *

	time_t tt;
	struct utimbuf ut;
	struct stat st;
	struct tm *t;

	time(&tt);
	t = localtime(&tt);

	//年月日
	t->tm_year = 101; //2001年
	t->tm_mon =4;    //5月
	t->tm_mday = 20; //20日
	t->tm_wday = 0; //日曜日

	//時間
	t->tm_hour = 15;
	t->tm_min = 35;
	t->tm_sec = 25;

	ut.actime =0; //※アクセス時間変更途中

	ut.modtime = mktime(t);
	utime("sample.txt",&ut);
	stat("sample.txt",&st);
	printf("任意更新:%s",ctime(&st.st_mtime)); //確認用出力

	*
	 * 更新時間などの情報取得・表示
	 *

	struct _finddata_t fdata;

	int fh = _findfirst("sample.txt", &fdata);
	_findclose(fh);
	printf("作成    : %s", asctime(localtime(&fdata.time_create))); //確認用出力
	printf("アクセス: %s", asctime(localtime(&fdata.time_access))); //確認用出力
	printf("更新    : %s\n", asctime(localtime(&fdata.time_write))); //確認用出力

	return 0;
}

*/
