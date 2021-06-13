#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////
///////////////////////Generalized Trees///////////////////////
///////////////////////////////////////////////////////////////

//Metoda Primul Fiu si Frate Dreapta - adauga, inaltime, grad//

int n, i, nod, parinte, *PF, *FD, parinte_prim, grad_maxim, inaltime_maxim;

void adauga_FD(int cheie, int cheie_FD) {
    if (FD[cheie_FD] == -1) {
            FD[cheie_FD] = cheie;
            return;
    } else {
        adauga_FD(cheie, FD[cheie_FD]);
    }
}

void adauga(int cheie, int cheie_parinte) {
    if (cheie == cheie_parinte) {
        return;
    }
    if (PF[cheie_parinte] == -1) {
        PF[cheie_parinte] = cheie;
        return;
    } else {
        adauga_FD(cheie, PF[cheie_parinte]);
    }
}

int maxim(int a, int b) {
    return (a > b ? a : b);
}

int inaltime(int nod, int h) {
    if (FD[nod] == -1) {
        if (PF[nod] == -1) {
            return h;
        }
        return inaltime(PF[nod], h + 1);
    }
    if (PF[nod] == -1) {
        return inaltime(FD[nod], h);
    }
    return maxim(inaltime(FD[nod], h), inaltime(PF[nod], h + 1));
}

void grad(int nod, int gr){
    if (gr > grad_maxim) {
        grad_maxim = gr;
    }
    if (PF[nod] != -1) {
        grad(PF[nod], 1);
    }
    if (FD[nod] != -1) {
        grad(FD[nod], gr + 1);
    }
}

////Metoda Indicator catre parinte - adauga, inaltime, grad////

#define MAX_N 1000

typedef struct
{
    int cheie;
    int parinte;
}Nod;
Nod arbore[MAX_N];

int numar_noduri;


/* Functia adauga creste cu 1 la fiecare adaugare numarul de noduri citit initial de la tastatura si adauga noul nod */
void adauga(int cheie, int parinte)
{
    numar_noduri++;
    arbore[numar_noduri].cheie = cheie;
    arbore[numar_noduri].parinte = parinte;
}

/* Functia grad afiseaza gradul maxim al arborelui folosind un vector de frecventa */
void grad()
{
    int frecv[MAX_N], i, grad_maxim = 1;

    for (i = 1; i <= numar_noduri; i++)
        frecv[i] = 0; // initializez vectorul de frecventa cu 0

    for (i = 1 ; i <= numar_noduri; i++)
        if(arbore[i].cheie != arbore[i].parinte) // cazul in care inca nu am ajuns la radacina
            frecv[arbore[i].parinte]++;

    for (i = 1; i <= numar_noduri; i++)
        if(grad_maxim < frecv[i])
            grad_maxim = frecv[i];

    printf("%d", grad_maxim);
}

/*
    Functia contorizare calculeaza si returneaza inaltimea fiecarui nod;
    Cu o structura repetitiva (while) merg dintr-un nod, de jos in sus, inspre tatal sau pana la radacina
*/
int contorizare(int cheie, int parinte)
{
    int nr = 1;
    while(cheie != parinte) // cat timp inca nu am ajuns la radacina
    {
        nr++;
        parinte = arbore[parinte].parinte;
        cheie = arbore[cheie].parinte;
    }
    return nr;
}

/* Functia inaltime ia rand pe rand nodurile arborelui si actualizeaza un maxim conform rezultatului returnat de functia contorizare */
void inaltime()
{
    int i, maxim = 0, x;
    for (i = 1; i <= numar_noduri; i++)
    {
        x = contorizare(arbore[i].cheie, arbore[i].parinte);
        if (x > maxim)
            maxim = x;
    }

    printf("%d\n", maxim);
}


///////////////////////////////////////////////////////////////
///////////////////////Binary Trees////////////////////////////
///////////////////////////////////////////////////////////////

/////cu pointeri - adauga, inaltime, preordine, in, post///////

int n, i, cheie;

typedef struct ab{
    int cheie;
    struct ab *st;
    struct ab *dr;
}AB;

AB *arb;

