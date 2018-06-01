#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER 20  // Кількість елментів дерева
 
typedef struct Node  // Структура дерева, що має наступні поля:
{
	int value;  // Поле ціле число
	struct Node *left;  // Вкащівник на лівого нащадка
	struct Node *right;  // Вказівник на правного нащадка 
	struct Node *parent;  // Вкащівник на батьківсткий вузел
} Node;  // Імʼя структури

Node *newNode(int value, Node *parent)  // Функція генерації нового вузла, отримує аргумети ціле число та вказівник на пращура
{
	Node *element;  // Декларація вказівника на елемент, що буде генеруватись

	if ((element = (Node *) malloc(sizeof(Node))) == NULL)  // Динамічно виділяємо памʼять під новий елемент, перевіряємо успішність виділення
	{
		printf("ERROR!\nNo free memory!\n");  // Якщо памʼять не була виділена, друкуємо повідомлення з відповідним текстом
		exit(1);  // та аварійно завершуємо аиконання процесу
	}
											// Якщо памʼять була виділена: 
	element->left = element->right = NULL;  // Встановлюємо вказівники на лівого і правого нащадків рівні NULL
	element->value = value;					// Поле цілого числа ініціалізуємо отриманим аргументом
	element->parent = parent;     			// Пращуром вузла є переданий функції вузел

	return element; 						// Та повертаємо згенерований елемент у місце виклику функції 
}

void createTree(int value, Node **head)	 // Функція створення дерева
{
	Node *current;  // Вказівник на поточний елемент 

	if (*head == NULL)  // Якщо у дерева немає голови, перший створений вузел стане головою 
	{
		*head = newNode(value, NULL);  // Вкиликаємо фукцію створення нового узла, передаємо ціле число та NULL, бо у голови пращура немає
		
		return;  // Поевертаґмось у місце виклику
	}
						// Якшо голова вже є: 
	current = *head;	// Шукаємо місце для вставки нового елемента, починаючи з голови дерева

	while (1)     // У нескінченному циклі перебираємо гілки дерева, поки не знайдемо місце для вставки нового вузла
	{			  // Для цього порівнюємо передане ф-ції число і поле "ціле число" поточного елемента
		if (current->value < value)  // Якщо передане ф-ції число більше поля "ціле число" поточного елемента, переходимо до правої гілки
		{
			if (current->right)  // Якщо вказівник поточного на правий не "пустий"
			{
				current = current->right;  // Вважаємо правий, за поточний
				continue;                  // Та переходимо до наступної ітерації циклу 
			}
			else    // Якшо вказівник направо поточного "пустий", місце для вставки поточного знайдено
			{
				current->right = newNode(value, current);    // Вставляємо на це місце новий елемент, викликаючи фукцію нового вузла. Передаємо ф-ції ціле число та поточний елемент, який буде пращуром для нового
				return;  // Та повертаємось у місце виклику ф-ції
			}
		}
		else if (current->value > value)  // Якщо передане ф-ції число меньше поля "ціле число" поточного елемента, переходимо до лівої гілки
		{								  // Аналогічно виконуєио пошук місця для вставки нового елемета
			if (current->left)
			{
				current = current->left;
				continue;
			}
			else
			{
				current->left = newNode(value, current);
				return;
			}
		}
		else
			return;
	}
}

void deleteTree(Node **current)  // Функція видалення дерева
{
    if (*current)  // Якщо поточний елемент існує
    {
        deleteTree(&((*current)->left));  // Оброблюємо праве піддерево, використовуючи рекурсивний виклик функції, передаємо вказівник на лівий елемент
        deleteTree(&((*current)->right));  // Оброблюємо ліве піддерево, використовуючи рекурсивний виклик функції, передаємо вказівник на правий елемент
        free(*current);  // Та видлаяємо отриманий у ході рекрсії поточний елемент
    }

    return;
}

