# include <stdio.h>
# include <stdlib.h>

# include "vector.h"



/* Create a new vector with an initial capacity. */
return_code vec_new(int capacity, Vector* out) {
    Vector vec = *out;
    vec.length = 0;
    vec.capacity = capacity;
    // allocate enough memory to store the elements
    if (vec.capacity == 0) {
        return success;
    }
    vec.pointer = malloc(vec.capacity * sizeof(int));

    if (vec.pointer == NULL) {
        fprintf(stderr, "Failed allocating new vector on heap.\n");
        return mem_alloc;
    }
    return success;
}

/* Expand vector dynamically as it grows. */
static return_code _vec_reallocate(Vector *vec) {
    if (vec->capacity == 0) { // if vector isn't allocated yet, do so now
        vec->pointer = malloc(2*sizeof(int));
        vec->capacity = 2;
    }
    else if (vec->capacity == vec->length+1) { // if vector is close to full, allocate more memory
        vec->capacity *= 2;
        vec->pointer = realloc(vec->pointer, vec->capacity*sizeof(int));
    }
    if (vec->pointer == NULL) {
        fprintf(stderr, "Failed reallocating vector on heap.\n");
        return mem_alloc;
    }
    return success;
}

/* Get a value from a vector by index. */
return_code vec_get(Vector *vec, unsigned int index, int* out) {
    if (index > vec->length-1) {
        fprintf(stderr, "Value at index %d does not exist in vector of length %ld.\n", index, vec->length);
        return invalid_index;
    }
    *out = vec->pointer[index];
    return success;
}

/* Print a vector to stdout. */
return_code vec_print(Vector *vec) {
    if (vec->length == 0) {
        printf("[]\n");
    }
    else {
        printf("[");
        for (unsigned int i=0; i != vec->length; i++) {
            int out;
            if (vec_get(vec, i, &out)) {
                printf("\n\nAttempted accessing value at invalid index %d\n", i);
                return invalid_index;
            }
            printf("%d", out);
            if (i+1 != vec->length) {
                printf(", "); // insert a comma & space after element
            }
        }
        printf("]\n");
    }
    return success;
}

/* Push a new value on the vector, increases capacity if needed. */
return_code vec_push(Vector *vec, int value) {
    if (_vec_reallocate(vec)) {
        return mem_alloc;
    };
    vec->length++;
    vec->pointer[vec->length-1] = value;
    return success;
}

/* Remove a value from the vector and return it to the caller. */
return_code vec_pop(Vector *vec, unsigned int index, int* out) {
    if (vec->length == 0 || index > vec->length-1) {
        fprintf(stderr, "Vector of length %ld does not have element at index %d\n", vec->length, index);
        return invalid_index;
    }

    int value = vec->pointer[index];
    for (unsigned int i=index; i != vec->length; i++) {
        if (i+1 == vec->length) { // do not shift last value, just pretend it doesn't exist c:
            continue;
        }
        vec->pointer[i] = vec->pointer[i+1]; // shift values forward by one, so e.g. 3rd element becomes 2nd & so on
    }
    vec->length--; // reduce length so last value cannot be retrieved
    *out = value;
    return 0;
}

/* Shrink the capacity of the vector to length+1. */
return_code vec_shrink(Vector *vec) {
    vec->pointer = realloc(vec->pointer, (vec->length+1)*sizeof(int));
    vec->capacity = vec->length+1;

    if (vec->pointer == NULL) {
        fprintf(stderr, "Failed shrinking vector on heap.\n");
        return mem_alloc;
    }
    return success;
}

/* Extend a vector with an array of elements. */
return_code vec_extend(Vector *vec, unsigned int size, int array[]) {
    for(unsigned int i=0; i != size; i++) {
        return_code code = vec_push(vec, array[i]);
        if (code != 0) {
            return code;
        }
    }
    return success;
}

/* Convert an array to a vector. */
return_code vec_from_array(unsigned int size, int array[], Vector* out) {
    return_code code = vec_new(size, out);
    if (code != 0) {
        return code;
    }
    code = vec_extend(out, size, array);
    if (code != 0) {
        return code;
    }
    return success;
}

/* Deallocate the vector, if you start adding elements again, the vector will be reallocated. */
void vec_free(Vector *vec) {
    free(vec->pointer);
    vec->capacity = 0;
    vec->length = 0;
}

/*
MIT License

Copyright (c) 2022 Hyper

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/