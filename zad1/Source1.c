?  /*. Napisati program koji prvo procita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamicki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i ucitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrzi ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAME 128
#define MAXRED 1024
#define MAXBOD 50

typedef struct {
	char ime[MAXNAME];
	char prezime[MAXNAME];
	double bodovi;
}Student;

int brojacRedova(char imeDatoteke[MAXNAME]) {
	int brojac = 0;
	FILE* fp = NULL;

	fp = fopen(imeDatoteke, "r");
	if (fp == NULL) {
		printf("\nGreska u otvaranju datoteke!");
	}
	else {
		printf("\nUspjesno otvaranje datoteke!");
	}

	char buffer[MAXRED] = { 0 };

	while (!feof(fp)) {
		fgets(buffer, MAXRED, fp);
		if (strcmp("\n", buffer) != 0) {
			brojac++
		}
	}

	fclose(fp);
	return brojac;
}

void citanjeStud(Student* stud, int brStud, char imeDatoteke[MAXNAME]) {
	FILE* fp = NULL;
	int i = 0;

	fp = fopen(imeDatoteke, "r");

	if (fp == NULL) {
		printf("\nGreska u otvaranju datoteke!");
	}
	else {
		printf("\nUspjesno otvaranje datoteke!");
	}

	for (i = 0; i < brStud; i++) {
		fscanf(fp, "%s %s %d\n", (stud + i)->ime, (stud + i)->prezime, &((stud + i)->bodovi));
	}

	fclose(fp);
	return brojac;
}

void ispisStud(Student* stud, int brStud) {
	double prosjek = 0;
	int i = 0;

	for (i = 0; i < brStud; i++) {
		prosjek = (double)(stud + 1)->bodovi / MAXBOD;
		printf("\nStudent %s %s imao je %d bodova, odnosno %.2lf posto (relativni bodovi).", (stud + i)->ime, (stud + i)->prezime, (stud + i)->bodovi, prosjek * 100);
	}
}

int main() {
	char imeDatoteke[MAXNAME] = { 0 };

	FILE* test = NULL;

	while (test == NULL) {
		printf("\nMolimo upisite ime datoteke sa listom studenata:\n");
		scanf("%s", imeDatoteke);
		test = fopen(imeDatoteke, "r");

		if (test == NULL) {
			printf("\nGreska u otvaranju datoteke!");
		}
		else {
			printf("\nUspjesno otvaranje datoteke!");
		}
	}

	int brojStudenata = 0;
	brojStudenata = brojacRedova(imeDatoteke);

	Student* stud = NULL;
	stud = (Student*)malloc(brojStudenata * sizeof(Student));

	citanjeStud(stud, brojStudenata, imeDatoteke);

	ispisStud(stud, brojStudenata);

	return 0;
}