#include "re.h"

state_t *state_create(void) {
    return (state_t *)calloc(1, sizeof(state_t));
}

int get_transition_index(char c) {
    if      (c >= 'A' && c <= 'B') { return c - 'A';      }
    else if (c >= 'a' && c <= 'z') { return c - 'a' + 26; }
    else if (c >= '0' && c <= '9') { return c - '0' + 52; }
    else                           { return -1;           }
}

state_t *re_compile(char *pattern) {
    state_t *next_state = NULL;
    state_t *starting_state = state_create();
    /* A block is a regular expression enclosed in parentheses */
    state_t *start_of_last_block = NULL;
    state_t *current_state = starting_state;
    bool is_or = false;
    bool refering_to_block = false;
    stack_t *start_of_blocks = stack_create();

    for (int i = 0, len = strlen(pattern); i < len; i++) {
        char c = pattern[i];
        switch (c) {
        case '(':
            stack_push(start_of_blocks, current_state);
            break;
        case ')':
            refering_to_block = true;
            start_of_last_block = (state_t *)stack_pop(start_of_blocks);
            break;
        case '*':
            break;
        case '|':
            is_or = true;
            break;
        default:
            if (!is_or) { next_state = state_create(); }
            current_state->transitions[get_transition_index(c)] = next_state;
            if (!is_or) { current_state = next_state; }
            refering_to_block = false;
            break;
        }
    } 
    current_state->accepting_state = true;
    stack_destroy(start_of_blocks);
    return starting_state;
}

bool re_matches(state_t *pattern, char *word) {
    state_t *current_state = (state_t *)pattern;
    for (int i = 0, len = strlen(word); i < len; i++) {
        current_state = current_state->transitions[get_transition_index(word[i])];
        if (!current_state) { return false; }
    }
    return current_state->accepting_state;
}

void re_destroy(state_t *pattern) {
    for (int i = 0; i < TRANSITION_COUNT; i++) {
        state_t *curr_transition = pattern->transitions[i];
        if (curr_transition && curr_transition != pattern) {
            re_destroy(curr_transition);
        }
    }
    free(pattern);
}
