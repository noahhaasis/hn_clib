#include "re.h"

int get_transition_index(char c) {
    if      (c >= 'A' && c <= 'B') { return c - 'A';      }
    else if (c >= 'a' && c <= 'z') { return c - 'a' + 26; }
    else if (c >= '0' && c <= '9') { return c - '0' + 52; }
    else                           { return -1;           }
}

state_t *re_compile(char *pattern) {
    for (int i = 0, len = strlen(pattern); i < len; i++) {
        switch (pattern[i]) {
        case '(':
            break;
        case ')':
            break;
        case '*':
            break;
        case '|':
            break;
        default:
            break;
        }
    } 
    return NULL;
}

bool re_matches(state_t *pattern, char *word) {
    state_t *current_state = pattern;
    for (int i = 0, len = strlen(word); i < len; i++) {
        current_state = current_state->transitions[get_transition_index(word[i])];
        if (!current_state) { return false; }
    }
    return current_state->accepting_state;
}

void re_destroy(state_t *pattern) {
    for (int i = 0; i < TRANSITION_COUNT; i++) {
        if (pattern->transitions[i] && pattern->transitions[i] != pattern) {
            re_destroy(pattern->transitions[i]);
        }
    }
    free(pattern);
}
