#include "rec_inotify.h"
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
    rec_inotify("/home/musashi/CCDC");
    
}
