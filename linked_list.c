#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define NUMBER 5 // Кількість елементів списку

typedef struct Node //" Структура вузла, шо має наступні поля:
{
	int value;         // 1. Поле "Ціле число" - від 1 до 100;
	char sumbol;       // 2. Поле "Символ" - маленькі літери англ. алфавіту;
	struct Node *next; // 3. Поле "Вказівник" - містить вказівник на наступний елемент списку. Вказівник останнього = NULL;
} Node; // Ім'я структури

void menuDraw(void) // Функція друку меню
{
	printf("\n\n\n\n+--------[Menu]---------+\n");
	printf("|                       |\n");
	printf("+-----------------------+\n");
	printf("| #1 Print List         |\n");
	printf("+-----------------------+\n");
	printf("| #2 Sort List          |\n");
	printf("+-----------------------+\n");
	printf("| #3 Split By Value     |\n");
	printf("+-----------------------+\n");
	printf("| #4 Split By Sumbols   |\n");
	printf("+-----------------------+\n");
	printf("| #5 Add Node           |\n");
	printf("+-----------------------+\n");
	printf("| #6 Delele Node        |\n");
	printf("+-----------------------+\n");
	printf("\nPlease, enter your choise, or press \"0\" to exit:\n-> ");

	return;
}

void newNode(Node **head, Node **last) // Функція створення нового узла списку
{
	Node *current; // Вказівник на поточний елемент списку

	if ((current = (Node *) malloc(sizeof(Node))) == NULL) // Динамічно виділяємо пам'ять, одразу перевіряємо успішність виділення
	{
		printf("ERROR!\nNo free memory!\n");               // Якшо памʼять не виділена, программа видасть сповіщення про це
		exit(1);										   // Та аваріно завершить роботу
	}
	else  // Якщо процес виділння памʼяті пройшов успішно, ініціалізуємо поточний елемент:
	{
		current->next = NULL;                  // 1. Встановлємо вказівник на наступний елемент рівний NULL;
		current->value = 1 + rand() % 100;	   // 2. Рандомно генеруємо значення у діапазоні від 1 до 100;
		current->sumbol = 97 + rand() % 26;    // 3. Рандомно генеруємо букву англ. алфавіту за таблицею ASCII
	}

	if(!(*head))                        // Перевіряємо наявність голови списку, якщо відсутня:
	{
		*head = current;                // Поточному елементу присвоюємо статус голови
	}              
	else                                // Інакше:
	{
		(*last)->next = current;        // Вказівнику попереднього на наступний присвоюємо поточний
	}

	*last = current;                    // В будь-якому випадку, поточний - останній створений елемент списку

	return;
}

void printList(Node *head)  // Функція для друку спску
{
	int i = 0;

	printf("\n+---------+---------+-----------+\n");
	printf("| Element | Integer | Character |\n");                           // Друк шапки
	printf("+---------+---------+-----------+\n");

	while (head != NULL)   // Друкуємо стільки рядків, скільки елементів у списку
	{
		printf("| #%-7d| %-8d| %-10c|\n", i+1, head->value, head->sumbol);  // Заповюємо поля таблиці значеннями елементів списку
		printf("+---------+---------+-----------+\n");
		head = head->next;  // Пересуваємо вказівник на насупний елемент

		i++;
	}

	return;
}

Node *getLastNode(Node *head)  // Службова функція для пошуку і повернення останнього елемента спику
{
	Node *element = head;          // Декларація та ініціалізація елемента значенням першого   

	while (element->next != NULL)  // Перебираємо елементи списку, поки не знайдемо останній
	{
		element = element->next;   // Перехід до наступного елемента списку
	}

	return element;                // Повернення останнього елемента
}

void deleteList(Node *head)  // Функція видалення динамічно створеного списку
{
    Node *current, *tmp;  // Декларація вказівника на елемент, рівного NULL
    
    current = head->next;

    while (current != NULL)                 // Переглядаємо усі елементи списку, поки:
	{
		tmp = current;               // Надаємо тимчасовій змінній значення поточного елемента  
	
		head->next = current->next;  // Перекидаеємо вказівник на поточний на наступний за ним
		
		free(tmp);		             // Видаляємо поточний				

		current = head->next;        // Переходимо до наступного елемену
	}

	free(head);  // Після того, як всі елементи видалено - видаляємо голову

	return;
}

