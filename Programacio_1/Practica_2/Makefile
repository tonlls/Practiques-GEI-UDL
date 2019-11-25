CXXFLAGS = -ansi -Wall
TARGETS=ex1 ex2

all: $(TARGETS)

dist: segona-practica.tar.gz

test: $(TARGETS)
	echo "**** Exercici 1.0 ****"
	./ex1 < ex1-jp0.txt
	echo "**** Exercici 1.1 ****"
	./ex1 < ex1-jp1.txt
	echo "**** Exercici 1.2 ****"
	./ex1 < ex1-jp2.txt
	echo "**** Exercici 1.3 ****"
	./ex1 < ex1-jp3.txt
	echo "**** Exercici 1.4 ****"
	./ex1 < ex1-jp4.txt
	echo "**** Exercici 1.5 ****"
	./ex1 < ex1-jp5.txt
	echo "**** Exercici 1.6 ****"
	./ex1 < ex1-jp6.txt
	echo "**** Exercici 2.0 ****"
	./ex2 < ex2-jp0.txt
	echo "**** Exercici 2.1 ****"
	./ex2 < ex2-jp1.txt
	echo "**** Exercici 2.2 ****"
	./ex2 < ex2-jp2.txt
	echo "**** Exercici 2.3 ****"
	./ex2 < ex2-jp3.txt

check: $(TARGETS)
	for x in `seq 10`; do python entremaliat.py lorem.txt > test.txt; ./ex1 < test.txt; done

clean:
	$(RM) $(TARGETS)

segona-practica.tar.gz: Makefile ex1-jp*.* ex2-jp*.* ex1.cpp ex2.cpp entremaliat.py lorem.txt
	tar zcvf $@ $^

