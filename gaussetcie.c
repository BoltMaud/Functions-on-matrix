#include "gaussetcie.h"
// TOUTES CES FONCTIONS SONT POUR RESOLUTION
void addmultiple(Matrice *A ,Matrice *B,int i,int j,float c){
  int k;
  for(k=0;k<A->c;k++){
	A->mat[i][k]=A->mat[i][k]+c*A->mat[j][k];
   }
   B->mat[i][0]=B->mat[i][0]+c*B->mat[j][0];
}

int choixpivot(Matrice *A,int i){
  int j,a=1;
  for(j=i;j<A->c&&a;j++){
    if(!egal(A->mat[j][i],0))a=0;
	}
	if (a==0)return j;
	else return -1;
}

int choixpivotpartiel(Matrice * A,int i){
	int p,v,j;
	p=i;
	v=fabsf(A->mat[i][i]);
	for (j=i;j<A->c;j++){
		if(fabs(A->mat[j][i])>v) {
			p=j;
			v=fabs(A->mat[j][i]);
		}
	}
	return p;
}

void echangeligne(Matrice *A,Matrice *B,int i,int j){
	int k;
	float temp;
	for(k=0;k<A->c;k++){
	  temp=A->mat[i][k];
	  A->mat[i][k]=A->mat[j][k];
	  A->mat[j][k]=temp;
	}
    temp=B->mat[i][0];
    B->mat[i][0]=B->mat[j][0];
    B->mat[j][0]=temp;
	}

void triangulaire(Matrice *A,Matrice *B){
  int i,j;
  for(i=0;i<(A->l)-1;i++){
    j=choixpivotpartiel(A,i);
    echangeligne(A,B,i,j);
    for(j=i+1;j<A->c;j++){
       addmultiple(A,B,j,i,-(A->mat[j][i]/A->mat[i][i]));
       }
  }
  }

void remontee(Matrice*A,Matrice *B,Matrice*X){
  int i,j;
  for(i=A->l-1;i>-1;i--){
    X->mat[i][0]=B->mat[i][0];
    for(j=i+1;j<A->c;j++){
      X->mat[i][0]=X->mat[i][0]-(A->mat[i][j])*(X->mat[j][0]);
      }
	X->mat[i][0]=(X->mat[i][0])/(A->mat[i][i]);
  }
}

void resolgauss(Matrice * A,Matrice*B,Matrice* X){
	Matrice *cA=copyMatrix(A);
	Matrice *cB=copyMatrix(B);
  triangulaire(cA,cB);
  remontee(cA,cB,X);
  free(cA);
  free(cB);
  }



//TOUTES CES FONCTIONS SONT POUR RANG

void echangelignebb(Matrice *A,int i,int j){
	int k;
	float temp;
	for(k=0;k<A->c;k++){
	  temp=A->mat[i][k];
	  A->mat[i][k]=A->mat[j][k];
	  A->mat[j][k]=temp;
	}
	}
void addmultiplebb(Matrice *A,int i,int j,float c){
  int k;
  for(k=0;k<A->c;k++){
	A->mat[i][k]=A->mat[i][k]+c*A->mat[j][k];
  }
}
void triangulairebb(Matrice *A){
  int i,j;
  for(i=0;i<(A->l)-1;i++){
    j=choixpivotpartiel(A,i);
    echangelignebb(A,i,j);
    for(j=i+1;j<A->l;j++){
    	if (A->mat[i][i]!=0)
       addmultiplebb(A,j,i,-(A->mat[j][i]/A->mat[i][i]));
       }
  }
  }

int toutelalignenulle(float *v,int max){
	int i,stop=1;
	for(i=0;i<max&&stop;i++){
		if(!egal(v[i],0.000000))stop=0;
		}
		return stop;
	}
int rang (Matrice *m){
	int r,stop=1,j;
	Matrice *copie=copyMatrix(m);
	triangulairebb(copie);
	r=m->l;
	for(j=m->l-1;j>-1&&stop;j--){
		if(toutelalignenulle(copie->mat[j],copie->c))r--;
		else stop=0;
		}
		free(copie);
	return r ;
}

//TOUTES CES FONCTIONS SONT POUR INVERSE
void addmultiplebis(Matrice *A ,Matrice *B,int i,int j,float c){
  int k;
  for(k=0;k<A->c;k++){
	A->mat[i][k]=A->mat[i][k]+c*A->mat[j][k];
	B->mat[i][k]=B->mat[i][k]+c*B->mat[j][k];
   }
   }
void echangelignebis(Matrice *A,Matrice *B,int i,int j){
	int k;
	float temp;
	for(k=0;k<A->c;k++){
	  temp=A->mat[i][k];
	  A->mat[i][k]=A->mat[j][k];
	  A->mat[j][k]=temp;
	  temp=B->mat[i][k];
	  B->mat[i][k]=B->mat[j][k];
	  B->mat[j][k]=temp;
	}
	}
