default:clear
	gcc -ansi -pedantic -Wall -std=c17  -c common.c
	gcc -ansi -pedantic -Wall -std=c17  -c udp.c
	gcc -ansi -pedantic -Wall -std=c17  -c tcp.c 
	gcc -ansi -pedantic -Wall -std=c17  -c server.c
	gcc -ansi -pedantic -Wall -std=c17  server.o -o server
clear:
	rm -f *.o
	rm -f server