#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*2. Definirati strukturu osoba (ime, prezime, godina rodenja) i napisati program koji:
A. dinamicki dodaje novi element na pocetak liste,
B. ispisuje listu,
C. dinamicki dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. brise odredeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.
*/

struct _osoba;
typedef struct _osoba* pozicija;
typedef struct _osoba
{
	char ime[50], prezime[50];
	int godinaR;
	pozicija next;
}osoba;

pozicija inicijalizacija();
int dodajNaPocetak(pozicija);
int ispis(pozicija);
int dodajNaKraj(pozicija);
int pronadjiPrezime(pozicija);
int izbrisiElement(pozicija);
int oslobodiMemoriju(pozicija);
pozicija pronadjiPrethodni(pozicija,char*);

int main()
{
	pozicija head = NULL;
	int izbor = 0, uvjet=1;

	head = inicijalizacija(head);

	while (uvjet)
	{
		printf("Unesi 1 za dodavanje na pocetak, 2 za ispis, 3 za dodavanje na kraj, 4 za pronaci prezime,5 za izbrisati element ili 6 za izaci iz petlje: ");
		scanf("%d", &izbor);

		switch (izbor)
		{

			case 1:
				dodajNaPocetak(head);
				break;
			
			case 2:
				ispis(head->next);
				break;

			case 3:
				dodajNaKraj(head);
				break;

			case 4:
				pronadjiPrezime(head->next);
				break;

			case 5:
				izbrisiElement(head);
				break;

			case 6:
				uvjet = 0;
				break;
		}


	}
	
	printf("\nOslobadjanje memorije...\n....\n....\n");
	oslobodiMemoriju(head);
	ispis(head->next);

	return 0;
}


pozicija inicijalizacija(pozicija p)
{
	p = (pozicija)malloc(sizeof(osoba));

	if (p==NULL)
	{
		printf("GRESKA U INICIJALIZACIJI!\n");
		return NULL;
	}

	strcpy(p->ime, "");
	strcpy(p->prezime, "");
	p->godinaR = 0;
	p->next = NULL;

	return p;
}

int dodajNaPocetak(pozicija p)
{
	pozicija q = NULL;
	q = inicijalizacija(q);

	printf("Unesi ime osobe: ");
	scanf("%s", q->ime);
	printf("Unesi prezime osobe: ");
	scanf("%s", q->prezime);
	printf("Unesi godinu rodjenja osobe: ");
	scanf("%d", &q->godinaR);

	q->next = p->next;
	p->next = q;


	return 0;
}

int ispis(pozicija p)
{
	if (p == NULL)
	{
		printf("LISTA JE PRAZNA!\n");
	}

	while (p != NULL)
	{
		printf("%s %s %d\n", p->ime, p->prezime, p->godinaR);
		p = p->next;
	}

	return 0;
}

int dodajNaKraj(pozicija p)
{
	pozicija q = NULL;

	while (p->next != NULL)
	{
		p = p->next;
	}

	q = inicijalizacija(q);

	printf("Unesi ime osobe: ");
	scanf("%s", q->ime);
	printf("Unesi prezime osobe: ");
	scanf("%s", q->prezime);
	printf("Unesi godinu rodjenja osobe: ");
	scanf("%d", &q->godinaR);

	q->next = p->next;
	p->next = q;


	return 0;
}

int pronadjiPrezime(pozicija p) 
{
	char trazenoPrezime[50] = { 0 };

	printf("Unesi prezime koje zelis pronaci:\n");
	scanf(" %s", trazenoPrezime);

	while (p != NULL && strcmp(p->prezime, trazenoPrezime)!=0)
	{
		p = p->next;
	}

	if (p == NULL)
	{
		printf("NE POSTOJI TAKVO PREZIME U LISTI!\n");
		return -1;
	}

	printf("Trazeno prezime nalazi se na adresi %d.\n", p);

	return 0;
}

int izbrisiElement(pozicija p) 
{
	pozicija prethodni = NULL;
	pozicija trenutni = NULL;

	char obrisiP[50] = { 0 };


	printf("Prezime koje zelis izbrisati: ");
	scanf(" %s", obrisiP);

	prethodni = pronadjiPrethodni(p, obrisiP);

	if (prethodni == NULL)
	{
		printf("GRESKA, NE POSTOJI UNESENO PREZIME!\n");
		return -1;
	}

	trenutni = prethodni->next;
	prethodni->next = trenutni->next;
	free(trenutni);

	return 0;
}

int oslobodiMemoriju(pozicija p)
{
	pozicija temp = NULL;
	
	while (p->next != NULL)
	{
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}

	return 0;
}

pozicija pronadjiPrethodni(pozicija p, char* prez)
{
	pozicija prev = NULL, curr = NULL;

	prev = p;
	curr = p->next;

	while (curr != NULL && strcmp(curr->prezime, prez) != 0)
	{
		prev = curr;
		curr = curr->next;
	}

	if (curr == NULL)
	{
		printf("GRESKA!\n");
		return -1;
	}

	return prev;
}