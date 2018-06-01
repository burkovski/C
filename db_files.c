#include <stdio.h>
// #include <conio.h>
#include <malloc.h>
#include <locale.h>

#define KEY_CODE_ENTER	13
#define KEY_CODE_ESC	27
#define KEY_CODE_1		49
#define KEY_CODE_2		50
#define KEY_CODE_3		51
#define KEY_CODE_4		52
#define KEY_CODE_5		53
#define KEY_CODE_6		54
#define KEY_CODE_7		55
#define KEY_CODE_8		56
#define KEY_CODE_9		57

#define KEY_CODE_n		110
#define KEY_CODE_y		121
#define KEY_CODE_N		78
#define KEY_CODE_Y		89

#define SORT_BY_NAME	1
#define SORT_BY_ADDR	2
#define SORT_BY_PHONE	3
void menuDraw()
{
	system("clear");
	printf("+--------[Menu]------+\n");
	printf("| #1   Load db       |\n");
	printf("| #2   Display db    |\n");
	printf("| #3   Sort db       |\n");
	printf("| #4   Add record    |\n");
	printf("| #5   Edit record   |\n");
	printf("| #6   Remove record |\n");
	printf("| #7   Save db       |\n");
	printf("| #8   Save as db    |\n");
	printf("| #9   About         |\n");
	printf("| #Esc Exit          |\n");
	printf("+--------------------+\n");
}
typedef struct tagPhoneBook
{
	char			name[32];
	char			address[32];
	char			phone[32];
}t_db;

int		keyCode = 0;
char	strBuf[16];
FILE	*fd;
int		fileSize = 0;
t_db	*dbArrayPtr = NULL;
t_db	test[20];
t_db	*ptr = NULL;
int		dbArraySize	= 0;
int		err;
int		i,j, tmp, counter;
char	dataChanged = 0;
/* Повертає код натиснутої клавіші */
int keyPoller()
{
	while(!_kbhit());
	return _getch();
}
/* Очищує поточну строку консолі */
void clearLine()
{
	int i = 79;
		while(i--)
			printf(" ");
	printf("\r");
}
/* Друкує повідомлення, чекає поки буде натиснута клавіша */
void printBackMsg()
{

	printf("\nBack to main menu : press any key");
	getch();
	menuDraw();
}
/*  Запит  чи ігнорувати втрату даних*/
int confirmDataLost()
{
	if(dataChanged)
	{
		printf("All DB changes will be lost, continue? (Enter - continue, any key - return)\n");
	if(keyPoller() == KEY_CODE_ENTER)
		return 1;
	return 0;
	}
	return 1;
}
/* виводить данні з масиву структур  */
void printDbTable()
{
	if(!dbArrayPtr)
	{
		clearLine();
		printf("DB empty, nothing to display\r");
		return;
	}
	system("cls");
	printf("+-[id]-+---------[Name]-------+-------[Address]--------+--------[Phone]-------+\n");
	for(i = 0; i < dbArraySize; i ++)
	{
		ptr = dbArrayPtr + i;
		//ptr = &dbArrayPtr[i];
		tmp = i;
		j = 0;
		/* Вирівнювання стовпчика таблиці */
		while(tmp/=10)
			j++;
		j = 4 - j;

		printf("| %d" , i);
		
		if(j > 0)
			while(j--)
				printf(" ");

		printf("| %s" , ptr -> name); 
		j  = 21 - strlen(ptr -> name);

		if (j > 0)
			while (j--)
				printf(" ");
		printf("| %s" , ptr -> address); 

		j  = 23 - strlen(ptr -> address);
		
		if (j > 0)
			while (j--)
				printf(" ");
		printf("| %s" , ptr -> phone); 

		j  = 21 - strlen(ptr -> phone);
		if (j > 0)
			while (j--)
				printf(" ");
		printf("|\n");
		/* Якщо елементів більше ніж 20, виводим таблицю сторінками*/
		if(!((i+1)%20))
		{
			//printf("%d", i);
			printf("+------+----------------------+------------------------+----------------------+\n");
			printf("%d/%d page, Enter - show next page, any key - stop display\r",i/20+1, dbArraySize/20+1);
			/*Очікуемо поки користувач обере варіант дії*/
			keyCode = keyPoller();
			/* Якщо клавіша не ентер виходимо */
			if(keyCode != KEY_CODE_ENTER)
				return;
			/*інакше друкуємо наступну сторінку */
			keyCode = 0;
			system("cls");
			printf("+-[id]-+---------[Name]-------+-------[Address]--------+--------[Phone]-------+\n");
		}

	}
	printf("+------+----------------------+------------------------+----------------------+\n");
}

