#include<stdio.h>
#include<time.h>
#include<sys/types.h>
#include<utime.h>
#include<sys/stat.h>

class timestamp_manager{

 private:
  struct utimbuf current_time;
  

 public:
  void set_current_time();
  void time_update(char *filepath);

};

int main(void){

    timestamp_manager test;

    test.set_current_time();

    return 0;
}

void timestamp_manager::set_current_time()
{
    current_time.actime=time(NULL);
    current_time.modtime=current_time.actime;

    //printf("%ld|n", current_time.modtime);
}

void timestamp_manager::time_update(char *filepath)
{
    utime(filepath, &this->current_time);
}