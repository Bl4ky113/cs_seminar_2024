/**
 * Simple implementation of a Merge Sort in C
 **/

#include <stdio.h>
#include <stdlib.h>

int *generate_number_arr (int arr_size) {
    int *arr = (int *) malloc(sizeof(int) * arr_size);

    for (int i = 0; i < arr_size; i++) {
        arr[i] = rand() % 100;
    }

    return arr;
}

void merge_parts_arr (int *arr, int i_btm, int i_mid, int i_top) {
    int i_left, i_right, i_general;
    int size_left = i_mid - i_btm + 1;
    int size_right = i_top - i_mid;

    int arr_left[size_left];
    int arr_right[size_right];

    for (i_left = 0; i_left < size_left; i_left++) {
        arr_left[i_left] = arr[i_btm + i_left];
    }

    for (i_right = 0; i_right < size_right; i_right++) {
        arr_right[i_right] = arr[(i_mid + 1) + i_right];
    }

    i_left = 0;
    i_right = 0;
    i_general = i_btm;

    while (i_left < size_left && i_right < size_right) {
        if (arr_left[i_left] <= arr_right[i_right]) {
            arr[i_general] = arr_left[i_left];
            i_left++;
        } else {
            arr[i_general] = arr_right[i_right];
            i_right++;
        }

        i_general++;
    }

    while (i_left < size_left) {
        arr[i_general] = arr_left[i_left];
        i_left++;
        i_general++;
    }

    while (i_right < size_right) {
        arr[i_general] = arr_right[i_right];
        i_right++;
        i_general++;
    }

    return;
}

void merge_sort_number_arr (int *arr, int i_btm, int i_top) {
    if (i_btm >= i_top) {
        return;
    }

    int i_mid = i_btm + (i_top - i_btm) / 2;

    merge_sort_number_arr(arr, i_btm, i_mid);
    merge_sort_number_arr(arr, i_mid + 1, i_top);

    merge_parts_arr(arr, i_btm, i_mid, i_top);
    return;
}

void print_arr (int arr_size, int *arr) {
    fprintf(stdout, "[");
    for (int i = 0; i < arr_size; i++) {
        if (i != 0) {
            fprintf(stdout, ", ");
        }

        fprintf(stdout, "%d", arr[i]);
    }
    fprintf(stdout, "]\n");
    return;
}

int main (int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "ARRAY SIZE ARG NEEDED\n");
        return 1;
    }

    int arr_size = 0;
    sscanf(argv[1], "%d", &arr_size);
    
    int *num_arr = generate_number_arr(arr_size);
    print_arr(arr_size, num_arr);

    merge_sort_number_arr(num_arr, 0, arr_size - 1);
    print_arr(arr_size, num_arr);

    return 0;
}
