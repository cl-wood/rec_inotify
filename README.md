rec_inotify
===========

Can watch the directory you specify, along with any sub-dirs. Recurses arbitrary deep, but I'm lazy so it only works for <= 1000 dirs. Certain dirs, like /etc/, contain MANY sub-dirs, and so you might want to just pick some sub-dirs to watch recursively and watch /etc without recursion.

Compile with: 
    make

Run with:
    python run.py | tee inotify.log

Troubleshooting:
    If you start getting bad file descriptors, pgrep for regular/recursive inotify and kill those processes

