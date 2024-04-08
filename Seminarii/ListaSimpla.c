#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina {
    char* producator;
    int serie;
};

struct Nod {
    Masina inf;
    struct Nod* next;
};

void afisareMasina(Masina masina) {
    printf("\nMasina %s are seria %d.", masina.producator, masina.serie);
}

Masina initMasina(const char* producator, int serie) {
    Masina masinaNoua;
    masinaNoua.serie = serie;
    masinaNoua.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
    strcpy(masinaNoua.producator, producator);

    return masinaNoua;
}

void inserareLaInceput(Nod** cap, Masina masina) {
    //1. aloc memorie pentru un nou nod
    Nod* nou = (Nod*)malloc(sizeof(Nod)); 
    //2. copiez informatiile in noul nod
    nou->inf = masina;
    //3. noul nod pointeaza catre actualul cap al listei
    nou->next = *cap;
    //4. capul listei devine noul nod
    *cap = nou;
}

void traversareLista(Nod* cap) {
    while (cap) {
        afisareMasina(cap->inf);
        cap = cap->next;
    }
}

void inserareLaFinal(Nod** cap, Masina masina) {
    //1. Aloc memorie
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    //2. copiez informatia
    nou->inf = masina;
    //3. Noul nod va fi ultimul din lista => pointeaza catre NULL
    nou->next = NULL;
    //4. Verific daca lista e goala
    if ((*cap) != NULL) {
        // Daca NU => se gaseste ultimul nod din lista
        Nod* aux = *cap;
        while (aux->next) {
            aux = aux->next;
        }
        //5. Se leaga noul nod la sfarsitul listei
        aux->next = nou;
    }
    else {
        //Daca DA => noul nod devine capul listei
        *cap = nou;
    }
}

int numarAparitiiFord(Nod* cap, char* producator) {
    int numar = 0;
    while (cap)
    {
        if (strcmp(cap->inf.producator, producator) == 0)
        {
            numar++;
        }
        cap = cap->next;
    }
    return numar;
}

void stergereNoduriDupaCriterii(Nod** cap, char* producator) {
    //Se parcurge lista si se verifica daca primul nod trebuie sters
    while (*cap != NULL && strcmp((*cap)->inf.producator, producator) == 0) {
        Nod* copie = *cap; //Fac o copie
        *cap = (*cap)->next; //Merg la urmatorul nod 
        free(copie->inf.producator); //Eliberez memoria pentru sirul de caractere
        free(copie); //Eliberez memoria pentru Nod
    }
    //Daca lista a devenit goala, se opreste procesul
    if (*cap == NULL) 
        return;
    //Se parcurge lista pentru a gasi si sterge alte noduri 
    Nod* current = *cap;
    while (current->next) {
        //Daca nodul urmator trebuie sters
        if (strcmp(current->next->inf.producator, producator) == 0) {
            Nod* copie = current->next;
            //Se elimina legatura dintre nodul curent si cel care trebuie sters
            current->next = current->next->next;
            //Dezaloc memoria
            free(copie->inf.producator);
            free(copie);
        }
        else {
            current = current->next;
        }
    }
}


Masina* conversieLaVector(Nod* cap, int* size) {
    //Calculez lungimea listei
    int len = 0;
    Nod* current = cap;
    while (current) {
        len++;
        current = current->next;
    }
    //Aloc memorie pentru vectorul de masini
    *size = len;
    Masina* vector = (Masina*)malloc(len * sizeof(Masina));
    //Parcurg lista si copiez fiecare masina in vector;
    current = cap;
    int i = 0;
    while (current) {
        vector[i++] = current->inf;
        current = current->next;
    }
    return vector;
}

void dezalocare(Nod** cap) {
    while ((*cap) != NULL) {
        Nod* copie = *cap; //Fac o copie pentru a retine nodul precedent
        *cap = (*cap)->next; //Parcurg pana la urmatorul nod
        free(copie->inf.producator); //Eliberez memoria
        free(copie);
    }
}

int main() {
    Nod* cap = NULL;
    inserareLaInceput(&cap, initMasina("Renault", 1234));
    inserareLaInceput(&cap, initMasina("Ford", 5678));
    inserareLaInceput(&cap, initMasina("Ford", 5679));
    inserareLaInceput(&cap, initMasina("Ford", 5677));
    inserareLaInceput(&cap, initMasina("Peugeot", 9101));
    inserareLaInceput(&cap, initMasina("Bmw", 1213));

    printf("Lista initiala:\n");
    traversareLista(cap);

    printf("\n\nDupa stergerea masinilor Ford:\n");
    stergereNoduriDupaCriterii(&cap, "Ford");
    traversareLista(cap);

    int nr = numarAparitiiFord(cap, "Ford");
    printf("\n\nMasina Ford apare de %d ori\n", nr);

    printf("\nVector:\n");
    int size;
    Masina* vector = conversieLaVector(cap, &size);
    for (int i = 0; i < size; i++) {
        afisareMasina(vector[i]);
    }
    free(vector);

    dezalocare(&cap);

    return 0;
}