void ascendingSortList(Node *head)  // Фунцкція сортування за зростанням
{	
	int flag = 0, tmp;     // Декларація локальний робочих змінних функції
	Node *element = head;  // Декларація вказівника на елемент та ініціалізація вкащівником на перший елемент списку

	if (head->next != NULL)  // Якщо елементів у списку більше, ніж один - приступаємо до сортвання
	{
		while (flag < NUMBER)  // Вихід з циклу відбуваєтьсяб коли список відсотований 
		{
			if ((element->next)->value < element->value)  // Саме сортування - якщо наступний елемент більший за поточний:
			{
				tmp = (element->next)->value;             //
				(element->next)->value = element->value;  // Міняємо їх місцями за допомогою тимцасової змінної
				element->value = tmp;                     //

				flag = 0;              // За такої умови - список ще не відсортований повністю, обнуляємо змінну умови виходу з циклу
				tmp = 0;               // Обнуляємо тимчасову змінну              
			}
			else         // Якщо попередня умова не виконується:
				flag++;  // Збільшуємо змінну умови виходу з циклу 
	                     // Таким чином - якщо список відсортовано -> flag == NUMBER -> вихід з циклу
			element = element->next;  // Переходимо до наступного елемента
			
			if (element->next == NULL)  // Якщо поточний елемент - останній:
				element = head;         // Повертаємось до першого елемента. Для того, щоб зациклити прохід по списку
		}
	}

	printf("List was sorted successfully!\n");  // Друк на єкран повідомлення про успішну сортировку списку

	return;
}

void descendingSortList(Node *head)  // Функція сортування за спаданням
{	
	int flag = 0, tmp;     // Декларація локальний робочих змінних функції
	Node *element = head;  // Декларація вказівника на елемент та ініціалізація вкащівником на перший елемент списку

	if (head->next != NULL)  // Якщо елементів у списку більше, ніж один - приступаємо до сортвання
	{
		while (flag < NUMBER)  // Вихід з циклу відбуваєтьсяб коли список відсотований 
		{
			if ((element->next)->value > element->value)  // Саме сортування - якщо наступний елемент менший за поточний:
			{
				tmp = (element->next)->value;             //
				(element->next)->value = element->value;  // Міняємо їх місцями за допомогою тимцасової змінної
				element->value = tmp;                     //

				flag = 0;              // За такої умови - список ще не відсортований повністю, обнуляємо змінну умови виходу з циклу
				tmp = 0;               // Обнуляємо тимчасову змінну              
			}
			else         // Якщо попередня умова не виконується:
				flag++;  // Збільшуємо змінну умови виходу з циклу 
	                     // Таким чином - якщо список відсортовано -> flag == NUMBER -> вихід з циклу
			element = element->next;  // Переходимо до наступного елемента
			
			if (element->next == NULL)  // Якщо поточний елемент - останній:
				element = head;         // Повертаємось до першого елемента. Для того, щоб зациклити прохід по списку
		}
	}

	printf("List was sorted successfully!\n");  // Друк на єкран повідомлення про успішну сортировку списку

	return;
}

