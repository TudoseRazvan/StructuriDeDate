#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h> 
#include<string.h>

typedef struct Masina Masina;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Masina {
	char* producator;
	int serie;
};

struct Nod {
	Masina inf;
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int dimensiune;
};

void afisareMasina(Masina masina) {
	printf("\n Masina %s are seria %d.", masina.producator, masina.serie);
}

Masina initMasina(const char* producator, int serie) {
	Masina masinaNoua;
	masinaNoua.serie = serie;
	masinaNoua.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(masinaNoua.producator, producator);

	return masinaNoua;
}

// Func?ia pentru inserarea unei ma?ini la sfâr?itul unei liste
void inserareLaFinal(Nod** cap, Masina masina) {
    // Aloca?i memorie pentru un nou nod
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    // Ini?ializa?i noul nod cu informa?iile ma?inii ?i cu urm?torul nod NULL
    nou->inf = masina;
    nou->next = NULL;
    // Verifica?i dac? lista nu este goal?
    if ((*cap) != NULL) {
        // Dac? lista nu este goal?, parcurge?i lista pân? la ultimul nod
        Nod* aux = *cap;
        while (aux->next) {
            aux = aux->next;
        }
        // Lega?i noul nod la sfâr?itul listei
        aux->next = nou;
    }
    else {
        // Dac? lista este goal?, noul nod devine primul nod al listei
        *cap = nou;
    }
}

// Func?ia pentru ini?ializarea unei tabele de dispersie
HashTable initHashTable(int dim) {
    HashTable hashTable;
    // Aloc? memorie 
    hashTable.vector = (Nod**)malloc(sizeof(Nod*) * dim);
    // Seteaz? dimensiunea tabelei de dispersie
    hashTable.dimensiune = dim;
    // Ini?ializeaz? fiecare element din vector cu NULL, indicând c? lista este goal? la început
    for (int i = 0; i < dim; i++) {
        hashTable.vector[i] = NULL;
    }
    return hashTable;
}

// Func?ia pentru calcularea valorii hash a unei serii
int hash(int serie, int dim) {
    return serie % dim;
}

// Func?ia pentru inserarea unei ma?ini într-o tabel? de dispersie
void inserareInHT(HashTable* ht, Masina masina) {
    // Verifica?i dac? dimensiunea tabelei de dispersie este valid?
    if (ht->dimensiune > 0) {
        // Calcula?i pozi?ia din tabel? folosind func?ia hash
        int pozitie = hash(masina.serie, ht->dimensiune);
        // Verifica?i dac? pozi?ia calculat? este valid?
        if (pozitie >= 0 && pozitie < ht->dimensiune) {
            // Insereaz? ma?ina în lista corespunz?toare din tabelul de dispersie
            inserareLaFinal(&(ht->vector[pozitie]), masina);
        }
    }
}

// Func?ia pentru traversarea ?i afi?area con?inutului unei tabele de dispersie
void traversareHT(HashTable hashT) {
    // Parcurge?i fiecare pozi?ie din tabelul de dispersie
    for (int i = 0; i < hashT.dimensiune; i++) {
        // Afi?a?i num?rul de pozi?ie
        printf("\n Pozitie: %d", i);
        // Parcurge?i lista asociat? fiec?rei pozi?ii ?i afi?a?i ma?inile
        Nod* copie = hashT.vector[i];
        while (copie != NULL) {
            afisareMasina(copie->inf);
            copie = copie->next;
        }
    }
}

// Func?ia pentru eliberarea memoriei ocupate de o list?
void dezalocareLista(Nod* cap) {
    // Parcurge?i lista ?i dezaloca?i fiecare nod ?i produc?torul asociat ma?inii
    while (cap) {
        Nod* temp = cap;
        cap = cap->next;
        free(temp->inf.producator);
        free(temp);
    }
}

// Func?ia pentru c?utarea unei ma?ini într-o tabel? de dispersie dup? un criteriu dat
Nod* cautareDupaCriteriu(HashTable ht, int serieCautata) {
    // Calcula?i pozi?ia din tabelul de dispersie folosind func?ia hash
    int pozitie = hash(serieCautata, ht.dimensiune);
    // Verifica?i dac? pozi?ia calculat? este valid?
    if (pozitie >= 0 && pozitie < ht.dimensiune) {
        // Parcurge?i lista asociat? pozi?iei ?i c?uta?i ma?ina cu seria dorit?
        Nod* copie = ht.vector[pozitie];
        while (copie != NULL) {
            if (copie->inf.serie == serieCautata) {
                return copie;
            }
            copie = copie->next;
        }
    }
    return NULL;
}

// Func?ia pentru conversia de la o structur? la alta (lista simplu înl?n?uit? la tabel? de dispersie)
HashTable conversieLaAltaStructura(Nod* cap, int dimensiune) {
    // Ini?ializa?i o tabel? de dispersie cu dimensiunea specificat?
    HashTable ht = initHashTable(dimensiune);
    // Parcurge?i lista ?i insera?i fiecare ma?in? în tabelul de dispersie
    while (cap) {
        inserareInHT(&ht, cap->inf);
        cap = cap->next;
    }
    return ht;
}


void main() {
	HashTable hashT = initHashTable(10);
	inserareInHT(&hashT, initMasina("Renault", 1234));
	inserareInHT(&hashT, initMasina("Ford", 5678));
	inserareInHT(&hashT, initMasina("Ford", 5679));
	inserareInHT(&hashT, initMasina("Ford", 5677));
	inserareInHT(&hashT, initMasina("Ford", 5677));
	inserareInHT(&hashT, initMasina("Peugeot", 9101));
	inserareInHT(&hashT, initMasina("Ford", 5677));
	inserareInHT(&hashT, initMasina("Bmw", 1213));

	traversareHT(hashT);

	int serieCautata = 5679;
	Nod* rezultatCautare = cautareDupaCriteriu(hashT, serieCautata);
	if (rezultatCautare != NULL) {
		printf("\n\n Masina cu seria %d a fost gasita:", serieCautata);
		afisareMasina(rezultatCautare->inf);
	}
	else {
		printf("\n Ma?ina cu seria %d nu a fost gasita.", serieCautata);
	}

	// Dezalocarea memoriei ocupate de tabela de dispersie
	for (int i = 0; i < hashT.dimensiune; i++) {
		dezalocareLista(hashT.vector[i]);
	}
	free(hashT.vector);
}
