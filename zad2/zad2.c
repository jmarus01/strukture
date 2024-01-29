#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_MAX (50)
#define ALLOC_FAIL (-1)
#define SUCCESS (0)
#define NOT_FOUND (0)

typedef struct Person* position;

struct Person {
    char name[NAME_MAX];
    char surname[NAME_MAX];
    int year_of_birth;
    position next;
};

typedef struct Person person;


position add_head() {
    position head = NULL;
    head = (position)malloc(sizeof(person));
    head->next = NULL;
    return head;
}

int add_to_front(position Head) {

    position p = NULL;
    p = Head;

    position q = NULL;

    q = (position)malloc(sizeof(person));

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
    scanf(" %d", &(q->year_of_birth));

    printf("\nOsoba dodana na pocetak liste!");

    return SUCCESS;
}

int add_to_back(position Head) {
    position p = NULL;
    p = Head;

    while (p->next != NULL) {
        p = p->next;
    }

    position q = NULL;

    q = (position)malloc(sizeof(person));
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
    scanf(" %d", &(q->year_of_birth));

    printf("\nOsoba dodana na kraj liste!");

    return SUCCESS;
}

int print_list(position Head) {
    position temp;
    temp = Head->next;

    int counter = 1;

    while (temp != NULL) {
        printf("\nOsoba br %d: ", counter);
        printf("\nIme osobe: %s", temp->name);
        printf("\nPrezime osobe: %s", temp->surname);
        printf("\nGodina rodenja osobe: %d", temp->year_of_birth);
        temp = temp->next;
        counter++;
    }

    printf("\nLISTA ISPISANA!");

    return SUCCESS;
}

position find_element(position Head) {
    position p = Head;

    char surname_search[NAME_MAX];

    printf("\nUnesi trazeno prezime: ");
    scanf(" %s", surname_search);

    int counter = 1;

    while (p->next != NULL && strcmp(surname_search, p->next->surname) != 0) {
        p = p->next;
        counter++;
    }

    if (strcmp(surname_search, p->next->surname) == 0) {
        printf("\nPronadjeno odgovarajuce prezime, na %d. mjestu!", counter);
        return p->next;
    }
    else {
        printf("\nNije pronadjeno odgovarajuce prezime!");
        return NOT_FOUND;
    }
}

position find_previous(position Head) {
    position p = Head;

    char surname_search[NAME_MAX];

    printf("\nUnesi trazeno prezime: ");
    scanf(" %s", surname_search);

    int brojac = 1;

    while (p->next != NULL && strcmp(surname_search, p->next->surname) != 0) {
        p = p->next;
        brojac++;
    }

    if (strcmp(surname_search, p->next->surname) == 0) {
        printf("\nPronadjeno odgovarajuce prezime, na %d. mjestu, vracen prethodni!", brojac);
        return p;
    }
    else {
        printf("\nNije pronadjeno odgovarajuce prezime!");
        return NOT_FOUND;
    }
}

int erase_element(position before) {

    position p = NULL;

    p = before->next;

    before->next = p->next;

    free(p);

    return SUCCESS;
}

int main() {

    position Head = NULL;
    Head = add_head();

    if (Head == NULL) {
        printf("\nAlokacija neuspjesna!");
        return ALLOC_FAIL;
    }
    else {
        printf("\nAlokacija uspjesna, kreiran Head!");
    }

    int i = 0;

    for (i = 0; i < 2; i++)
        add_to_front(Head);

    for (i = 0; i < 2; i++)
        add_to_back(Head);

    print_list(Head);

    position searched_element = NULL, previous_element = NULL;

    searched_element = find_element(Head);

    previous_element = find_previous(Head);

    erase_element(previous_element);

    print_list(Head);

    return SUCCESS;
}