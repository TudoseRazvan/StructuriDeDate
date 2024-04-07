#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 

typedef struct Nod {
    int data;
    struct Nod* next;
} Nod;

// Functia pentru adaugarea unui element la coada
void put(Nod** front, Nod** rear, int x) {
    Nod* temp = (Nod*)malloc(sizeof(Nod)); // Alocam memorie pentru noul nod

    if (temp == NULL) { // Verificam daca alocarea a esuat
        printf("Coada e plina!\n");
        return;
    }

    temp->data = x; // Initializam datele noului nod
    temp->next = NULL; // Noul nod va fi ultimul din coada

    if (*front == NULL) { // Verificam daca coada este goala
        *front = *rear = temp; // Daca da, frontul si rearul sunt noul nod
    }
    else {
        (*rear)->next = temp; // Legam noul nod la nodul curent rear
        *rear = temp; // Rear-ul devine noul nod
    }
}

// Functia pentru extragerea unui element din coada
int get(Nod** front, Nod** rear) {
    int x = -1;
    Nod* temp;

    if (*front == NULL) { // Verificam daca coada este goala
        printf("Coada este goala\n");
    }
    else {
        x = (*front)->data; // Salvam datele din primul nod
        temp = *front; // Salvam adresa primului nod

        *front = (*front)->next; // Front-ul devine urmatorul nod
        if (*front == NULL) { // Verificam daca coada devine goala
            *rear = NULL; // Daca da, rear-ul devine NULL
        }

        free(temp); // Eliberam memoria pentru nodul extras
    }
    return x; // Returnam valoarea extrasa
}

// Functia pentru afisarea elementelor din coada
void Afisare(Nod* front) {
    while (front != NULL) { // Parcurgem coada pana la final
        printf("%d ", front->data); // Afisam datele din fiecare nod
        front = front->next; // Trecem la urmatorul nod
    }
    printf("\n");
}

// Functia pentru scoaterea unui nod din lista dupa un anumit criteriu
void scoateNodDupaCriteriu(Nod** cap, int criteriu) {
    Nod* p = *cap;
    Nod* anterior = NULL;

    while (p != NULL) {
        if (p->data == criteriu) { 
            if (anterior == NULL) { // Daca nodul cautat este primul din lista
                *cap = p->next; // Actualizam capul listei
            }
            else {
                anterior->next = p->next; // Legam nodul anterior de urmatorul nod
            }
            free(p); // Eliberam memoria ocupata de nodul eliminat
            return;
        }
        anterior = p; // Salvam nodul anterior pentru a ajusta legaturile
        p = p->next; // Trecem la urmatorul nod
    }

    printf("Nu s-a gasit niciun nod care sa corespunda criteriului.\n");
}

// Functia pentru conversia unei liste la un vector
int* conversieLaVector(Nod* cap, int* dimensiune) {
    int* vector;
    int lungime = 0;

    // Calculam lungimea listei
    Nod* p = cap;
    while (p != NULL) {
        lungime++;
        p = p->next;
    }

    // Alocam memorie pentru vector
    vector = (int*)malloc(lungime * sizeof(int));
    if (vector == NULL) {
        printf("Alocarea de memorie a esuat.\n");
        *dimensiune = 0;
        return NULL;
    }

    // Copiem valorile din lista in vector
    p = cap;
    int i = 0;
    while (p != NULL) {
        vector[i++] = p->data;
        p = p->next;
    }

    *dimensiune = lungime;
    return vector;
}

// Functia pentru dezalocarea unei liste
void dezalocaLista(Nod** cap) {
    Nod* p = *cap;
    Nod* temp;

    while (p != NULL) {
        temp = p; // Salvam adresa nodului curent
        p = p->next; // Trecem la urmatorul nod
        free(temp); // Eliberam memoria pentru nodul curent
    }

    *cap = NULL; // Setam capul listei la NULL pentru a marca lista ca fiind goala
}


int main() {
    Nod* front = NULL; 
    Nod* rear = NULL; 

    put(&front, &rear, 10);
    put(&front, &rear, 20);
    put(&front, &rear, 30);
    put(&front, &rear, 40);
    put(&front, &rear, 50);

    Afisare(front);

    int elementExtras = get(&front, &rear);
    printf("Elementul extras din coada: %d\n", elementExtras);

    Afisare(front);

    scoateNodDupaCriteriu(&front, 50);
    printf("Dupa scoaterea nodurilor cu criteriul 50: ");
    Afisare(front);

    int size;
    int* vector = conversieLaVector(front, &size);
    printf("Vectorul obtinut din coada: ");
    for (int i = 0;i < size;i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");

    dezalocaLista(&front);
    printf("Coada dupa dezalocare: \n");
    Afisare(front);

    return 0;
}