void deleteNode(Node *head)  // Функція видалення елемента списку
{
	char choise1;                            // Локальні службові змінні
	bool flag = true;                            //
	Node *previous = NULL, *current, *tmp;   // Локальні службові вказівники типу Node 

	current = head;  // Надаємо поточному елементу статусу першого

	while (getchar() != '\n');  // Очищення потоку вводу від зайвих символів
		
	printf("\nEnter the character of element, that you want to remove: ");  // Запрошення ввести букву елементів, які підлягають видаленню
	scanf("%c", &choise1);  // Збереження букви-маркера, елементи з котрою будуть видалені
	
	while (current != NULL)                 // Переглядаємо усі елементи списку, поки:
	{
		tmp = current;
		// надаємо тимчасовій змінній 
		// значення поточного елем.

		if (tmp->sumbol == choise1)  // Не знайдемо такий, що містить букву-маркер
			{
				if (tmp == head)  // Якщо такий елемент - голова списку
				{					
					free(tmp);  // Та видаляємо його
					                                             // Далі знаходимо значення нової голови списку:                                         
					if (head->next != NULL)                      // Якщо в списку є елементи окрім голови:
					{                                            
						head->value = (head->next)->value;    // 
						head->sumbol = (head->next)->sumbol;  //	Наступний, після голови елемент стає головою списку				
						head->next = (head->next)->next;      //						
					}
					else                                         // Інкаше:
					{
						printf("WARNING!\nList is empty!\n");    // Друк застереження про те шо список пустий	
						head->value = 0;                         // 
						head->sumbol = ' ';		                 //	Надання голові "пустих" значень		
						head->next = NULL;                       //
					}					
				}
				else if(tmp == getLastNode(tmp))    // Якщо елемент з буквою-маркером хвіст списку, то
				{
					previous->next = NULL;          // Встановлюємо вказівник попереднього на наступний елемент на NULL 
					
					free(tmp);				        // Видаляємо поточний
				}				
				else  // Інакше елемент з буквою-маркером не голова і не хвіст:
				{	
					previous->next = current->next; // Перекидаеємо вказівник на поточний на наступний за ним
					
					free(tmp);		                // Видаляємо поточний				
				}

				flag = false;  // Службовий маркер, який слугує для превірки входу у тіло структури вибору. 
			}	           // За відсутності такого - друк повідомлення відсутності шукомих елементів
			
		previous = current;           // Надання попередньому елементу значення поточного, а

		current = current->next;      // поточному - наступного
	}

	if (flag)                                       // Якщо входу у попередній цикл не було 
		printf("\nNo such elements, try again!\n"); // друк повідомлення.
	else
		printf("\nDeleted successfully!\n");        // Інакше - друк повідомлення про успішне видалення усіх елементів з відповдною буквою-маркером

	return;
}

void addNode(Node *head)  // Функція додання нового елеманта до списку
{
	Node *newElement = ((Node *) malloc(sizeof(Node *)));  // Видіолення динамично памʼяті для нього
	Node *lastElement = getLastNode(head);                 // Останній елемент. Встан. значення за допомогою попер. фукції
	char newSumbol;                                        // 
	int newValue;                                          // Службові змінні
	
	lastElement->next = newElement;  // Встановлюємо вказівник останнього на наступний на елемент, що додаємо

	printf("\nEnter the value of the element you want to add\nValue = ");  // Запрошення ввести значення поля "Ціле число" нового елемента 
	while (getchar() != '\n');                                             // "Фільтр" для очищення стандартного потоку вводу
	scanf("%d", &newValue);                                                // збереження значення
    newElement->value = newValue;                                          // Ініціалізація поля "Ціле число" нового елемента

	printf("Character = ");          // Запрошення ввести значення поля "Символ" нового елемента       
	while (getchar() != '\n');       // "Фільтр" для очищення стандартного потоку вводу
	scanf("%c", &newSumbol);         // Збереження значення
    newElement->sumbol = newSumbol;  // Ініціалізація поля "Символ" нового елемента

    newElement->next = NULL;         // Встановлення вказівника нового елемента на наступни на NULL

    printf("Added successfully\n");  // Повідомлення про успішне доповнення списку новим елементом

	return;
}

