#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10
#define STACK_MAX 100
#define QUEUE_MAX 5
#define HASH_SIZE 10

/* ============================================================
 * 1. TABLEAUX
 * ============================================================ */

int array_get(const int a[], int i) {
    return a[i];
}

void array_delete(int a[], int *n, int i) {
    if (n == NULL || i < 0 || i >= *n) {
        printf("Suppression impossible : indice invalide.\n");
        return;
    }

    for (int j = i; j < *n - 1; j++) {
        a[j] = a[j + 1];
    }
    (*n)--;
}

int array_insert(int a[], int *n, int capacity, int i, int x) {
    if (n == NULL || i < 0 || i > *n || *n >= capacity) {
        printf("Insertion impossible : indice invalide ou tableau plein.\n");
        return 0;
    }

    for (int j = *n; j > i; j--) {
        a[j] = a[j - 1];
    }
    a[i] = x;
    (*n)++;
    return 1;
}

void print_array(const int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

/* ============================================================
 * 2. LISTES CHAINEES
 * ============================================================ */

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *list_insert_head(Node *head, int val) {
    Node *new_node = malloc(sizeof *new_node);
    if (new_node == NULL) {
        fprintf(stderr, "Erreur : allocation memoire impossible.\n");
        return head;
    }

    new_node->value = val;
    new_node->next = head;
    return new_node;
}

void print_list(const Node *head) {
    const Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

/* ============================================================
 * 3. PILES (STACK)
 * ============================================================ */

typedef struct {
    int S[STACK_MAX];
    int n;
} Stack;

void init_stack(Stack *stack) {
    stack->n = 0;
}

int stack_push(Stack *stack, int x) {
    if (stack->n >= STACK_MAX) {
        printf("Pile pleine !\n");
        return 0;
    }

    stack->S[stack->n] = x;
    stack->n++;
    return 1;
}

int stack_peek(const Stack *stack, int *value) {
    if (stack->n == 0) {
        printf("Pile vide !\n");
        return 0;
    }

    *value = stack->S[stack->n - 1];
    return 1;
}

int stack_pop(Stack *stack, int *value) {
    if (stack->n == 0) {
        printf("Pile vide !\n");
        return 0;
    }

    stack->n--;
    *value = stack->S[stack->n];
    return 1;
}

/* ============================================================
 * 4. FILES CIRCULAIRES (QUEUE)
 * ============================================================ */

typedef struct {
    int Q[QUEUE_MAX];
    int front;
    int rear;
    int size;
} Queue;

void init_queue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int enqueue(Queue *q, int x) {
    if (q->size == QUEUE_MAX) {
        printf("File pleine !\n");
        return 0;
    }

    q->rear = (q->rear + 1) % QUEUE_MAX;
    q->Q[q->rear] = x;
    q->size++;
    return 1;
}

int dequeue(Queue *q, int *value) {
    if (q->size == 0) {
        printf("File vide !\n");
        return 0;
    }

    *value = q->Q[q->front];
    q->front = (q->front + 1) % QUEUE_MAX;
    q->size--;
    return 1;
}

/* ============================================================
 * 5. TABLES DE HACHAGE (CHAINAGE)
 * ============================================================ */

typedef struct HashNode {
    char key[50];
    int value;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode *buckets[HASH_SIZE];
} HashTable;

void init_hash_table(HashTable *ht) {
    for (int i = 0; i < HASH_SIZE; i++) {
        ht->buckets[i] = NULL;
    }
}

int hash_function(const char *key) {
    unsigned int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += (unsigned char)key[i];
    }
    return (int)(sum % HASH_SIZE);
}

int hash_insert(HashTable *ht, const char *key, int value) {
    if (key == NULL || strlen(key) >= 50) {
        printf("Cle invalide ou trop longue (maximum 49 caracteres).\n");
        return 0;
    }

    int index = hash_function(key);
    HashNode *current = ht->buckets[index];

    /* Mettre a jour la valeur si la cle existe deja. */
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return 1;
        }
        current = current->next;
    }

    HashNode *new_node = malloc(sizeof *new_node);
    if (new_node == NULL) {
        fprintf(stderr, "Erreur : allocation memoire impossible.\n");
        return 0;
    }

    strcpy(new_node->key, key);
    new_node->value = value;
    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;
    return 1;
}

