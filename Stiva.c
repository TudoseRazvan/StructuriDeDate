#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>


typedef struct Nod Nod;

struct Nod
{
	int data;
	struct Nod* next;
};

void push(Nod** top, int x)
{
	Nod* t;
	t = (Nod*)malloc(sizeof(Nod));

	if (t == NULL)
		printf("Stiva e plina!\n");
	else {
		t->data = x;
		t->next = *top; //Actualizeaza legatura noului nod cu vechiul top
		*top = t; //Actualizeaza topul stivei pt a indica spre noul nod
	}
}

int pop(struct Nod** top)
{
	Nod* t;
	int x = -1;
	if (*top == NULL)
	{
		printf("Stiva e goala!\n");
	}
	else 
	{
		t = *top;
		*top = (*top)->next;
		x = t->data;
		free(t);
	}
	return x;
}

void Afisare(struct Nod* top)
{
	Nod* p;
	p = top;

	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

// Scoatere nod dupa criteriu
void scoatereDupaCriteriu(Nod** top, int val)
{
    Nod* p = *top;
    Nod* prev = NULL; //Urmareste nodul precedent pentru parcurgere

    while (p != NULL) {
        if (p->data == val) {
            if (prev == NULL)
                *top = p->next; // Actualizeaza topul daca nodul eliminat este primul
            else
                prev->next = p->next; // Actualizeaza legatura nodului anterior cu urmatorul dupa eliminare
            free(p); // Dezaloca memoria pentru nodul eliminat
            return;
        }
        prev = p;
        p = p->next;
    }
    printf("Nu s-a gasit nodul cu valoarea specificata.\n");
}

// Conversie la alta structura
int* conversieLaVector(Nod* top, int* dimensiune)
{
    Nod* p = top;
    int count = 0;

    // Determinarea dimensiunii vectorului
    while (p != NULL) {
        count++;
        p = p->next;
    }

    *dimensiune = count;

    // Alocarea memoriei pentru vector
    int* vector = (int*)malloc(count * sizeof(int));
    if (vector == NULL) {
        printf("Eroare la alocarea memoriei pentru vector.\n");
        return NULL;
    }

    // Copierea elementelor din stiva in vector
    p = top;
    for (int i = 0; i < count; i++) {
        vector[i] = p->data;
        p = p->next;
    }

    return vector;
}

// Dezalocare
void dezalocare(Nod** top)
{
    Nod* p = *top;
    while (p != NULL) {
        Nod* temp = p;
        p = p->next;
        free(temp); // Dezaloca memoria pentru fiecare nod in parte
    }
    *top = NULL;
}

int main()
{
	Nod* top = NULL;

	push(&top, 10);
	push(&top, 20);
	push(&top, 30);
	push(&top, 40);
	push(&top, 50);

	Afisare(top);

	printf("%d ", pop(&top));

    scoatereDupaCriteriu(&top, 30);
    Afisare(top);

    int dimensiune;
    int* vector = conversieLaVector(top, &dimensiune);
    if (vector != NULL) {
        printf("Vectorul obtinut din stiva:\n");
        for (int i = 0; i < dimensiune; i++) {
            printf("%d ", vector[i]);
        }
        printf("\n");
        free(vector); // Dezalocare vector
    }

    dezalocare(&top); // Dezalocare stiva

    return 0;

	return 0;
}