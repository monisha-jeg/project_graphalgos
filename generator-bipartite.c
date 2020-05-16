#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
	int i, v1, v2;

	int m = atoi(argv[2]);
	int n = atoi(argv[3]);
	int e = atoi(argv[4]);

	FILE *file = fopen(argv[1], "w");  

	fprintf(file, "%d %d %d\n", m, n, e);
	for(i = 1; i <= e; i++)
	{
		v1 = (rand()%(m-1)) + 1;
		v2 = m + (rand()%(n-1)) + 1;
		fprintf(file, "%d %d\n", v1, v2);
	}
			
	fclose(file);
	return 0;
}