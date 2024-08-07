#include <stdio.h>

int main(int argc, char *argv[]) {
	int num;
	int s=0;
	printf ("Ingresa el numero de vertices de tu grafo\n");
	scanf ("%d", &num);
	int M [num][num];
	int Vec [num];
	printf ("Recuerda que un lazo equivale a 2 en la matriz\n");
	for(int c=0;c<num;c++){
		for (int x=0;x<num;x++){
			printf("Ingresa un valor(%d,%d)",c,x);
			scanf("%d",&M[c][x]);
			s=s+M[c][x];
		}
		Vec[c]=s;
		s=0;
	}
	for(int c=0;c<num;c++){
		for (int x=0;x<num;x++){
			printf("%d",M[c][x]);
		}
		printf("\n");
	}
	for (int c=0;c<num;c++){
		printf("-");
	}
	printf ("\n");
	for(int c=0;c<num;c++){
		printf ("%d",Vec[c]);
	}
	//for (int c=0;c<num;c++){
	//printf("1");
	//}
	//for (int c=0;Vec[c]==Vec[c+1];c++){
		
	//}
	for (int c=0;c<num;c++){
		if (Vec[c]==Vec[c+1]){
			c=c+1;
			printf("Es regular");
		}
		
		else {
			c=num;
		}
		printf("No es regular");
	}
	return 0;
}


