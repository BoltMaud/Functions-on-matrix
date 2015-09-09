#include "minicas.h"

int main(int argc, char *argv[])
{
	if(argc == 2)
		execute(argv[1]);
	else
		interprete();

	return 0;
}
