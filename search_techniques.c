//Just some basic search techniques in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//for ascending sorted arrays
void linear_search(int *where, int len, int what){
    int i;
    for (i = 0; i < len; ++i) {
        if (where(i) == x) {
            //somethig
            printf("Linear search: %d", i);
        }
    }
}

int binary_search(int left, int right, int *where, int what){
    if (left > right) {
        return -1;
    }
    int mid = (right - left) >> 1 + left;
    if (where[mid] == what) {
        return mid;
    }
    if (where[mid] < what) {
        return  binary_search(mid + 1, right, where, what);
    } else {
        return  binary_search(left, mid - 1, where, what);
    }    
}

int interpolation_search(int low, int high, int *where, int what) {
    if (low > high) {
        return -1;
    }
    int mid = low + ((what - where[low]) * (high - low) / (where[high] - where[low]));
    if (where[mid] == what) {
        return mid + 1;
    }
    if (where[mid] > what) {
        return interpolation_search(mid - 1, high,  where, what);
    }else {
        return interpolation_search(low, mid + 1,  where, what);
    }
}

//searches for strings
// preprocessing for the suffix rule
void preprocess_strong_suffix(int *shift, int *bpos, char *cuvant){
    int m = strlen(cuvant), i = m, j = m + 1;
    bpos[i] = j;
    while(i > 0) {
        //if the character in position i-1 is different from that in position j-1
        // continue searching to the right
        while(j <= m && cuvant[i - 1] != cuvant[j - 1]) {
            if (shift[j]==0) {
                shift[j] = j - i;
            }
            //we put the position of the next border
            j = bpos[j];
        }
        // p [i-1] match p [j-1], the border is found
        i--;
        j--;
        bpos[i] = j;
    }
}

//preprocessing for the second case
void preprocess_case2(int *shift, int *bpos, char *cuvant) {
    int m = strlen(cuvant), i, j;
    j = bpos[0];
    for(i = 0; i <= m; ++i) {
        // we set the border position of the first pattern character in 
        //the shift vector that have shift [i] = 0
        if(shift[i] == 0) {
            shift[i] = j;
        }
        // the suffix becomes smaller than bpos [0] so we use the next
        //lowest value of border as the value of j
        if (i == j) {
            j = bpos[j];
        }
    }
}

int boyer_moore_search(char *x, char *cuvant) {
    int nr = 0, s = 0, j, m = strlen(cuvant), n = strlen(x);
    int bpos[m + 1], shift[m + 1];
    for (i = 0; i < m + 1; ++i){
        shift[i] = 0;
    }
    preprocess_strong_suffix(shift, bpos, cuvant);
    preprocess_case2(shift, bpos, cuvant);
    while(s <= n - m) {
        j = m - 1;
        //we reduce the index j of the word as long as the characters
        //match for this shift
        while((j >= 0) && (cuvant[j] == x[s + j] || cuvant[j] == '*')) {
            j--;
        }
        // if we find the occurrence at this shift, j will be -1 after while
        if (j < 0) {
            nr++;
            s += shift[0];
        } else {
            //pat[i] different from pat[s + j] so shift of shift[j + 1] times
            s += shift[j+1];
        }
    }
    return nr;
}

//makes the array for prefixes that are also suffixes
void prefix_suffix(char* cuvant, int* ps) {
    int m = strlen(cuvant), len = 0, i = 1;
    ps[0] = 0;
    while (i < m) {
       if (cuvant[i] == cuvant[len]) {
          len++;
          ps[i] = len;
          i++;
       } else {
          if (len != 0) {
          len = ps[len - 1];
          } else {
             ps[i] = 0;
             i++;
          }
       }
    }
}

int kmp_search(char* x, char* cuvant) {
    int nr = 0, m = strlen(cuvant), n = strlen(x), ps[m], i = 0, j = 0;
    prefix_suffix(cuvant, ps);
    while (i < n) {
       if (cuvant[j] == x[i] || cuvant[j] == '*') {
          j++;
          i++;
       }
       if (j == m) {
          nr++;
          j = ps[j - 1];
       } else if (i < n && cuvant[j] != x[i] && cuvant[j] != '*') {
          if (j != 0) {
            j = ps[j - 1];
          } else {
            i++;
          }
       }
    }
   return nr;
}

int main() {
    clock_t start_t = clock();
    int v[5] = {0, 1, 2, 3, 4};
    
    clock_t t1_linear = clock();
    linear_search(v, 5, 4);
    clock_t t2_linear = clock();
    printf(" - time: %d\n", t2_linear - t1_linear);
    
    clock_t t1_binary = clock();
    printf("Binary search: %d", binary_search(0, 4, v, 4));
    clock_t t2_binary = clock();
    printf(" - time: %d\n", t2_binary - t1_binary);
    
    clock_t t1_interpolation = clock();
    printf("Interpolation search: %d ", interpolation_search(0, 4, v, 4));
    clock_t t2_interpolation = clock();
    printf(" - time: %d\n", t2_interpolation - t1_interpolation);
    
    char s1[] = {"ANA ARE MERE"};
    char s2[] = {"ANA"};
    char s3[] = {"A*A"};
    clock_t t1_BM = clock();
    printf("Boyer Moore: %d", boyer_moore(s1, s2));
    clock_t t2_BM = clock();
    printf(" - time: %d\n", t2_BM - t1_BM);
    clock_t t3_BM = clock();
    printf("Boyer Moore: %d", boyer_moore(s1, s3));
    clock_t t4_BM = clock();
    printf(" - time: %d\n", t4_BM - t3_BM);
    
    clock_t t1_KMP = clock();
    printf("KMP: %d", cautare_kmp(s1, s2));
    clock_t t2_KMP = clock();
    printf(" - time: %d\n", t2_KMP - t1_KMP);
    clock_t t3_KMP = clock();
    printf("KMP: %d", cautare_kmp(s1, s3));
    clock_t t4_KMP = clock();
    printf(" - time: %d\n", t4_KMP - t3_KMP);
    
    clock_t end_t = clock();
    clock_t total_t = (end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total CPU time: %d", total_t);
  
  
  return 0;
}
