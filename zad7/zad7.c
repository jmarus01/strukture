/*7. Napisati program koji pomo?u vezanih listi(stabala) predstavlja strukturu direktorija.
Omogu?iti unos novih direktorija i pod - direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij.To?nije program treba preko menija simulirati
korištenje DOS naredbi : 1 - "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 50
#define SUCCESS 1
#define NULL 0
#define NOT_FOUND -1
#define _CRT_SECURE_NO_WARNINGS

typedef struct RootNode* Node;

struct RootNode {
	char name[MAX];
	Node FirstChild;
	Node NextBrother;
};

typedef struct PathNode* pNode;

struct PathNode {
	Node path;
	pNode Next;
};

Node CreateNode(char naziv[]) {						//STVORI ROOT
	Node S = (Node)malloc(sizeof(Node));
	S->FirstChild = NULL;
	S->NextBrother = NULL;
	strcpy(S->name, naziv);

	return S;
}

Node CreateNewDir(char* naziv, Node S) {			//NOVI DIR
	Node p = CreateNode(naziv);

	if (S->FirstChild == 0) {
		S->FirstChild = p;
		return p;
	}

	Node q = S->FirstChild;

	while (q->NextBrother != NULL) {		//while petlja za doc do zadnjeg brata u listi
		/*if (strcmp(q->NextBrother, naziv) > 0)
			break;*/	//ovo je ako bi trebalo po abecedi
		q = q->NextBrother;
	}

	q->NextBrother = p;		//zadnjeg brata spajamo na taj novi node

	return p;
}

Node Find(char name[], Node S) {					//TRAZI
	/*if (S == NULL) {
		printf("Empty");
		return NULL;
	}*/
	Node p = S;

	if (strcmp(name, p->name) == 0) {
		return p;
	}
	else {
		if (p->FirstChild != NULL) {
			p = p->FirstChild;
			Find(name, p);
		}
		if (p->NextBrother != NULL) {
			p = p->NextBrother;
			Find(name, p);
		}
	}
	return NULL;
}

pNode FindPrev(pNode path, Node S) {							//TRAZI PRETHODNOG ODNOSNO RODITELJA
	pNode p = S;
	char name[MAX];

	printf("Koji dir zelite naci? ");
	scanf("%s\n", &name);
	Node newcurrnode = Find(name, p);

	int counter = 1;

	while (p->Next != NULL && strcmp(newcurrnode, p->Next) != 0) {
		p = p->Next;
		counter++;
	}

	if (strcmp(newcurrnode, p->Next) == 0) {
		printf("\nPronadjeno na %d. mjestu, vracen prethodni!", counter);
		return p;
	}
	else {
		printf("\nNije pronadjen!");
		return NOT_FOUND;
	}
	return p;
}

Node PrintPreorder(Node S) {		//PREORDER ISPIS

	printf("%s", S->name);
	Node p = S;

	while (p != NULL) {
		if (p->FirstChild != NULL) {
			p = p->FirstChild;
			PrintPreorder(p);
		}
		if (p->NextBrother != NULL) {
			p = p->NextBrother;
			PrintPreorder(p);
		}
	}

	return SUCCESS;
}


/*Node PrintPostorder(Node S) {		//POSTORDER ISPIS
	if (S == NULL) {
		printf("Empty!");
		return;
	}

	Node p = S;

	while (p != NULL) {
		if (S->FirstChild != NULL) {
			p = S->FirstChild;
			PrintPostorder(p);
		}
		if (p->NextBrother != NULL) {
			p = p->NextBrother;
			PrintPostorder(p);
		}
	}

	printf("%s", S->name);

	return SUCCESS;
}*/



/*Node PrintInorder(Node S) {		//INORDER ISPIS
	if (S == NULL) {
		printf("Empty!");
		return;
	}

	Node p = S;

	while (p != NULL) {
		if (S->FirstChild != NULL) {
			p = S->FirstChild;
			PrintInorder(p);
		}

		printf("%s", S->name);

		if (p->NextBrother != NULL) {
			p = p->NextBrother;
			PrintInorder(p);
		}
	}

	return SUCCESS;
}*/


/*funkcija za stvoriti listu/dodat cvor u listu*/


int main() {

	int num;
	char name[MAX];

	//		"root"						
	//	"dir1"	"dir2"
	//dir72

	Node root = CreateNode("root");
	Node currnode = root;

	pNode pathHead = malloc(sizeof(pNode));


	printf("Izaberite DOS naredbu!\n");
	printf("1 - md (novi direktorij), 2 - cd dir  (promijeni direktorij), 3 - cd.. (promijeni prethodni direktorij), 4 - dir (svi fileovi i njihova velicina) i 5 – izlaz");
	scanf("%d", &num);

	switch (num) {
	case 1:
		printf("Ime vaseg dir: ");
		scanf("%s\n", &name);  //dir1
		CreateNewDir(name, currnode);

		break;

	case 2:
		printf("Koji dir zelite naci? ");
		scanf("%s\n", &name);
		Node newcurrnode = Find(name, currnode);
		if (newcurrnode == NULL) {
			printf("Ne postoji dir!");
		}
		else {
			printf("Usao si u dir.");
			currnode = newcurrnode;
			AddPathNode(pathHead, currnode); //na kraj vezane liste patha dodaj currnode u kojeg smo usli
		}

		break;

	case 3:
		FindPrev(pathHead, currnode);
		break;

	case 4:
		PrintPreorder(currnode);
		break;

	case 5:
		printf("Program je prekinut !!");
		break;

	default:
		printf("Niste izabrali ponuden broj!");
		break;
	}

	return 0;
}