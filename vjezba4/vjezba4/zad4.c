
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MaxDegree 10

struct polinom;

typedef struct polinom* position;

struct polinom
{
	int Coeff;
	int Exp;
	position Next;
};


//void citajPol(position, char*);
void datUpis(position);
void ispisiPol(position);
void zbrojiPol(position, position, position);
void prodPol(position, position, position);
void unosK(position);
position traziZadnji(position);
void unosP(position);

int main()
{
	struct polinom	P1, P2, S, P;
	char c = 1;

	P1.Next = NULL;
	P2.Next = NULL;
	S.Next = NULL;
	P.Next = NULL;

	while (c != '0')
	{
		printf("\tA-unos 1.polinoma na pocetak\n\tB-unos 2.polinoma na pocetak\n\tC-Unos 1. polinoma na kraj\n\tD-Unos 2. polinoma na kraj\n\tE-upis 1. polinoma u datoteku\n\tF-upis 2. polinoma u datoteku\n\tG-ispis polinoma\n\tH-zbroj polinoma\n\tI-produkt polinoma\n\t0-izlaz\n");
		scanf(" %c", &c);

		switch (c)
		{
		case 'a':
		case 'A':
			unosP(&P1);
			break;
		case 'b':
		case 'B':
			unosP(&P2);
			break;
		case 'c':
		case 'C':
			unosK(&P1);
			break;
		case 'd':
		case 'D':
			unosK(&P2);
			break;
		case 'e':
		case 'E':
			datUpis(P1.Next);
			break;
		case 'f':
		case 'F':
			datUpis(P2.Next);
			break;
		case 'g':
		case 'G':
			ispisiPol(P1.Next);
			ispisiPol(P2.Next);
			break;
		case 'h':
		case 'H':
			zbrojiPol(P1.Next, P2.Next, &S);
			printf("Suma polinoma je:\n");
			ispisiPol(S.Next);
			break;
		case 'i':
		case 'I':
			prodPol(P1.Next, P2.Next, &P);
			printf("Produkt polinoma je:\n");
			ispisiPol(P.Next);
			break;
		case '0':
			printf("Kraj\n");
			break;
		default:
			printf("Krivi unos!\n");
		}

	}


	return 0;
}


void citajPol(position P, char* ime_dat)
{
	FILE* dat;
	position q, temp, prev;

	dat = fopen(ime_dat, "r");
	if (dat == NULL)
	{
		printf("Greska u otvaranju datoteke!!!");
		exit(1);
	}
	else
	{
		while (feof(dat) == 0)
		{
			q = (position)malloc(sizeof(struct polinom));

			fscanf(dat, " %d %d", &q->Coeff, &q->Exp);

			temp = P->Next;
			prev = P;
			while (temp != NULL && temp->Exp > q->Exp)
			{
				prev = temp;
				temp = temp->Next;
			}

			prev->Next = q;

			if (temp != NULL)
				q->Next = temp;
			else
				q->Next = NULL;
		}
	}


}

void ispisiPol(position P)
{

	printf("\n");

	//P = P->Next;

	while (P != NULL)
	{
		if (P->Coeff > 0)
			printf(" + %d*x^%d", P->Coeff, P->Exp);
		else
			printf("%d*x^%d", P->Coeff, P->Exp);
		P = P->Next;

		/*if (P->Next != NULL)
			printf("+");*/
	}


	printf("\n");

}

void zbrojiPol(position P1, position P2, position S)
{
	position q, temp;

	while (P1 != NULL && P2 != NULL)
	{
		q = (position)malloc(sizeof(struct polinom));
		q->Next = NULL;


		if (P1->Exp > P2->Exp)
		{
			q->Exp = P1->Exp;
			q->Coeff = P1->Coeff;
			P1 = P1->Next;
		}
		else if (P1->Exp < P2->Exp)
		{
			q->Exp = P2->Exp;
			q->Coeff = P2->Coeff;
			P2 = P2->Next;
		}
		else  // P1->Exp == P2->Exp
		{
			q->Exp = P1->Exp;
			q->Coeff = P1->Coeff + P2->Coeff;
			P1 = P1->Next;
			P2 = P2->Next;
		}
		S->Next = q;
		S = q;
	}

	if (P1 != NULL)
		temp = P1;
	else
		temp = P2;

	while (temp != NULL)
	{
		q = (position)malloc(sizeof(struct polinom));
		q->Next = NULL;
		q->Exp = temp->Exp;
		q->Coeff = temp->Coeff;
		S->Next = q;
		S = q;
		temp = temp->Next;
	}
}


void prodPol(position P1, position P2, position P)
{
	position q, first = P1, second = P2, temp, prev;
	int n;

	while (first != NULL)
	{
		second = P2;
		while (second != NULL)
		{
			temp = P->Next;
			prev = P;

			n = first->Exp + second->Exp;

			while (temp != NULL && temp->Exp > n)
			{
				prev = temp;
				temp = temp->Next;
			}

			if (temp != NULL && temp->Exp == n)
				temp->Coeff += first->Coeff * second->Coeff;
			else
			{
				q = (position)malloc(sizeof(struct polinom));

				q->Exp = n;
				q->Coeff = first->Coeff * second->Coeff;

				prev->Next = q;
				q->Next = temp;
			}

			second = second->Next;
		}
		first = first->Next;
	}

	while (P->Next != NULL)
	{
		if (P->Next->Coeff == 0)
		{
			temp = P->Next;
			P->Next = P->Next->Next;
			free(temp);
		}
		P = P->Next;
	}

}

void datUpis(position P)
{
	FILE* dat;
	char imeDat[10];

	printf("\nUnesi ime datoteke u koju zelis spremiti listu:");
	scanf(" %s", imeDat);

	dat = fopen(imeDat, "w");

	if (NULL == dat)
		printf("\n Greska u otvaranju datoteke");
	else
	{
		while (P != NULL)
		{
			fprintf(dat, "\n %d %d", P->Coeff, P->Exp);
			P = P->Next;
		}
		fclose(dat);
	}
}

void datUcitaj(position P)
{
	FILE* dat;
	char imeDat[10];
	position temp;

	printf("\nUnesi ime datoteke iz koje zelis procitati listu:");
	scanf(" %s", imeDat);

	dat = fopen(imeDat, "r");

	if (dat == NULL)
		printf("\n Ne postoji datoteke s tim imenom");
	else
	{
		while (feof(dat) == 0)
		{
			temp = (position)malloc(sizeof(struct polinom));

			fscanf(dat, " %d %d", temp->Coeff, temp->Exp);
			printf(" %d %d\n", temp->Coeff, temp->Exp);

			temp->Next = P->Next;
			P->Next = temp;
			P = temp;
		}

		fclose(dat);
	}
}

position traziZadnji(position P)
{
	while (P->Next != NULL)
		P = P->Next;

	return P;
}


void unosK(position P)
{
	position temp;
	temp = (position)malloc(sizeof(struct polinom));
	printf("\nUnesite koeficijent i eksponent:\n");
	scanf(" %d %d", &temp->Coeff, &temp->Exp);

	P = traziZadnji(P);
	temp->Next = P->Next;
	P->Next = temp;

}

void unosP(position P) {
	position temp;

	temp = (position)malloc(sizeof(struct polinom));
	printf("Unesite koeficijent i eksponent:\n");
	scanf(" %d %d", &temp->Coeff, &temp->Exp);
	temp->Next = P->Next;
	P->Next = temp;
}
