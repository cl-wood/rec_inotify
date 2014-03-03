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
#include <pthread.h>
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

void watch_dir(char *dir)
{

  int length, i = 0;
  int fd;
  int wd;
  char buffer[BUF_LEN];

  fd = inotify_init();

  if (fd < 0) {
    perror("inotify_init");
  }

  wd = inotify_add_watch(fd, "/home/musashi/CCDC", IN_MODIFY | IN_CREATE | IN_DELETE);
  length = read(fd, buffer, BUF_LEN);  

  if (length < 0) {
    perror("read");
  }  

  while (i < length) {
    struct inotify_event *event = (struct inotify_event *)&buffer[ i ];
    if (event->len) {
      if (event->mask & IN_CREATE) {
        if (event->mask & IN_ISDIR) {
          printf("The directory %s was created.\n", event->name);       
        }
        else {
          printf("The file %s was created.\n", event->name);
        }
      }
      else if (event->mask & IN_DELETE) {
        if (event->mask & IN_ISDIR) {
          printf("The directory %s was deleted.\n", event->name);       
        }
        else {
          printf("The file %s was deleted.\n", event->name);
        }
      }
      else if (event->mask & IN_MODIFY) {
        if (event->mask & IN_ISDIR) {
          printf("The directory %s was modified.\n", event->name);
        }
        else {
          printf("The file %s was modified.\n", event->name);
        }
      }
    }
    i += EVENT_SIZE + event->len;
  }

  inotify_rm_watch(fd, wd);
  close(fd);

} // End watch_dir()

void watch_dir_continuously(void* dir) {

    printf("%s\n", (char *) dir); fflush(stdout);

    while (1) {
        printf("[*] Watching...\n");
        watch_dir( (char *) dir);
    }
}

void rec_inotify(char *dir)
{
    int i;
    get_dirs(dir);
    pthread_t threads[1000];
    int ptRet[1000];

    for (i = 0; i < numDirs; i++) {
        ptRet[i] = pthread_create(&threads[i], 
                                  NULL, 
                                  (void*) watch_dir_continuously, 
                                  (void*) &ret[i]);
    }

    // Done, cleanup
    for (i = 0; i < numDirs; i++) {
        pthread_join(threads[i], NULL);
    }

} // End rec_inotify()


