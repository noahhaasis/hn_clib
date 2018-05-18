#include "array.h"


bool array_contains(void *arr[], int arr_len, void *elem) {
    for (int i = 0; i < arr_len; i++) {
        if (arr[i] == elem) { return true; }
    }
    return false;
}
