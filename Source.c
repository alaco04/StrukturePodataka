#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#define ERROR_OF -1
#define BUFFER_SIZE 1024

int count_rows(char* filename);


int main() {
	printf("Hello world");
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
	while (!foef(fp)) {
		fgets(buffer, BUFFER_SIZE, fp);
			++count;
	 }
	fclose(fp);
	return 0;
}