#include <stdio.h>

/*
 * Calcul itératif du n-ième terme de Fibonacci.
 * Convention : F(0) = 0 et F(1) = 1.
 */
int fib_dyn(int n) {
    if (n < 0) {
        return -1; /* Entrée invalide */
    }

    if (n <= 1) {
        return n;
    }

    int val1 = 0;
    int val2 = 1;

    for (int i = 2; i <= n; i++) {
        int temp = val1 + val2;
        val1 = val2;
        val2 = temp;
    }

    return val2;
}

/*
 * Calcul récursif naïf du n-ième terme de Fibonacci.
 */
int fib_naif(int n) {
    if (n < 0) {
        return -1; /* Entrée invalide */
    }

    if (n <= 1) {
        return n;
    }

    return fib_naif(n - 1) + fib_naif(n - 2);
}

int main(void) {
    int n;

    printf("Entrez n pour calculer F(n) (entier >= 0) : ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Entrée invalide. Entrez un entier positif ou nul.\\n");
        return 1;
    }

    if (n > 45) {
        printf("Attention : la méthode récursive naïve est lente pour les grandes valeurs.\\n");
    }

    printf("\\nFibonacci F(%d) :\\n", n);
    printf("Méthode dynamique : %d\\n", fib_dyn(n));
    printf("Méthode naïve récursive : %d\\n", fib_naif(n));

    return 0;
}
