* files
	* aqueducte.py -> aquest script, en forma iterativa, calcula el cost minim entre construir un pont o be un aqueducte a traves dels parametres introduits
	* aqueducte_rec.py -> aquest script, en forma recursiva, calcula el cost minim entre construir un pont o be un aqueducte a traves dels parametres introduits
	
* functions
	* read_file(my_file) -> llegeix d'un descriptor de fitxer ja obert i retorna una tupla amb totes les dades
	* calc_radius(rects) -> calcula el/s radi del cemicercle entre 2 o mes punts
	* possible_pic(height,rad,cols,pic) -> comprova si una imperfeccio del terreny interferirà amb la construcció
	* its_posible_2pilars(f_input) -> comprova si es possible construir un pont de 2 columnes, al final i al principi
	* its_posible_multi_pilar(f_input)-> comprova si es possible construir un aqueducte, amb una columna per cada imperfecció del terreny
	* its_possible(f_input) -> comprova si es possible fer o bee un pont o un aqueducte
	* calc_multi_pilar(f_input) -> calcula el cost de construir un aqueducte
	* calc_2pilar(f_input) -> calcula el cost de construir un pont
	* calc(f_input) -> calcula el minim cost entre un aqueducte i un pont
	
###https://github.com/Algorismia/TonLlucia
###