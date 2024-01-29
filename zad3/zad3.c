#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_MAX(50)
#define ALLOC_FAIL(-1)
#define FILE_FAIL(-1)
#define SUCCESS(0)
#define NOT_FOUND(0)
#define EXIT_FAIL(-1)
#define BUFFER_MAX(400)

typedef struct Person* Position;

struct Person {
    char name[NAME_MAX];
    char surname[NAME_MAX];
    int brith_year;
    Position next;
};

typedef struct Person Person;


Position AddHead() {
    Position head = NULL;
    head = (Position)malloc(sizeof(Person));
    head->next = NULL;
    return head;
}

int AddToTheBeginning(Position Head) {       //DODAJ NA POCETAK

    Position p = NULL;
    p = Head;

    Position q = NULL;

    q = (Position)malloc(sizeof(Person));

    if (q == NULL) {
        printf("\nNeuspjesno dodavanje novog elementa liste!");
        return ALLOC_FAIL;
    }
    else {
        printf("\nDodan novi element liste!");
    }

    q->next = p->next;
    p->next = q;

    printf("\nUnesite ime osobe: ");
    scanf(" %s", q->name);
    printf("\nUnesite prezime osobe: ");
    scanf(" %s", q->surname);
    printf("\nUnesite godinu rodenja osobe: ");
    scanf(" %d", &(q->birth_year));

    printf("\nOsoba dodana na pocetak liste!");

    return SUCCESS;
}

int AddToTheEnd(Position Head) {       //DODAJ NA KRAJ
    Position p = NULL;
    p = Head;

    while (p->next != NULL) {
        p = p->next;
    }

    Position q = NULL;

    q = (Position)malloc(sizeof(Person));
    if (q == NULL) {
        printf("\nNeuspjesno dodavanje novog elementa liste!");
        return ALLOC_FAIL;
    }
    else {
        printf("\nDodan novi element liste!");
    }

    q->next = p->next;
    p->next = q;

    printf("\nUnesite ime osobe: ");
    scanf(" %s", q->name);
    printf("\nUnesite prezime osobe: ");
    scanf(" %s", q->surname);
    printf("\nUnesite godinu rodenja osobe: ");
    scanf(" %d", &(q->birth_year));

    printf("\nOsoba dodana na kraj liste!");

    return SUCCESS;
}

int PrintList(Position Head) {      //ISPIS LISTE
    Position temp;
    temp = Head->next;

    int counter = 1;

    while (temp != NULL) {
        printf("\nOsoba br %d: ", counter);
        printf("\nIme osobe: %s", temp->name);
        printf("\nPrezime osobe: %s", temp->surname);
        printf("\nGodina rodenja osobe: %d", temp->birth_year);
        temp = temp->next;
        counter++;
    }

    printf("\nLISTA ISPISANA!");

    return SUCCESS;
}

Position NeededElement(Position Head) {       //TRAZI ELEMENT
    Position p = Head;

    char findSurname[NAME_MAX];

    printf("\nUnesi trazeno prezime: ");
    scanf(" %s", findSurname);

    int counter = 1;

    while (p->next != NULL && strcmp(findSurname, p->next->surname) != 0) {
        p = p->next;
        counter++;
    }

    if (strcmp(findSurname, p->next->surname) == 0) {
        printf("\nPronadjeno odgovarajuce prezime, na %d. mjestu!", counter);
        return p->next;
    }
    else {
        printf("\nNije pronadjeno odgovarajuce prezime!");
        return NOT_FOUND;
    }
}

Position findPrevious(Position Head) {      //TRAZI PRETHODNI
    Position p = Head;

    char findSurname[NAME_MAX];

    printf("\nUnesi trazeno prezime: ");
    scanf(" %s", findSurname);

    int counter = 1;

    while (p->next != NULL && strcmp(findSurname, p->next->surname) != 0) {
        p = p->next;
        counter++;
    }

    if (strcmp(findSurname, p->next->surname) == 0) {
        printf("\nPronadjeno odgovarajuce prezime, na %d. mjestu, vracen prethodni!", counter);
        return p;
    }
    else {
        printf("\nNije pronadjeno odgovarajuce prezime!");
        return NOT_FOUND;
    }
}

