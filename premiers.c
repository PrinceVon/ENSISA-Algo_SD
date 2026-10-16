#include <stdio.h>
#include <math.h>

/*
 * Compter les nombres premiers compris entre 2 et n inclus.
 * Retourne 0 si n < 2.
 */
int prems_naif(int n) {
    if (n < 2) {
        return 0;
    }

    int sum = 0;
    int premier[n];

    for (int i = 2; i <= n; i++) {
        int racine = (int)sqrt(i);
        int cle = 0;

        for (int j = 0; j < sum && premier[j] <= racine; j++) {
            if (i % premier[j] == 0) {
                cle = 1;
                break;
            }
        }

        if (cle == 0) {
            premier[sum] = i;
            sum++;
        }
    }

    return sum;
}

/*
 * Compter les nombres premiers compris entre 2 et n inclus,
 * avec une méthode de type crible d'Ératosthène.
 */
int prems_dyn(int n) {
    if (n < 2) {
        return 0;
    }

    int sum = 0;
    int premiers[n + 1];

    for (int i = 0; i <= n; i++) {
        premiers[i] = 0;
    }

    for (int i = 2; i <= n; i++) {
        if (premiers[i] == 0) {
            sum++;

            /* Marquer les multiples de i à partir de i*i. */
            if (i <= n / i) {
                for (int k = i * i; k <= n; k += i) {
                    premiers[k] = -1;
                }
            }
        }
    }

    return sum;
}

int main(void) {
    int n;

    printf("Entrez une limite n (entier >= 0) : ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Entrée invalide. Entrez un entier positif ou nul.\\n");
        return 1;
    }

    printf("\\nNombre de nombres premiers <= %d :\\n", n);
    printf("Méthode naïve : %d\\n", prems_naif(n));
    printf("Méthode dynamique (crible) : %d\\n", prems_dyn(n));

    return 0;
}
