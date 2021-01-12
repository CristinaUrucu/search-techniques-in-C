#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int c;
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

void subtree(int *what, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && what[left] > what[largest]) {
        largest = left;
    }
    if (right < n && what[right] > what[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(&what[i], &what[largest]);
        subtree(what, n, largest);
    }
}


void heap_sort(int *what, int n) {
    int i;
    for (i = n / 2 - 1; i >= 0; --i) {
        subtree(what, n, i);
    }
    for (i = n - 1; i > 0; i--) {
        swap(&what[0], &what[i]);
        subtree(what, i, 0);
    }
}

int partition (int *what,int low, int high) {
    int pivot = what[high];
    int j, i;
    i = (low - 1);
    for (j = low; j < high; ++j) {
        if (what[j] < pivot) {
            i++;
            swap(&what[i], &what[j]);
        }
    }
    swap(&what[i + 1], &what[high]);
    return (i + 1);
}

void quick_sort(int *what,int low,int high) {
    int partition_index;
    if (low < high) {
        partition_index = partition(what, low, high);
        quick_sort(what, low, partition_index - 1);  // Before partition_index
        quick_sort(what, partition_index + 1, high); // After partition_index
    }
}

void shell_sort(int *what, int n) {
    int i, j, value, interval = 0;
    while (interval < n / 3) {
        interval = interval * 3 + 1;
    }
    while(interval > 0){
        for (i = interval; i < n; ++i) {
            value = what[i];
            j = i;
            while((j > interval - 1) && what[j - interval] > value){
                what[j] = what[j - interval];
                j = j - interval;
            }
            what[j] = value;
        }
        interval = (interval - 1) / 3;
    }
}

int main() {
    int v[] = {5, 12, 3, 0, 22, 17};
    int n = sizeof(v) / sizeof(v[0]);
    shaker_sort(v, n);
    insertion_sort(v, n);
    selection_sort(v, n);
    bubble_sort(v, n);
    heap_sort(v, n);
    quick_sort(v, 0, n - 1);
    shell_sort(v, n);

    return 0;
}
