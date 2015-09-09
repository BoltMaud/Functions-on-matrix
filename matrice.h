#ifndef Matrix_
#define Matrix_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
  float **mat;
  int l;
  int c;
  char*id;
} Matrice;

//egalité entre les floattants c'est un bordel
int egal(float a, float b);

//alloue et met a 0
Matrice *alloue(int l, int c);

//free
void desalloue(Matrice *m);

//matrice identité ; des 1 sur diago
//paramètre : le nombre de colones/lignes
Matrice *id(int a);

//alloue la même matrice
Matrice * copyMatrix(Matrice *m);

//remplir la matrice
Matrice *Matri(float *val, int l, int c);

//affichage de la matrice
void affichage(Matrice *m);

// TOUTES CES FUTURES FONCTIONS ALLOUES UNE NOUVELLE MATRICE

//addition des matrices
Matrice *addition(Matrice *m1, Matrice *m2);

//sub
Matrice *sub(Matrice *m1, Matrice *m2);

//multiplication matrice
Matrice *mult(Matrice *m1, Matrice *m2);

//multiplication par un scalaire (flottant)
Matrice *mult_scal(Matrice *m, float k);

//exponentielle de matrice CARRE
Matrice *exponentiel(Matrice *m,int n);

//colones deviennent lignes
Matrice *transposition(Matrice *m);

//

//fonction auxiliaire du det
Matrice *aux_det(Matrice *A,int n, int i);

float det_aux(Matrice *A,int n);

//marche
float det(Matrice *A);




#endif // Matrix
