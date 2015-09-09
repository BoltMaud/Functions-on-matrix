#include "minicas.h"


Matrice **tableauMatrice;
int tailleMatrice = 10;
Var **tableauVariable;
int tailleVariable = 10;

void initialize()
{
	tableauMatrice = (Matrice**)malloc(tailleMatrice*sizeof(Matrice*));
	tableauVariable = (Var**)malloc(tailleVariable*sizeof(Var*));

	int i;
	for(i=0; i<tailleMatrice; i++)
	{
		tableauMatrice[i] = NULL;
		tableauVariable[i] = NULL;
	}
}

void close()
{
	tailleMatrice--;
	for(; tailleMatrice >= 0; tailleMatrice--)
		if(tableauMatrice[tailleMatrice] != NULL)
			desalloue(tableauMatrice[tailleMatrice]);

	tailleVariable--;
	for(; tailleVariable >= 0; tailleVariable--)
	{
		if(tableauVariable[tailleVariable] != NULL)
		{
			free(tableauVariable[tailleVariable]->name);
			free(tableauVariable[tailleVariable]);
		}
	}
}

int execute(char *path)
{
	initialize();

	printf("Executing : %s\n", path);
	FILE *file;
	char c;
	char *line = malloc(200);
	int n = 0;

	file = fopen(path, "r");
	if(file == NULL)
		return 1;

	while((c = fgetc(file)) != EOF)
       	{
		if(c == '\n')
		{
			line[n] = '\0';
			printf("> %s\n", line);
			n = 0;
			execLine(line);
			line = malloc(200);
		}
		else
			line[n++] = c;
	}

	fclose(file);
	close();

	return 0;
}

int interprete()
{
	initialize();

	char c;
	int n = 0;
	bool quit = false;
	char *line = malloc(200);

	printf("Interprete\n");
	printf("> ");
	while(!quit && (c = getc(stdin)) != EOF)
       	{
		if(c == '\n')
		{
			line[n] = '\0';
			n = 0;
			quit = execLine(line);
			line = malloc(200);
			if(!quit)
				printf("> ");
		}
		else
			line[n++] = c;
	}

	close();

	return 1;
}

bool execLine(char *line)
{
	char *name, *function, *param;
	int i, pos = 0;
	bool quit = false, var = true;

	for(i=0; i<strlen(line); i++)
	{
		if(line[i] == ':')
		{
			int size = i - 1;
			name = malloc(size);
			strncpy(name, line, size);
			pos = i + 2;
		}
		else if(line[i] == '(')
		{
			var = false;
			int size = i - pos;
			function = malloc(size);
			strncpy(function, line+pos, size);
			pos = i + 1;
		}
		else if(line[i] == ')')
		{
			int size = i - pos;
			param = malloc(size);
			strncpy(param, line+pos, size);
		}
	}

	if(pos == 0)
		quit = true;
	else
	{
		if(var)
		{
			int size = strlen(line) - pos;
			char *var = malloc(size);
			strncpy(var, line+pos, size);
			ajoutVar(name, atof(var));
			printf("\t%f\n", chercheVar(name));
			free(var);
		}
		else
		{
			switchFunction(name, function, param);
			free(function);
			free(line);
		}
	}

	return quit;
}

int switchFunction(char *name, char *function, char *param)
{
	if(strcmp(function, "matrix") == 0)
		return Matrix(name, param);

	char **params = parseParam(param);

	int id = matrixExists(name);
	if(id != -1)
		id = placeTabMatrice();

	Matrice *m2, *m3;
	int idParam = matrixExists(params[0]);
	if(idParam == -1)
		return 1;
	else
		m2 = tableauMatrice[idParam];

	if(strcmp(function, "invert") == 0)
	{
		tableauMatrice[id] = inverse(m2);
		affichage(tableauMatrice[id]);
	}
	else if(strcmp(function, "nullspace") == 0)
	{
		noyau(m2);
	}
	else if(strcmp(function, "determinant") == 0)
	{
		printf("\t%f\n", det(m2));
	}
	else if(strcmp(function, "rank") == 0)
	{
		printf("\t%d\n", rang(m2));
	}
	else if(strcmp(function, "mult_scal") == 0)
	{
		tableauMatrice[id] = mult_scal(m2, atof(params[1]));
		affichage(tableauMatrice[id]);
	}
	else
	{
		idParam = matrixExists(params[1]);
		if(idParam == -1)
			return 1;
		else
			m3 = tableauMatrice[idParam];

		if(strcmp(function, "addition") == 0)
		{
			tableauMatrice[id] = addition(m2, m3);
			affichage(tableauMatrice[id]);
		}
		else if(strcmp(function, "sub") == 0)
		{
			tableauMatrice[id] = sub(m2, m3);
			affichage(tableauMatrice[id]);
		}
		else if(strcmp(function, "mult") == 0)
		{
			tableauMatrice[id] = mult(m2, m3);
			affichage(tableauMatrice[id]);
		}
		else if(strcmp(function,"solve")==0){
			tableauMatrice[id]=alloue(m2->l,1);
			resolgauss(m2,m3,tableauMatrice[id]);
			affichage(tableauMatrice[id]);
			}
		else
		{
			printf("\tFonction incconnue: %s\n", function);
			return 2;
		}
	}

	if(tableauMatrice[id] != NULL)
		tableauMatrice[id]->id = name;

	return 0;
}

