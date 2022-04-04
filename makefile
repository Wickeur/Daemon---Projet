opt = -c -Wall -Wextra

invocateur.exe : invocateur.o
	gcc -o invocateur.exe invocateur.o

invocateur.o : invocateur.c
	gcc ${opt} invocateur.c

daemon.exe : daemon.o
	gcc -o daemon.exe daemon.o

daemon.o : daemon.c
	gcc ${opt} daemon.c

clean : 
	rm *.o
	rm *.exe

all : invocateur.exe daemon.exe