void splitByValue(Node *head, Node *newHead1, Node *newHead2)  // Функція розбиття списку на парні та непарні числа
{
	Node *element = head;   // Вказівник на елемент - встановлюємо на голову
	Node *current1 = NULL;;         // Вказівник на поточний для парних
	Node *current2 = NULL;;         // і для не парних чисел
	Node *last1 = NULL;;            // Вкащівник на попередній для парних
	Node *last2 = NULL;;            // і для не парних чисел

	if (head->next != NULL)	 //Перевіряємо, чи є елементи для розбиття
	{
		while (element != NULL)  // Перебираємо у циклі всі елементи списку
		{	
		
			if((element->value) % 2 == 0)  // Якщо елемент парний:
			{	
				if ((current1 = (Node *) malloc(sizeof(Node))) == NULL)  // Виділ. динам. памʼять, одразу перев. успішність цього процесу
				{
					printf("ERROR!\nNo free memory!\n");  // Якщо памʼять не була виділена - видаемо повідомлення про це
					exit(1);                              // та аварійно завершуємо програму
				}
				else                                     // Інакше           
				{
					current1->next = NULL;               //  
					current1->value = element->value;    // Записуємо значення знайеного елемента в поточний
					current1->sumbol = element->sumbol;  //
				}

				if(newHead1 == NULL)         // Перевіряємо чи є у списку голова, якщо ні:
				{
					newHead1 = current1;     // Поточний елемент голова 
				}
				else                         // Інакше: 
				{
					last1->next = current1;  // Встановлюємо вказівник попер. елемента на наступний на поточний
				}

				last1 = current1;            // Після відпрацюівання даного блоку поточний елемент робимо попереднім
			}		
			else  // Аналогічні дії виконуються, якщо число не є парним - непарне
			{	
				if ((current2 = (Node *) malloc(sizeof(Node))) == NULL)
				{
					printf("ERROR!\nNo free memory!\n");
					exit(1);
				}
				else
				{
					current2->next = NULL;
					current2->value = element->value;
					current2->sumbol = element->sumbol;
				}

				if(newHead2 == NULL)
				{
					newHead2 = current2;
				}
				else
				{
					last2->next = current2;
				}

				last2 = current2;
			}
			
			element = element->next;
		}
		
		printf("\n\nPaired numbers:");  // Друк парних чисел
		printList(newHead1);            //
		printf("\n");
		printf("Odd numbers:");         // Друк непарних чисел
		printList(newHead2);            //

		// deleteList(newHead1);  // Видалення динамічно створених списків
		// deleteList(newHead2);  //		
	}
	else  // Якщо список не має елементів для розбиття
		printf("\nNo elements to split!\n");  // друкуємо повідомлення про це

	return;
}

void splitBySumbol(Node *head, Node *newHead1, Node *newHead2)  // Функція розбиття списку на голосні та приголосні літери
{
	Node *element = head;   // Вказівник на елемент - встановлюємо на голову	
	Node *current1;         // Вказівник на поточний для голосних
	Node *current2;         // і для приголосних літер
	Node *last1;            // Вкащівник на попередній для голосних
	Node *last2;            // і для приголосних літер

	if (head->next != NULL)	 //Перевіряємо, чи є елементи для розбиття
	{
		while (element != NULL)  // Перебираємо у циклі всі елементи списку
		{	
		
			if((element->sumbol) == 'a' || (element->sumbol) == 'e' || (element->sumbol) == 'i' || (element->sumbol) == 'o' || (element->sumbol) == 'u' || (element->sumbol) == 'y')  // Якщо елемент містить голосну літеру, то
			{	
				if ((current1 = (Node *) malloc(sizeof(Node))) == NULL)  // Виділ. динам. памʼять, одразу перев. успішність цього процесу
				{
					printf("ERROR!\nNo free memory!\n");  // Якщо памʼять не була виділена - видаемо повідомлення про це
					exit(1);                              // та аварійно завершуємо програму
				}
				else                                     // Інакше
				{
					current1->next = NULL;               //  
					current1->value = element->value;    // Записуємо значення знайеного елемента в поточний
					current1->sumbol = element->sumbol;  //
				}

				if(newHead1 == NULL)         // Перевіряємо чи є у списку голова, якщо ні:
				{
					newHead1 = current1;     // Поточний елемент голова 
				}
				else                         // Інакше: 
				{
					last1->next = current1;  // Встановлюємо вказівник попер. елемента на наступний на поточний
				}

				last1 = current1;            // Після відпрацюівання даного блоку поточний елемент робимо попереднім
			}		
			else  // Аналогічні дії виконуються, якщо літера не є голосною - приголосна
			{	
				if ((current2 = (Node *) malloc(sizeof(Node))) == NULL)
				{
					printf("ERRORR!\nNo free memory!\n");
					exit(1);
				}
				else
				{
					current2->next = NULL;
					current2->value = element->value;
					current2->sumbol = element->sumbol;
				}

				if(newHead2 == NULL)
				{
					newHead2 = current2;
				}
				else
				{
					last2->next = current2;
				}

				last2 = current2;
			}
			
			element = element->next;
		}
		
		printf("\n\nVowels characters:");  // Друк голосних
		printList(newHead1);               // 
		printf("\n");
		printf("Consonants characters:");  // Друк приголосних
		printList(newHead2);               //
	}
	else  // Якщо список не має елементів для розбиття
		printf("\nNo elements to split!\n");  // друкуємо повідомлення про це

	return;
}