int sortPartBy(t_db *a, int l, int r, char o)
{
	int i = l, j = r	;
	t_db tmp;
	t_db *pivot = a + ((l + r)/ 2); 
	switch(o)
	{
		case SORT_BY_NAME:	
			while(i <=j )
			{
				while(strcmp((a + i) -> name, pivot  -> name) < 0)
				{
					i++;
					//counter ++;
				}
				while(strcmp((a + j) -> name, pivot  -> name) > 0)
				{
					j--;
					//counter ++;
				}
				if (i <= j)
				{
					printf("Replacing [value=%s index=%d]  <--> [value=%s index=%d]\r",(a + i) -> name,i,(a + j) -> name, j);
					memcpy(&tmp, (a + i), sizeof(t_db));
					memcpy((a + i), (a + j), sizeof(t_db));
					memcpy((a + j), &tmp, sizeof(t_db));
					i++;
					j--;
					counter ++;
			   }
			}
		break;
		case SORT_BY_ADDR:			
			while(i <=j )
			{
				while(strcmp((a + i) -> address, pivot  -> address) < 0)
					i++;
				while(strcmp((a + j) -> address, pivot  -> address) > 0)
					j--;
				if (i <= j)
				{
					printf("Replacing [value=%s index=%d]  <--> [value=%s index=%d]\r",(a + i) -> address,i,(a + j) -> address, j);
					memcpy(&tmp, (a + i), sizeof(t_db));
					memcpy((a + i), (a + j), sizeof(t_db));
					memcpy((a + j), &tmp, sizeof(t_db));
					i++;
					j--;
					counter ++;
			   }
			   
			}
		break;
		case SORT_BY_PHONE:
			while(i <=j )
			{
				while(strcmp((a + i) -> phone, pivot  -> phone) < 0)
					i++;
				while(strcmp((a + j) -> phone, pivot  -> phone) > 0)
					j--;
				if (i <= j)
				{
					printf("Replacing [value=%s index=%d]  <--> [value=%s index=%d]\r",(a + i) -> phone,i,(a + j) -> phone, j);
					memcpy(&tmp, (a + i), sizeof(t_db));
					memcpy((a + i), (a + j), sizeof(t_db));
					memcpy((a + j), &tmp, sizeof(t_db));
					i++;
					j--;
					counter ++;
			   }
			}
		break;
	}
	return i;
}

void sortBy(t_db *a, int l, int r, char o) {

      int i = sortPartBy(a, l, r, o);

      if (l < i - 1)
            sortBy(a, l, i - 1, o);

      if (i < r)
            sortBy(a, i, r, o);

}


