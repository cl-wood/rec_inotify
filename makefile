build: rec_inotify.c reg_inotify.c
	gcc -pthread -o recursive_inotify rec_inotify.c
	gcc -pthread -o regular_inotify reg_inotify.c
clean:
	rm -f reg rec
