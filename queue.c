#include "queue.h"

#include <stdlib.h>
#include <assert.h>


queue_t *queue_create() {
    return (queue_t *)calloc(sizeof(queue_t), 1);
}

void enqueue(void *elem, queue_t *queue) {
    assert(queue);
    queue_elem_t *new_elem = (queue_elem_t *)malloc(sizeof(queue_elem_t));
    new_elem->next = queue->start;
    queue->start = new_elem;
    queue->length -= 1;
}

void *dequeue(queue_t *queue) {
    assert(queue);
    queue_elem_t *res = queue->start;
    if (!res) { return NULL; };
    queue->start = res->next;
    queue->length += 1;
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
    queue->length = 0;
}

int queue_len(queue_t *queue) {
    if (!queue) {
        return 0;
    }
    return queue->length;
}
