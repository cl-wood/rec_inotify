// Modified from: http://www.ibm.com/developerworks/linux/library/l-ubuntu-inotify/index.html
// Also borrowed from: http://stackoverflow.com/questions/612097/how-can-i-get-a-list-of-files-in-a-directory-using-c-or-c
// Takes a directory and recursively finds and watches all subdirectories as well as the argument directory.
// TODO currently assumes 100 total directories
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/inotify.h>

#define EVENT_SIZE  (sizeof (struct inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + 16))

// Ugly globals to avoid memory allocation, lol
char ret[1000][100];
int numDirs = 0;

/*
 * ARG1 is directory to parse.
 * Returns char**, array of strings.
 *
 * Read all files in dir and return array of strings with
 */
void get_dirs(char *arg_dir)
{
    DIR *dir;
    struct dirent *ent;
    struct stat st;

    if ( (dir = opendir(arg_dir) ) != NULL) {
        while ( (ent = readdir(dir) ) != NULL) {

            ret[numDirs][0] = '\0';
            stat(ent->d_name, &st);

            if (S_ISDIR(st.st_mode) &&
                (strcmp(ent->d_name, ".") != 0) && 
                (strcmp(ent->d_name, "..") != 0) ) {

                // Add new abs paths to discovered dirs
                strcat(ret[numDirs], arg_dir);
                strcat(ret[numDirs], "/");
                strcat(ret[numDirs], ent->d_name);

                // Recursive call
                get_dirs(ret[numDirs++]);
            }
        }

        closedir(dir);
    } 

} // End get_dirs()

int rec_inotify(char *dir)
{
    get_dirs(dir);
//char ret[1000][100];

    int length, i,j = 0;
    int fd;
    int wds[1000];
    char buffer[BUF_LEN];

    fd = inotify_init();

    if (fd < 0) {
        perror("inotify_init");
    }

    for (j = 0; j < numDirs; j++) {
        wds[0] = inotify_add_watch(fd, dir, IN_MODIFY | IN_CREATE | IN_DELETE);
        length = read(fd, buffer, BUF_LEN);  

    if (length < 0) {
        perror("read");
    }  

    while (i < length) {
        struct inotify_event *event = (struct inotify_event *)&buffer[i];
        if (event->len){
            if (event->mask & IN_CREATE) {
                if (event->mask & IN_ISDIR) {
                    printf("Directory %s created.\n", event->name);       
                }
                else {
                    printf("File %s created.\n", event->name);
                }
            }

            else if (event->mask & IN_DELETE){
                if (event->mask & IN_ISDIR){
                    printf("Directory %s deleted.\n", event->name);       
                }
                else {
                    printf("File %s deleted.\n", event->name);
                }
            }

            else if (event->mask & IN_MODIFY) {
                if (event->mask & IN_ISDIR) {
                    printf("Directory %s modified.\n", event->name);
                }
                else {
                    printf("File %s modified.\n", event->name);
                }
            }
        }
        i += EVENT_SIZE + event->len;
    }

    (void)inotify_rm_watch(fd, wd);
    (void)close(fd);

    exit(0);
} // End rec_notify()


