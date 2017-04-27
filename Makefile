all: MainGraphe

entree_sortie.o: entree_sortie.c entree_sortie.h
	gcc -c entree_sortie.c

SVGwriter.o: SVGwriter.c SVGwriter.h
	gcc -c SVGwriter.c
dijkstra.o: dijkstra.c dijkstra.h
	gcc -c dijkstra.c
MainGraphe.o: MainGraphe.c
	gcc -c MainGraphe.c


Graphe.o: Graphe.c Graphe.h SVGwriter.h Struct_File.h Struct_Liste.h
	gcc -c Graphe.c

Struct_File.o: Struct_File.c Struct_File.h
	gcc -c Struct_File.c

Struct_Liste.o: Struct_Liste.c Struct_Liste.h
	gcc -c Struct_Liste.c
test_dijkstra.o: test_dijkstra.c
	gcc -c dijkstra.c

Largeur.o : Largeur.c Largeur.h Graphe.h SVGwriter.h Struct_File.h Struct_Liste.h
	gcc -c Largeur.c

evaluation_NChaines.o: evaluation_NChaines.c evaluation_NChaines.h
	gcc -c evaluation_NChaines.c

test_dijkstra: test_dijkstra.o dijkstra.o Largeur.o Graphe.o entree_sortie.o SVGwriter.o Struct_File.o Struct_Liste.o evaluation_NChaines.o
	gcc -Wall -O -o MainGraphe MainGraphe.o Largeur.o Graphe.o entree_sortie.o SVGwriter.o Struct_File.o Struct_Liste.o evaluation_NChaines.o -lm 


MainGraphe: MainGraphe.o dijkstra.o Largeur.o Graphe.o entree_sortie.o SVGwriter.o Struct_File.o Struct_Liste.o evaluation_NChaines.o
	gcc -Wall -O -o MainGraphe MainGraphe.o Largeur.o Graphe.o entree_sortie.o SVGwriter.o Struct_File.o Struct_Liste.o evaluation_NChaines.o -lm 
clean: 
	rm -fr MainGraphe  *.o
