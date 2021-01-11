//search-techniques-in-C
//Just some basic search techniques in C
#include <stdio.h>
#include <stdlib.h>
//for ascending sorted arrays
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

int main() {
  int v[5] = {0, 1, 2, 3, 4};
  linear_search(v, 5, 4);
  printf("\n");
  printf("%d\n", binary_search(0, 4, v, 4));
  printf("%d\n", interpolation_search(0, 4, v, 4));
  
  
  return 0;
}
