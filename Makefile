all: MainGraphe -lm

entree_sortie.o: entree_sortie.c entree_sortie.h
	gcc -c entree_sortie.c -g

SVGwriter.o: SVGwriter.c SVGwriter.h
	gcc -c SVGwriter.c -g
dijkstra.o: dijkstra.c dijkstra.h
	gcc -c dijkstra.c -g
Graphe.o: Graphe.c Graphe.h SVGwriter.h Struct_File.h Struct_Liste.h
	gcc -c Graphe.c -g

Struct_File.o: Struct_File.c Struct_File.h
	gcc -c Struct_File.c -g

Struct_Liste.o: Struct_Liste.c Struct_Liste.h
	gcc -c Struct_Liste.c -g

Largeur.o : Largeur.c Largeur.h Graphe.h SVGwriter.h Struct_File.h Struct_Liste.h
	gcc -c Largeur.c -g

evaluation_NChaines.o: evaluation_NChaines.c evaluation_NChaines.h
	gcc -c evaluation_NChaines.c -g
MainGraphe.o: MainGraphe.c
	gcc -c MainGraphe.c -g
MainGraphe: MainGraphe.o dijkstra.o Largeur.o Graphe.o entree_sortie.o SVGwriter.o Struct_File.o Struct_Liste.o evaluation_NChaines.o
	gcc -Wall -O -o MainGraphe dijkstra.o MainGraphe.o Largeur.o Graphe.o entree_sortie.o SVGwriter.o Struct_File.o Struct_Liste.o evaluation_NChaines.o -g -lm 
clean: 
	rm -fr MainGraphe  *.o
