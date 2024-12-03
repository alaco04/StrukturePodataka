#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct cvor* position;
typedef struct cvor {

    int broj;
    position next;

}cvor;

int dodajelement(position head, int a);
int ucitaj(const char* filename, position head);
int operacije(position head, char operacija);
void ispis(position head);

int main() {

    position head = (position)malloc(sizeof(cvor));
    if (head == NULL) {
        printf("Greska prilikom alokacije\n");
        return -1;
    }
    head->next = NULL;

    ucitaj("postfiks.txt", head);
    ispis(head);




    return 0;
}

int dodajelement(position head, int a) {
    position novi = (position)malloc(sizeof(cvor));
    if (novi == NULL) {
        printf("Greska u alokaciji\n");
        return -1;
    }
    novi->broj = a;
    novi->next = head->next;
    head->next = novi;

    return EXIT_SUCCESS;
}

int ucitaj(const char* filename, position head) {

    FILE* fp = NULL;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Greska u otvaranju\n");
        return -1;
    }
    char buffer[1024];
    int number;
    int bytes;
    char operacija;
    int offset = 0;
    fgets(buffer, sizeof(buffer), fp);
    while (1) {
        if (sscanf(buffer + offset, "%d %n", &number, &bytes) == 1) {
            dodajelement(head, number);
            offset = offset + bytes;
        }
        else if (sscanf(buffer + offset, "%c%n", &operacija, &bytes) == 1) {
            offset = offset + bytes;
            operacije(head, operacija);

        }
        else {
            break;
        }

    }

    return EXIT_SUCCESS;
}

int operacije(position head, char operacija) {
    position trenutni = head->next;


    if (trenutni == NULL || trenutni->next == NULL) {
        printf("Nema dovoljno elemenata\n");
        return -1;
    }


    switch (operacija) {
    case '+':
        trenutni->next->broj += trenutni->broj;
        head->next = head->next->next;
        free(trenutni);
        break;

    case '-':
        trenutni->next->broj -= trenutni->broj;
        head->next = head->next->next;
        free(trenutni);
        break;

    case '*':
        trenutni->next->broj *= trenutni->broj;
        head->next = head->next->next;
        free(trenutni);
        break;

    case '/':
        if (trenutni->broj == 0) {
            printf("Greška: dijeljenje s nulom!\n");
            return -1;
        }
        trenutni->next->broj /= trenutni->broj;
        head->next = head->next->next;
        free(trenutni);
        break;

    default:
        printf("Nepoznata operacija\n");
        return -1;
    }

    return EXIT_SUCCESS;
}


void ispis(position head) {
    position temp = head->next;
    while (temp != NULL) {
        printf("%d", temp->broj);
        temp = temp->next;

    }
    return EXIT_SUCCESS;
}