int DeleteElement(Position Previous) {      //IZBRISI ELEMENT

    Position p = NULL;

    p = Previous->next;

    Previous->next = p->next;

    free(p);

    return SUCCESS;
}

int AddAfter(Position p)        //DODAJ NAKON
{
    Position q = NULL;

    q = (Position)malloc(sizeof(Person));
    if (q == NULL) {
        printf("\nNeuspjesno dodavanje novog elementa liste!");
        return ALLOC_FAIL;
    }
    else {
        printf("\nDodan novi element liste!");
    }

    q->next = p->next;
    p->next = q;

    printf("\nUnesite ime osobe: ");
    scanf(" %s", q->name);
    printf("\nUnesite prezime osobe: ");
    scanf(" %s", q->surname);
    printf("\nUnesite godinu rodenja osobe: ");
    scanf(" %d", &(q->birth_year));

    printf("\nOsoba dodana iza %s %s!", p->name, p->surname);

    return SUCCESS;
}

int AddBefore(Position p)       //DODAJ PRIJE
{
    Position q = NULL;

    q = (Position)malloc(sizeof(Person));
    if (q == NULL) {
        printf("\nNeuspjesno dodavanje novog elementa liste!");
        return ALLOC_FAIL;
    }
    else {
        printf("\nDodan novi element liste!");
    }

    q->next = p->next;
    p->next = q;

    printf("\nUnesite ime osobe: ");
    scanf(" %s", q->name);
    printf("\nUnesite prezime osobe: ");
    scanf(" %s", q->surname);
    printf("\nUnesite godinu rodenja osobe: ");
    scanf(" %d", &(q->brith_year));

    printf("\nOsoba dodana ispred %s %s!", q->next->name, q->next->surname);

    return SUCCESS;
}

int Sort(Position p)        //SORTIRAJ
{
    printf("\nSortiranje liste...");

    Position j, j_prev, temp, end;

    end = NULL;

    while (p->next != end)
    {
        j_prev = p;
        j = p->next;

        while (j->next != end)
        {
            if (strcmp(j->surname, j->next->surname) > 0)
            {
                temp = j->next;
                j_prev->next = temp;
                j->next = temp->next;
                temp->next = j;
                j = temp;
            }

            j_prev = j;
            j = j->next;
        }

        end = j;
    }

    return SUCCESS;
}

int EnterIntoFile(Position p)       //UNOS PODATAKA
{
    p = p->next;
    char FileName[NAME_MAX] = { 0 };

    printf("\nUnesite ime datoteke: ");
    scanf(" %s", FileName);

    FILE* f = NULL;

    f = fopen(FileName, "w");

    if (f == NULL)
    {
        printf("\nNeuspjesno otvaranje datoteke!");
        return FILE_FAIL;
    }
    else
    {
        printf("\nUspjesno otvaranje datoteke!");
    }

    fprintf(f, "IME\tPREZIME\tGODINA RODENJA");

    while (p->next != NULL)
    {
        fprintf(f, "\n%s\t%s\t%d", p->name, p->surname, p->birth_year);
        p = p->next;

        if (p->next == NULL)
        {
            fprintf(f, "\n%s\t%s\t%d", p->name, p->surname, p->birth_year);
        }
    }

    fclose(f);

    return SUCCESS;

}

int AddToTheEnd(Position p, char* dat, int i)       //DODAJ NA KRAJ
{
    char buffer[BUFFER_MAX] = { 0 };
    int j = 0;
    int counter = 0;
    int bufferint = 0;
    FILE* f = NULL;
    f = fopen(dat, "r");

    if (f == NULL)
    {
        printf("\nNeuspjesno otvaranje datoteke!");
        return FILE_FAIL;
    }
    else
    {
        printf("\nUspjesno otvaranje datoteke!");
    }

    while (p->next != NULL) {
        p = p->next;
    }

    Position q = NULL;

    q = (Position)malloc(sizeof(Person));
    if (q == NULL) {
        printf("\nNeuspjesno dodavanje novog elementa liste!");
        return ALLOC_FAIL;
    }
    else {
        printf("\nDodan novi element liste!");
    }

    fscanf(f, "%s\t%s\t%d", buffer, buffer, bufferint);

    for (j = 0; j < i; j++)
    {
        fscanf(f, "%s\t%s\t%d", buffer, buffer, bufferint);
    }
    fscanf(f, "%s\t%s\t%d", q->name, q->surname, q->birth_year);

    while (!feof(f))
    {
        fgets(buffer, BUFFER_MAX, f);
    }

    printf("\nUspjesno uneseno u listu!");

    q->next = p->next;
    p->next = q;

    fclose(f);

    return SUCCESS;
}