void triangulairebis(Matrice *A,Matrice *B){
  int i,j;
  for(i=0;i<(A->l)-1;i++){
    j=choixpivotpartiel(A,i);
   echangelignebis(A,B,i,j);// POURQUOI CA MARCHE COMME CA PAKOMPRI
    for(j=i+1;j<A->c;j++){
       addmultiplebis(A,B,j,i,-(A->mat[j][i]/A->mat[i][i]));
       }
  }
  }


void remonteebis(Matrice *A,Matrice *I){
  int i,j,k,l;
  float a;
	for(j=A->l-1;j>-1;j--){
		a=A->mat[j][j];
		for(i=0;i<A->c;i++){
			I->mat[j][i]=I->mat[j][i]/a;
			A->mat[j][i]=A->mat[j][i]/a;
		}
		for(k=j+1;k<=A->l-1;k++){
			for(l=0;l<A->l;l++){
				I->mat[j][l]=I->mat[j][l]-A->mat[j][k]*I->mat[k][l];
				A->mat[j][l]=A->mat[j][l]-A->mat[j][k]*A->mat[k][l];
			}
		}
	}

}


Matrice * inverse(Matrice *A){
	if(A->l!=A->c){printf("Non carrée (inverse)\n"); return NULL;}
	else{
	if(det(A)==0){printf("Matrice non inversible\n"); return NULL;}
	else {
	Matrice *copieA=copyMatrix(A);
	Matrice * I=id(A->l);
	triangulairebis(copieA,I);
	remonteebis(copieA,I);
	free(copieA);
	return I;
	}
	}
}

// ON S ATTAQUE AU NOYAU

/*
on va utiliser la meme fonction d'échelonnage que pour inverse
on va noter le nombre de ligne vide avec la fonction toutelalignenulle n
boucle on resoud faut faire la resolution speciale chaque resultat on affiche
on free
*/

void remonteN(Matrice*A,Matrice *B,Matrice*X,int l){
  int i,j;
 	for(i=l;i>-1;i--){
 		for(j=i+1;j<A->c;j++){
 			X->mat[i][0]=X->mat[i][0]-(A->mat[i][j])*(X->mat[j][0]);
 			}
 			X->mat[i][0]=(X->mat[i][0])/(A->mat[i][i]);
		}
}

//j'ai pas fait de condition matrice null
int nombrelignevide(Matrice *m){
	int i,stop=1,c=0;
	for (i=m->l-1;i>-1&&stop;i--){
		if(toutelalignenulle(m->mat[i],m->c)) c++;
		else stop=0;
		}
	return c;
}


void noyau(Matrice *m){
	Matrice *copiem=copyMatrix(m);
	triangulairebb(copiem);
	affichage(copiem);
	int nblv=nombrelignevide(copiem);
	int i;
	printf("une famille du noyau est :\n");
	for (i=m->l-nblv;i<m->l;i++){
		Matrice *b=alloue(m->l,1);
		Matrice *x=alloue(m->l,1);
		x->mat[i][0]=1;
		remonteN(copiem,b,x,m->l-nblv-1);
		affichage(x);
		free(x);
		free(b);
		}
	}

//TOUTES CES FONCTIONS SONT POUR LU

//addmultiplebis
//echangelignebis
int choixpivotpartielsup(Matrice * A,int i){
	int p,v,j;
	p=i;
	v=fabsf(A->mat[i][i]);
	for (j=A->l-1;j>i;j--){
		if(fabs(A->mat[j][i])>v) {
			p=j;
			v=fabs(A->mat[j][i]);
		}
	}
	return p;
}
void triangulaireinf(Matrice *A,Matrice *B){
  int i,j;
  for(i=A->l-1;i>-1;i--){
    j=choixpivotpartielsup(A,i);
    affichage(A);
    printf("%d",j);
    printf("%d",i);
   // echangelignebis(A,B,i,j);// POURQUOI CA MARCHE COMME CA PAKOMPRI
    for(j=A->l-1;j>i;j--){
    	affichage(A);
    	printf("L%d + %f L%d",j,-(A->mat[j][i]/A->mat[i][i]),i);
    	 addmultiplebis(A,B,j,i,-(A->mat[j][i]/A->mat[i][i]));
    	 affichage(A);
       }
  }
  }

void trianinf(Matrice *A, Matrice *B){
	float p,q;
	int i,k,j;
	for(k=A->l-1;k>-1;k--){
		p=A->mat[k][k];
		for(i=k+1;i<A->l;i++){
			q=A->mat[i][k];
			A->mat[i][k]=0;
			for(j=k+1;j<A->l;j++){
				A->mat[i][j]=A->mat[i][j]-A->mat[k][j]*(q/p);
				}
		}
	}
}
void LU(Matrice *A){
	Matrice *L=copyMatrix(A);
	Matrice *U=id(A->l);
	trianinf(L,U);
	affichage(L);
	printf("u");
	affichage(U);
	}


