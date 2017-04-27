#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include "Graphe.h"
#include "Largeur.h"
#include "Struct_Liste.h"

int main(int argc,char**argv){

  char filename[104],filenameres[104],filenamencha[104];;
  int chmeth;

  if(argc!=3){
    printf("usage: %s <file> <numeromethod>\n",argv[0]);
    printf("where numeromethode = 1 if using Width firs search\n");
    return 1;
  }

  chmeth=atoi(argv[2]);
  strcpy(filename,argv[1]);
  strcpy(filenameres,argv[1]);
  strcpy(filenamencha,argv[1]);
  strcat(filenameres,".res");
  strcat(filenamencha,".ncha");

  FILE *f=fopen(filenameres,"r");

  if (f==NULL){
    printf("Probleme lecture du fichier %s\n",filenameres);
    exit(1);
  }

  Graphe G;

  lecture_graphe(&G,f);

  fclose(f);
  int cpt;
  cpt = nbarcsmin( &G, 10, 15);
  ListeEntier chemin = cheminuv( &G, 3, 16 );
  Liste_chemin* tmp = chemin_commodites( &G );
  //ecrire_commodites( &G, filenamencha );

  int longueur;
  longueur = calcul_longueur( filenamencha, &G );
  printf( "LONGUEUR = %d\n", longueur );
  int gamma;
  gamma = calcul_largeur( filenamencha, &G );
  printf( "LARGEUR = %d\n", gamma );

  //afficheGrapheSVG(&G,filename);


  return 0;
}
