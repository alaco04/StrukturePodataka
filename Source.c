#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#define ERROR_OF -1
#define BUFFER_SIZE 1024

int count_rows(char* filename);
//void ispis(int n, char* filename);

typedef struct {
	char ime[50];
	char prezime[50];
	int bodovi;
}Student;


int main() {
	int n,i,max;
	
	n = count_rows("Studenti.txt");
	Student* studenti = NULL;
	studenti = (Student*)malloc(n * sizeof(Student));
	//ispis(n, "Studenti.txt");

	int i;
	double rel;
	printf("Unesite maksimalan broj bodova: ");
	scanf("%d", &max);

	FILE* fp = NULL;
	fp = fopen("Studenti.txt", "r");
	if (fp == NULL) {
		printf("Error opening file\n");
		return ERROR_OF;
	}


	for (i = 0;i < n;i++) {
		rel = (double)studenti[i].bodovi / max;
		fscanf(fp, "%s %s %d",studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
	}
	fclose(fp);

	for (i = 0;i < n;i++) {
		rel = (double)studenti[i].bodovi / max;
		printf("%s %s %d %f\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, rel * 100);
	}

	free(studenti);
	return 0;
}

int count_rows(char* filename) {
	FILE* fp = NULL;
	char buffer[BUFFER_SIZE];
	int count = 0;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error opening file\n");
		return ERROR_OF;
	}
	while (!feof(fp)) {
		fgets(buffer, BUFFER_SIZE, fp);
			++count;
	 }
	fclose(fp);
	return count;
}

