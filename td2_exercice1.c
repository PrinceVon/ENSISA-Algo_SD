#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* 1. Checking if the array is sorted increasing */
int is_sorted_increasing(int A[], int n) {
    for (int i = 1; i < n; i++) {
        if (A[i] <= A[i - 1])
            return 0;
    }
    return 1;
}

/* 2. linear_search */
int linear_search(int A[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (A[i] == x)
            return i;
    }
    return -1;
}

/* 3. Jump search */
int jump_search(int A[], int n, int x) {
    if (!is_sorted_increasing(A, n))
        return -1;

    int step = (int)sqrt(n);
    int start = 0;
    int end = step;

    while (start < n && A[(end < n ? end : n) - 1] < x) {
        start = end;
        end += step;
        if (start >= n)
            return -1;
        if (end > n)
            end = n;
    }

    for (int i = start; i < end; i++) {
        if (A[i] == x)
            return i;
        if (A[i] > x)
            return -1;
    }

    return -1;
}

/* 4. Binary_search */
int binary_search(int A[], int n, int x) {
    if (!is_sorted_increasing(A, n))
        return -1;

    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (A[mid] == x)
            return mid;
        if (A[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

/* 5. Performance comparison */
int main(void) {
    int n = 100000;
    int *A = malloc(n * sizeof(int));

    if (A == NULL) {
        printf("Erreur d'allocation memoire.\n");
        return 1;
    }

    /* Generer un tableau trie */
    for (int i = 0; i < n; i++)
        A[i] = i * 2;

    int x = A[n - 1];  /* cible presente */
    clock_t debut, fin;
    double temps;

    printf("Tableau trie : %s\n",
           is_sorted_increasing(A, n) ? "oui" : "non");

    printf("Linear search : indice %d\n",
           linear_search(A, n, x));
    printf("Jump search   : indice %d\n",
           jump_search(A, n, x));
    printf("Binary search : indice %d\n",
           binary_search(A, n, x));

    /* Mesuring linear search */
    debut = clock();
    linear_search(A, n, x);
    fin = clock();
    temps = (double)(fin - debut) / CLOCKS_PER_SEC;
    printf("Linear search : %.6f secondes\n", temps);

    /* Mesuring Jump search */
    debut = clock();
    jump_search(A, n, x);
    fin = clock();
    temps = (double)(fin - debut) / CLOCKS_PER_SEC;
    printf("Jump search   : %.6f secondes\n", temps);

    /* Mesuring Binary search */
    debut = clock();
    binary_search(A, n, x);
    fin = clock();
    temps = (double)(fin - debut) / CLOCKS_PER_SEC;
    printf("Binary search : %.6f secondes\n", temps);

    free(A);
    return 0;
}
