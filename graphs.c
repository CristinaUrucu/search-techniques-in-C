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

//citire, inserare, algoritmul lui Prim sau Kruska,
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


    return 0;
}