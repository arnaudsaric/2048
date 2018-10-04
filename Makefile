all:
	gcc -g -static core.c checks.c actions.c -std=c99 -o 2048

clean:
	rm -f 2048
