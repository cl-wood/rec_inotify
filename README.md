rec_inotify
===========

Watches the directory you specify, along with any sub-dirs. Recurses arbitrary deep, but I'm lazy so it only works for <= 1000 dirs.

Compile with: 
    gcc -pthread run.c

Run with:
    ./a.out [dir to watch]


