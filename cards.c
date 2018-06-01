#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void suffle(int[][13]);
void deal(const[][13], const char *[], const char *[]);

main()
{
	char *suit[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};
	char *face[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

	int deck[4][13] = {0};

	srand(time(NULL));

	suffle(deck);
	deal(deck, face, suit);

	return 0;
}

void suffle(int wDeck[][13])
{
	int card, row, column;

	for (card = 1; card <= 52; card++)
	{
		row = rand() % 4;
		column = rand() % 13;

		while (wDeck[row][column] != 0)
		{
			row = rand() % 4;
			column = rand() % 13;
		}

		wDeck[row][column] = card;
	}
}

void deal(const int wDeck[][13], const char *wSuit[], const char *wFace[])
{
	int card, row, column;

	for (card = 1; card <= 52; card++)
		for (row = 1; row <= 3; row++)
			for (column = 1; column <= 13; column++)

				if (wDeck[row][column] == card)
					printf("\n%5s of %-8s\n", wFace[column], wSuit[row] /*,card % 2 == 0 ? '\n' : '\t'*/);
					//printf("%d\n", card);
}