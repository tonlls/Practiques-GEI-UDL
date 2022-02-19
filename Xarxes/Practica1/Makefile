cli_src = $(wildcard client/src/*.c)
cli_obj = $(cli_src:.c=.o)
flags = -ansi -pedantic -Wall -std=c17

default: all

print-%  : ; @echo $* = $($*)

all: Client
Client: client clean

client: $(cli_src)
	gcc $(flags) -c $^
	mv *.o $@/out/
	gcc $(flags) $@/out/$@.o -o $@/out/$@

clean:
	rm -f client/out/*.o

.PHONY: clean client Client all