#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SELLER 100

void slr(int *);
void print(int *);

int main()
{
	int counts [9] = {0};
	
	srand(time(NULL));

	slr(counts);
	print(counts);

	return 0;	
}

void slr(int *counts)
{
	int i, salary;

	for (i = 0; i < SELLER; i++)
	{
		salary = 200 + 0.09 * (rand() % 10001);
		//printf("\n%d) Salary: %d\n", i+1, salary);

		*(counts + (salary / 100 - 2)) += 1;
	}
 }

void print(int *counts)
{
	int i;

	printf("\n+----------------------------------+\n");
	printf("|  Statement of employees salaries |\n");
	printf("+-----------------+----------------+\n");
	printf("|     Salary      |    Employees   |\n");
	printf("+-----------------+----------------+\n");
	
	for (i = 0; i < 9; i++)
	{
		if (i == 8)
		{
			printf("| -> More $%d:  | %-15d|\n", 100 * (i + 2), *(counts + i));
			printf("+----------------------------------+\n\n");
			return;
		}
		printf("| -> $%d-$%d:   | %-15d|\n", 100 * (i + 2), 100 * (i + 2) + 99, *(counts + i));
		printf("+-----------------+----------------+\n");
	}
}