AB* add (AB* r, int x) {
    if (r == NULL) {
        AB *aux = (AB*) malloc(sizeof(AB));
        if (aux == NULL) {
            printf("eroare de alocare!!\n");
        }
        aux->st = NULL;
        aux->dr = NULL;
        aux->cheie = x;
        return aux;
    }
    if (r->cheie < x) {
        r->dr = add(r->dr, x);
    } else {
        r->st = add(r->st, x);
    }
    return r;
}

int maxim(int a, int b) {
    return (a > b ? a : b);
}

int inaltime(AB* r, int h) {
    if (r->st == NULL) {
        if (r->dr == NULL) {
            return h;
        }
        return maxim(h, inaltime(r->dr, h + 1));
    }
    if (r->dr == NULL) {
        return maxim(h, inaltime(r->st, h + 1));
    }
    return maxim(inaltime(r->st, h + 1), inaltime(r->dr, h + 1));
}

void preordine(AB* r) { //radacina, stanga, dreapta
    if (r != NULL) {
        printf("%d ", r->cheie);
        preordine(r->st);
        preordine(r->dr);
    }
}

void inordine(AB* r) { // stanga, radacina, dredapta
    if (r != NULL) {
        inordine(r->st);
        printf("%d ", r->cheie);
        inordine(r->dr);
    }
}

void postordine(AB* r) { // stanga, dredapta, radacina
    if (r != NULL) {
        postordine(r->st);
        postordine(r->dr);
        printf("%d ", r->cheie);
    }
}

///////////////////////////////////////////////////////////////
///////////////////////AVL Trees///////////////////////////////
///////////////////////////////////////////////////////////////

//////////////////adica ordonat + echilibrat//////////////////
//1 stanga -- SS
//2 stanga -- SD
//1 dreapta -- DD
//2 dreapta -- DS

/////////////////////////////////Stergere/////////////////////
//nod terminal + se inlocuieste cu nodul la st./dr.///////////
//din parcurgerea inordine///////////////////////////////////

///////////////////////////////////////////////////////////////
///////////////////////B Trees - Multicai//////////////////////
///////////////////////////////////////////////////////////////

//citire, inserare, afiseaza arborele in preordine cu spatii,//
//fara alte caractere intre siruri/////////////////////////////

#define N   2
#define NN (N*2)



struct Nod {
	char cheie[30];
	struct Pagina* p;
	int contor;
};
typedef struct Nod Nod;

struct Pagina {
	int m;
	struct Pagina* p0;
	Nod e[NN + 1];
};
typedef struct Pagina Pagina;

Pagina *radacina;
Nod v;

