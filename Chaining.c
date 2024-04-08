#include <stdio.h>
#include <stdlib.h>

typedef struct Nod {
    int data;
    struct Nod* next;
} Nod;

void InserareInListaNesortata(struct Nod** cap, int x) {
    Nod* t = (Nod*)malloc(sizeof(Nod));    // Se aloca memorie pentru noul nod
    t->data = x;                            // Se seteaza valoarea data pentru nod
    t->next = NULL;                         // Noul nod va fi ultimul din lista

    if (*cap == NULL) {                     // Daca lista este goala, noul nod devine capul listei
        *cap = t;
    }
    else {
        Nod* current = *cap;
        while (current->next != NULL) {     // Se parcurge lista pana la ultimul nod
            current = current->next;
        }
        current->next = t;                  // Se leaga noul nod la sfarsitul listei
    }
}


void InserareInListaSortata(struct Nod** cap, int x) {
    Nod* t = (Nod*)malloc(sizeof(Nod));
    t->data = x;
    t->next = NULL;

    if ((*cap) != NULL) {
        Nod* aux = *cap;
        Nod* q = NULL;
        while (aux != NULL && aux->data < x) {
            q = aux;
            aux = aux->next;
        }
        if (q == NULL) {
            t->next = *cap;
            *cap = t;
        }
        else {
            t->next = q->next;
            q->next = t;
        }
    }
    else {
        *cap = t;
    }
}

int hash(int key) {
    return key % 10;
}

void InserareHashTable(struct Nod* H[], int key) {
    int index = hash(key);
    //InserareInListaSortata(&H[index], key);
    InserareInListaNesortata(&H[index], key);
}

void afisareHashTable(struct Nod* H[], int size) {
    for (int i = 0; i < size; i++) {
        printf("H[%d]: ", i);
        Nod* current = H[i];
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

void dezalocare(struct Nod* H[], int size) {
    for (int i = 0; i < size; i++) {
        Nod* current = H[i];
        while (current != NULL) {
            Nod* temp = current;
            current = current->next;
            free(temp);
        }
        H[i] = NULL;
    }
}

Nod* cautareDupaCriteriu(struct Nod* H[], int size, int criteriu) {
    for (int i = 0; i < size; i++) {
        Nod* current = H[i];
        while (current != NULL) {
            if (current->data == criteriu) {
                return current;
            }
            current = current->next;
        }
    }
    return NULL;
}


// Functie pentru conversia tabelei de dispersie in alta structura
Nod** conversieLaVector(struct Nod* H[], int size, int* vectorSize) {
    *vectorSize = size; // Dimensiunea vectorului va fi aceeasi cu dimensiunea tabelei de dispersie
    Nod** vector = (Nod**)malloc(size * sizeof(Nod*)); // Alocam memorie pentru vectorul de pointeri catre noduri

    for (int i = 0; i < size; i++) {
        // Pentru fiecare slot din tabela de dispersie
        // Copiem lista inlantuita corespunzatoare in vector
        vector[i] = H[i];
    }

    return vector;
}


int main() {
    Nod* HT[10];

    for (int i = 0; i < 10; i++)
        HT[i] = NULL;

    InserareHashTable(HT, 12);
    InserareHashTable(HT, 22);
    InserareHashTable(HT, 42);
    InserareHashTable(HT, 62);
    InserareHashTable(HT, 39);
    InserareHashTable(HT, 79);
    InserareHashTable(HT, 85);
    InserareHashTable(HT, 48);
    InserareHashTable(HT, 96);
    InserareHashTable(HT, 127);
    InserareHashTable(HT, 131);
    InserareHashTable(HT, 10);

    printf("HashTable:\n");
    afisareHashTable(HT, 10);

    Nod* temp = cautareDupaCriteriu(HT, 10, 22);
    if (temp != NULL) {
        printf("\nElementul cautat (22) a fost gasit in tabela de dispersie.\n");
    }
    else {
        printf("\nElementul cautat (22) nu a fost gasit in tabela de dispersie.\n");
    }

    Nod** vector;
    int vectorSize;

    vector = conversieLaVector(HT, 10, &vectorSize);

    printf("\nVector:\n");
    for (int i = 0; i < vectorSize; i++) {
        printf("V[%d]: ", i);
        Nod* current = vector[i];
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }

    // Dezalocam memoria alocata pentru vector
    for (int i = 0; i < vectorSize; i++) {
        dezalocare(&vector[i], 1);
    }
    free(vector);


    //dezalocare(HT, 10);

    return 0;
}
