#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "trie.h"
#include "stack.h"
#include "re.h"
#include "queue.h"
#include "bloom_filter.h"


void test_trie_creation(void) {
    printf("Testing  trie_create ...\n");
    node_t *root = trie_create();
    assert(root);
    assert(!root->is_word);
    for (int i = 0; i < CHILDREN_COUNT; i++) { assert(!root->children[i]); }
    trie_destroy(root);
}
void test_adding_word(void) {
    printf("Test adding word to trie...\n");
    node_t *root = trie_create();
    trie_add(root, "thisisacomplicatedandlongword");
    assert(trie_contains(root, "thisisacomplicatedandlongword"));
    assert(!trie_contains(root, "thisisacomplicatedandlongwors"));
    trie_destroy(root);
}

void test_case_insensitivity(void) {
    printf("Test trie case insensitivity ...\n");
    node_t *root = trie_create();
    trie_add(root, "notashortword");
    assert(trie_contains(root, "NOTASHORTworD"));
    trie_destroy(root);
}

void test_removing_word(void) {
    printf("Testing trie_remove_word...\n");
    node_t *root = trie_create();
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

void trie_test_all(void) {
    test_trie_creation();
    test_adding_word();
    test_case_insensitivity();
    test_removing_word();
}


void stack_test_create(void) {
    printf("Testing stack_create...\n");
    stack_t *stack = stack_create();
    assert(stack);
    assert(!stack->top);
    stack_destroy(stack);
}

void stack_test_push(void) {
    printf("Testing stack_push ...\n");
    stack_t *stack = stack_create();
    int val = 8;
    stack_push(stack, &val);
    assert((int)*(int *)stack->top->value == val);
    stack_destroy(stack);
}

void stack_test_peek(void) {
    printf("Testing stack_peek ...\n");
    stack_t *stack = stack_create();
    int val = 8;
    stack_push(stack, &val);
    for (int i = 0; i < 100; i++) {
        assert(*(int *)stack_peek(stack) == val);
    }
    stack_destroy(stack);
}

void stack_test_complete(void) {
    printf("Testing all stack functions in combination ...\n");
    stack_t *stack = stack_create();
    int push_data[8] = {1,2,3,4,5,6,1,19};
    int pop_data[8];
    for (int i = 0; i < 8; i++) {
        stack_push(stack, &push_data[i]);
    }
    for (int i = 7; i >= 0; i--) {
        pop_data[i] = (int)*(int *)stack_pop(stack);
    }
    for (int i = 0; i < 8; i++) {
        assert(push_data[i] == pop_data[i]);
    }
    stack_destroy(stack);
}

void stack_test_all(void) {
    stack_test_create();
    stack_test_push();
    stack_test_peek();
    stack_test_complete();
}


void re_test_creating_simple_pattern(void) {
    printf("Testing simple pattern creation ...\n");
    state_t *pattern = re_compile("aaa");
    assert(pattern);
    re_destroy(pattern);
}

void re_test_matching_simple_pattern(void) {
    printf("Testing simple pattern matching ...\n");
    state_t *pattern = re_compile("aaa");
    assert(re_matches(pattern, "aaa"));
    re_destroy(pattern);
}

void re_test_creating_and_matchin_pattern_with_or(void) {
    printf("Testing pattern containing a or ...\n");
    state_t *pattern = re_compile("a|b");
    assert(pattern);
    assert(re_matches(pattern, "b"));
    assert(re_matches(pattern, "a"));
    re_destroy(pattern);

    pattern = re_compile("aaabbb|cdada");
    assert(re_matches(pattern, "aaabbbdada"));
    assert(re_matches(pattern, "aaabbcdada"));
    re_destroy(pattern);
}

void re_test_creating_and_matching_pattern_with_star(void) {
    printf("Testing pattern containing a star ...\n");
    state_t *pattern = re_compile("a*");
    assert(re_matches(pattern, "aaaaaaaaaaaaaa"));
    assert(re_matches(pattern, "a"));
    assert(re_matches(pattern, ""));
    re_destroy(pattern);

    pattern = re_compile("0101a*b");
    assert(re_matches(pattern, "0101aaaaaaaaaaaaaab"));
    assert(re_matches(pattern, "0101b"));
    assert(re_matches(pattern, "0101ab"));
    assert(!re_matches(pattern, "0101abb"));
    assert(!re_matches(pattern, "01011ab"));
    re_destroy(pattern);
}

void re_test_creating_and_matching_pattern_with_plus(void) {
    printf("Testing pattern containing a plus ...\n");
    state_t *pattern = re_compile("a+b*");
    assert(re_matches(pattern, "aaaa"));
    assert(re_matches(pattern, "abbb"));
    assert(!re_matches(pattern, "bbb"));
    re_destroy(pattern);
}

void re_test_creating_and_matching_pattern_with_dot(void) {
    printf("Testing pattern containing a dot ...\n");
    state_t *pattern = re_compile("a.*");
    assert(re_matches(pattern, "abababa"));
    assert(re_matches(pattern, "a"));
    assert(re_matches(pattern, "accc"));
    assert(!re_matches(pattern, "sdfsd"));
    re_destroy(pattern);
}

void re_test_all(void) {
    re_test_creating_simple_pattern();
    re_test_matching_simple_pattern();
    re_test_creating_and_matchin_pattern_with_or();
    re_test_creating_and_matching_pattern_with_star();
    re_test_creating_and_matching_pattern_with_plus();
    re_test_creating_and_matching_pattern_with_dot();
}


void queue_test_queue_create(void) {
    queue_t *queue = queue_create();
    assert(queue);
    assert(queue_len(queue) == 0);
    assert(!queue->start);
    assert(!queue->end);
    free(queue);
}

void queue_test_enqueue_and_dequeue(void) {
    queue_t *queue = queue_create();
    int data_count = 3;
    int data[] = {1, 2, 3};
    for (int i = 0; i < data_count; i++) {
        enqueue(&data[i], queue);
    }
    for (int i = 0; i < data_count; i++) {
        assert(*(int *)dequeue(queue) == data[i]);
    }
    queue_remove_elements(queue);
    free(queue);
}

void queue_test_len(void) {
    queue_t *queue = queue_create();
    enqueue("", queue);
    enqueue("", queue);
    enqueue("", queue);
    assert(queue_len(queue) == 3);
    dequeue(queue);
    assert(queue_len(queue) == 2);
    queue_remove_elements(queue);
    free(queue);
}

void queue_test_remove_elements(void) {
    queue_t *queue = queue_create();
    enqueue("", queue);
    enqueue("", queue);
    enqueue("", queue);
    queue_remove_elements(queue);
    assert(!dequeue(queue));
    assert(queue_len(queue) == 0);
    free(queue);
}

void queue_test_all(void) {
    queue_test_queue_create();
    queue_test_enqueue_and_dequeue();
    queue_test_len();
    queue_test_remove_elements();
}

void bloom_filter_test_create(void) {
    bloom_filter_t *filter = bloom_filter_create(10, 0.05);
    assert(filter);
    assert(filter->arr_len);
    assert(filter->bit_array);
    assert(filter->hash_count);
}

void bloom_filter_test_add(void) {
    bloom_filter_t *filter = bloom_filter_create(10, 0.05);
    char *elems[10] = {
        "hello", "soosososo", "2", 
        "3", "d", "234nkjk-?", "7", 
        "222", "nice", "10"};

    for (int i = 0; i < 10; i++) {
        bloom_filter_add(filter, elems[i]);
        assert(bloom_filter_might_contain(filter, elems[i]));
    }
}

void bloom_filter_test_add_empty_string(void) {

}

void bloom_filter_test_all(void) {
    bloom_filter_test_create();
    bloom_filter_test_add();
}

int main(void) {
    trie_test_all();
    printf("Tested the trie module successully!\n");
    stack_test_all();
    printf("Tested the stack module successully!\n");
    re_test_all();
    printf("Tested the regular expression module successfully!\n");
    queue_test_all();
    printf("Tested the queue module successfully!\n");
    bloom_filter_test_all();
    printf("Tested the bloom filter module successfully!\n");
    printf("All tests ran successfully!\n");
    return 0;
}
