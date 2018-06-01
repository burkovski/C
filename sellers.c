#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void calculation(int *);
void print(int *);

int main()
{
	int *sales[][4] = {0};

	srand(time(NULL));

	calculation(sales);
	print(sales);

	return 0;
}

void calculation(int *sales)
{
	int i, j;

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 4; j++)
		{
			*((sales + i) + j) = (rand() % 26 + 50) * (rand() % 6) * 30;
			//printf("%d %d) %d\n", i, j, *((sales + i) + j));			
		}
	}

	return;
}

void print(int *sales)
{
	int i, j, ovrp, ovrs;

	printf("\n+----------------------------------------------------------------------------------+\n");
	printf("|                              Statement of sales                                  |\n");
	printf("+----------------+-----------+-----------+-----------+-----------+-----------------+\n");
	printf("|<<<<<<<<<<<<<<<<| Seller #1 | Seller #2 | Seller #3 | Seller #4 | Ovr for product |\n");
	printf("+----------------+-----------+-----------+-----------+-----------+-----------------+\n");
	
	for (i = 0; i < 5; i++)
	{
		ovrp = 0;

		printf("|   Product #%d   |", i + 1);

		for (j = 0; j < 4; j++)
		{
			ovrp +=  *((sales + i) + j);
			printf(" %-10d|", *((sales + i) + j));

			if (j == 3)
				printf(" %-16d|\n", ovrp);
		}
		printf("+----------------+-----------+-----------+-----------+-----------+-----------------+\n");
	}
	
	printf("| Ovr for seller |");

	for (j = 0; j < 4; j++)
	{
		ovrs = 0;

		for (i = 0; i < 5; i++)
			ovrs += *((sales + i) + j);
		
		printf(" %-10d|", ovrs);

	}

	printf(">>>>>>>>>>>>>>>>>|\n");
	printf("+----------------+-----------+-----------+-----------+-----------+-----------------+\n\n");

	return;
}