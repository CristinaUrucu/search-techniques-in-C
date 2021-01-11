#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    Student c;
    c = *a;
    *a = *b;
    *b = c;
}

void shaker_sort(int *where, int len) {
    int i, j, k;
    for (i = 0; i < len; ++i) {
        for (j = i + 1; j < len; ++j){
            if (where[j] < where[j - 1]) {
                swap(&where[j], &where[j - 1]);
            }
        }
        len--;
        for (k = len - 1; k > i; --k) {
            if (where[k] < where[k - 1]) {
                swap(&where[k], &where[k - 1]);
            }
        }
    }
}

void insertion_sort(int *what, int len){
    int i, j, key;
    for (i = 1; i < len; ++i) {
        key = what[i];
        j = i - 1;
        while (j >= 0 && what[j] > key) {
            what[j + 1] = what[j];
            j = j - 1;
        }
        what[j + 1] =  key;
    }  
}

void selection_sort(int *what, int len) {
    int i, j, min_idx;
    for (i = 0; i < len - 1; ++i) {
        min_idx = i;
        for (j = i + 1; j < len; j++) {
            if (what[j] < what[min_idx]) {
                min_idx = j;
            }
        }
        swap(&what[min_idx], &what[i]);
    }
}

void bubble_sort(int *what, int n) {
   int i, j;
   for (i = 0; i < n-1; i++) {
       for (j = 0; j < n-i-1; j++) {
           if (what[j] > what[j + 1]) {
              swap(&what[j], &what[j+1]);
           }
       }
   }
}




int main() {
int v[] = {5, 12, 3, 0, 22, 17};
shaker_sort(v, 6);
insertion_sort(v, 6);
selection_sort(v, 6);
bubble_sort(v, 6);

return 0;
}
