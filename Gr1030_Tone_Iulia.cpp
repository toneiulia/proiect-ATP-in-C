#include<stdio.h>
#include<string.h>

typedef struct {
	int is;
	int cod;
	char denumire[20];
	char gama[20];
	float pret;
	int cantitate;
	struct data {
		int zi;
		int luna;
		int an;
	}data;
}com;

int nr_art(FILE *f, int p)
{
	int l, m;
	l = ftell(f);
	fseek(f, 0, 2);
	m = ftell(f) / p;
	fseek(f, l, 0);
	return m;
}

void creare()
{
	FILE *f;
	com a;
	int n, i;
	char nume_f[20];
	printf("\nNume fisier: ");
	gets_s(nume_f);
	f = fopen(nume_f, "wb+");
	printf("n= "); scanf_s("%d", &n);
	while (!feof(stdin))
	{
		if (n > nr_art(f, sizeof(com)))
		{
			fseek(f, 0, SEEK_END);
			a.is = 0;
			for (i = nr_art(f, sizeof(com)); i < n; i++)
				fwrite(&a, sizeof(com), 1, f);
			fseek(f, (n - 1) * sizeof(com), 0);
			a.is = 1;
			a.cod = n;
			printf("Denumire produs: "); getc(stdin); gets_s(a.denumire);
			printf("Gama: "); gets_s(a.gama);
			printf("Pret: "); scanf_s("%f", &a.pret);
			printf("Cantitate: "); scanf_s("%d", &a.cantitate);
			printf("Data livrarii: ");
			scanf("%d %d %d", &a.data.zi, &a.data.luna, &a.data.an);
			fwrite(&a, sizeof(com), 1, f);
		}
		else {
			fseek(f, (n - 1) * sizeof(com), SEEK_SET);
			fread(&a, sizeof(com), 1, f);
			if (a.is == 0)
			{
				a.is = 1;
				a.cod = n;
				printf("Denumire produs: "); getc(stdin); gets_s(a.denumire);
				printf("Gama: "); gets_s(a.gama);
				printf("Pret: "); scanf_s("%f", &a.pret);
				printf("Cantitate: "); scanf_s("%d", &a.cantitate);
				printf("Data livrarii: ");
				scanf("%d %d %d", &a.data.zi, &a.data.luna, &a.data.an);
				fseek(f, (n - 1) * sizeof(com), SEEK_SET);
				fwrite(&a, sizeof(com), 1, f);
			}
			else printf("Inregistrarea exista deja\n");
		}
		printf("\nn= "); scanf_s("%d", &n);
	}
	fclose(f);
}

void adaugare()
{
	FILE *f;
	com a;
	int n, i;
	char nume_f[20];
	printf("\nNume fisier: ");
	gets_s(nume_f);
	f = fopen(nume_f, "rb+");
	printf("\nn= "); scanf_s("%d", &n);
	while (!feof(stdin))
	{
		if (n > nr_art(f, sizeof(com)))
		{
			fseek(f, 0, SEEK_END);
			a.is = 0;
			for (i = nr_art(f, sizeof(com)); i < n; i++)
				fwrite(&a, sizeof(com), 1, f);
			fseek(f, (n - 1) * sizeof(com), 0);
			a.is = 1;
			a.cod = n;
			printf("Denumire produs: "); getc(stdin); gets_s(a.denumire);
			printf("Gama: "); gets_s(a.gama);
			printf("Pret: "); scanf_s("%f", &a.pret);
			printf("Cantitate: "); scanf_s("%d", &a.cantitate);
			printf("Data livrarii: ");
			scanf("%d %d %d", &a.data.zi, &a.data.luna, &a.data.an);
			fwrite(&a, sizeof(com), 1, f);
		}
		else {
			fseek(f, (n - 1) * sizeof(com), 0);
			fread(&a, sizeof(com), 1, f);
			if (a.is == 0)
			{
				a.is = 1;
				a.cod = n;
				printf("Denumire produs: "); getc(stdin); gets_s(a.denumire);
				printf("Gama: "); gets_s(a.gama);
				printf("Pret: "); scanf_s("%f", &a.pret);
				printf("Cantitate: "); scanf_s("%d", &a.cantitate);
				printf("Data livrarii: ");
				scanf("%d %d %d", &a.data.zi, &a.data.luna, &a.data.an);
				fseek(f, (n - 1) * sizeof(com), SEEK_SET);
				fwrite(&a, sizeof(com), 1, f);
			}
			else printf("Inregistrarea exista deja");
		}
		printf("\nn= "); scanf_s("%d", &n);
	}
	fclose(f);
}

void modificare()
{
	FILE *f;
	com a;
	int n;
	char nume_f[20];
	printf("\nNume fisier= ");
	gets_s(nume_f);
	f = fopen(nume_f, "rb+");
	printf("\nn= "); scanf_s("%d", &n);
	while (!feof(stdin))
	{
		if (n > nr_art(f, sizeof(com)))
			printf("S-a depasit lungimea fisierului");
		else 
		{
			fseek(f, (n - 1) * sizeof(com), 0);
			fread(&a, sizeof(com), 1, f);
			if (a.is == 1)
			{
				printf("Denumire produs: "); getc(stdin); gets_s(a.denumire);
				printf("Gama: "); gets_s(a.gama);
				printf("Pret: "); scanf_s("%f", &a.pret);
				printf("Cantitate: "); scanf_s("%d", &a.cantitate);
				printf("Data livrarii: ");
				scanf("%d %d %d", &a.data.zi, &a.data.luna, &a.data.an);
				fseek(f, (n - 1) * sizeof(com), SEEK_SET);
				fwrite(&a, sizeof(com), 1, f);
			}
			else printf("Nu exista");
		}
		printf("\nn= "); scanf_s("%d", &n);
	}
	fclose(f);
}

