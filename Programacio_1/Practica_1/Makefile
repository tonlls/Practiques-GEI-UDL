CXXFLAGS = -ansi -Wall

all: ex1 ex2

test: test-ex1 test-ex2

dist: primera-practica.tar.gz

test-ex1: ex1
	for JP in 0 1 2 3 4; do \
		echo "**** Exercici 1.$$JP ****"; \
		./ex1 < ex1-jp$$JP.txt; \
	done

test-ex2: ex2
	echo "**** Exercici 2 ****"
	./ex2 < ex2-jp0.txt

check: ex1
		@for JP in 1 2 3; do \
			echo "**** Exercici 1.$$JP ****"; \
			./ex1 < ex1-jp$$JP.txt > temp.txt; \
			grep `cat ex1-jp$$JP.out` temp.txt; \
		done

clean:
	$(RM) -f ex1 ex2 temp.txt

primera-practica.tar.gz: Makefile ex1-jp*.* ex2-jp*.* ex1.cpp ex2.cpp
	tar zcvf $@ $^
