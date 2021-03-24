default:clear
	gcc -ansi -pedantic -Wall -std=c17 -o server server.c
test:clear_tests
	gcc -ansi -pedantic -Wall -std=c17 -o tests/params tests/params.c
	gcc -ansi -pedantic -Wall -std=c17 -o tests/basicserver tests/basicserver.c
	gcc -ansi -pedantic -Wall -std=c17 -o tests/console tests/console.c
clear_tests:
	rm -f tests/console tests/params 
clear:
	rm -f server