#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include "Graphe.h"
#include "Largeur.h"
#include "Struct_Liste.h"
#include "evaluation_NChaines.h"


/*void menu(void)
{
  printf("--------------------------------------------\n");
  printf("FICHIER 1 : 00783_rat\n");
  printf("FICHIER 2 : 05934_rl\n");
  printf("FICHIER 3 : 07397_pla\n");
  printf("--------------------MENU--------------------\n");
  printf("|0: QUITTER LE MENU\n");
  printf("|1: ECRIRE FICHIERS NCHA\n");
  printf("|2: CALCUL LONGUEUR\n");
  printf("|3: CALCUL LARGEUR\n");
  printf("|4: EVALUATION DES CHAINES\n");
  printf("--------------------------------------------\n");
}*/


int main(int argc,char* *argv)
{ 
  char filename[104],filenameres[104],filenamencha[104];;
    int chmeth;
    int ch;
    double longueur1, longueur2, longueur3;
    int gamma1, gamma2, gamma3;
    double eval1, eval2, eval3;

  if(argc!=2){
    printf("usage: <numeromethod>\n");
    printf("Numeromethode = 1  pour le parcours en largeur\n");
    printf("Numeromethode = 2  pour l'algorithme de Diskjtra'\n");
    printf("Numeromethode = 3  pour l'algorithme Optimisé'\n");
    return 1;
  }
  chmeth = atoi(argv[1]);

  char* test1res = "Instances_res/00783_rat.res";
  char* test1cha = "Instances_res/00783_rat.ncha";

  char* test2res = "Instances_res/05934_rl.res";
  char* test2cha = "Instances_res/05934_rl.ncha";

  char* test3res = "Instances_res/07397_pla.res";
  char* test3cha = "Instances_res/07397_pla.ncha";

  FILE *f1 = fopen( test1res, "r" );
  if ( f1 == NULL ){
      printf( "Probleme lecture du fichier 00783_rat.res\n");
      exit( 1 );
  }

  FILE *f2 = fopen( test2res, "r" );
  if ( f2 == NULL ) {
      printf( "Probleme lecture du fichier 05934_rl.res\n");
      exit( 1 );
  }

  FILE *f3 = fopen( test3res, "r" );
  if ( f2 == NULL ) {
      printf("Probleme lecture du fichier 07397_pla.res\n");
      exit( 1 );
  }

  Graphe G1, G2, G3;

  lecture_graphe( &G1, f1 );
  lecture_graphe( &G2, f2 );
  lecture_graphe( &G3, f3 );

  fclose(f1);
  fclose(f2);
  fclose(f3);
  printf("--------------------------------------------\n");
  printf("FICHIER 1 : 00783_rat\n");
  printf("FICHIER 2 : 05934_rl\n");
  printf("FICHIER 3 : 07397_pla\n");
  printf("--------------------------------------------\n");

  if( chmeth == 1 ) {
    
    ecrire_commodites( &G1, test1cha );   
    ecrire_commodites( &G2, test2cha );
    ecrire_commodites( &G3, test3cha );

    gamma1 = calcul_largeur( test1cha, &G1 );
    gamma2 = calcul_largeur( test2cha, &G2 );
    gamma3 = calcul_largeur( test3cha, &G3 );

    longueur1 = calcul_longueur( test1cha, &G1 );
    longueur2 = calcul_longueur( test2cha, &G2 );
    longueur3 = calcul_longueur( test3cha, &G3 );

    eval1 = evaluation_NChaines( gamma1, longueur1, test1cha ); 
    eval2 = evaluation_NChaines( gamma2, longueur2, test2cha ); 
    eval3 = evaluation_NChaines( gamma3, longueur3, test3cha ); 
  
    printf( "Instance = %s, Evaluation = %f, Gamma = %d, Longueur = %f\n", test1cha, eval1, gamma1, longueur1 );
    printf( "Instance = %s, Evaluation = %f, Gamma = %d, Longueur = %f\n", test2cha, eval2, gamma2, longueur2 );
    printf( "Instance = %s, Evaluation = %f, Gamma = %d, Longueur = %f\n", test3cha, eval3, gamma3, longueur3 );
  }
  else if( chmeth == 2 ) {

  } 
  else if( chmeth == 3 ) {

  }
        
  return 0;
}
int cpt;
  cpt = nbarcsmin( &G, 10, 15);
