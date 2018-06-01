#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER 10 // Кількість студентів
#define NAMESIZE 30 // Максимальний розмір ім'я
#define SCORESNUMBER 20 // Кількість оцінок

struct STUDENT // Структура, згідно завдання
{
	char name[NAMESIZE]; // Ім'я
	int group; // Номер групи
	int scores[SCORESNUMBER]; // Масив оцінок
} statement[NUMBER], changedStatement[NUMBER]; // Масиви структур

typedef struct STUDENT STUDENT;  // Створюємо псевдонім структури

void editStatement(STUDENT *current)  // Функція створення відомості - масиву 10 структур
{
	for (int i = 0; i < NUMBER; i++)  // У циклі перебираємо всіх студентів
	{
		printf("\nEnter name of student: ");  // Запрошуємо ввести ім'я з клавіатури
		scanf("%s", (current + i)->name);  // Зберігаємо
		while (getchar() != '\n');  // Очищуємо поток вводу від зайвих символів

		printf("Enter group number: ");  // Аналогічно з номером групи
		scanf("%d", &(current + i)->group);  
		while (getchar() != '\n');

		printf("Scores:");  
			
		int success = 2 + rand() % 3;  // Генерація коефіціента успішності студента

		for (int j = 0; j < SCORESNUMBER; j++)  // У циклі
		{
			(current + i)->scores[j] = success + rand() % 2;  // Генеруємо оцінки відповідного студента

			if (j < SCORESNUMBER - 1)
				printf(" %d", (current + i)->scores[j]);  // Та друкуємо їх
			else
				printf(" %d;\n", (current + i)->scores[j]);
		}
	}

	return;	
}

void writeStatement(STUDENT *current)  // Функція запису отриманого масиву структур у файл
{
	FILE *file;  // Декларація вказівника типу FILE
	
	if ((file = fopen("statement.txt", "w")) == NULL)  // Відкриваємо файл для запису, перевіряємо успішність операції
	{
		printf("ERROR!\n");  // У випадку безуспішного відкриття файлу, друкуємо повідомленя про помилку 
		exit(1);             // та аварійно завершуежмо процес 
	}

	for (int i = 0; i < NUMBER; i++)  // Інакше
	{
		fprintf(file, "%s %d ", (current + i)->name, (current + i)->group); // Записуємо імʼя та номер групи у файл
		for(int j = 0; j < SCORESNUMBER; j++)  // За допомогою циклу 
			fprintf(file, "%d ", (current + i)->scores[j]);  // Записуємо масив оцінок

		fprintf(file, "\n");
	}

	fclose(file);  // Закриваємо файл

	return;
}

void readStatement(STUDENT *current)  // Функція для зчитування записаного у файл масиву структур у новий масив
{
	FILE *file;

	if ((file = fopen("statement.txt", "r")) == NULL)  // Аналогічно до попередньої фунуції
	{
		printf("ERROR!\n");
		exit(1);
	}

	for (int i = 0; i < NUMBER; i++)  //  За допомогою циклу
	{
		fscanf(file, "%s %d ", (current + i)->name, &(current + i)->group);  // Зчитуємо записаний у файл масив структур у новий 
		for (int j = 0; j < SCORESNUMBER; j++)
			fscanf(file, "%d ", &(current + i)->scores[j]);
	}

	fclose(file);  // Закриваємо файл

	return;
}

void printSuccessfulStudents(STUDENT *current)  // Функція для друку студентів, бал котрих вищий за 4
{
	float total = 0, overallRating = 0;  // Службові змінні

	for (int j = 0; j < SCORESNUMBER; j++)
		total += current->scores[j];  // Підрахунок сумми оцінок певного студента

	overallRating = total / SCORESNUMBER;  // обрахунок середнього арифметичного


	if (overallRating >= 4)  // За умови, якщо середній бал більший за 4
	{
		printf("\n-> Name: %s;\n-> Group #%d;\n-> Scores:", current->name, current->group);  // Друкуємо імʼя, номер групи, оцінки та середній бал
		for (int i = 0; i < SCORESNUMBER; i++)
		{
			if (i < SCORESNUMBER - 1)
				printf(" %d,", current->scores[i]);
			else
				printf(" %d;\n", current->scores[i]);
		}	

		printf("-> Average score: %.2f;\n\n", overallRating);
	}

	return;
}

int main(void)
{
	
	srand(time(NULL));

	editStatement(statement);         // 

	writeStatement(statement);        // Виклик функцій

	readStatement(changedStatement);  // 

	printf("\n\n[*] Students, average score more than 4 [*]\n");
	for (int i = 0; i < NUMBER; i++)  // У циклі 
		printSuccessfulStudents((changedStatement + i));  // Викликаємо функцію друку студентів з сер. балом вищим за 4

	return 0;
}