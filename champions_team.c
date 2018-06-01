#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20

int main()

{
	struct team
	{
		char name[100];
		int points;
	}array[SIZE], result[3];

	int i;
	srand(time(NULL));

	for(i = 0; i < SIZE; i++)
	{
		scanf("%s", array[i].name);
		array[i].points = rand()%100;
		printf("%d) %s: %d\n\n", i+1, array[i].name, array[i].points);
	}
	
	result[0] = array [0];
	result[1] = array [0];
	result[2] = array [0];
	
	for(i = 0; i < SIZE; i++)
	{
		if(array[i].points > result[0].points)
		{
			result[1] = result[0];
			result[0] = array[i];
		}
		
		else
		{
			if(array[i].points > result[1].points)
			{
				result[2] = result[1];
				result[1] = array[i];
			}

		}
	}

	printf("First place: %s\n", result[0].name);
	printf("Second place: %s\n", result[1].name);
	printf("Third place: %s\n", result[2].name);

	return 0;
}

