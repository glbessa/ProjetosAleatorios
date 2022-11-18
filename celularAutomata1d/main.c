#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define LENGTH 39

#define WHITE_TILE "\x1b[97m\x1b[107m"
#define RESET_TILE "\x1b[0m"
#define INVISIBLE_CURSOR "\x1b[?25l"

#define SLEEP_TIME 150000

void randomInitialize(int *cells, int length);
int *generate(int *cells, int length);
int rules(int a, int b, int c);
void printAutomata(int *cells, int length, char * msg);
int generateRandomInt(int min, int max);

int main(char *args[])
{
	srand(time(NULL));
	int *cells = (int *) malloc(sizeof(int) * LENGTH);
	int *newCells;

	// rule 90
	//cells[19] = 1;
	// rule 184, 122
	randomInitialize(cells, LENGTH);
	// rule 110
	//cells[LENGTH - 1] = 1;

	printf("%s", INVISIBLE_CURSOR);

	printAutomata(cells, LENGTH, "");
	usleep(SLEEP_TIME);
	while (1)
	{
		newCells = generate(cells, LENGTH);
		printAutomata(newCells, LENGTH, "");
		cells = newCells;
		usleep(SLEEP_TIME);
	}
	
	return 0;
}

void randomInitialize(int *cells, int length)
{
	for(int i = 0; i < length; i++)
	{
		cells[i] = generateRandomInt(0, 1);
	}
}

int *generate(int *cells, int length)
{
	int *newCells = (int *) malloc(sizeof(int) * length);
	for (int i = 1; i < length - 1; i++)
	{
		newCells[i] = rules(cells[i-1], cells[i], cells[i+1]);
	}
	return newCells;
}

int rules(int a, int b, int c)
{
	// 000 001 010 011 100 101 110 111
	// custom rule
	//int stateRules[] = {0, 1, 0, 1, 1, 0, 1, 0};
	// rule 90
	//int stateRules[] = {0, 1, 0, 1, 1, 0, 1, 0};
	// rule 184
	//int stateRules[] = {0, 0, 0, 1, 1, 1, 0, 1};
	// rule 110
	//int stateRules[] = {0, 1, 1, 1, 0, 1, 1, 0};
	// rule 122
	int stateRules[] = {0, 1, 0, 1, 1, 1, 1, 0};

	char str[4];
	sprintf(str, "%i%i%i", a, b, c);

	int cod = strtol(str, NULL, 2);
	int newState = stateRules[cod];

	return newState;
}

void printAutomata(int *cells, int length, char * msg)
{
	printf(msg);
	for (int i = 0; i < length; i++)
	{
		if (cells[i] == 0)
			printf("  ");
		else
			printf("%s %s ", WHITE_TILE, RESET_TILE);
	}
	printf("\n");
}

int generateRandomInt(int min, int max)
{
	return (rand() % (max+1)) + min;
}