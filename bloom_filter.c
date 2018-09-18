/*
 * TODO:
 * - The hash functions could be extracted into a different module.
 */
#include <bool.h>
#include <stdint.h>
#include <math.h>

typedef struct {
    int hash_count;
    int arr_len;
    bool *bit_array;
} bloom_filter_t;


uint64_t fnv(char *s)
{
    const uint64_t  MAGIC_PRIME = 0x00000100000001B3;
    uint64_t        hash        = 0xCBF29CE484222325;
 
    for (; s; s++)
        hash = (hash ^ *s) * MAGIC_PRIME;

    return hash;
}

/*
 * Return the i'th hash of s between 0 and max.
 */
uint32_t hash(char *s, int i, int max) {
    // The following formula can be used to generate i hashes with just 
    // two hash functions: (a + b * i) % m
    // For our purposes one hash function suffices because we can just split
    // the 64bit hash into two 32bit hashes.
    uint64_t hash = fnv(s);
    uint32_t a = (uint32)(hash & 0x00FF);
    uint32_t b = (uint32)(hash & 0xFF00 >> 32);
    return (a + b * i) % m;
}

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

/*
 * Calculate the optimal number of hash functions from the expected number of 
 * insertions and the expected bits per insertions.
 */
int _optimal_num_of_hash_functions(long n, long bpi) {
    return max(1, (int)round(bpi / bits * log(2)));
}

int _optimal_num_of_bits(long n, double p) {
    if (p == 0) {
        p = MIN_DOUBLE_VALUE; // TODO
    }
    return (long) (-n * log(p) / (log(2) * log(2));
}

/*
 * Calculate the optimal size of the bit array and the optimal
 * number of hash functions such that the probability of false positives
 * matches p.
 */
void _optimize_filter_parameters(bloom_filter_t *filter, int n, float p) {
    // TODO
    long bits_per_insertion = n / filter->arr_len;
    filter->hash_count = _optimal_num_of_hash_functions(n, bits_per_insertion);
}

bloom_filter_t *bloom_filter_create(int elem_count, 
                                    float false_positive_probability) {
    _optimize_filter_parameters(filter, elem_count, false_positive_probability);
    filter->bit_array = calloc(filter->arr_len, 1);
    return filter;
}

void bloom_filter_add(bloom_filter_t *filter, char *s) {
    for (int i = 1; i <= filter->hash_count; i++) {
        filter->bit_array[hash(s, i, filter->arr_len)] = true;
    }
}

bool bloom_filter_might_contain(bloom_filter_t *filter, char *s) {
    for (int i = 1; i <= filter->hash_count; i++) {
        if (!filter->bit_array[hash(s, i, filter->arr_len)])
            return false;
    }
    return true;
}