int PrintFromFile(Position p)       //ISPISI IZ DATOTEKE
{
    int status = 0;
    int counter = 0, i = 0;
    char FileName[NAME_MAX] = { 0 };
    char buffer[BUFFER_MAX] = { 0 };
    int bufferint = 0;

    printf("\nUnesite ime datoteke: ");
    scanf(" %s", FileName);

    FILE* f = NULL;

    f = fopen(FileName, "r");

    if (f == NULL)
    {
        printf("\nNeuspjesno otvaranje datoteke!");
        return FILE_FAIL;
    }
    else
    {
        printf("\nUspjesno otvaranje datoteke!");
    }

    while (!feof(f)) {
        fgets(buffer, BUFFER_MAX, f);
        if (strcmp("\n", buffer) != 0) {
            counter++;
        }
    }

    counter = counter - 1;

    for (i = 0; i < counter; i++)
    {
        status = AddToTheEnd(p, FileName, i);
        if (status != 0)
            return EXIT_FAIL;
    }


    fclose(f);



    return SUCCESS;
}

int ReadFromFile(Position Head) {       //CITAJ IZ DATOTEKE
    Position p = Head;
    Position q = NULL;
    char FileName[NAME_MAX];

    printf("\nUpisite ime datoteke za citanje: ");
    scanf(" %s", FileName);

    FILE* fp = NULL;

    fp = fopen(FileName, "r");

    if (fp == NULL)
    {
        printf("\nNeuspjesno otvaranje datoteke!");
        return FILE_FAIL;
    }
    else
    {
        printf("\nUspjesno otvaranje datoteke!");
    }

    while (fgetc(fp) != '\n');

    while (!feof(fp)) {
        q = (Position)malloc(sizeof(Person));
        if (q == NULL) {
            printf("\nNeuspjesno dodavanje novog elementa liste!");
            return ALLOC_FAIL;
        }
        else {
            printf("\nDodan novi element liste!");
        }

        q->next = p->next;
        p->next = q;
        fscanf(fp, " %s %s %d", q->name, q->surname, &(q->birth_year));
        p = p->next;
    }

    printf("\nUspjesno ucitavanje liste iz datoteke!");

    return SUCCESS;
}



int main()
{
    int status = 0;
    Position Head = NULL;
    Head = AddHead();

    if (Head == NULL) {
        printf("\nAlokacija neuspjesna!");
        return ALLOC_FAIL;
    }
    else {
        printf("\nAlokacija uspjesna, kreiran Head!");
    }

    int i = 0;

    for (i = 0; i < 2; i++)
        AddToTheBeginning(Head);

    for (i = 0; i < 2; i++)
        AddToTheEnd(Head);

    PrintList(Head);

    Position NeededElement = NULL, PreviousElement = NULL;

    NeededElement = FindElement(Head);
    if (NeededElement == NULL) return NOT_FOUND;

    PreviousElement = findPrevious(Head);
    PreviousElement = findPrevious(Head);
    if (PreviousElement == NULL) return NOT_FOUND;

    DeleteElement(PreviousElement);

    PrintList(Head);

    AddAfter(FindElement(Head));

    PrintList(Head);

    AddBefore(findPrevious(Head));

    PrintList(Head);

    Sort(Head);

    PrintList(Head);

    status = EnterIntoFile(Head);

    if (status != 0)
        return EXIT_FAIL;

    Position HeadDat = NULL;
    HeadDat = AddHead();

    if (HeadDat == NULL) {
        printf("\nAlokacija neuspjesna!");
        return ALLOC_FAIL;
    }
    else {
        printf("\nAlokacija uspjesna, kreiran prvi clan liste!");
    }

    status = ReadFromFile(HeadDat);

    if (status != 0)
        return EXIT_FAIL;

    PrintList(HeadDat);

    return SUCCESS;
}