Pagina* insereaza(Pagina *pag, char x[30], Nod *nod) {
	int i, s, d, mij;
	Pagina *q, *r;

	if (!nod) {
		//v.cheie = x;
		strcpy(v.cheie, x);
		v.contor = 1;
		v.p = NULL;
	} else {
		v = *nod;
	}
	if (pag == NULL) { //daca nu exista radacina
		pag = (Pagina*)calloc(sizeof(Pagina), 1);
		pag->e[++pag->m] = v;
		return pag;
	}

	//se cauta binar pozitia cheii x in pagina curenta
	s = 1;
	d = pag->m;
	while (s <= d) 	{
		mij = (s + d) / 2;
		//if (pag->e[mij].cheie == x) //gasit
		if (strcmp(pag->e[mij].cheie, x) == 0) {
			pag->e[mij].contor++;
			return pag;
		}
		//if (x < pag->e[mij].cheie)
		if (strcmp(x, pag->e[mij].cheie) < 0)
			d = mij - 1;
		else
			s = mij + 1;
	}

	//daca este pagina terminala sau daca se propaga insertia
	if (pag->p0 == NULL || nod)
	{
		if (pag->m < NN) //se poate adauga un nod in pagina curenta
		{
			++pag->m;
			for (i = pag->m; i > d + 1; i--)
				pag->e[i] = pag->e[i - 1];
			pag->e[i] = v;
		}
		//pagina curenta pag este plina => supradepasire => pagina trebuie scindata
		else
		{
			Pagina *a = pag;
			Pagina *b = (Pagina*)calloc(sizeof(Pagina), 1);
			pag = (Pagina*)calloc(sizeof(Pagina), 1);

			//scindarea paginii curente
			for (i = 1; i <= N; i++)
				b->e[i] = a->e[i + N];
			a->m = b->m = N;

			//cheia noudului v e cheia de scindare
			//if (v.cheie > a->e[N].cheie && v.cheie < b->e[1].cheie)
			if (strcmp(v.cheie, a->e[N].cheie) > 0 && strcmp(v.cheie, b->e[1].cheie) < 0)
				pag->e[++pag->m] = v;
			else
			{
				//ultima cheie a nodului a este folosita la scindare
				//if (v.cheie < a->e[N].cheie)
				if (strcmp(v.cheie, a->e[N].cheie) < 0) {
					pag->e[++pag->m] = a->e[N];
					//for (i = a->m; i > 1 && a->e[i - 1].cheie > v.cheie; i--)
					for (i = a->m; i > 1 && strcmp(a->e[i - 1].cheie, v.cheie) > 0; i--)
						a->e[i] = a->e[i - 1];
					a->e[i] = v;
				}
				//prima cheie a nodului a este folosita la scindare
				else
				{
					pag->e[++pag->m] = b->e[1];
					//for (i = 1; i < b->m && b->e[i + 1].cheie < v.cheie; i++)
					for (i = 1; i < b->m && strcmp(b->e[i + 1].cheie, v.cheie) < 0; i++)
						b->e[i] = b->e[i + 1];
					b->e[i] = v;
				}
			}

			//se refac legaturile intre pagini
			b->p0 = pag->e[1].p; //prima legatura a paginii b devine legatura nodului parinte
			pag->p0 = a;         //prima legatura a nodului parinte devine fostul vecin stanga
			pag->e[1].p = b;     //a doua legatura a nodului parinte devine fostul vecin dreapta
		}
	}
	else
	{
		if (d == 0) //s-a ajuns la cel mai din stanga element => prima legatura
			q = pag->p0;
		else
			q = pag->e[d].p;
		r = insereaza(q, x, NULL);
		if (r != q) //daca pagina in care s-a inserat s-a scindat <=> arborele crescut cu un nivel
		{
			/*se incearca inserarea nodului din pagina scindata in pagina curenta
			in caz de succes, arborele nu va creste in inaltime*/
			pag = insereaza(pag, r->e[1].cheie, &r->e[1]);
			free(r); //se sterge pagina scindata, intrucat nodul a fost inserat intr-o alta pagina
		}
	}

	return pag;
}

void afisare(Pagina *arbore) {
	int i;

	if (!arbore)
		return;
    for (i = 1; i <= arbore->m; i++) {
		printf("%s ", arbore->e[i].cheie);
	}
	afisare(arbore->p0);
	for (i = 1; i <= arbore->m; i++) {
		afisare(arbore->e[i].p);
	}


}

int cautare(Pagina *pag, char x[30])
{
	/*Cauta cheia x in arbore. Returneaza 1 daca cheia exista, 0 daca nu exista.*/
	int s, d, mij;

	if (pag == NULL)
		return 0;

	s = 1;
	d = pag->m;
	while (s <= d) //cautare binara
	{
		mij = (s + d) / 2;
		//if (x == pag->e[mij].cheie)
		if (strcmp(x, pag->e[mij].cheie) == 0)
			return 1;
		//if (x < pag->e[mij].cheie)
		if (strcmp(x, pag->e[mij].cheie) < 0)
			d = mij - 1;
		else
			s = mij + 1;
	}
	if (d == 0)
		return cautare(pag->p0, x);
	return cautare(pag->e[d].p, x);
}

void vecinStang(Pagina *pag, Pagina *st, Pagina *r, int d)
{
	int i;

	if (st->m == N) //daca pagina din stanga are fix N elemente => contopire
	{
		st->e[N + 1] = pag->e[d];
		st->e[N + 1].p = r->p0;
		st->m = NN;
		for (i = N + 2; i <= NN; i++)
			st->e[i] = r->e[i - N - 1];

		for (i = d; i < pag->m; i++)
			pag->e[i] = pag->e[i + 1];
		pag->m--;
		free(r);
	}
	else //imprumut
	{
		r->m = N;
		for (i = N; i > 1; i--)
			r->e[i] = r->e[i - 1];
		r->e[1] = pag->e[d];
		r->e[1].p = r->p0;
		r->p0 = st->e[st->m].p;

		pag->e[d] = st->e[st->m];
		pag->e[d].p = r;
		st->m--;
	}
}

