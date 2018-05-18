#ifndef RE_H
#define RE_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"

#define TRANSITION_COUNT 62 // [A-Za-Z0-9]

typedef struct state {
    bool accepting_state;
    struct state *transitions[TRANSITION_COUNT];
} state_t;


state_t *re_compile(char *pattern);

bool re_matches(state_t *pattern, char *word);

void re_destroy(state_t *pattern);

#endif
