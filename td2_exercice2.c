#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 1. Preparing the sorting system */

void swap_int(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int is_sorted_ascending(int A[], int n) {
    for (int i = 1; i < n; i++)
        if (A[i] < A[i - 1])
            return 0;
    return 1;
}

void copy_array(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

/* 2. Selection sort */

void selection_sort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;

        for (int j = i + 1; j < n; j++)
            if (A[j] < A[min])
                min = j;

        if (min != i)
            swap_int(&A[i], &A[min]);
    }
}

/* 3. Insertion sort */

void insertion_sort(int A[], int n) {
    for (int i = 1; i < n; i++) {
        int key = A[i];
        int j = i - 1;

        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }

        A[j + 1] = key;
    }
}

/* 4. Bubble sort */

void bubble_sort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int changed = 0;

        for (int j = 0; j < n - 1 - i; j++) {
            if (A[j] > A[j + 1]) {
                swap_int(&A[j], &A[j + 1]);
                changed = 1;
            }
        }

        if (!changed)
            break;
    }
}

/* 5. Merge sort */

void merge(int A[], int temp[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (A[i] <= A[j])
            temp[k++] = A[i++];
        else
            temp[k++] = A[j++];
    }

    while (i <= mid)
        temp[k++] = A[i++];

    while (j <= right)
        temp[k++] = A[j++];

    for (i = left; i <= right; i++)
        A[i] = temp[i];
}

void merge_sort_rec(int A[], int temp[], int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    merge_sort_rec(A, temp, left, mid);
    merge_sort_rec(A, temp, mid + 1, right);
    merge(A, temp, left, mid, right);
}

void merge_sort(int A[], int temp[], int n) {
    merge_sort_rec(A, temp, 0, n - 1);
}

/* 6. Quick sort */

int partition(int A[], int low, int high) {
    int pivot = A[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (A[j] <= pivot) {
            i++;
            swap_int(&A[i], &A[j]);
        }
    }

    swap_int(&A[i + 1], &A[high]);
    return i + 1;
}

void quick_sort_rec(int A[], int low, int high) {
    if (low < high) {
        int p = partition(A, low, high);
        quick_sort_rec(A, low, p - 1);
        quick_sort_rec(A, p + 1, high);
    }
}

void quick_sort(int A[], int n) {
    quick_sort_rec(A, 0, n - 1);
}

/* 7. Comparaison des performances */

int main(void) {
    int sizes[] = {1000, 5000, 10000};
    int nb_sizes = 3;

    srand((unsigned int)time(NULL));

    printf("Comparaison des tris (temps en secondes)\n\n");
    printf("%-8s %-12s %-12s %-12s %-12s %-12s\n",
           "n", "Selection", "Insertion", "Bubble",
           "Merge", "Quick");

    for (int s = 0; s < nb_sizes; s++) {
        int n = sizes[s];

        int *original = malloc(n * sizeof(int));
        int *A = malloc(n * sizeof(int));
        int *temp = malloc(n * sizeof(int));

        if (original == NULL || A == NULL || temp == NULL) {
            printf("Erreur d'allocation memoire.\n");
            free(original);
            free(A);
            free(temp);
            return 1;
        }

        for (int i = 0; i < n; i++)
            original[i] = rand() % 1000001;

        clock_t start;
        double t[5];

        copy_array(original, A, n);
        start = clock();
        selection_sort(A, n);
        t[0] = (double)(clock() - start) / CLOCKS_PER_SEC;

        copy_array(original, A, n);
        start = clock();
        insertion_sort(A, n);
        t[1] = (double)(clock() - start) / CLOCKS_PER_SEC;

        copy_array(original, A, n);
        start = clock();
        bubble_sort(A, n);
        t[2] = (double)(clock() - start) / CLOCKS_PER_SEC;

        copy_array(original, A, n);
        start = clock();
        merge_sort(A, temp, n);
        t[3] = (double)(clock() - start) / CLOCKS_PER_SEC;

        copy_array(original, A, n);
        start = clock();
        quick_sort(A, n);
        t[4] = (double)(clock() - start) / CLOCKS_PER_SEC;

        printf("%-8d ", n);
        for (int i = 0; i < 5; i++)
            printf("%-12.6f ", t[i]);
        printf("\n");

        /* Verifier le resultat */
        printf("Tableau trie correctement : %s\n\n",
               is_sorted_ascending(A, n) ? "oui" : "non");

        free(original);
        free(A);
        free(temp);
    }

    return 0;
}