int main(void)  
{
	int choise;   // Службова змінні	
	Node *head = NULL;      // Вказівник на голову списку
	Node *newHead1 = NULL;  // Нова голова - для парних чисел або голосних літер
	Node *newHead2 = NULL;  // Нова голова - для непарних чисел або приголосних літер
	Node *last = NULL;      // Вказівник на останній елемент

	srand(time(NULL));  // Ініціалізація сем'я для рандому

	for (int i = 0; i < NUMBER; i++)  // Цикл створення необхідної кількості вузлів списку
	{
		newNode(&head, &last);  // Виклик функції нового узла списку
	}

	do  // Цикл з післяумовою
	{
		menuDraw(); // Виклик функції друку меню
		
		while (scanf("%d", &choise) != 1)   // Службовий цикл для уникнення помилок вводу
		{
			while (getchar() != '\n');  // Очищення стандартного потоку вводу					
			
			printf("ERROR INPUT! Try again...\n");  // Друк повідомлення про помилку

			printf("\nPlease, enter your choise, or press any key to exit:\n-> ");  // Запрошення ввести корректні дані				
		}
		
		switch (choise)  // Структура множинного вибору - для переходу між пунктами меню
		{
			case 1:         
			printList(head);  // Виклик функції друку списку
			break;

			case 2:
			while(1)  // Нескінченний цикл для вибору типу сортування: за спаданням або за зростанням
			{
				printf("\nPress <1> for ascending sort or <2> to descending sort: ");
				
				while (scanf("%d", &choise) != 1)  // Службовий цикл для уникнення помилок вводу
				{
					while (getchar() != '\n');     // Очищення стандартного потоку вводу				
					
					printf("ERROR INPUT! Try again...\n");  // Друк повідомлення про помилку
				
					printf("\nPress <1> for ascending sort or <2> to descending sort: ");  // Запрошення зробити вибір 
				}

				if (choise == 1)              // Якщо вибір "1", то:
				{
					ascendingSortList(head);  // Викликаємо функцію сортування за спаданням
					break;			          // Виходимо з нескінченного циклу
				}
				else if (choise == 2)         // Якщо вибір "2", то:
				{
					descendingSortList(head); // Викликаємо функцію сортування за зростанням
					break;			          // Виходимо з нескінченного циклу				
				}	
				else                          // Інакше друкуємо повідомлення про помилку вводу
					printf("\nERROR INPUT!\nPlease, try again...\n");

				printf("\n");	
			}
			break;

			case 3:
			if (head->next != NULL)
				splitByValue(head, newHead1, newHead2);   // Виклик функції розбиття на парні та непрані
			else
				printf("\nERROR!\nNo elements to split\n");
			break;

			case 4:
			if (head->next != NULL)
				splitBySumbol(head, newHead1, newHead2);  // Виклик функції розабиття на голосні та приголосні
			else
				printf("\nERROR!\nNo elements to split\n");
			break;

			case 5:
			addNode(head);     // Виклик функції Додання нового вузла
			break;

			case 6:
			deleteNode(head);  // Виклик функції видалення вузла
			break;
		}
	}
	while (choise > 0 && choise < 7);  // Умова продовження циклу
			
	deleteList(head);  // Виклик функції видалення динамічно створеного списку, якщо такого не відбулось в меню
	
	printf("\nGood Bye!\n");  // Друк прошального повідомлення					

	return 0;
}