void vecinDrept(Pagina *pag, Pagina *dr, Pagina *r, int d)
{
	int i;

	r->e[N] = pag->e[d + 1];
	r->e[N].p = dr->p0;
	r->m = N;

	if (dr->m == N) //daca pagina din dreapta are fix N elemente => contopire
	{
		r->m = NN;
		for (i = N + 1; i <= NN; i++)
			r->e[i] = dr->e[i - N];

		for (i = 1; i < pag->m; i++)
			pag->e[i] = pag->e[i + 1];
		pag->m--;
		free(dr);
	}
	else //contopire
	{
		pag->e[d + 1] = dr->e[1];
		pag->e[d + 1].p = dr;

		dr->p0 = dr->e[1].p;
		for (i = 1; i < dr->m; i++)
			dr->e[i] = dr->e[i + 1];
		dr->m--;
	}
}

Pagina* suprima(Pagina *pag, char x[30], Nod *nod)
{
	int i, s, d, mij;
	Pagina *q, *r;

	//daca nu exista cheia in arbore
	if (pag == NULL || pag->m == 0)
		return NULL;

	s = 1;
	d = pag->m;
	while (s <= d) //cautare binara
	{
		mij = (s + d) / 2;
		//if (x == pag->e[mij].cheie)
		if (strcmp(x, pag->e[mij].cheie) == 0)
			break;
		//if (x < pag->e[mij].cheie)
		if (strcmp(x, pag->e[mij].cheie) < 0)
			d = mij - 1;
		else
			s = mij + 1;
	}

	/*se suprima cu ajutorul nodului, cu cheie maxima,
	mai mica decat cheia nodului curent*/
	//if (x == pag->e[mij].cheie)
	if (strcmp(x, pag->e[mij].cheie) == 0)
	{
		if (pag->p0 == NULL) //pagina curenta este pagina terminala
		{
			/*daca se elimina un nod dintr-o pagina neterminala,
			se schimba continutul nodurilor, dar se pastreaza legatura*/
			if (nod)
			{
				q = nod->p;
				*nod = pag->e[pag->m];
				nod->p = q;
			}
			for (i = mij; i < pag->m; i++)
				pag->e[i] = pag->e[i + 1];
			pag->m--;

			//pagina terminala curenta s-a golit => arborele scade in inaltime
			//posibil doar pentru N == 1
			for (q = pag; pag && pag->m == 0; free(q), q = pag)
				pag = pag->p0;

			return pag;
		}
		/*dupa mutarea cheii intr-o pagina terminala,
		se trece la eliminarea ei, prin repetarea pasului curent;
		se presupune ca cheia de sters este mai mica cu o unitate*/
		return suprima(pag, x - 1, &pag->e[mij]);
	}

	if (d == 0)
		q = pag->p0;
	else
		q = pag->e[d].p;
	r = suprima(q, x, nod); //se incearca eliminarea cheii din subarborele corespunzator

	//conditia (r == NULL) garanteaza ca este pagina terminala
	/*daca nu exista cheia aleasa sa inlocuiasca cheia de sters
	se repeta pasul de stergere folosind cheia cu cea mai mare valoare*/
	if (r == NULL)
	{
		if (nod)
			return suprima(pag, pag->e[d].cheie, nod);
		else //daca nu exista cheia in subarbore
			return pag;
	}

	if (r->m < N) //subdepasire => imprumut sau contopire
	{
		Pagina *st, *dr;
		if (d == 1)
			st = pag->p0;
		else
			st = pag->e[d - 1].p;
		dr = pag->e[d + 1].p;

		if (r == pag->p0) //cel mai din stanga nod
			vecinDrept(pag, dr, r, d);
		else if (d == pag->m) //cel mai din dreapta nod
			vecinStang(pag, st, r, d);
		else //are 2 vecini
		{
			/*
			se imprumuta de la vecinul cu nr maxim de noduri in pagina sau se contopesc 2 pagini;
			cum nu pot exista simultan 2 pagini cu mai putin de N elemente =>
			oricare pagina poate fi aleasa pentru contopire, daca este cazul
			*/

			//se imprumuta de la vecinul drept
			if (dr->m > st->m)
				vecinDrept(pag, dr, r, d);
			//se imprumuta (sau contopeste) de la (cu) vecinul stang
			else
				vecinStang(pag, st, r, d);
		}
	}

	//radacina subarborelui curent s-a golit => arborele scade in inaltime
	for (q = pag; pag && pag->m == 0; free(q), q = pag)
		pag = pag->p0;

	return pag;
}

