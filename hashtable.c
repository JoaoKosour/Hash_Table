// Implementacao de uma tabela hash com codificação de strings - Joao Kosour USP 11218556

#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

int hash(HASHTABLE **hash_table, char *_nome, int *k, int **atores) {
    unsigned int hash = name_to_hash(_nome);
    HASHTABLE *search_elem = find_hash_element(hash_table, hash);
    if (search_elem){
        if (!strcmp(_nome, search_elem->nome))
        return search_elem->index;
        else
            printf("Dois nomes tem a mesma hash: %d \n-> %s \n-> %s\nVerifique a linha 32 do arquivo hashtable.c!\n", hash, _nome, search_elem->nome);
    }
    search_elem = create_hash_table_element(hash_table, _nome, k, atores);
    hash_table_insert(hash_table, search_elem);
    return search_elem->index;
}


// Essa funcao transforma uma string em hash, só sao levados em conta os 10 primeiros caracteres
unsigned int name_to_hash(char *nome) {
    unsigned int hash = 0;

    for (size_t i = 0; nome[i] != '\0'; i++) {
        hash += (((hash + nome[i] + i)) + (i+1)) * ((i%7) + 1);
    }
    //printf("\nA hash criada para ''%s'' foi %ld", nome, hash);
    return hash;
}


// Essa funcao insere um elemento na hash table, lidando com colisoes
void hash_table_insert(HASHTABLE **hash_table, HASHTABLE *hash) {
    // Fazemos o mod entre a hash e o define TABLE_SIZE para descobrir o index na tabela hash
    int table_index = hash->hash % TABLE_SIZE;

    // Criamos um elemento aux para podermos percorrer as listas de colisao se preciso
    HASHTABLE *aux = hash_table[table_index];

    // Se no nosso index nao tem nada, inserimos ali mesmo
    if (table_index <= TABLE_SIZE && !hash_table[table_index]) 
        hash_table[table_index] = hash;

    // Se no nosso index tem algo, vamos percorrendo a lista até achar onde encaixar
    // Atualizamos o index j para podermos usar a estrutura de matriz da solucao
    else {
        while (1) {
            if (aux->next_colision == NULL) {
                aux->next_colision = hash;
                break;
            }
            aux = aux->next_colision;
        }
    }
}


// Essa funcao cria um elemento da hash table e retorna um ponteiro para ele.
HASHTABLE *create_hash_table_element(HASHTABLE **hash_table, char *_nome, int *k, int **atores) {
    // Criamos o novo elemento da hashtable
    HASHTABLE *new_table = calloc(1, sizeof(HASHTABLE));
    new_table->hash = name_to_hash(_nome);
    new_table->index = *k;
    *k = *k + 1;
    new_table->next_colision = NULL;
    strcpy(new_table->nome, _nome);

    *atores = realloc(*atores, (*k) * sizeof(unsigned int));
    atores[0][new_table->index] = new_table->hash;

    return new_table;
}


// Essa funcao acessa a hash table e busca por uma dada hash, retorna um ponteiro para o elemento encontrado
HASHTABLE *find_hash_element(HASHTABLE **hash_table, unsigned int hash) {
    // Achamos primeiramente o index dessa hash na hashtable
    int table_index = hash % TABLE_SIZE;
    
    // Ja sabemos que nao tem nenhum elemento ali entao retornamos que nao existe
    if (table_index > TABLE_SIZE || !hash_table[table_index]) return NULL;
    
    // Criamos um ponteiro auxiliar para percorrer a lista no caso de colisao
    HASHTABLE *aux = hash_table[table_index];

    // Se o elemento tiver a mesma hash, achamos, é o primeiro da lista
    if (hash_table[table_index]->hash == hash) return hash_table[table_index];

    // Caso contrario, percorremos a lista de colisoes e achamos onde a hash esta
    else {
        while (aux->next_colision != NULL) {
            aux = aux->next_colision;
            if (aux->hash == hash) return aux;
        }
    }

    // Caso nenhuma hash seja encontrada no inicio da lista nem na lista de colisao
    // Retornamos um ponteiro nulo, pois nao foi encontrada.
    return NULL;
}