#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#define CHILDREN_COUNT 26

typedef struct node {
    bool is_word;
    struct node *children[CHILDREN_COUNT];
} node;

void trie_add(node* root, char* word);

void trie_remove(node *root, char *word);

bool trie_contains(node* root, char* word);

void trie_destroy(node* root);

node *trie_create(void);

#endif
