#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct Nod Nod;

struct Nod
{
	struct Nod* prev;
	int data;
	struct Nod* next;
};


void create(Nod** cap, int A[], int n)
{
	Nod* t, *ultim;
	int i;
	
	*cap = (Nod*)malloc(sizeof(Nod));
	(*cap)->data = A[0];
	(*cap)->prev = (*cap)->next = NULL;
	ultim = *cap;

	for (i = 1;i < n;i++) {
		t = (Nod*)malloc(sizeof(Nod));
		t->data = A[i];
		t->next = ultim->next;
		t->prev = ultim;
		ultim->next = t;
		ultim = t;
	}

}


void Traversare(struct Nod* p)
{
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}


int Length(struct Nod* p)
{
	int len = 0;

	while (p!=NULL)
	{
		len++;
		p = p->next;
	}
	return len;
}


void Inserare(Nod** cap, int poz, int x)
{
	Nod* t;
	Nod* p = *cap;
	int i;
	if (poz < 0 || poz >Length(p))
		return;
	//Inserare la inceput cu index dat;
	if (poz == 0)
	{
		t = (Nod*)malloc(sizeof(Nod));
		t->data = x;
		t->prev = NULL;
		t->next = *cap;
		if(*cap != NULL)
			(*cap)->prev = t;
		(*cap) = t;
	}
	else
	{
		for (i = 0;i < poz - 1;i++)
			p = p->next;
		t = (Nod*)malloc(sizeof(Nod));
		t->data = x;

		t->prev = p;
		t->next = p->next;
		if (p->next != NULL)
			p->next->prev = t;
		p->next = t;
	}
}

void InserareLaInceput(Nod** cap, int x)
{
	Nod* t = (Nod*)malloc(sizeof(Nod));
	t->data = x;
	t->prev = NULL;
	t->next = (*cap);
	if(*cap!=NULL)
		(*cap)->prev = t;
	(*cap) = t;
}

void InserareLaFinal(Nod** cap, int x)
{
	Nod* t = (Nod*)malloc(sizeof(Nod));
	Nod* p = *cap;
	t->data = x;
	t->next = NULL;
	//Verificam daca lista este goala 
	if (*cap == NULL) {
		//Daca da, inseamna ca acesta este primul element care este inserat
		t->prev = NULL;
		*cap = t;
		return;
	}
	//Daca lista nu e goala, parcurgem pana la ultimul nod
	while (p->next != NULL)
		p = p->next;
	p->next = t; //Conecteaza noul nod la lista existenta
	t->prev = p; //Stabileste si legatura inversa
}

void Stergere(Nod** cap, int poz)
{
	Nod* p = *cap;
	if (poz < 0 || poz > Length(p))
		return;

	if (poz == 0)
	{
		*cap = (*cap)->next;
		int x = p->data;
		free(p);
		if (*cap != NULL)
			(*cap)->prev = NULL;
	}
	else
	{
		for (int i = 0;i < poz - 1;i++)
			p = p->next;
		p->prev->next = p->next;
		if (p->next != NULL)
			p->next->prev = p->next;
		int x = p->data;
		free(p);
	}
}

void StergereLaInceput(Nod** cap)
{
	Nod* p = *cap;
	*cap = (*cap)->next;
	int x = p->data;
	free(p);
	if (*cap != NULL)
		(*cap)->prev = NULL;
}

void StergereLaFinal(Nod** cap)
{
	if (*cap == NULL) {
		return; // Nu avem ce sterge, lista este deja goala
	}
	if ((*cap)->next == NULL) {
		// Avem un singur nod în lista, deci trebuie sa-l stergem
		free(*cap);
		*cap = NULL; // Lista este acum goala
		return;
	}
	Nod* p = *cap;
	//Parcurge pana la penultimul nod din lista
	while (p->next->next != NULL) {
		p = p->next;
	}
	free(p->next); // Stergem ultimul nod
	p->next = NULL; // Actualizam ultimul nod pentru a nu mai indica catre nimic
}

//Reverse 
void InversareaListei(Nod** cap)
{
	Nod* p = *cap;
	Nod* CapNou = NULL; // Noua variabila pentru capul inversat al listei

	// Parcurge pana la sfarsitul listei si actualizeaza capul inversat
	while (p != NULL) {
		Nod* temp = p->next; // Salvam urmatorul nod inainte de a-l schimba
		p->next = CapNou; // Inlocuim legatura spre urmatorul nod cu legatura catre nodul precedent
		p->prev = temp; // Actualizam si legatura spre nodul precedent cu urmatorul nod original
		CapNou = p; // Actualizam noul cap al listei
		p = temp; // Avansam la urmatorul nod original
	}

	*cap = CapNou; // Actualizam capul listei initiale cu noul cap inversat
}




int main() {
	Nod* cap = NULL;

	int A[] = { 10,20,30,40,50 };
	create(&cap,A, 5);

	//printf("Length is :%d\n", Length(cap));

	Traversare(cap);

	Inserare(&cap, 0, 54);
	Inserare(&cap, 1, 15);
	Inserare(&cap, 4, 27);

	Traversare(cap);

	InserareLaInceput(&cap, 28);
	Traversare(cap);

	InserareLaFinal(&cap, 100);
	Traversare(cap);

	Stergere(&cap, 4);
	Traversare(cap);

	StergereLaInceput(&cap);
	Traversare(cap);

	StergereLaFinal(&cap);
	Traversare(cap);

	InversareaListei(&cap);
	Traversare(cap);

}