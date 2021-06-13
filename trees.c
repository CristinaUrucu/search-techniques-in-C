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

        ///////////////////////////////////////////////////////////////
        ///////////////////////Binary Trees////////////////////////////
        ///////////////////////////////////////////////////////////////

        scanf("%d", &n);
        for (i = 0; i < n; ++i) {
            scanf("%d", &cheie);
            arb = add(arb, cheie);
        }
        printf("%d\n", inaltime(arb, 1));
        preordine(arb);


        free(arb);



    return 0;
}