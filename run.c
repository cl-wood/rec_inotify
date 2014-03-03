#include "rec_inotify.h"
#include <pthread.h>
#include <stdio.h>

int main() 
{
    /*
    get_dirs("/home/musashi/CCDC");
    
    int i = 0;
    while (ret[i][0] != '\0') {
        printf("%s\n", ret[i++]);
    }
    */

    //while (1) {
    //    printf("[*] Watching...\n");
    //    watch_dir("/home/musashi/CCDC");
    //}

    //watch_dir_continuously("/home/musashi/CCDC");
    //watch_dir("/home/musashi/CCDC");
    rec_inotify("/home/musashi/CCDC");
    
}