int Matrix(char *name, char *param)
{
	int i, pos, n = 0, oldPos = 0;
	int in = 1;
	int hauteur = 0, largeur = nbVal(param, ']');
	float *tab = malloc(nbVal(param, '\0')*sizeof(float));

	for(pos=0; pos<strlen(param); pos++)
	{
		if(param[pos] == '[')
		{
			in = 0;
			i = 0;
			oldPos = pos + 1;
		}
		else if(in == 0 && (param[pos] == ',' || param[pos] == ']'))
		{
			i++;
			int size = pos - oldPos;
			char *val = malloc(size);
			strncpy(val, param+oldPos, size);
			if(val[0] >= 'a' && val[0] <= 'z')
			{
				float v;
				if((v = chercheVar(val)) != INFINITY)
					tab[n++] = v;
				else
				{
					printf("\tVariable inconnue : %s\n", val);
					return 1;
				}
			}
			else
				tab[n++] = atof(val);
			free(val);
			if(param[pos+1] == ' ')
				oldPos = pos + 2;
			else
				oldPos = pos + 1;
		}
		if(param[pos] == ']')
		{
			in = 1;
			hauteur++;
		}
	}

	i = placeTabMatrice();
	tableauMatrice[i] = Matri(tab, hauteur, largeur);
	tableauMatrice[i]->id = name;
	affichage(tableauMatrice[i]);

	return 0;
}

float chercheVar(char *name)
{
	int i;
	for(i=0; i<tailleVariable; i++)
	{
		if(tableauVariable[i] != NULL)
		{
			if(strcmp(tableauVariable[i]->name, name) == 0)
			{
				return tableauVariable[i]->val;
			}
		}
	}

	return INFINITY;
}

void ajoutVar(char *name, float var)
{
	int id = idVar(name);
	tableauVariable[id]->name = name;
	tableauVariable[id]->val = var;
}

int idVar(char *name)
{
	int id;
	for(id=0; id<tailleVariable; id++)
		if(tableauVariable[id] != NULL)
			if(strcmp(tableauVariable[id]->name, name) == 0)
				return id;
	return placeTabVariable();
}

int placeTabVariable()
{
	int id;
	for(id=0; id<tailleVariable; id++)
	{
		if(tableauVariable[id] == NULL)
		{
			Var *var = (Var*)malloc(sizeof(Var));
			tableauVariable[id] = var;
			return id;
		}
	}

	tailleVariable += 10;
	tableauVariable = (Var**)realloc(tableauVariable, tailleVariable*sizeof(Var*));

	return tailleVariable-10;
}

int placeTabMatrice()
{
	int i;
	for(i=0; i<tailleMatrice; i++)
		if(tableauMatrice[i] == NULL)
			return i;

	tailleMatrice += 10;
	tableauMatrice = (Matrice**)realloc(tableauMatrice, tailleMatrice*sizeof(Matrice*));

	return tailleMatrice-10;
}

int nbVal(char *param, char fin)
{
	int pos, nb = 0;
	for(pos=0; param[pos]!=fin; pos++)
		if(param[pos] == ',')
			nb++;
	return nb+1;
}

int matrixExists(char *name)
{
	int i;
	for(i=0; i<tailleMatrice; i++)
		if(tableauMatrice[i] != NULL)
			if(strcmp(tableauMatrice[i]->id, name) == 0)
				return i;
	return -1;
}

char **parseParam(char *param)
{
	char **params = (char**)malloc(10*sizeof(char*));
	int oldPos = 0, pos, n = 0;

	for(pos=0; pos<=strlen(param); pos++)
	{
		if(param[pos] == ',' || param[pos] == '\0')
		{
			if(param[oldPos] == ',')
				oldPos++;
			if(param[oldPos] == ' ')
				oldPos++;
			if(param[pos-1] == ' ')
				pos--;
			int size = pos - oldPos;
			params[n] = malloc(size);
			strncpy(params[n++], param+oldPos, size);
			oldPos = pos;
		}
	}
	params[n] = NULL;

	return params;
}
