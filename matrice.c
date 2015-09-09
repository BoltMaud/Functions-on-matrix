#include "matrice.h"

int egal(float a, float b){
	if(fabsf(a-b)<0.001)return 1;
	else return 0;
}

Matrice *alloue(int l, int c)
{
  Matrice *m = (Matrice*)malloc(sizeof(Matrice));
  m->l = l;
  m->c = c;
  m->mat = (float**)malloc(sizeof(float*)*m->l);
  int i;
  for(i=0; i<l; i++)
  {
	m->mat[i] = (float*)malloc(sizeof(float)*m->c);
	int j;
	for(j=0; j<c; j++)
		m->mat[i][j] = 0;
  }
  return m;
}


Matrice *Matri(float *val, int l, int c)
{
	Matrice *m = alloue(l, c);
	int i, j, n = 0;
	for(i=0; i<l; i++)
	  for(j=0; j<c; j++, n++)
	    m->mat[i][j] = val[n];
	return m;
}



void affichage(Matrice *m)
{ if(m==NULL){ printf("erreur : matrice NULL\n"); }
  else {int i, j;
  for(i=0; i < m->l; i++)
  {
	printf("[");
	for(j=0; j < m->c; j++)
	{
		printf(" %f ", m->mat[i][j]);
	}
	printf("]\n");
  }
  printf("\n");
  }
}

Matrice *addition(Matrice *m1, Matrice *m2)
{
  if(m1->l != m2->l || m1->c != m2->c)
  {
	printf("addition impossible");
	return NULL;
  }
  Matrice *cm1=copyMatrix(m1);
  Matrice *cm2=copyMatrix(m2);

  Matrice *m3 = alloue(m1->l ,m1->c);
  int i, j;
  for (i=0; i < cm1->l; i++)
    for(j=0; j < cm1->c; j++)
	m3->mat[i][j] = cm1->mat[i][j] + cm2->mat[i][j];
	free(cm1);
	free(cm2);
  return m3;
}

Matrice *sub(Matrice *m1, Matrice *m2)
{
  if(m1->l != m2->l || m1->c != m2->c)
  {
        printf("sub impossible");
        return NULL;
  }
  Matrice *cm1=copyMatrix(m1);
  Matrice *cm2=copyMatrix(m2);
  Matrice *m3 = alloue(m1->l, m1->c);
  int i, j;
  for (i=0; i < cm1->l; i++)
    for(j=0; j < cm1->c; j++)
      m3->mat[i][j] = cm1->mat[i][j] - cm2->mat[i][j];
	free(cm1);
	free(cm2);
   return m3;
}

Matrice *mult(Matrice *m1, Matrice *m2)
{
  if(m1->c != m2->l)
  {
	printf("mult impossible");
	return NULL;
  }
Matrice *cm1=copyMatrix(m1);
 Matrice *cm2=copyMatrix(m2);
  Matrice *m3 = alloue(cm1->l, cm2->c);
  int i,j,k;
  for(i=0; i < cm1->l; i++)
  {
    for(j=0; j < cm2->c; j++)
    {
      m3->mat[i][j] = 0;
      for(k=0; k < cm1->c; k++)
        m3->mat[i][j] = m3->mat[i][j] + cm1->mat[i][k]*cm2->mat[k][j];
    }
  }
  free(cm1);
	free(cm2);

  return m3;
}

Matrice *mult_scal(Matrice *m, float k){
	Matrice *cm=copyMatrix(m);
	Matrice *mnouv=alloue(m->l,m->c);
	int i,j;
	for(i=0;i<cm->l;i++){
	  for(j=0;j<cm->c;j++){
		mnouv->mat[i][j]=k*cm->mat[i][j];
	  }
	}
	free(cm);
	return mnouv;
}

void desalloue(Matrice *m)
{
	int i;
	for(i=0; i < m->l; i++)
	{
	  free(m->mat[i]);
	}
	free(m->mat);
	free(m);
}
Matrice *id(int a){
	Matrice *m=alloue(a,a);
	int i;
	for(i=0;i<a;i++){
		m->mat[i][i]=1;
		}
	return m;
}

Matrice *exponentiel(Matrice *m,int n){
  if(m->l!=m->c){printf("il faut une matrice carré"); return NULL;}
  else {Matrice *mnouv=alloue(m->l,m->c);
 		mnouv=id(m->l);//toujours des matrices carrés!!
 		while(n!=0){
			Matrice *temp=mnouv;
			mnouv=mult(mnouv,m);
			desalloue(temp);
			n--;
 		 }
  return mnouv;
  }
}

Matrice *transposition(Matrice *m){
	Matrice *t=alloue(m->c,m->l);
	int i,j;
	for(i=0;i<t->l;i++){
	  for(j=0;j<t->c;j++){
		t->mat[i][j]=m->mat[j][i];
	  }
	}
	return t;
}

Matrice *aux_det(Matrice *A,int n, int i){
  Matrice *B=alloue(n-1,n-1);
  int l,k;
  for(l=0;l<i;l++){
    for(k=1;k<A->c;k++){
	B->mat[l][k-1]=A->mat[l][k];
    }
  }
  for(l=i+1;l<A->l;l++){
    for(k=1;k<A->c;k++){
	B->mat[l-1][k-1]=A->mat[l][k];
    }
  }
  return B;
}


//ici n est le nb de colone
float det_aux(Matrice *A,int n){
  if(A->l!=A->c){printf("erreur : pas carré"); return 666;}
  else {
  if(n==2) return A->mat[0][0]*A->mat[1][1]-(A->mat[0][1]*A->mat[1][0]);
  if(n==1) return A->mat[0][0];
  else {
	static float d=0;
 	static float c=1;
	int i;
	for(i=0;i<n;i++){
	  Matrice *B=aux_det(A,n,i);
	  d=d+A->mat[i][0]*c*det_aux(B,n-1);
	  c=-c;
	  free(B);
	}
  return d;
  }
  }
}

float det(Matrice *A){
	Matrice *cA=copyMatrix(A);
	float a =det_aux(cA,cA->c);
	free(cA);
	return a;
	}

Matrice * copyMatrix(Matrice *m){
	Matrice * nouv=alloue(m->l,m->c);
	int i,j;
	for(i=0;i<m->l;i++){
	  for(j=0;j<m->c;j++){
		 nouv->mat[i][j]=m->mat[i][j];
	  }
	}
	return nouv;
}