int main()
{

	setlocale(LC_ALL,"Ukrainian");
	memset(strBuf, sizeof(strBuf), 0);
	strcpy(strBuf, "");
	menuDraw();
	while(1)
	{	
		switch(keyCode = keyPoller())
		{
			case KEY_CODE_1:
				if(!confirmDataLost())
				{
					menuDraw();
					break;
					
				}
				dataChanged = 0;
				clearLine();
				printf("Input file name : ");
				scanf("%s",strBuf);
				menuDraw();
				if(err = fopen_s(&fd, strBuf, "rb"))
				{
					printf("\rCan`t read file (%s), error(%d)\r", strBuf,err);
					break;
				}
				/* Встановлюємо каретку в кінець файлу*/
				fseek(fd, 0, SEEK_END);
				/* Отримуємо розмір файлу в байтах */
				fileSize = ftell(fd);
				/* Рахуємо кількість єелементів*/
				dbArraySize = fileSize / sizeof(t_db);
				/* Якшо пам`ять вже виділина, звільняємо */
				if(dbArrayPtr)
					free(dbArrayPtr);
				/* Виділяємо озрахований об`єм */
				dbArrayPtr = (t_db*)malloc(sizeof(t_db) * dbArraySize);
				/* повертаємо каретку до початку файлу */
				fseek(fd, 0, SEEK_SET);
				/* читаємо файл */
				printf("Reading file [name=%s size=%d bytes] Successfuly readed %d/%d records", strBuf, fileSize, 
				fread(dbArrayPtr, sizeof(t_db), dbArraySize, fd), dbArraySize);
				fclose(fd);
			break;
			case KEY_CODE_2: 
				printDbTable();
				printBackMsg();

			break;
			case KEY_CODE_3: 
				if(!dbArrayPtr)
				{
					clearLine();
					printf("DB empty, nothing to sort\r");
					break;
				}
				while(1)
				{
					system("cls");
					printf("+----------[Sort]-------------------\n|\n");
					printf("+-> #1   By name\n");
					printf("+-> #2   By address\n");
					printf("+-> #3   By phone\n");
					printf("+-> #Any Exit\n");
					keyCode = keyPoller();
					counter = 0;
					switch(keyCode)
					{
					case KEY_CODE_1 : sortBy(dbArrayPtr, 0, dbArraySize-1, SORT_BY_NAME); break;
					case KEY_CODE_2 : sortBy(dbArrayPtr, 0, dbArraySize-1, SORT_BY_ADDR);break;
					case KEY_CODE_3 : sortBy(dbArrayPtr, 0, dbArraySize-1, SORT_BY_PHONE);break;
					default:
						break;
					}
					clearLine();
					printf("+------------------------------------\n");
					printf("\rSuccess! Total sort iterations=%d\n(Enter - sort again /Any key - back main menu)",counter);
					
					dataChanged = 1;
						
						keyCode = keyPoller();
						if(keyCode != KEY_CODE_ENTER)
							break;

				}
				menuDraw();
					
				
			break;
			case KEY_CODE_4: 
				while(1)
				{
					system("cls");
					printf("+----------[Add new record]----------\n|\n");
					if(!dbArrayPtr)
					{
						dbArrayPtr = (t_db*)malloc(sizeof(t_db));
						dbArraySize = 1;
					}
					else
					{
						dbArraySize ++;
						dbArrayPtr = (t_db*)realloc(dbArrayPtr, dbArraySize * sizeof(t_db));
					}

					if(!dbArrayPtr)
					{
						printf("Memory alloc/realloc error! Press any key to back main menu");
						printBackMsg();
						break;
					}

					ptr = dbArrayPtr + dbArraySize - 1;
					memset(ptr, sizeof(t_db), 0);
					printf("+-> Name (%d)\t\t: ", sizeof(ptr -> name)); scanf("%s",ptr -> name);
					printf("+-> Address (%d)\t: ", sizeof(ptr -> address)); scanf("%s",ptr -> address);
					printf("+-> Phone num (%d)\t: ", sizeof(ptr -> phone)); scanf("%s",ptr -> phone);
					printf("-------------------------------------\n");
					printf("Success! Add another one? \n(Yes : Enter / Any key : No)");
					dataChanged = 1;
						keyCode = keyPoller();
						if(keyCode != KEY_CODE_ENTER)
							break;

					}

					menuDraw();
			break;
			case KEY_CODE_5:
				if(!dbArrayPtr)
				{
					clearLine();
					printf("DB empty, nothing to edit\r");
					break;
				}
				while(1)
				{
					printDbTable();
					clearLine();
					printf("+----------[Edit record]-------------\n|\n");
					printf("+->Input inex : ");
					scanf("%d",&i);
					if(i < 0 || i >= dbArraySize)
					{
						printf("Fail! Index not exists, try again?\n(Yes : Enter / Any key : No)");
						keyCode = keyPoller();
						if(keyCode != KEY_CODE_ENTER)
							break;
						continue;
					}
					
					ptr = dbArrayPtr + i;
					memset(ptr, sizeof(t_db), 0);
					printf("+-> Org. name (%d)\t: ", sizeof(ptr -> name)); scanf("%s",ptr -> name);
					printf("+-> Address (%d)\t: ", sizeof(ptr -> address)); scanf("%s",ptr -> address);
					printf("+-> Phone num (%d)\t: ", sizeof(ptr -> phone)); scanf("%s",ptr -> phone);
					printf("-------------------------------------\n");
					printf("Success! Edit another one? \n(Yes : Enter / Any key : No)");
					dataChanged = 1;
						keyCode = keyPoller();
						if(keyCode != KEY_CODE_ENTER)
							break;

					}

				menuDraw();
			break;
			case KEY_CODE_6: 
				if(!dbArrayPtr)
				{
					clearLine();
					printf("DB empty, nothing to remove\r");
					break;
				}

				while(1)
				{
					printDbTable();
					clearLine();
					printf("+----------[Remove record]-----------\n|\n");
					printf("+->Input inex : ");
					scanf("%d",&i);
					if(i < 0 || i >= dbArraySize)
					{
						printf("Fail! Index not exists, try again?\n(Yes : Enter / Any key : No)");
						keyCode = keyPoller();
						if(keyCode != KEY_CODE_ENTER)
							break;
						continue;
					}
					if(dbArraySize > 1)
					{
						for(;i < dbArraySize - 1; i++)
						{
							ptr = dbArrayPtr + i;
							memcpy(ptr, (ptr+1), sizeof(t_db));
						}	
						dbArraySize --;
						dbArrayPtr = (t_db*)realloc(dbArrayPtr, dbArraySize * sizeof(t_db));
					}
					else
					{
						free(dbArrayPtr);
						dbArraySize = 0;
					}
					printf("Success! Remove another one? \n(Yes : Enter / Any key : No)");
					dataChanged = 1;
					keyCode = keyPoller();
					if(keyCode != KEY_CODE_ENTER)
						break;

				}
				menuDraw();
			break;
			case KEY_CODE_7: 
				if(!dbArraySize)
				{
					clearLine();
					printf("DB empty, nothing to write\r");
					getch();
					break;
				}
				if(!strlen(strBuf))
				{
					printf("Input file name : ");
					scanf("%s",strBuf);
				}
				if(err = fopen_s(&fd, strBuf, "wb"))
				{
					printf("\rCan`t write file (%s), error(%d)\r", strBuf,err);
					break;
				}
				printf("Writing file [name=%s size=%d bytes]\nSuccessfuly witten %d/%d records",strBuf, dbArraySize*sizeof(t_db),
				fwrite(dbArrayPtr, sizeof(t_db), dbArraySize , fd), dbArraySize);
				dataChanged = 0;
				fclose(fd);
				printBackMsg();
			break;
			case KEY_CODE_8: 
				if(!dbArraySize)
				{
					clearLine();
					printf("DB empty, nothing to write\r");
					getch();
					break;
				}
				printf("Input file name : ");
				scanf("%s",strBuf);
				if(err = fopen_s(&fd, strBuf, "wb"))
				{
					printf("\rCan`t write file (%s), error(%d)\r", strBuf,err);
					break;
				}
				printf("Writing file [name=%s size=%d bytes]\nSuccessfuly witten %d/%d records",strBuf, dbArraySize*sizeof(t_db),fwrite(dbArrayPtr, sizeof(t_db), dbArraySize , fd), dbArraySize);
				dataChanged = 0;
				fclose(fd);
				printBackMsg();
			break;
			case KEY_CODE_9: 
				printf("AppName    : HP Elitebook\n");
				printf("\nTeam: \nBurkovski D. A.\nKovalchuk D. A.\nLevus N. O.\nKochura O. Y.\nShabanin I.\n\n");
				printf("Other      : \ndreamtemmail@gmail.com\n");
				printBackMsg();
			break;
			case KEY_CODE_ESC:
				if(!confirmDataLost())
				{
					menuDraw();
					break;
					
				}
				if(dbArrayPtr)
					free(dbArrayPtr);
				//free(S);
				return 0;
			break;
			default:
				clearLine();
				printf("No such option (%c:%i)  \r", keyCode,keyCode);
				//menuDraw();
		}
	}

}