int hash_search(const HashTable *ht, const char *key, int *value) {
    int index = hash_function(key);
    const HashNode *current = ht->buckets[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            *value = current->value;
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void free_hash_table(HashTable *ht) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *current = ht->buckets[i];
        while (current != NULL) {
            HashNode *temp = current;
            current = current->next;
            free(temp);
        }
        ht->buckets[i] = NULL;
    }
}

/* ============================================================
 * 6. STRUCTURES C IMBRIQUEES
 * ============================================================ */

typedef struct {
    int street_number;
    char street_name[50];
    char city[30];
} Address;

typedef struct {
    int student_id;
    char name[40];
    float gpa;
    Address home_address;
} Student;

void print_student(const Student *student) {
    printf("Identifiant : %d\n", student->student_id);
    printf("Nom : %s\n", student->name);
    printf("Moyenne : %.2f\n", student->gpa);
    printf("Adresse : %d, %s, %s\n",
           student->home_address.street_number,
           student->home_address.street_name,
           student->home_address.city);
}

/* ============================================================
 * PROGRAMME PRINCIPAL : TESTS
 * ============================================================ */

int main(void) {
    /* 1. Test des tableaux */
    printf("=== 1. TEST TABLEAU ===\n");
    int my_array[MAX_SIZE] = {52, -8, 11, 0, 2, -7};
    int size = 6;

    printf("Tableau initial : ");
    print_array(my_array, size);

    printf("Valeur a l'index 2 : %d\n", array_get(my_array, 2));

    printf("Insertion de 3 a l'index 3 : ");
    if (array_insert(my_array, &size, MAX_SIZE, 3, 3)) {
        print_array(my_array, size);
    }

    printf("Suppression a l'index 2 : ");
    array_delete(my_array, &size, 2);
    print_array(my_array, size);

    /* 2. Test de la liste chainee */
    printf("\n=== 2. TEST LISTE CHAINEE ===\n");
    Node *my_list = NULL;
    my_list = list_insert_head(my_list, 11);
    my_list = list_insert_head(my_list, 32);
    my_list = list_insert_head(my_list, -2);

    printf("Ma liste chainee : ");
    print_list(my_list);

    /* 3. Test de la pile */
    printf("\n=== 3. TEST PILE (STACK) ===\n");
    Stack my_stack;
    init_stack(&my_stack);

    stack_push(&my_stack, 10);
    stack_push(&my_stack, 20);
    stack_push(&my_stack, 30);

    int value;
    if (stack_peek(&my_stack, &value)) {
        printf("Sommet actuel (Peek) : %d\n", value);
    }
    if (stack_pop(&my_stack, &value)) {
        printf("Element retire (Pop) : %d\n", value);
    }
    if (stack_peek(&my_stack, &value)) {
        printf("Nouveau sommet (Peek) : %d\n", value);
    }

    /* 4. Test de la file */
    printf("\n=== 4. TEST FILE (QUEUE) ===\n");
    Queue my_queue;
    init_queue(&my_queue);

    enqueue(&my_queue, 100);
    enqueue(&my_queue, 200);
    enqueue(&my_queue, 300);

    if (dequeue(&my_queue, &value)) {
        printf("Element sorti (Dequeue) : %d (attendu : 100)\n", value);
    }
    if (dequeue(&my_queue, &value)) {
        printf("Element sorti (Dequeue) : %d (attendu : 200)\n", value);
    }

    /* 5. Test de la table de hachage */
    printf("\n=== 5. TEST TABLE DE HACHAGE ===\n");
    HashTable my_map;
    init_hash_table(&my_map);

    hash_insert(&my_map, "Alice", 19);
    hash_insert(&my_map, "Bob", 14);

    if (hash_search(&my_map, "Alice", &value)) {
        printf("Note de Alice retrouvee : %d / 20\n", value);
    } else {
        printf("Alice n'a pas ete trouvee.\n");
    }

    if (hash_search(&my_map, "Charlie", &value)) {
        printf("Note de Charlie : %d\n", value);
    } else {
        printf("Charlie n'existe pas dans la table.\n");
    }

    /* 6. Test des structures imbriquees */
    printf("\n=== 6. TEST STRUCTURE C ===\n");
    Student student1 = {
        .student_id = 24001,
        .name = "Alice Dupont",
        .gpa = 16.5f,
        .home_address = {
            .street_number = 12,
            .street_name = "Rue de l'Universite",
            .city = "Mulhouse"
        }
    };

    print_student(&student1);

    /* Liberation de la memoire allouee dynamiquement */
    free_list(my_list);
    free_hash_table(&my_map);

    return 0;
}
