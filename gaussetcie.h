#ifndef GAUSS
#define GAUSS
#include "matrice.h"

// TOUTES CES FONCTIONS SONT POUR RESOLUTION
//ATTENTION CES FONCTIONS MODOFIE A ET B

/**
*\param Matrice B : ici en matrice colone (seulement pour resolutino)
*\param Matrice A : carre je crois
*\param int i : la ligne
*\param int j : la ligne qu'on va rajouter
*\param float c : le coeff
* Cette fonction ajoute 'c' fois la ligne j à la ligne i
*/
//critique pas on voit mieux avec cette mise en forme
void addmultiple(Matrice *A ,Matrice *B,int i,int j,float c);

//marche mais j'utilise partiel, mieux je crois
int choixpivot(Matrice *A,int i);

//recherche du pivot sous la diagonale
int choixpivotpartiel(Matrice * A,int i);

//echange les lignes i et j des deux matrices
//ici B est colone
void echangeligne(Matrice *A,Matrice *B,int i,int j);

//met A sous forme triangulaire et modifie B en conséquence
void triangulaire(Matrice *A,Matrice *B);

//resolution enfait mais faut d'abord faire triangulaire
void remontee(Matrice*A,Matrice *B,Matrice*X);

//triangulaire  + remontee
void resolgauss(Matrice * A,Matrice*B,Matrice* X);

//FIN RESOLUTION

//TOUTES CES FONCTIONS SONT POUR RANG

//la meme que pour resol sauf 1 seule matrice
void echangelignebb(Matrice *A,int i,int j);

//la meme
void addmultiplebb(Matrice *A,int i,int j,float c);

//la meme
void triangulairebb(Matrice *A);

//auxiliaire a rang, donne 0 si v non rempli de 0 1sinon
int toutelalignenulle(float *v,int max);

//renvoie le rang de m
int rang (Matrice *m);

//TOUTES CES FONCTIONS SONT POUR INVERSE

void addmultiplebis(Matrice *A ,Matrice *B,int i,int j,float c);
void echangelignebis(Matrice *A,Matrice *B,int i,int j);
void triangulairebis(Matrice *A,Matrice *B);
void remonteebis(Matrice *A,Matrice *I);
Matrice * inverse(Matrice *A);


void remonteN(Matrice*A,Matrice *B,Matrice*X,int l);
int nombrelignevide(Matrice *m);
void noyau(Matrice *m);

#endif // GAUSS

