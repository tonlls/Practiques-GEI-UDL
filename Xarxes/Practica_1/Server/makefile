default:clear
	gcc -ansi -pedantic -Wall -std=c17  -c common.c
	gcc -ansi -pedantic -Wall -std=c17  -c udp.c
	gcc -ansi -pedantic -Wall -std=c17  -c tcp.c 
	gcc -ansi -pedantic -Wall -std=c17  -c server.c
	gcc -ansi -pedantic -Wall -std=c17  server.o -o server
default_o:clear_o
	gcc -ansi -pedantic -Wall -std=c17 -o server server.c
test:clear_tests
	# gcc -ansi -pedantic -Wall -std=c17 -o tests/params tests/params.c
	# gcc -ansi -pedantic -Wall -std=c17 -o tests/basicserver tests/basicserver.c
	gcc -ansi -pedantic -Wall -std=c17 -o test test.c
	# gcc -ansi -pedantic -Wall -std=c17 -o tests/console tests/console.c
	# gcc -ansi -pedantic -Wall -std=c17 -o tests/rand tests/rand.c
clear_tests:
	rm -f tests/console tests/params test/basicserver test/rand
clear_o:
	rm -f server
clear:
	rm -f *.o
	rm -f server