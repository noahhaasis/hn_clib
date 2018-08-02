#include "queue.h"

#include <stdlib.h>


void queue_create(queue_t *queue) {
    queue = (queue_t *)calloc(sizeof(queue_t), 1);
}

void enqueue(void *elem, queue_t *queue) {
    queue_elem_t *new_elem = (queue_elem_t *)malloc(sizeof(queue_elem_t));
    new_elem->next = queue->start;
    queue->start = new_elem;
}

void *dequeue(queue_t *queue) {
    queue_elem_t *res = queue->start;
    if (!res) { return NULL; };
    queue->start = res->next;
    return res->data;
}

void queue_destroy(queue_t *queue) {
    queue_elem_t *next;
    queue_elem_t *elem = queue->start;
    while (elem) {
        next = elem->next;
        free(elem);
        elem = next;
    }
}

int queue_len(queue_t *queue) {
    if (!queue) {
        return 0;
    }
    return queue->length;
}