/*void preordine(Nod* nod) {
    printf("%s ", nod.cheie);
    int i;
    for (i = 0; i < nod.contor; ++i) {
        preordine(nod.p[i]);
    }
}*/

//citire, inserare, inaltime, numar de pagini//////////////
void inaltime(Pagina *pag) {
    int h = 1;
    Pagina *q = pag;
    do {
        q = q->p0;
        h++;
    }while (q);
    h--;
    printf("%d", h);
}
int nr = 0;

void nrpag(Pagina *pag) {
    int i;
    if (pag) {
        nr++;
        nrpag(pag->p0);
        for (i = 1 ; i<= pag->m; ++i) {
            nrpag(pag->e[i].p);
        }
    } else {
        return;
    }
}

void afnrpag(Pagina *pag) {
    nrpag(pag);
    printf("%d", nr);
}



int main() {
    ///////////////////////////////////////////////////////////////
    ///////////////////////Generalized Trees///////////////////////
    ///////////////////////////////////////////////////////////////

    //Metoda Primul Fiu si Frate Dreapta - adauga, inaltime, grad//
     scanf("%d", &n);
    PF = (int*)malloc(n * sizeof(int));
    if (PF == NULL){
        printf("eroare de alocare");
        exit(1);
    }
    FD = (int*)malloc(n * sizeof(int));
    if (FD == NULL){
        printf("eroare de alocare");
        exit(1);
    }

    for (i = 1; i <= n; ++i) {
        PF[i] = -1;
        FD[i] = -1;
    }

    for (i = 1; i <= n; ++i) {
        scanf("%d %d", &nod, &parinte);
        if (nod == parinte) {
            parinte_prim = nod;
        }
        adauga(nod, parinte);
    }

    if (n == 1) {
        grad_maxim = 1;
        inaltime_maxim = 1;
        printf("%d\n%d", inaltime_maxim, grad_maxim);
    } else {
        grad(parinte_prim, 0);
        printf ("%d\n%d", inaltime(parinte_prim, 1), grad_maxim);
    }

    free(PF);
    free(FD);

     ////Metoda Indicator catre parinte - adauga, inaltime, grad////

    ///////////////////////////////////////////////////////////////
    ///////////////////////Binary Trees////////////////////////////
    ///////////////////////////////////////////////////////////////

     int i;
        scanf("%d", &numar_noduri);
        for (i = 1; i <= numar_noduri; i++)
            scanf("%d %d", &arbore[i].cheie, &arbore[i].parinte);
     //   adauga(6, 2);

    inaltime();
    grad();

    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &cheie);
        arb = add(arb, cheie);
    }
    printf("%d\n", inaltime(arb, 1));
    preordine(arb);
    free(arb);

    ///////////////////////////////////////////////////////////////
    ///////////////////////B Trees - Multicai//////////////////////
    ///////////////////////////////////////////////////////////////

    int i, n;
        char sir[30];
        scanf("%d", &n);
    	radacina = NULL;
    	for (i = 1; i <= n; i++) {
    	    scanf("%s", &sir);
    		radacina = insereaza(radacina, sir, NULL);
    	}
        //preordine(radacina);
    	//printf("Arborele-B initial:\n");
    	afisare(radacina);
    	/*printf("\n\n");

    	for (i = 1; i <= n; i++)
    	{
    		printf("Dupa stergerea lui %d:\n", i);
    		radacina = suprima(radacina, i, NULL);
    		afisare(radacina, 1);
    		printf("\n\n");
    	}*/

    	inaltime(radacina);
        printf(" ");
        afnrpag(radacina);



    return 0;
}