#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _person;
typedef struct _person* position;

typedef struct _person {
	char fname[50], lname[50];
	int birth_year;
	position next;
}person;

position create_person(char* fname, char* lname, int birth_year);
int prepend_list(position head, char* fname, char* lname, int birth_year);
int print_list(position first);
position find_last(position head);
int append_list(position head, char* fname, char* lname, int birth_year);
position find_lastname(position head, char* lname);
int delete(position head, char* lname);

int main() {
	person head = { .fname = "", .lname = "", .birth_year = 0, .next = NULL };
	char fname[50], lname[50];
	int birth_year;
	int izbor=1; 

	while (izbor != 0){
		
		printf("\nIzaberi:\n");
		printf("1 - dodaj novi element na pocetak liste\n");
		printf("2 - ispis liste\n");
		printf("3 - dodaj novi element na kraj liste\n");
		printf("4 - pronadi element u listi (po prezimenu)\n");
		printf("5 - obrisi odredeni element iz liste\n");
		printf("0 - Izlaz\n");
		scanf("%d", &izbor);

		
		if (izbor == 1) {
			printf("\nUnesite ime: ");
			scanf(" %49s", fname);
			printf("Unesite prezime: ");
			scanf(" %49s", lname);
			printf("Unesite godinu rodenja: ");
			scanf("%d", &birth_year);
			prepend_list(&head, fname, lname, birth_year);
		}

		else if(izbor==2){
			printf("\nLista osoba:\n");
			print_list(head.next);
		}

		else if(izbor==3){
			printf("\nUnesite ime: ");
			scanf(" %s", fname);
			printf("Unesite prezime: ");
			scanf(" %s", lname);
			printf("Unesite godinu rodenja: ");
			scanf("%d", &birth_year);
			append_list(&head, fname, lname, birth_year);
		}
		

		else if (izbor == 4) {
			printf("\nUnesite prezime za pretragu: ");
			scanf(" %s", lname);
			position osoba = find_lastname(&head, lname);
			if (osoba) {
				printf("\nPronadena osoba: %s %s %d\n", osoba->fname, osoba->lname, osoba->birth_year);
			}
			else {
				printf("\nOsoba s prezimenom %s nije pronadena.\n", lname);
			}
		}

		else if (izbor == 5) {
			printf("\nUnesite prezime za brisanje: ");
			scanf(" %s", lname);
			delete(&head, lname);
		}

		else if (izbor == 0) {
			printf("Izlaz iz programa.\n");
			break;
		}

		else{
			printf("Neispravan unos. Pokusajte ponovo.\n");
		}
	} 

	return 0;

}

position create_person(char* fname, char* lname, int birth_year) {
	position new_person = NULL;

	new_person = (position)malloc(sizeof(person));
	if (!new_person) {
		printf("\nNije uspjesno malociranje\n");
		return NULL;
	}
	strcpy(new_person->fname, fname);
	strcpy(new_person->lname, lname);
	new_person->birth_year = birth_year;
	new_person->next =NULL;

	return new_person;
}


int prepend_list(position head, char* fname, char* lname, int birth_year) {
	position new_person = NULL;
	position temp;
	new_person = create_person(fname, lname, birth_year);


	if (!new_person) {
		return -1;
	}
	temp = head->next;
	new_person->next=temp;
	head->next = new_person;

	return 0;
}

int print_list(position first) {
	position temp = first;

	while (temp != NULL) {
		printf("%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
		temp = temp->next;
	}

	return temp;
}

int append_list(position head, char* fname, char* lname, int birth_year) {
	position new_person = NULL;
	position last=NULL;

	new_person = create_person(fname, lname, birth_year);

	if (!new_person) {
		return -1;
	}

	last = find_last(head);
	last->next = new_person;
	new_person->next = NULL;

	return 0;
}

position find_last(position head)
{
	position temp = head;

	while (temp->next){
		temp = temp->next;
	}

	return temp;
}

position find_lastname(position head, char* lname) {
	position temp = head->next;

	while (temp != NULL) {
		if (strcmp(temp->lname, lname) == 0) {
			return temp;
		}
		temp = temp->next;
	}

	return NULL;
}

int delete(position head, char* lname) {
	position temp = head;


	while (temp->next != NULL && strcmp(temp->next->lname, lname) != 0) {
		temp = temp->next;
	}

	if (temp->next == NULL) {
		printf("Osoba s prezimenom %s nije pronadena.\n", lname);
		return -1;
	}

	position to_delete = temp->next;
	temp->next = to_delete->next;
	free(to_delete);

	printf("Osoba s prezimenom %s je obrisana.\n", lname);
	return 0;
}