?/*****************************************************************************************************
9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u ?vorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vra?a
pokaziva? na korijen stabla.
b) Napisati funkciju replace koja ?e svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat ?e se u stablo na
slici Slika 2.
c) Prepraviti program na na?in da umjesto predefiniranog cjelobrojnog polja korištenjem
funkcije rand() generira slu?ajne brojeve u rasponu <10, 90>. Tako?er, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
dijela zadatka.
******************************************************************************************************/





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

struct Tree;
typedef struct Tree* Position;

typedef struct Tree {
	int El;
	Position L;
	Position R;
}tree;

Position CreateElement(int element);
Position Insert(Position current, Position new);
int Replace(Position current);
int File(Position head);
int RandomNum(int min, int max);
int Inorder(Position current);
int Inorder_file(Position current, FILE* fp);

/*
u mainu stvaramo binarno stablo pretraživanja koriste?i brojeve iz prvog niza,
ispisujemo elemente stabla po inorder redu od najmanjeg do najve?eg i spremamo ih u datoteku,
mijenjamo svaki element u stablu s sumom njegovih prethodnika,
ponovo ispisujemo elemente stabla po inorder redu (sada promijenjene) i spremamo ih u datoteku,
korisnik unosi raspon brojeva izme?u 10 i 90,
generiramo 10 nasumi?nih brojeva unutar toga raspona i spremamo ih u drugi niz ovo array2,
stvaramo novo stablo koriste?i brojeve iz array2,
ispisujemo elemente novog stabla po inorder redu i spremamo ih u datoteku
*/
int main()
{

	Position first = NULL;
	Position root = NULL;
	Position q = NULL;

	int array[10] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };
	int array2[10] = { 0 };
	int min = 0;
	int max = 0;
	int i = 0;

	srand(time(NULL));



	for (i = 0; i < 10; i++)
	{
		q = CreateElement(array[i]);
		if (i == 0)
		{
			first = q;
		}
		else
		{
			Insert(first, q);
		}
	}

	printf("(Inorder) ispis prije sume:  \n");
	Inorder(first);

	File(first);


	Replace(first);

	puts("\n\n");
	printf("(Inorder) ispis poslije sume:  \n");

	Inorder(first);

	File(first);


	printf("\n\n Unesite raspon brojeva 10-90\n");
	printf("Donja granica: ");
	scanf(" %d", &min);
	if (min < 10) {
		printf("Premali broj, mora biti veci ili jednak od 10\n");
		scanf(" %d", &min);
	}
	printf("Gornja granica: ");
	scanf(" %d", &max);
	if (max > 90 || max < min) {
		printf("Broj je prevelik, mora biti manji ili jednak od 90\n");
		scanf(" %d", &min);
	}
	puts("\n");

	for (i = 0; i < 10; i++)
	{
		array2[i] = RandomNum(min, max);
	}

	for (i = 0; i < 10; i++)
	{
		q = CreateElement(array2[i]);
		if (i == 0)
		{
			first = q;
		}
		else
		{
			Insert(first, q);
		}
	}

	Inorder(first);
	File(first);
	puts("\n");

	return 0;
}

//ova funkcija stvara novi ?vor s odre?enom vrijednoš?u i vra?a pokaziva? na taj ?vor
Position CreateElement(int element)
{
	Position new = NULL; //deklariramo pokaziva? new tipa Position i postavlja ga na NULL
	new = (Position)malloc(sizeof(tree)); //dinami?ki dodjeljujemo memoriju za novi ?vor veli?ine strukture tree i pokaziva? new pokazuje na tu memoriju
	new->El = element; //postavljamo vrijednost ?vora na element, koji je proslije?en kao argument funkcije
	new->L = NULL; //postavlja lijevo dijete ?vora na NULL
	new->R = NULL; //postavlja desno dijete ?vora na NULL
	return new; //vra?a pokaziva? na novostvoreni ?vor
}

//funkcija insert koja dodaje element u stablo
Position Insert(Position current, Position new)
{
	if (current == NULL)
	{
		return new;
	}
	if ((current->El) <= (new->El))
	{
		current->R = Insert(current->R, new);
	}
	else if ((current->El) > (new->El))
	{
		current->L = Insert(current->L, new);
	}
	return current;
}

//obilazimo stablo i ispisiujemo elemenate od najmanjeg do najve?eg
int Inorder(Position current)
{
	if (current)
	{
		Inorder(current->L);
		printf("%d ", current->El);
		Inorder(current->R);
	}

	return 0;
}

//funkcija replace svaki element stabla mijenja sa sumom elemenata u njegovom lijevom i desnom podstablu
int Replace(Position current)
{
	int L1 = 0;
	int R1 = 0;
	int L2 = 0;
	int R2 = 0;

	if (NULL != current)
	{
		if (current->L != NULL)
		{
			L1 = current->L->El;
		}
		if (current->R != NULL)
		{
			R1 = current->R->El;
		}

		Replace(current->L);
		Replace(current->R);

		if (current->L != NULL)
		{
			L2 = current->L->El;
		}

		if (current->R != NULL)
		{
			R2 = current->R->El;
		}

		return current->El = L2 + R2 + L1 + R1;
	}

	return 0;
}

//funkcija ispisuje od najmanjeg u datoteku elemente stabla
int Inorder_file(Position current, FILE* fp)
{
	if (current == NULL)
	{
		return 2;
	}

	Inorder_file(current->L, fp);
	fprintf(fp, "%d\t", current->El);
	Inorder_file(current->R, fp);

	return 0;
}

//otvara datoteku i ispisuje elemente
int File(Position root)
{
	FILE* fp = NULL;

	fp = fopen("stablo.txt", "a");

	if (!fp) {
		printf("ERROR: Cannot open file!\n");
		return -1;
	}

	Inorder_file(root, fp);
	fprintf(fp, "\n\n");

	fclose(fp);

	return 0;
}

//funkcija generira i vra?a nasumi?ni broj unutar odre?enog raspona
int RandomNum(int min, int max)
{
	int n = 0;
	n = max - min + 1;
	int m = RAND_MAX - (RAND_MAX % n);
	int rand_num = rand();
	while (rand_num > m)
		rand_num = rand();
	return rand_num % n + min;
}