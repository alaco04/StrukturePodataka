#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR_OF -1
#define BUFFER_SIZE 1024

int count_rows(char* filename);
void stvori(); 

typedef struct {
	char ime[50];
	char prezime[50];
	int bodovi;
}Student;


int main() {
	int n, i, max;
	stvori(); 
	n = count_rows("Studenti.txt");
	
	Student* studenti=(Student*)malloc(n * sizeof(Student));

	
	printf("Unesite maksimalan broj bodova: ");
	scanf("%d", &max);

	FILE* fp = fopen("Studenti.txt", "r");
	if (fp == NULL) {
		printf("Error opening file\n");
		return ERROR_OF;
	}


	for (i = 0;i < n;i++) {
		fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
	}
	fclose(fp);

	for (i = 0;i < n-1;i++) {
		double rel = (double)studenti[i].bodovi / max*100;
		printf("%s %s %d %f\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, rel);
	}

	free(studenti);
	return 0;
}

void stvori() {
	char ime[50]; 
	char prezime[50];
	int bodovi;
	int i = 0;

	FILE* fp = fopen("Studenti.txt", "w");
	if (fp == NULL) {
		printf("Error creating file\n");
		return ERROR_OF;
	}

	while (1) {
		printf("Unesite ime %d. studenta:\n ",i+1);
		scanf("%s", ime);

		if (strcmp(ime, "stvori") == 0) {
			break;
		}
		printf("Unesite prezime %d. studenta:\n ",i+1);
		scanf("%s", prezime);

		printf("Unesite bodove %d. studenta:\n ", i+1); 
		scanf("%d", &bodovi);
		fprintf(fp, "%s %s %d\n", ime, prezime, bodovi);
		i++;
	}

	fclose(fp); 
	
}


int count_rows(char* filename) {
	FILE* fp = NULL;
	char buffer[BUFFER_SIZE];
	int count = 0;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error opening file\n");
		return;
	}
	while (!feof(fp)) {
		fgets(buffer, BUFFER_SIZE, fp);
		++count;
	}
	fclose(fp);
	return count;
}
