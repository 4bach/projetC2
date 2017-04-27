
#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H
#define lNl 20


typedef struct  {
  int u;
  double dist;
} Tas_elem;

typedef struct {
  int nb_tot;
  int nb_elem;
  Tas_elem* *elem;
  int* tab;
} Tas;




int racine(void);
int hasPere(int i);

int filsGauche(int i);
int filsDroit(int i);
int pere(int i);
void init(Tas* t);

int taille(Tas* t);
int isNoeud(Tas* t, int i);

int hasFilsdroit(Tas* t, int i);
int hasFilsgauche(Tas* t, int i);
int Estfeuille(Tas* t, int i);
void echanger(Tas* t, int i,int j);
void monter(Tas* t,int i);
int plusPetitfils(Tas* t,int i);
void descendre(Tas* t,int i);
Tas_elem* min(Tas* t);
void insert(Tas *t,double dist,int s);
Tas_elem* suppMin(Tas* t);
int recherche(Tas* t,int s);
void supp_elem(Tas*t, int i);
void init_lambda(int taille,double* lambda,int s);
void init_pred(int taille,int* pred);
void init_marque(int taille,int* marque);
void init_tab_som(Tas* t);
int Tasvide(Tas* t);
void Dijkstra(Graphe* G,int u,int* prev,double* lambda);
void affiche_prev(int* prev,int taille);
void affiche_lambda(double* lambda,int taille);
#endif
