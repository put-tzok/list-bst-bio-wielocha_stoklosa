#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ns[] = { 1000, 20000, 30000, 40000/* TODO: fill values which will be used as lists' sizes */ };

// each list node contains an integer key value and pointer to next list node
struct node {
    int key;
    struct node *next;
};

// list's beginning is called the head of list
struct node *head = NULL;

struct node* list_insert(int value) {
    struct node *createNode = malloc(sizeof(createNode));    // tworze dynamicznie obiekt
    (*createNode).key = value;                                 // key od createNode ustawiam na wartosc value
    (*createNode).next = head;                                 // nastepny element po createNode jest ustawiony jako glowa, dzieki czemu bedzie na poczatku listy
    head = createNode;                                       // ustawiam glowe na pierwszy element listy czyli createNode
    return createNode;
}

struct node *p;                              // tworzê nowy obiekt strukty p

struct node* list_search(int value) {
    p = head;                                // p ustawiam jako g³owe, czyli pierwszy element listy
    while (p != NULL && (*p).key != value)   // podczas gdy p nie jest zerem i key od p nie jest wartoœci¹ value
        p = (*p).next;                       // przeskakuj na nastêpny element listy
    return p;                                // zwróæ p
    return NULL;
}

void list_delete(int value) {
    if((*head).key = value){                    // jeœli key od glowy jest wartoœci¹ value
        head = (*head).next;}                   // przeskakuj na nastêpny element listy
    else                                        // w innym przypadku
    {
        struct node *prev = head;               // tworzê nowy obiekt struktury prev i ustawiam go jako g³owê
        p = (*head).next;                       // ustawiam p jako nastêpny element od g³owy
        while(p != NULL && (*p).key != value)   // podczas gdy p nie jest zerem i key od p nie jest wartoœci¹ value
        {
            prev = p;                           // ustawiam prev jako p
            p = (*p).next;                      // p przeskakuje na nastêpny element listy
        }
        if (p != NULL){                         // jeœli w tym else jeszcze moje p nie jest tylko zerem
            (*prev).next = (*p).next;}          // ustawiam nastêpny element od prev na nastêpny element od p
    }
}

unsigned int list_size() {
    int size = 0;                               // tworze inta size(rozmiar) i ustawiam jako 0
    p = head;                                   // ustawiam moje p jako g³owê
    while(p != NULL)                            // podczas gdy p nie jest zerem
    {
        size = size + 1;                        // moj size(rozmiar) zwiêksza siê o 1
        p = (*p).next;                          // moje p przeskakuje na kolejny element listy
    }
    return size;                                // zwracam size(rozmiar)
    return 0;
}

/*
 * Fill an array with increasing values.
 *
 * Parameters:
 *      int *t:     pointer to the array
 *      int n:      number of elements in the array
 */
void fill_increasing(int *t, int n) {
    for (int i = 0; i < n; i++) {
        t[i] = i;
    }
}

/*
 * Reorder array elements in a random way.
 *
 * Parameters:
 *      int *t:     pointer to the array
 *      int n:      number of elements in the array
 */
void shuffle(int *t, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % i;
        int temp = t[i];
        t[i] = t[j];
        t[j] = temp;
    }
}

int main() {
    bool no_yes[] = { false, true };

    for (unsigned int i = 0; i < sizeof(no_yes) / sizeof(*no_yes); i++) {
        bool enable_shuffle = no_yes[i];

        for (unsigned int j = 0; j < sizeof(ns) / sizeof(*ns); j++) {
            unsigned int n = ns[j];

            // always create an array of size `n` and fill it with increasing values
            int *t = malloc(n * sizeof(*t));
            fill_increasing(t, n);

            // if true, reorder array elements randomly
            if (enable_shuffle) {
                shuffle(t, n);
            }

            // insert elements in the order present in array `t`
            clock_t insertion_time = clock();
            for (unsigned int k = 0; k < n; k++) {
                struct node *iter = list_insert(t[k]);
                assert(iter != NULL);       // inserted element cannot be NULL
                assert(iter->key == t[k]);  // inserted element must contain the expected value
            }
            insertion_time = clock() - insertion_time;

            // reorder array elements before searching
            shuffle(t, n);

            // search for every element in the order present in array `t`
            clock_t search_time = clock();
            for (unsigned int k = 0; k < n; k++) {
                struct node *iter = list_search(t[k]);
                assert(iter != NULL);       // found element cannot be NULL
                assert(iter->key == t[k]);  // found element must contain the expected value
            }
            search_time = clock() - search_time;

            // reorder array elements before deletion
            shuffle(t, n);

            // delete every element in the order present in array `t`
            for (unsigned int k = 0, l = n; k < n; k++, l--) {
                assert(list_size() == l);   // list size must be equal to the expected value
                list_delete(t[k]);
            }
            assert(list_size() == 0);       // after all deletions, the list size is zero
            assert(head == NULL);           // after all deletions, the list's head is NULL

            free(t);

            printf("%d\t%s\t%f\t%f\n", n, enable_shuffle ? "true" : "false",
                    (double)insertion_time / CLOCKS_PER_SEC,
                    (double)search_time / CLOCKS_PER_SEC);
        }
    }
    return 0;
}
