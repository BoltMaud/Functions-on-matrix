#ifndef MINICAS_H
#define MINICAS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrice.h"
#include "gaussetcie.h"

typedef struct
{
	char *name;
	float val;
} Var;

void initialize();
void close();
int execute(char *file);
bool execLine(char *line);
char **parseParam(char *param);
int Matrix(char *name, char *param);
int nbVal(char *param, char fin);
int switchFunction(char *name, char *function, char *param);
int matrixExists(char *name);
float chercheVar(char *name);
void ajoutVar(char *name, float var);
int idVar(char *name);
int placeTabVariable();
int placeTabMatrice();
int interprete();

#endif // MINICAS_H
