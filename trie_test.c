#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "trie.h"


void test_trie_creation(void) {
    node *root = trie_create();
    assert(root);
    assert(!root->is_word);
    for (int i = 0; i < CHILDREN_COUNT; i++) { assert(!root->children[i]); }
}

void test_adding_word(void) {
    node *root = trie_create();
    trie_add(root, "thisisacomplicatedandlongword");
    assert(trie_contains(root, "thisisacomplicatedandlongword"));
    assert(!trie_contains(root, "thisisacomplicatedandlongwors"));
    trie_destroy(root);
}

void test_case_insensitivity(void) {
    node *root = trie_create();
    trie_add(root, "notashortword");
    assert(trie_contains(root, "NOTASHORTworD"));
    trie_destroy(root);
}

void test_removing_word(void) {
    node *root = trie_create();
    trie_add(root, "");
    trie_add(root, "hello");
    trie_add(root, "HellO");
    trie_add(root, "ssooss");
    trie_add(root, "hell");
    assert(trie_contains(root, ""));
    assert(trie_contains(root, "hello"));
    assert(trie_contains(root, "ssooss"));
    assert(trie_contains(root, "hell"));
    trie_remove(root, "hello");
    assert(!trie_contains(root, "hello"));
    assert(trie_contains(root, "hell"));
    assert(trie_contains(root, "ssooss"));
    trie_destroy(root);
}

int main(void) {
    test_trie_creation();
    test_adding_word();
    test_case_insensitivity();
    test_removing_word();
    printf("All tests ran successfully!\n");
    return EXIT_SUCCESS;
}