void stergere()
{
	FILE *f;
	com a;
	int n;
	char nume_f[20];
	printf("\nNume fisier: ");
	gets_s(nume_f);
	f = fopen(nume_f, "rb+");
	printf("\nn= "); scanf_s("%d", &n);
	while (!feof(stdin))
	{
		if (n > nr_art(f, sizeof(com)))
			printf("S-a depasit lungimea ");
		else {
			fseek(f, (n - 1) * sizeof(com), 0);
			fread(&a, sizeof(com), 1, f);
			if (a.is == 1) {
				a.is = 0;
				fseek(f, (n - 1) * sizeof(com), 0);
				fwrite(&a, sizeof(com), 1, f);
			}
			else printf("Nu exista");
		}
		printf("\nn= "); scanf_s("%d", &n);
	}
	fclose(f);
}

void raport1()
{
	FILE *f, *g;
	com a;
	char nume_f[20];
	printf("\nNume fisier: ");
	gets_s(nume_f);
	f = fopen(nume_f, "rb");
	if (f) {

		printf("=================================AFISARE================================================");
		g = fopen("raport.txt", "w");
		printf("\n");
		fprintf(g,"                              LISTA PRODUSE                              \n");
		fprintf(g,"======================================================================================\n");
		fprintf(g,"COD||      DENUMIRE      ||        GAMA        ||  PRET  ||CANTITATE|| ZI ||LUNA|| AN \n");
		fprintf(g,"======================================================================================\n");
		printf("                              LISTA PRODUSE                              \n");
		printf("=======================================================================================\n");
		printf("COD||      DENUMIRE      ||        GAMA        ||  PRET  ||CANTITATE|| ZI ||LUNA|| AN \n");
		printf("========================================================================================");
		fread(&a, sizeof(com), 1, f);
		while (!feof(f))
		{
			if (a.is == 1)
			{
				printf("\n%3d||%-20s||%-20s||%8.2f||%9d||%4d||%4d||%4d", a.cod, a.denumire, a.gama, a.pret, a.cantitate, a.data.zi, a.data.luna, a.data.an);
				fprintf(g,"\n%3d||%-20s||%-20s||%8.2f||%9d||%4d||%4d||%4d", a.cod, a.denumire, a.gama, a.pret, a.cantitate, a.data.zi, a.data.luna, a.data.an);
			}
			fread(&a, sizeof(com), 1, f);
		}
		fclose(f); fclose(g);
	}
}

void raport2()
{
	FILE *f, *g;
	com a;
	char nume_f[20];
	float x;
	printf("\nNume fisier: ");
	gets_s(nume_f);
	f = fopen(nume_f, "rb");
	printf("Afisare comenzi cu valoare mai mare decat: ");
	scanf_s("%f", &x);
	if (f) {
		printf("=================================AFISARE================================================");
		g = fopen("raport2.txt", "w");
		printf("\n");
		fprintf(g, "                              LISTA PRODUSE                              \n");
		fprintf(g, "======================================================================================\n");
		fprintf(g, "COD||      DENUMIRE      ||        GAMA        ||  PRET  ||CANTITATE|| ZI ||LUNA|| AN \n");
		fprintf(g, "======================================================================================\n");
		printf("                              LISTA PRODUSE                              \n");
		printf("=======================================================================================\n");
		printf("COD||      DENUMIRE      ||        GAMA        ||  PRET  ||CANTITATE|| ZI ||LUNA|| AN \n");
		printf("========================================================================================");
		fread(&a, sizeof(com), 1, f);
		while (!feof(f))
		{
			if (a.is == 1 && a.pret * a.cantitate >= x)
			{
				printf("\n%3d||%-20s||%-20s||%8.2f||%9d||%4d||%4d||%4d", a.cod, a.denumire, a.gama, a.pret, a.cantitate, a.data.zi, a.data.luna, a.data.an);
				fprintf(g, "\n%3d||%-20s||%-20s||%8.2f||%9d||%4d||%4d||%4d", a.cod, a.denumire, a.gama, a.pret, a.cantitate, a.data.zi, a.data.luna, a.data.an);
			}
			fread(&a, sizeof(com), 1, f);
		}
		fclose(f); fclose(g);
	}
}

int main()
{
	int x;
	printf("\nAlegeti o optiune:\n1.Creare fisier\n2.Adaugare\n3.Modificare articol\n4.Stergere articol\n5.Afisare completa\n6.Afisare comenzi dupa venit\n0.Iesire\n");
	scanf("%d", &x);
	while (x)
	{
		switch (x)
		{
		case 1:
			getc(stdin);
			creare();
			break;
		case 2:
			getc(stdin);
			adaugare();
			break;
		case 3:
			getc(stdin);
			modificare();
			break;
		case 4:
			getc(stdin);
			stergere();
			break;
		case 5:
			getc(stdin);
			raport1();
			break;
		case 6:
			getc(stdin);
			raport2();
			break;
		default:
			printf("nu exista\n");
		}
		printf("\nAlegeti o optiune:\n1.Creare fisier\n2.Adaugare\n3.Modificare articol\n4.Stergere articol\n5.Afisare completa\n6.Afisare comenzi dupa venit\n0.Iesire\n");
		scanf("%d", &x);
	}
}