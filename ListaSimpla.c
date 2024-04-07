//Lista Simplu Inlantuita:
/*
-inserareLaInceput

-inserarareLaSfarsit

-traversare

-cautare Nod / Informatie Utila dupa criterii

-stergere Noduri dupa criterii (primul nod, ultimul nod, de pe pozitie)

-conversie la alta structura invatata la seminar(inclusiv la vector)

-dezalocare structura
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Nod Nod;

struct Nod
{
	int data;
	struct Nod* next;
};

void create(Nod** cap, int A[], int n) 
{
	int i;
	struct Nod* temp, *ultim;
	*cap = (Nod*)malloc(sizeof(Nod));
	(*cap)->data = A[0];
	(*cap)->next = NULL;
	ultim = *cap;

	for (i = 1;i < n;i++) {
		temp = (Nod*)malloc(sizeof(Nod));
		temp->data = A[i];
		temp->next = NULL;
		ultim->next = temp;
		ultim = temp;
	}
}

void traversare(struct Nod* p)
{
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
}

void DisplayRecursiv(struct Nod* p)
{
	if (p != NULL) {
		printf("%d ", p->data);
		DisplayRecursiv(p->next);
	}
}

int contor(struct Nod* p)
{
	int contor = 0;
	while (p != NULL) {
		contor++;
		p = p->next;
	}
	//printf("\nIn lista sunt %d noduri.", contor);
	return contor;
}

int SumaElementelorDinLista(struct Nod* p)
{
	int suma = 0;
	while (p != NULL) {
		suma += p->data;
		p = p->next;
	}
	printf("\nSuma elementelor din lista este: %d", suma);
	return suma;
}

void ElementMaximDinLista(struct Nod* p)
{
	int elementMaxim = 0;
	while (p != NULL) {
		if (p->data > elementMaxim) {
			elementMaxim = p->data;
		}	
		p = p->next;
	}
	printf("\nElementul maxim este: %d", elementMaxim);
}

//Cauta un nod dupa o anumita cheie
void LinearSearch(struct Nod* p, int cheie)
{
	if (p == 0) {
		printf("Lista este goala => cheia nu poate fi cautata.");
	}

	while (p != NULL) {
		if (p->data == cheie) {
			printf("\nCheia %d a fost gasita!", cheie);
			break;
		}
		p = p->next;
	}
}

void Inserare(struct Nod** cap, int index, int x)
{
	struct Nod* t;
	struct Nod* p = *cap;

	if (index<0 || index > contor(p)) {
		return -1;
	}

	t = (Nod*)malloc(sizeof(Nod));
	t->data = x;

	if (index == 0)
	{
		t->next = *cap;
		*cap = t;
	}
	else {
		for (int i = 0;i < index - 1;i++)
			p = p->next;
		t->next = p->next;
		p->next = t;
	}
}

void InserareLaInceput(struct Nod** cap, int x)
{
	Nod* t = (Nod*)malloc(sizeof(Nod));
	t->data = x;
	t->next = *cap; //Leaga noul nod la vechiul cap al listei

	*cap = t; //Actualizeaza adresa capului listei
}

void InserareLaFinal(struct Nod** cap, int x)
{
	Nod* t;

	//Pas 1 -> alocarea memoriei pentru t
	t = (Nod*)malloc(sizeof(Nod));
	t->data = x;
	t->next = NULL;

	//Pas 2 -> verifica daca lista este goala
	if ((*cap) != NULL) {
		//Pas 3 -> Crearea unui AUXILIAR si il parcurg
		Nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		//Inserez nodul la final, dupa ce am parcurs auxiliarul
		aux->next = t;
	}
	else {
		*cap = t;
	}
}


void InserareInListaSortata(struct Nod** cap, int x)
{
	Nod* t; //Nodul pe care il inseram

	t = (Nod*)malloc(sizeof(Nod));
	t->data = x;
	t->next = NULL;

	if ((*cap) != NULL) {
		//Cele 2 noduri care ne vor ajuta sa inseram valoarea lui x
		Nod* aux = *cap; //Nod folosit pentru a parcurge lista
		Nod* q = NULL;
		while (aux->next != NULL && aux->data < x) {
			q = aux; //Memoreaza valoarea mai mica decat x pentru inserare si legare
			aux = aux->next;
		}
		//Leaga lista
		t->next = q->next;
		q->next = t;
	}
	else {
		*cap = t;
	}
}

int StergeNod(struct Nod** cap, int poz)
{
	Nod* copie = *cap; //este o copie pentru cap
	Nod* q = NULL; //Pastreaza variabila nodului anterior celui pe care il stergem
	int x = -1;

	if (poz < 1 || poz > contor(copie))
		return -1;
	else {
		//Verificam pt eliminarea primului nod
		if (poz == 1) {
			q = copie;
			x = copie->data;
			*cap = copie->next; //Trebuie modificat cap, nu copie
			free(q);
			return x;
		}
		else {
			//Sterge nodul de pe pozitie
			for (int i = 0;i < poz - 1;i++) 
			{
				q = copie;
				copie = copie->next;
			}
			q->next = copie->next;
			x = copie->data;
			free(copie);
			return x;
		}
	}

}

//Stergerea primului nod e la fel ca dezalocarea doar ca fara parcurgerea prin while
void StergePrimulNod(Nod** cap) 
{
	if (*cap == NULL || (*cap)->next == NULL)
	{
		//Lista este goala deja
		return -1;
	}

	Nod* nodDeSters = *cap; // Salvam adresa primului nod intr-un pointer temporar
	*cap = (*cap)->next; // Actualizam adresa de inceput a listei sa fie adresa celui de-al doilea nod
	free(nodDeSters); // Eliberam memoria ocupata de primul nod
}

void StergeUltimulNod(Nod** cap) {
	if (*cap == NULL || (*cap)->next == NULL) 
	{
		//Lista este goala sau are doar un nod
		free(*cap);
		*cap = NULL;
		return -1;
	}

	Nod* predecesor = *cap;
	Nod* curent = (*cap)->next;

	//Parcurge lista pana la penultimul nod
	while (curent->next != NULL) {
		predecesor = predecesor->next;
		curent = curent->next;
	}

	//Elibereaza ultimul nod si actualizeaza legatura predecesorului sau
	free(curent);
	predecesor->next = NULL;
}

//Conversie la vector de int
int* ConversieLaVector(Nod* cap)
{
	int nrNoduri = contor(cap);

	//Alocam memorie pentru vector
	int* vector = (int*)malloc(sizeof(int));
	if (vector == NULL) {
		printf("Eroare la alocarea memoriei!");
		return NULL;
	}

	//Parcurge lista si salveaza nodurile in vector
	int i = 0;
	while (cap != NULL) {
		vector[i++] = cap->data;
		cap = cap->next;
	}

	return vector;
}

void Dezalocare(Nod** cap) {
	while ((*cap) != NULL) {
		Nod* temp = *cap; //Salveaza adresa nodului curent pt a nu pierde referinta catre urmatorul nod
		*cap = (*cap)->next; //Avanseaza la urmatorul nod
		free(temp); //Dezaloca nodul curent
	}
}


int main() {
	Nod* cap = NULL;

	//int A[] = { 3,5,7,10,15,25,32,8,2};

	//create(&cap, A, 8);
	traversare(cap);
	//DisplayRecursiv(cap);

	contor(cap);
	//SumaElementelorDinLista(cap);
	//ElementMaximDinLista(cap);

	//Inserari simple
	Inserare(&cap, 0, 3);
	Inserare(&cap, 1, 5);
	Inserare(&cap, 2, 7);
	Inserare(&cap, 3, 10);
	Inserare(&cap, 4, 15);
	Inserare(&cap, 5, 34);
	Inserare(&cap, 6, 50);
	Inserare(&cap, 7, 61);
	Inserare(&cap, 6, 45);

	//Traversare
	traversare(cap);

	//Cauta un nod dupa o anumita cheie
	int cheie = 10;
	LinearSearch(cap, cheie);

	//Inserare la final
	printf("\n");
	InserareLaFinal(&cap, 182);
	traversare(cap);

	//Inserare intr-o lista sortata deja
	printf("\n");
	InserareInListaSortata(&cap, 18);
	traversare(cap);

	//Inserarea la inceput
	printf("\n");
	InserareLaInceput(&cap, 52);
	traversare(cap);

	//Stergerea unui nod de pe o anumita pozitie
	printf("\n");
	StergeNod(&cap, 1);
	traversare(cap);

	printf("\n");
	//Testare pentru conversia listei la vector
	int* vector = ConversieLaVector(cap);
	if (vector != NULL) {
		for (int i = 0;i < contor(cap);i++) {
			printf("%d ", vector[i]);
		}
	}

	printf("\nSterge ultimul nod: \n");
	StergeUltimulNod(&cap);
	traversare(cap);

	printf("\nSterge primul nod: \n");
	StergePrimulNod(&cap);
	traversare(cap);

	//Dezalocarea structurii
	printf("\n");
	Dezalocare(&cap);
	printf("Dezalocarea a fost facuta cu succes!");

	return 0;
}