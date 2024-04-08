#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina {
	long id;
	char* producator;
	int serie;
};

struct Nod {
	Masina inf;
	Nod* next;
};

void afisareMasina(Masina masina) {
	printf("\n%ld. Masina %s are seria %d.", masina.id, masina.producator, masina.serie);
}

Masina initMasina(long id, const char* producator, int serie) {
	Masina masinaNoua;
	masinaNoua.serie = serie;
	masinaNoua.id = id;
	masinaNoua.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(masinaNoua.producator, producator);

	return masinaNoua;
}

void push(Nod** cap, Masina masina) { // Func?ie pentru ad?ugarea unei ma?ini la începutul unei structuri de tip stiv?
	Nod* nou = (Nod*)malloc(sizeof(Nod)); // Alocarea memoriei pentru un nou nod
	nou->inf = masina; // Salvarea ma?inii în noul nod
	nou->next = *cap; // Setarea adresei urm?toare a noului nod c?tre vârful stivei
	*cap = nou; // Actualizarea vârfului stivei cu noul nod
}

void put(Nod** cap, Masina masina) { // Func?ie pentru ad?ugarea unei ma?ini la sfâr?itul unei structuri de tip coad?
	Nod* nou = (Nod*)malloc(sizeof(Nod)); // Alocarea memoriei pentru un nou nod
	nou->inf = masina; // Salvarea ma?inii în noul nod
	nou->next = NULL; // Ini?ializarea adresei urm?toare a noului nod cu NULL

	if ((*cap) != NULL) { // Verificarea dac? coada nu este goal?
		Nod* aux = *cap; // Declara?ia unui pointer auxiliar pentru parcugerea cozii
		while (aux->next) { // Parcurgerea cozii pân? la ultimul nod
			aux = aux->next; // Deplasarea pointerului c?tre urm?torul nod
		}
		aux->next = nou; // Legarea noului nod la sfâr?itul cozii
	}
	else {
		*cap = nou; // Dac? coada este goal?, noul nod devine primul nod al cozii
	}
}

Masina pop(Nod** varf) { // Func?ie pentru extragerea unei ma?ini din vârful unei stive
	Masina masina; // Declara?ia unei variabile pentru a stoca ma?ina extras?
	masina.id = -1; // Ini?ializarea identificatorului ma?inii cu o valoare nevalid?
	masina.serie = -1; // Ini?ializarea seriei ma?inii cu o valoare nevalid?
	masina.producator = NULL; // Ini?ializarea numelui produc?torului ma?inii cu NULL

	if (*varf) { // Verificarea dac? stiva nu este goal?
		masina = (*varf)->inf; // Salvarea ma?inii din vârful stivei în variabila local?
		Nod* temp = *varf; // Salvarea adresei vârfului stivei într-un pointer temporar
		(*varf) = (*varf)->next; // Mutarea vârfului stivei c?tre urm?torul nod
		free(temp); // Dezalocarea memoriei ocupate de fostul vârf al stivei
	}
	return masina; // Returnarea ma?inii extrase
}

//La fel ca la pop pentru stiva
Masina get(Nod** cap) {
	Masina masina;
	masina.id = -1;
	masina.serie = -1;
	masina.producator = NULL;
	if (*cap) {
		masina = (*cap)->inf;
		Nod* temp = *cap;
		*cap = (*cap)->next;
		free(temp);
	}
	return masina;
}


Masina cautareDupaId(Nod** stiva, long id) { // Func?ie pentru c?utarea unei ma?ini într-o stiv? dup? ID
	Masina masina; // Declara?ia unei variabile pentru a stoca ma?ina c?utat?
	masina.id = -1; // Ini?ializarea identificatorului ma?inii cu o valoare nevalid?
	masina.serie = -1; // Ini?ializarea seriei ma?inii cu o valoare nevalid?
	masina.producator = NULL; // Ini?ializarea numelui produc?torului ma?inii cu NULL
	Nod* stivaAuxiliara = NULL; // Ini?ializarea unei stive auxiliare pentru a memora nodurile extrase din stiv?

	while ((*stiva) != NULL && (*stiva)->inf.id != id) { // Parcurgerea stivei ?i a extragerii nodurilor pân? la g?sirea ma?inii cu ID-ul dorit
		push(&stivaAuxiliara, pop(stiva)); // Extrage nodul din stiv? ?i adaug?-l la stiva auxiliar?
	}
	if (*stiva) { // Verificarea dac? ma?ina a fost g?sit? în stiv?
		masina = pop(stiva); // Extrage ma?ina din vârful stivei
	}
	while (stivaAuxiliara) { // Reintroduce nodurile extrase anterior înapoi în stiv?
		push(stiva, pop(&stivaAuxiliara)); // Extrage nodul din stiva auxiliar? ?i adaug?-l înapoi în stiv?
	}
	return masina; // Returnarea ma?inii c?utate
}

Masina cautareDupaProducator(Nod** cap, const char* producatorCautat) {
	Masina masinaGasita;
	masinaGasita.id = -1;
	masinaGasita.serie = -1;
	masinaGasita.producator = NULL;

	Nod* current = *cap;
	while (current) {
		if (strcmp(current->inf.producator, producatorCautat) == 0) {
			masinaGasita = current->inf;
			break;
		}
		current = current->next;
	}

	return masinaGasita;
}


void main() {
	Nod* stiva = NULL;
	Masina masina;
	push(&stiva, initMasina(1, "Renault", 1234));
	push(&stiva, initMasina(2, "Ford", 5678));
	push(&stiva, initMasina(3, "Ford", 5679));
	push(&stiva, initMasina(4, "Ford", 5677));
	push(&stiva, initMasina(5, "Peugeot", 9101));
	push(&stiva, initMasina(6, "Bmw", 1213));

	Masina masinaCautata = cautareDupaId(&stiva, 3);
	afisareMasina(masinaCautata);
	free(masinaCautata.producator);

	printf("\n Stiva:");
	while (stiva) {
		masina = pop(&stiva);
		afisareMasina(masina);
		free(masina.producator);
	}



	Nod* coada = NULL;
	put(&coada, initMasina(1, "Renault", 1234));
	put(&coada, initMasina(2, "Ford", 5678));
	put(&coada, initMasina(3, "Ford", 5679));
	put(&coada, initMasina(4, "Ford", 5677));
	put(&coada, initMasina(5, "Peugeot", 9101));
	put(&coada, initMasina(6, "Bmw", 1213));

	printf("\n Coada:");
	while (coada) {
		masina = get(&coada);
		afisareMasina(masina);
		free(masina.producator);
	}

	Masina masinaCautata2 = cautareDupaProducator(&coada, "Ford");
	if (masinaCautata2.id != -1) {
		printf("\n Masina Ford gasita:");
		afisareMasina(masinaCautata2);
		free(masinaCautata2.producator);
	}
	else {
		printf("\n Masina Ford nu a fost gasita.");
	}
}