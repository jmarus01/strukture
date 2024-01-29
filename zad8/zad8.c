/*8. Napisati program koji omoguæava rad s binarnim stablom pretraživanja.Treba
omoguæiti unošenje novog elementa u stablo, ispis elemenata(inorder, preorder, postorder i
level order), brisanje i pronalaženje nekog elementa.*/
#include <stdio.h>
#include <stdlib.h>
#define SUCCESS 1
#define NULL 0
#define NOT_FOUND -1
#define _CRT_SECURE_NO_WARNINGS

typedef struct RootNode* Node;

struct RootNode {
	int Element;
	Node Left;
	Node Right;
};

Node AddEl(Node current, Node q) {						//DODAJ ELEMENT

	if (NULL == current) {
		return q;
	}
	else if (current->Element < q->Element) {
		current->Right = AddEl(current->Right, q);
	}
	else if (current->Element > q->Element) {
		current->Left = Unos(current->Left, q);
	}
	else
		free(q->Element);

	return current;
}

int PrintInOrder(Node current) {					//INORDER ISPIS

	if (current != NULL) {
		PrintInOrder(current->Left);
		printf(" \t%d\n", current->Element);
		PrintInOrder(current->Right);
	}
	return 0;
}

int PrintPreOrder(Node current) {			//PREORDER ISPIS

	if (current != NULL) {
		printf(" %d\n", current->Element);
		PrintPreOrder(current->Left);
		PrintPreOrder(current->Right);
	}
	return 0;
}

int PrintPostOrder(Node current) {		//POSTORDER ISPIS

	if (current) {
		PrintPreOrder(current->Left);
		PrintPreOrder(current->Right);
		printf(" %d\n", current->Element);
	}
	return 0;
}

void PrintCurrentLevel(Node root, int level)		//CURR LVL
{
	if (root == NULL)
		return;
	if (level == 1)
		printf("%d ", root->Element);
	else if (level > 1) {
		PrintCurrentLevel(root->Left, level - 1);
		PrintCurrentLevel(root->Right, level - 1);
	}
}

int height(Node node)							//VISINA
{
	if (node == NULL)
		return 0;
	else {

		int lheight = height(node->Left);
		int rheight = height(node->Right);


		if (lheight > rheight)
			return (lheight + 1);
		else
			return (rheight + 1);
	}
}

void PrintLevelorder(Node root)			//LEVELORDER ISPIS
{
	int h = height(root);
	int i;
	for (i = 1; i <= h; i++)
		PrintCurrentLevel(root, i);
}

Node DelNode(Node root, int key)					//BRISANJE
{
	if (root == NULL)
		return root;

	if (key < root->Element)
		root->Left = deleteNode(root->Left, key);
	else if (key > root->Element)
		root->Right = deleteNode(root->Right, key);
	else {
		if (root->Left == NULL) {
			Node temp = root->Right;
			free(root);
			return temp;
		}
		else if (root->Right == NULL) {
			Node temp = root->Left;
			free(root);
			return temp;
		}

		Node temp = minValueNode(root->Right);

		root->Element = temp->Element;

		root->Right = deleteNode(root->Right, temp->Element);
	}
	return root;
}

Node minValueNode(Node node)
{
	Node current = node;

	while (current && current->Left != NULL)
		current = current->Left;

	return current;
}

int main() {
	int choice = 0;
	int number = 0;
	int num_to_del = 0;

	Node root = NULL;
	Node  q = NULL;

	printf("Izabreite:\n 1 - unosenje novog elementa u stablo,\n 2 - ispis elemenata inorder,\n 3 - ispis elemenata preorder,\n");
	printf(" 4 - ispis elemenata postorder,\n 5 - ispis elemenata level order,\n 6 - brisanje i pronalazenje nekog elementa.\n");
	printf("Unesite izbor: ");
	scanf("%d", &choice);

	switch (choice) {
	case 1:
		q = (Node)malloc(sizeof(Node));
		q->Element = number;
		root = AddEl(root, q);
		break;

	case 2:
		printf("\n\t***ISPIS*\n");
		PrintInOrder(root);
		break;

	case 3:
		printf("\n\t***ISPIS*\n");
		PrintPreOrder(root);
		break;
	case 4:
		printf("\n\t***ISPIS*\n");
		PrintPostOrder(root);
		break;

	case 5:
		printf("\n\t***ISPIS*\n"); \
			PrintLevelOrder(root);
		break;

	case 6:
		printf("Unesite broj koji zelite izbrisati iz stabla :\n");
		scanf("%d", &num_to_del);
		root = DelNode(root, num_to_del);
		break;

	default:
		printf("Niste izabrali ponuden broj!");
		break;
	}
	return 0;
}