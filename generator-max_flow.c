#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
	int i, v1, v2, w;

	int n = atoi(argv[2]);
	int m = atoi(argv[3]);

	FILE *file = fopen(argv[1], "w");  

	fprintf(file, "%d %d\n", n, m);
	for(i = 1; i <= m; i++)
	{
		v1 = (rand()%(n-1)) + 1;
		v2 = (rand()%(n-1)) + 1;
		w = rand()%100;
		fprintf(file, "%d %d %d\n", v1, v2, w);
	}
	v1 = (rand()%(n-1))+1;
	v2 = (rand()%(n-1))+1;
	fprintf(file, "%d %d", v1, v2);
	
	fclose(file);
	return 0;
}