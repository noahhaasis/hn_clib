#include "trie.h"


void trie_add(node* root, char* word) {
    if (!word || !*word) { root->is_word = true; }
    else {
        int head_index = tolower(word[0]) - 97;
        if (!root->children[head_index]) {
            root->children[head_index] = calloc(1, sizeof(node));
        }
        trie_add(root->children[head_index], ++word);
    }
}

void trie_remove(node *root, char *word) {
    if (!word || !*word) { root->is_word = false; }
    else {
        int head_index = tolower(word[0]) - 97;
        node *child = root->children[head_index];
        if (!child) { return; }

        trie_remove(child, ++word);
        if (child->is_word) { return; }
        for (int i = 0; i < CHILDREN_COUNT; i++) {
            if (child->children[i]) { return; }
        }
        free(child);
        root->children[head_index] = NULL;
    }
}

bool trie_contains(node* root, char* word) {
    if (!word || !*word) { return root && root->is_word; }
    int head_index = tolower(word[0]) - 97;
    return root && trie_contains(root->children[head_index], ++word);
}

void trie_destroy(node* root) {
    for (int i = 0; i < CHILDREN_COUNT; i++) {
        if (root->children[i]) trie_destroy(root->children[i]);
    }
    free(root);
}

node *trie_create() {
    return calloc(1, sizeof(node));
}
