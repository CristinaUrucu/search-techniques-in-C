#include <stdio.h>
#include <stdlib.h>

//citire, inserare, afisare in ordine crescatoare cheile//
//ce respecta regula: ////////////////////////////////////
//parcugerea in adancime cat si in cuprindere a unei//////
//componente conexe genereaza aceeasi secventa de chei////

int i, j, k, iv, ok, N, M, n1, n2;
int a[20][20];
int coada[20], viz[20], vectAdancime[20], vectLatime[20];

void VizZero(int viz[20]) {
    int k;
    for (k = 1; k <= N; ++k) {
        viz[k] = 0;
    }
}

void ParcurgereAdancime(int start) {
    if (viz[start] == 0) {
        vectAdancime[iv] = start;
        iv++;
        viz[start] = 1;
    }
    for (j = 1; j <= N; ++j) {
        if (a[start][j] == 1 && viz[j] == 0) {
            vectAdancime[iv] = j;
            iv++;
            viz[j] = 1;
            ParcurgereAdancime(j);
            j = j - N;
        }
    }
}

void push(int coada[20], int x) {
    int k = 0;
    if (coada[k] == -1) {
        coada[k] = x;
    } else {
        while (coada[k] != -1) {
            k++;
        }
        coada[k] = x;
    }
}

int pop(int coada[20]) {
    if (coada[1] == -1) {
        return -1;
    }
    int aux = coada[1];
    int k;
    for (k = 1; k < N; ++k) {
        coada[k] = coada[k + 1];
    }
    coada[N] = -1;
    return aux;
}

void ParcurgereLatime(int start) {
    push(coada, start);
    while (coada[1] != -1) {
        int c = pop(coada);
        if (c != -1) {
            vectLatime[iv] = c;
            iv++;
            viz[c] = 1;
            for (j = 1; j <= N; ++j) {
                if (a[c][j] == 1 && viz[j] == 0) {
                    push(coada, j);
                    viz[j] = 1;
                }
            }
        }
    }
}

void initializareCoada(int coada[20]) {
    int k;
    for (k = 1; k <= N; ++k) {
        coada[k] = -1;
    }
}

//numarul de componente conexe ale grafului/////////////////
//1 daca draful este ciclic, si 0 daca acesta este aciclic//

int i, N, M, n1, n2, ciclu;
int a[20][20], viz[20];

void parcurgereCiclu(int start, int nodInitial) {
    int j;
    for (j = 1; j <= N; ++j) {
        if (a[start][j] == 1 && viz[j] == 1 && j != nodInitial) {
            ciclu = 1;
        }
        if (a[start][j] == 1 && viz[j] == 0) {
            viz[j] = 1;
            parcurgereCiclu(j, nodInitial);
        }
    }
}

void parcurgere(int start) {
    int j;
    for (j = 1; j <= N; ++j) {
        if ((a[start][j] == 1 || a[j][start] == 1) && viz[j] == 0) {
            viz[j] = 1;
            parcurgere(j);
        }
    }
}

int componenteConexe() {
    int cc = 0;
    for (i = 1; i <= N; ++i) {
        if (viz[i] == 0) {
            parcurgere(i);
            cc++;
        }
    }
    return cc;
}

////////////////////////////////////////////////////////
//////////////Grafuri ponderate/////////////////////////
////////////////////////////////////////////////////////

//citire, inserare, algoritmul lui PRIM,
//sa calculeze arborele de acoperire minim si sa afiseze
//suma ponderilor arcelor acestuia

int i, j, N, M, n1, n2, pondere;
int a[256][256], viz[256];

int prim() {
    int suma = 0;
    viz[1] = 1;
    int pas, i, j, min1, mini, minj;
    for (pas = 0; pas < N - 1; ++pas) {
        min1 = 999;
        mini = -1;
        minj = -1;
        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= N; ++j) {
                if (a[i][j] != 0 && viz[i] == 1 && viz[j] == 0) {
                    if (min1 > a[i][j]) {
                        min1 = a[i][j];
                        mini = i;
                        minj = j;
                    }
                }
            }
        }
        suma = suma + a[mini][minj];
        viz[minj] = 1;
    }
    return suma;
}

//KRUSKA

typedef struct
{
    int x, y, c;
}muchie;
muchie a[257], aux;

int n, v[257], m, s = 0;

// functie pentru a afisa o eroare in cazul in care n sau m nu respecta intervalele impuse
void eroare(int minim, int maxim, char c)
{
    printf("Numarul %c nu este in intervalul [%d, %d]. Dati alt numar %c: ", c, minim, maxim, c);
}

// citirea datelor
void citire()
{
    int x, y, c, i;
    scanf("%d %d", &n, &m);
    while ((n < 1) || (n > 256))
    {
        eroare(1, 256, 'n');
        scanf("%d", &n);
    }

    while ((m < 0) || (m > 256))
    {
        eroare(0, 256, 'm');
        scanf("%d", &m);
    }

    for (i = 1; i <= m; i++)
    {
        scanf("%d %d %d", &x, &y, &c);
        while (((x < 0) || (x > n)) || ((y < 0) || (y > n)) || ((c < -1024) || (c > 1024)))
        {
            printf("Cel putin unul dintre numere nu respecta intervalele impuse. Dati alta tripleta de numere: ");
            scanf("%d %d %d", &x, &y, &c);
        }
        a[i].x = x;
        a[i].y = y;
        a[i].c = c;
    }
}

// sortarea muchiilor in functie de cost
void sorteaza()
{
    int i, ok;
    do
    {
        ok = 1;
        for (i = 1; i < m; i++)
            if (a[i].c > a[i + 1].c)
            {
                aux = a[i];
                a[i] = a[i + 1];
                a[i + 1] = aux;
                ok = 0;
            }
    }while (ok == 0);
}

