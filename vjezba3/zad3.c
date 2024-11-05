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
position find_prev(position head, char* lname);
position find_lastname(position head, char* lname);
int delete(position head, char* lname);
int add_after(position head, char* prev_lname, char* fname, char* lname, int birth_year);
int add_before(position head, char* next_lname, char* fname, char* lname, int birth_year);
int sort(position head);
int write_file(position head);
int read_file(position head);


int main() {
	person head = { .fname = "", .lname = "", .birth_year = 0, .next = NULL };
	char fname[50], lname[50];
	int birth_year;
	int izbor = 1;

	while (izbor != 0) {

		printf("\nIzaberi:\n");
		printf("1 - dodaj novi element na pocetak liste\n");
		printf("2 - ispis liste\n");
		printf("3 - dodaj novi element na kraj liste\n");
		printf("4 - pronadi element u listi (po prezimenu)\n");
		printf("5 - obrisi odredeni element iz liste\n");
		printf("6 - dinamicki dodaj novi element iza odredenog elementa\n");
		printf("7 - dinamicki dodaj novi element ispred odreðenog elementa\n");
		printf("8 - sortiraj listu po prezimenima osoba\n");
		printf("9 - upisi listu u datoteku\n");
		printf("10 - citaj listu iz datoteke\n");
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

		else if (izbor == 2) {
			printf("\nLista osoba:\n");
			print_list(head.next);
		}

		else if (izbor == 3) {
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

		else if (izbor == 6) {
			char prez[50];
			printf("\nUnesite prezime osobe iza koje zelite dodati novu osobu: ");
			scanf(" %s", prez);
			printf("Unesite ime: ");
			scanf(" %s", fname);
			printf("Unesite prezime: ");
			scanf(" %s", lname);
			printf("Unesite godinu rodenja: ");
			scanf("%d", &birth_year);
			add_after(&head, prez, fname, lname, birth_year);
		}
		else if (izbor == 7) {
			char prez[50];
			printf("\nUnesite prezime osobe ispred koje zelite dodati novu osobu: ");
			scanf(" %s", prez);
			printf("Unesite ime: ");
			scanf(" %s", fname);
			printf("Unesite prezime: ");
			scanf(" %s", lname);
			printf("Unesite godinu rodenja: ");
			scanf("%d", &birth_year);
			add_before(&head, prez, fname, lname, birth_year);
		}

		else if (izbor == 8) {
			sort(&head);
		}

		else if (izbor == 9) {
			write_file(&head); 
		}

		else if (izbor == 10) {
			read_file(&head); 
		}

		else if (izbor == 0) {
			printf("Izlaz iz programa.\n");
			break;
		}

		else {
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
	new_person->next = NULL;

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
	new_person->next = temp;
	head->next = new_person;

	return 0;
}

int print_list(position first) {
	position temp = first;

	while (temp != NULL) {
		printf("%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
		temp = temp->next;
	}

	return 0;
}

int append_list(position head, char* fname, char* lname, int birth_year) {
	position new_person = NULL;
	position last = NULL;

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

	while (temp->next) {
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

position find_prev(position head, char* lname) {

	for (position temp = head; temp->next; temp = temp->next) {
		if (!strcmp(lname, temp->next->lname)) {
			return temp;
		}
	}

	return NULL;
}

int delete(position head, char* lname) {
	position prev = NULL;
	position to_delete = NULL;

	prev = find_prev(head, lname);
	if (prev->next == NULL) {
		printf("Osoba s prezimenom %s nije pronadena.\n", lname);
		return -1;
	}

	to_delete = prev->next; 
	prev->next = to_delete->next; 
	free(to_delete);

	printf("Osoba s prezimenom %s je obrisana.\n", lname);
	return 0;
}

int add_after(position head, char* prev_lname, char* fname, char* lname, int birth_year ) {
	position prev_person = find_lastname(head, prev_lname);

	if (!prev_person) {
		printf("Osoba nije pronadena\n");
		return -1;
	}

	position newperson = create_person(fname, lname, birth_year);
	
	newperson->next = prev_person->next; 
	prev_person->next = newperson;

	return 0;
}

int add_before(position head, char* next_lname, char* fname, char* lname, int birth_year) {
	position prev = find_prev(head, next_lname);

	if (!prev) {
		printf("Osoba s prezimenom nije pronadena.\n");
		return -1;
	}

	position newperson = create_person(fname, lname, birth_year); 
	newperson->next = prev->next; 
	prev->next = newperson;

	return 0;
}

int sort(position head) {
	position i, j, prev_j, temp, end; 
	end = NULL; 
	i = head; 

	while (i->next != end)  
	{
		prev_j = i; 
		j = i->next; 
		while (j->next != end) 
		{
			if (strcmp(j->lname, j->next->lname) > 0) 
			{
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;
				j = temp; 
			}
			prev_j = j; 
			j = j->next; 
		}
		end = j; 
	}
	return 0;
}

int write_file(position head) {
	position temp = head->next;
	FILE* fp; 
	char filename[10]; 

	printf("\nUnesi ime datoteke:");
	scanf(" %s", filename);

	fp = fopen(filename, "w"); 

	if (NULL == fp) 
		printf("\n Greska u otvaranju datoteke");
	else
	{
		while (temp != NULL) 
		{
			fprintf(fp, "\n %s %s %d", temp->fname, temp->lname, temp->birth_year); 
			temp = temp->next;  
		}
		fclose(fp);
	}
}

int read_file(position head) {
	FILE* fp; 
	char filename[10]; 
	position temp;

	printf("\nUnesi ime datoteke iz koje zelis procitati listu:");
	scanf(" %s", filename); 

    fp = fopen(filename, "r"); 
	char fname[50], lname[50]; 
	int birth_year; 

	if (fp == NULL) {
		printf("\n Ne postoji datoteke s tim imenom");
		return -1;
	}

	else
	{
		printf("Lista koja se nalazi u datoteki:\n");
		while (feof(fp) == 0) 
		{
			fscanf(fp, " %s %s %d", fname, lname, &birth_year); 
			printf("%s %s %d\n", fname, lname, birth_year);
		}
	
		fclose(fp); 
	}
}