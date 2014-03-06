#include "rec_inotify.h"
#include <pthread.h>
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    //get_dirs(argv[1]);
    watch_dir_continuously(argv[1]);
    //watch_dir(argv[1]);

}