// consider ca fiecare nod este initial o componenta conexa
void initializare()
{
    int i;
    for (i = 1; i <= n; i++)
        v[i] = i;
}

// functia imbina toate nodurile intre care exista muchii intr-o singura componenta conexa (sau mai multe daca nu exista muchie)
void inlocuieste(int x, int y)
{
    int i;
    for (i = 1; i <= n; i++)
        if (v[i] == x)
            v[i] = y;

}

void kruskal()
{
    int i = 1, k = 0;
    while (k < n - 1)
    {
        if (v[a[i].x] != v[a[i].y]) // daca inca fac parte din componente conexe diferite
        {
            s += a[i].c; // costul minim
            inlocuieste(v[a[i].x], v[a[i].y]);
            k++;
        }
        i++;
    }
}

////////////////////////////////////////////////////////
//////////////Grafuri orientate/////////////////////////
////////////////////////////////////////////////////////

//citire, inserare, Dijkstra, programul va calcula si///
//afisa n-1 valori separate prin spatiu, reprezentand///
//distanta minima de la primul nod (nodul cu cheia 1)///
//la toate celalalte noduri(2, 3, ..., n). Atentie,/////
//este posibil sa nu existe drum de la primul nod la////
//unele noduri, caz in care se va afisa lungimea 0//////

typedef struct {
    int nod, cost;
    struct graf *next;
} graf;

int n, m, inf = 1 << 30;
graf *a[270];
int d[270], h[270], poz[270], k;

void add (int where, int what, int cost) {
    graf *q = (graf*)malloc(sizeof(graf));
    if (q == NULL) {
        printf("Eroare la alocare.");
        exit(1);
    }
    q->nod = what;
    q->cost = cost;
    q->next = a[where];
    a[where] = q;
}

void read () {
    scanf("%d %d", &n, &m);
    int x, y, z;
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &x, &y, &z);
        add(x, y, z);
    }
}

void swap (int x, int y) {
    int t = h[x];
    h[x] = h[y];
    h[y] = t;
}

void upheap (int what) {
    int tata;
    while (what > 1) {
        tata = what >> 1;
        if (d[h[tata]] > d[h[what]]) {
            poz[h[what]] = tata;
            poz[h[tata]] = what;
            swap(tata, what);
            what = tata;
        }
        else
            what = 1;
    }
}

void downheap(int what) {
    int f;
    while (what <= k) {
        f = what;
        if ((what << 1) <= k) {
            f = what << 1;
            if (f + 1 <= k) {
                if (d[h[f + 1]] < d[h[f]]) {
                    ++f;
                }
            }
        } else {
            return;
        }
        if (d[h[what]] > d[h[f]]) {
            poz[h[what]] = f;
            poz[h[f]] = what;
            swap(what, f);
            what = f;
        }
        else {
            return;
        }
    }
}

void dijkstra_heap () {
    for (int i = 2; i <= n; ++i) {
        d[i] = inf;
        poz[i] = -1;
    }
    poz[1] = 1;
    h[++k] = 1;
    while (k) {
        int min = h[1];
        swap(1, k);
        poz[h[1]] = 1;
        --k;
        downheap(1);
        graf *q = a[min];
        while (q) {
            if (d[q->nod] > d[min] + q->cost) {
                d[q->nod] = d[min] + q->cost;
                if (poz[q->nod] != -1) {
                    upheap(poz[q->nod]);
                } else {
                    h[++k] = q->nod;
                    poz[h[k]] = k;
                    upheap(k);
                }
            }
            q = q->next;
        }
    }
}


void main() {

    scanf("%d %d", &N, &M);
    for (i = 1 ; i <= M; ++i) {
        scanf("%d %d", &n1, &n2);
        a[n1][n2] = 1;
        a[n2][n1] = 1;
    }

    int y;

    for (i = 1; i <= N; ++i) {
        VizZero(vectAdancime);
        VizZero(viz);
        iv = 1;
        ParcurgereAdancime(i);

        VizZero(vectLatime);
        initializareCoada(coada);
        VizZero(viz);
        iv = 1;
        ParcurgereLatime(i);

        ok = 0;
        for (k = 1; k <= N; ++k) {
            if (vectAdancime[k] != vectLatime[k]) {
                ok = 1;
            }
        }
        if (ok == 0) {
            printf("%d ", i);
        }
    }

    printf("%d ", componenteConexe());

    for (i = 1; i <= N; ++i) {
        viz[i] = 0;
    }
    for (i = 1; i <= N; ++i) {
        vizZero(viz);
        parcurgereCiclu(i, i);
        if (ciclu == 1) {
            break;
        }
    }
    printf("%d", ciclu);

    ////////////////////////////////////////////////////////
    //////////////Grafuri ponderate/////////////////////////
    ////////////////////////////////////////////////////////

    scanf("%d %d", &N, &M);

    for (i = 1; i <= M; ++i) {
        scanf("%d %d %d", &n1, &n2, &pondere);
        a[n1][n2] = pondere;
        a[n2][n1] = pondere;
    }

    printf("%d", prim());

    //Kruskal
    citire();
    initializare();
    sorteaza();
    kruskal();
    printf("%d", s);

    ////////////////////////////////////////////////////////
    //////////////Grafuri orientate/////////////////////////
    ////////////////////////////////////////////////////////

    read();
    dijkstra_heap();
    for (int i = 2; i <= n; ++i) {
        printf("%d ", d[i] == inf ? 0 : d[i]);
    }
    printf("\n");


    return 0;
}