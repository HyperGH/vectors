# Vectors

An implementation of vectors in C. Made to learn more about the language.

```c
Vector vec = vec_new(0);

vec_print(&vec); // []

vec_push(&vec, 2); // Add 2 to the end of the vector

int arr[] = {1, 2, 3, 4, 5, 6};
vec_extend(&vec, 6, arr);
vec_print(&vec); // [2, 1, 2, 3, 4, 5, 6]

int value = vec_get(&vec, 0);
int popped = vec_pop(&vec, 3);
printf("Value: %d, Popped: %d\n", value, popped); // Value: 2, Popped: 3

vec_shrink(&vec); // Shrink capacity to be length+1, this reallocates the vector

vec_print(&vec); // [2, 1, 2, 4, 5, 6]

vec_free(&vec); // Deallocate vector, all memory associated is freed
```
