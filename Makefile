
all: javaclp

javaclp: javaclp.c eiberead.s
	gcc -o javaclp javaclp.c eiberead.s

clean:
	rm -f javaclp 