int heightOfTree(Node *current)  // Ф-ція пошуку висоти дерева
{
	int left, right;  // Декларація цілочисленних змінних для визначення максимальної висоти лівого та правого піддерев 

	if (current->left)  // Якщо елемент зліва від поточного існує
		left = heightOfTree(current->left);  // змінну для визначення висоти лівого піддерева ініціалізуємо значенням, що поверне рекрсивний виклик ф-ції. Аргументом передаємо вказівник на лівий від поточного
	else            // Інакше
		left = -1;  // Надаємо змінній знацення -1

	if (current->right)  // Аналогічно оброблюємо праве піддерево
		right = heightOfTree(current->right);
	else
		right = -1;

	int max = left > right ? left : right;  // Встановлюємо за допомогою тернарного оператора яка із змінних, отриманих при рекрсивному обході дерева більша

	return max + 1;  // Повертаємо отримане значення. Не забуваємо додати 1
}

int widthOfTree(Node *current, int level)  // Службова ф-ція для визначення ширини дерева. Отримує як аргуманти вказівник на поточний та ціле число, яке показує глибину вкладенності елемента
{
	if (!current)  // Якшо переданого елемента не існує, повертаємо 0
		return 0;

	if (level == 1)  // Якщо вкладенність елемента 1, поверт. 1
		return 1;
	else if (level > 1)  // Інакше
	return widthOfTree(current->left, level-1) +  widthOfTree(current->right, level-1);  // Повертаємо суму результатів рекрсивних обходів правих і лівих піддерев
	
	widthOfTree(current->right, level-1);  // Рекурсивний виклик
}

int maxWightOfTree(Node *current)  // Головна функція обчислення ширини дерева 
{
	int maxWidth = 0, width, height = heightOfTree(current);  // Службові змінні
	
	for(int i = 1; i < height; i++)  // Цикл для знаходження максимальної кількості не порожніх  листків, що знах. на одній висоті. Кількість ітерацій рівна висоті дерева - 1
	{
		width = widthOfTree(current, i);  // Ширина поточної висоти елемнтів 
		
		if(width > maxWidth)   // Якщо отримана ширина поточної висоти більша за максимально визначену
			maxWidth = width;  // Вважаємо її максимальною
	}

	return maxWidth;  // Повертаєио отриманий у резульаті проходів максимум ширини
}

void printTree(Node *current, int level)  // Функція друку дерева, що вик. рекрсивний виклик. Аргументи - вказівник на поточний та рівень вкладенності елемента
{
    if(current)  // Якшо поточний елемент існує
    {
        printTree(current->right, level + 1); // Використовуючи рекусивний виклик, проходимо по правому піддереву
        
        for (int i = 0; i< level; i++)  // Цикл для визначення відступу та його друку
        	printf("   ");  

        printf("%d\n", current->value);  // Друкуємо поле "ціле число" поточного елемента

        printTree(current->left, level + 1);  // Обходимо ліве піддерево
    }
}

int main(void)
{
	Node *head = NULL;     // Вказівник на голову дерева
	int value, level = 0, sum = 0;  // Службові змінні

	srand(time(NULL));  // Генерація семені рандомі
	
	printf("\nIntegers:");

	for (int i = 0; i < NUMBER; i++)  // Генерація та друк чисел
	{	
		value = 1 + rand() % 100;

		printf(" %d", value);

		if (i < NUMBER - 1)
			printf(",");
		else
			printf(";\n\n");


		createTree(value, &head);  // Створення дерева

		sum += value;
	}

	printf("Tree:\n");

	for(int i = 0; i < heightOfTree(head); i++)  // Друк обмежувальних ліній
		printf("====");
	printf("\n");
 
	printTree(head, level);  // Друк дерева

	for(int i = 0; i < heightOfTree(head); i++)  // Друк обмежувальних ліній
		printf("====");
	
	printf("\n\nSum tree's elements: %d\n", sum); // Друк суми елементів дерева
	
	printf("\nHeight: %d;\n", heightOfTree(head));  // Визначення висоти дерева

	printf("\nWidth: %d.\n\n", maxWightOfTree(head));  // Визначення ширини дерева

	deleteTree(&head);  // Видалення дерева
  
	return 0;
}