/*
 * sample.c
 *
 *  Created on: 2020/05/12
 *      Author: kuwa
 */


#include <stdio.h>
#include <sys/utime.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>


int main(void)
{
	/*
	 * 更新時間等を変更
	 */

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

	/*
	 * 更新時間などの情報取得・表示
	 */

	struct _finddata_t fdata;

	int fh = _findfirst("sample.txt", &fdata);
	_findclose(fh);
	printf("作成    : %s", asctime(localtime(&fdata.time_create))); //確認用出力
	printf("アクセス: %s", asctime(localtime(&fdata.time_access))); //確認用出力
	printf("更新    : %s\n", asctime(localtime(&fdata.time_write))); //確認用出力

	return 0;
}



