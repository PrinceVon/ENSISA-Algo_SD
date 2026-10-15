/*
 * TD d'algorithmique : cinq algorithmes de tri
 * Compilation : gcc -std=c11 -Wall -Wextra -pedantic tri.c -o tri
 * Execution   : ./tri
 */
#include <stdio.h>
#include <stdlib.h>

void print_array(const int a[], int n) {
    for (int i = 0; i < n; ++i) printf("%d%s", a[i], i + 1 == n ? "\n" : " ");
}
void copy_array(int dst[], const int src[], int n) {
    for (int i = 0; i < n; ++i) dst[i] = src[i];
}
void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }
int is_sorted(const int a[], int n) {
    for (int i = 1; i < n; ++i) if (a[i - 1] > a[i]) return 0;
    return 1;
}

/* 1. Tri par selection : O(n^2) dans tous les cas. */
void selection_sort(int a[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < n; ++j)
            if (a[j] < a[min]) min = j;
        if (min != i) swap(&a[i], &a[min]);
    }
}

/* 2. Tri par insertion : meilleur cas O(n), pire cas O(n^2). */
void insertion_sort(int a[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) { a[j + 1] = a[j]; --j; }
        a[j + 1] = key;
    }
}

/* 3. Tri a bulles : meilleur cas O(n), pire cas O(n^2). */
void bubble_sort(int a[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (a[j] > a[j + 1]) { swap(&a[j], &a[j + 1]); swapped = 1; }
        }
        if (!swapped) break;
    }
}

/* 4. Tri fusion : O(n log n), memoire supplementaire O(n). */
static void merge(int a[], int temp[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right)
        temp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
    while (i <= mid) temp[k++] = a[i++];
    while (j <= right) temp[k++] = a[j++];
    for (i = left; i <= right; ++i) a[i] = temp[i];
}
static void merge_sort_rec(int a[], int temp[], int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort_rec(a, temp, left, mid);
    merge_sort_rec(a, temp, mid + 1, right);
    merge(a, temp, left, mid, right);
}
int merge_sort(int a[], int n) {
    if (n <= 1) return 1;
    int *temp = malloc((size_t)n * sizeof *temp);
    if (temp == NULL) {
        fprintf(stderr, "Erreur : allocation memoire impossible pour le tri fusion.\n");
        return 0;
    }
    merge_sort_rec(a, temp, 0, n - 1);
    free(temp);
    return 1;
}

/* 5. Tri rapide : moyen O(n log n), pire cas O(n^2). */
static int partition(int a[], int low, int high) {
    int pivot = a[high], i = low - 1;
    for (int j = low; j < high; ++j)
        if (a[j] <= pivot) { ++i; swap(&a[i], &a[j]); }
    swap(&a[i + 1], &a[high]);
    return i + 1;
}
static void quick_sort_rec(int a[], int low, int high) {
    if (low < high) {
        int p = partition(a, low, high);
        quick_sort_rec(a, low, p - 1);
        quick_sort_rec(a, p + 1, high);
    }
}
void quick_sort(int a[], int n) { if (n > 1) quick_sort_rec(a, 0, n - 1); }

int main(void) {
    const int original[] = {29, -3, 17, 0, 8, 8, -12, 41, 5};
    const int n = (int)(sizeof original / sizeof original[0]);
    int a[sizeof original / sizeof original[0]];

    printf("Tableau initial : ");
    print_array(original, n);

    printf("\n=== 1. TRI PAR SELECTION ===\n");
    copy_array(a, original, n); selection_sort(a, n); print_array(a, n);
    printf("Verification : %s\n", is_sorted(a, n) ? "OK" : "ECHEC");

    printf("\n=== 2. TRI PAR INSERTION ===\n");
    copy_array(a, original, n); insertion_sort(a, n); print_array(a, n);
    printf("Verification : %s\n", is_sorted(a, n) ? "OK" : "ECHEC");

    printf("\n=== 3. TRI A BULLES ===\n");
    copy_array(a, original, n); bubble_sort(a, n); print_array(a, n);
    printf("Verification : %s\n", is_sorted(a, n) ? "OK" : "ECHEC");

    printf("\n=== 4. TRI FUSION ===\n");
    copy_array(a, original, n);
    if (merge_sort(a, n)) {
        print_array(a, n);
        printf("Verification : %s\n", is_sorted(a, n) ? "OK" : "ECHEC");
    }

    printf("\n=== 5. TRI RAPIDE ===\n");
    copy_array(a, original, n); quick_sort(a, n); print_array(a, n);
    printf("Verification : %s\n", is_sorted(a, n) ? "OK" : "ECHEC");
    return 0;
}
