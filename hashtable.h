#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//tamanho da hash table
#define TABLE_SIZE 10000

//elemento da hash table
typedef struct HASHTABLE {
    char nome[35]; //nome do artista
    unsigned int hash; //hash criada pelo nome+sobrenome do artista
    int index; //index horizontal, para usar na implementacao com matriz
    struct HASHTABLE *next_colision; // lista encadeada dos elementos com mesmo hash
} HASHTABLE;

//cabecalho das funcoes
unsigned int name_to_hash(char *);
HASHTABLE *create_hash_table_element(HASHTABLE **, char *, int *, int **);
void hash_table_insert(HASHTABLE **, HASHTABLE *);
HASHTABLE *find_hash_element(HASHTABLE **, unsigned int);
int hash(HASHTABLE **, char *, int *, int **);
#endif