
game:
	gcc -Wall crupier.c -o crupier
	gcc -Wall jugador.c -o jugador
game1:
	gcc -Wall jugador.c -o jugador
	gcc -Wall crupier1.c -o crupier1
game2:
	gcc -Wall jugador2.c -o jugador2
	gcc -Wall crupier2.c -o crupier2
game3:
	gcc -Wall crupier3.c -o crupier3
	gcc -Wall jugador3.c -o jugador3
game4:
	gcc -Wall crupier4.c -o crupier4
	gcc -Wall jugador4.c -o jugador4
clear:
	$(RM) jugador jugador1 jugador2 jugador3 jugador4
	$(RM) crupier crupier1 crupier2 crupier3 crupier4
	$(RM) LLUCIÀ_PRA1_SO.tgz
dist: clear
	tar -zcvf LLUCIÀ_PRA1_SO.tgz crupier*.c jugador*.c makefile Memoria.pdf