all: MainGraphe

entree_sortie.o: entree_sortie.c entree_sortie.h
	gcc -c entree_sortie.c

SVGwriter.o: SVGwriter.c SVGwriter.h
	gcc -c SVGwriter.c

<<<<<<< HEAD
MainGraphe: MainGraphe.o Graphe.o entree_sortie.o SVGwriter.o Struct_File.o Struct_Liste.o evaluation_NChaines.o
	gcc -Wall -O -o MainGraphe MainGraphe.o Graphe.o entree_sortie.o SVGwriter.o Struct_File.o Struct_Liste.o evaluation_NChaines.o -lm 

MainGraphe.o: MainGraphe.c Graphe.h
=======
MainGraphe: MainGraphe.o Largeur.o Graphe.o entree_sortie.o SVGwriter.o Struct_File.o Struct_Liste.o evaluation_NChaines.o
	gcc -Wall -O -o MainGraphe MainGraphe.o Largeur.o Graphe.o entree_sortie.o SVGwriter.o Struct_File.o Struct_Liste.o evaluation_NChaines.o -lm 

MainGraphe.o: MainGraphe.c Graphe.h Largeur.h
>>>>>>> a3e2ede478f21cd4f0539fe14c29c85859bdff12
	gcc -c MainGraphe.c

Graphe.o: Graphe.c Graphe.h SVGwriter.h Struct_File.h Struct_Liste.h
	gcc -c Graphe.c

Struct_File.o: Struct_File.c Struct_File.h
	gcc -c Struct_File.c

Struct_Liste.o: Struct_Liste.c Struct_Liste.h
	gcc -c Struct_Liste.c

<<<<<<< HEAD
=======
Largeur.o : Largeur.c Largeur.h Graphe.h SVGwriter.h Struct_File.h Struct_Liste.h
	gcc -c Largeur.c

>>>>>>> a3e2ede478f21cd4f0539fe14c29c85859bdff12
evaluation_NChaines.o: evaluation_NChaines.c evaluation_NChaines.h
	gcc -c evaluation_NChaines.c


clean: 
	rm -fr MainGraphe  *.o
