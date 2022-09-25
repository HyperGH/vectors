# include <stdio.h>

# include "vector.h"

/* Example usage */
int main() {
    /* New vector with no capacity, if you know the approximate starting size of your vector, insert here
    This avoids needless reallocation
    A vector with no capacity is not allocated until the first element is pushed onto it. */
    Vector vec = vec_new(0);

    vec_print(&vec); // Print vector contents

    vec_push(&vec, 2); // Add 2 to the end of the vector

    int arr[] = {1, 2, 3, 4, 5, 6};
    vec_extend(&vec, 6, arr);
    vec_print(&vec);

    int value = vec_get(&vec, 0); // Getting element of index 0
    int popped = vec_pop(&vec, 3); // Removing element of index 3 and returning it
    printf("Value: %d, Popped: %d\n", value, popped);

    vec_shrink(&vec); // Shrink capacity to be length+1, this reallocates the vector

    vec_print(&vec);

    vec_free(&vec); // Deallocate vector, all memory associated is freed

    // Note that if you start pushing new elements after this, the vector will be reallocated.

    return 0;
}
