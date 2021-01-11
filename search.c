//search-techniques-in-C
//Just some basic search techniques in C
#include <stdio.h>
#include <stdlib.h>

void linear_search(int *where, int len, int what){
    int i;
    for (i = 0; i < len; ++i) {
        if (where(i) == x) {
            //somethig
            printf("%d ", i);
        }
    }
}

int binary_search(int left, int right, int *where, int what){
//for ascending sorted arrays
    if (left > right) {
        return -1;
    }
    int mid = (right - left) / 2 + left;
    if (where[mid] == what) {
        return mid;
    }
    if (where[mid] < what) {
        return  binary_search(mid + 1, right, where, what);
    } else {
        return  binary_search(left, mid - 1, where, what);
    }    
}

int main() {
  int v[5] = {0, 1, 2, 3, 4};
  linear_search(v, 5, 4);
  printf("\n");
  printf("%d\n", binary_search(0, 4, v, 4));
  
  return 0;
}
