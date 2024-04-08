#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Masina Masina;
typedef struct Nod Nod;
typedef struct LDI LDI;

struct Masina {
	char* producator;
	int serie;
};

struct Nod {
	Masina inf;
	Nod* next;
	Nod* prev;
};

struct LDI {
	Nod* prim;
	Nod* ultim;
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

void inserareLaInceput(Masina masina, LDI* ldi) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->prev = NULL;
	nou->next = ldi->prim;
	if (ldi->prim) {
		ldi->prim->prev = nou;
		ldi->prim = nou;
	}
	else {
		ldi->ultim = nou;
		ldi->prim = nou;
	}
}

void inserareLaFinal(Masina masina, LDI* ldi) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->prev = ldi->ultim;
	nou->next = NULL;
	if (ldi->ultim) {
		ldi->ultim->next = nou;
		ldi->ultim = nou;
	}
	else {
		ldi->ultim = nou;
		ldi->prim = nou;
	}
}

void traversareLista(LDI lista, int* nrMasini) {
	while (lista.prim) {
		afisareMasina(lista.prim->inf);
		(*nrMasini)++;
		lista.prim = lista.prim->next;
	}
}

void dezalocare(LDI* lista) {
	Nod* copie = lista->prim;
	while (copie) {
		free(copie->inf.producator);
		copie = copie->next;
		if (copie) {
			free(copie->prev);
		}
	}
	free(lista->ultim);
	lista->prim = lista->ultim = NULL;
}

void conversieLaVector(LDI lista, Masina** vectorMasini) {
	int nrMasini = 0;
	while (lista.prim) {
		(*vectorMasini)[nrMasini] = initMasina(lista.prim->inf.producator, lista.prim->inf.serie);
		nrMasini++;
		lista.prim = lista.prim->next;
	}
}

//void traversareListaCirculara(LDI lista) {
//	Nod* aux = lista.prim;
//	while (aux->next != lista.prim) {
//		afisareMasina(aux->inf);
//		aux = aux->next;
//	}
//	afisareMasina(aux->inf);
//}

void traversareListaCirculara(LDI lista) {
	Nod* aux = lista.prim;
	do {
		afisareMasina(aux->inf);
		aux = aux->next;
	} while (aux != lista.prim);
}

// Functia pentru cautarea unei masini dupa producator
Nod* cautareMasinaDupaProducator(LDI lista, char* producator) {
	Nod* current = lista.prim;
	while (current) {
		if (strcmp(current->inf.producator, producator) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL; // Returneaza NULL daca nu gaseste masina cu producatorul dat
}

// Functia pentru stergerea tuturor masinilor cu un anumit producator
void stergereMasiniDupaProducator(LDI* lista, char* producator) {
	// Se initializeaza un pointer catre primul nod al listei
	Nod* current = lista->prim;
	// Se parcurge lista pana la final sau pana cand se gasesc toate masinile cu producatorul dat
	while (current) {
		// Daca producatorul masinii curente coincide cu producatorul dat
		if (strcmp(current->inf.producator, producator) == 0) {
			// Se verifica daca masina curenta este primul nod al listei
			if (current == lista->prim) {
				lista->prim = current->next; // Actualizarea primului nod al listei
			}
			// Se verifica daca masina curenta este ultimul nod al listei
			if (current == lista->ultim) {
				lista->ultim = current->prev; // Actualizarea ultimului nod al listei
			}
			// Se actualizeaza legaturile intre nodurile adiacente
			if (current->prev) {
				current->prev->next = current->next; // Se elimina legatura spre nodul anterior
			}
			if (current->next) {
				current->next->prev = current->prev; // Se elimina legatura spre nodul urmator
			}
			// Se pastreaza adresa nodului curent intr-un nod temporar pentru a evita pierderea referintei
			Nod* temp = current;
			current = current->next; // Se trece la urmatorul nod
			// Se elibereaza memoria alocata pentru producatorul masinii si pentru nodul insusi
			free(temp->inf.producator);
			free(temp);
		}
		else {
			current = current->next; // Se trece la urmatorul nod din lista
		}
	}
}

// Functia pentru conversia listei de masini intr-un vector de masini
Masina* conversieLaVector2(LDI lista, int* size) {
	int len = 0;
	Nod* current = lista.prim;
	while (current) {
		len++;
		current = current->next;
	}
	*size = len;
	Masina* vector = (Masina*)malloc(len * sizeof(Masina));
	current = lista.prim;
	int i = 0;
	while (current) {
		vector[i++] = current->inf;
		current = current->next;
	}
	return vector;
}

// Functia pentru traversarea listei de la sfarsit la inceput
void traversareInversa(LDI lista, int* nrMasini) {
	Nod* current = lista.ultim;
	while (current) {
		afisareMasina(current->inf);
		(*nrMasini)++;
		current = current->prev;
	}
}


void main() {
	LDI lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	inserareLaInceput(initMasina("Ford", 1234), &lista);
	inserareLaInceput(initMasina("Renault", 5678), &lista);
	inserareLaInceput(initMasina("Mercedes", 9101), &lista);
	inserareLaFinal(initMasina("Bmw", 1112), &lista);

	int nrMasini = 0;
	traversareLista(lista, &nrMasini);

	Masina* vectorMasini = (Masina*)malloc(sizeof(Masina) * nrMasini);
	conversieLaVector(lista, &vectorMasini);
	printf("\n Afisare masini din vector:");
	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(vectorMasini[i]);
		free(vectorMasini[i].producator);
	}
	free(vectorMasini);

	//dezalocare(&lista);

	/*lista.ultim->next = lista.prim;
	lista.prim->prev = lista.ultim;
	traversareListaCirculara(lista);*/

	/*printf("\n\nConversie la vector:\n");
	Masina* vectorMasini2;
	int size;
	vectorMasini2 = conversieLaVector2(lista, &size);
	for (int i = 0; i < size; i++) {
		afisareMasina(vectorMasini2[i]);
	}
	free(vectorMasini2);*/

	printf("\n\nCautare masina cu producatorul \"Renault\":\n");
	Nod* masinaCautata = cautareMasinaDupaProducator(lista, "Renault");
	if (masinaCautata) {
		afisareMasina(masinaCautata->inf);
	}
	else {
		printf("Masina nu a fost gasita.\n");
	}

	printf("\n\nStergere masini cu producatorul \"Ford\":\n");
	stergereMasiniDupaProducator(&lista, "Ford");
	traversareLista(lista, &nrMasini);

	printf("\n\nAfisare lista invers:\n");
	traversareInversa(lista, &nrMasini);

	dezalocare(&lista);

	return 0;
}