# include <stdio.h>
# include <stdlib.h>

/* Dynamically resizable array-like struct */
struct Vector {
    int *pointer; // start of memory allocation
    unsigned long int length; // controls up to how many elements are currently defined
    unsigned long int capacity; // how much capacity is currently allocated, size of elements is capacity*sizeof int
};

/* Create a new vector with an initial capacity */
struct Vector new(int capacity) {
    struct Vector vec;
    vec.length = 0;
    vec.capacity = capacity;
    // allocate enough memory to store the elements
    if (!vec.capacity) {
        return vec;
    }
    vec.pointer = malloc(vec.capacity * sizeof(int));

    if (vec.pointer == NULL) {
        fprintf(stderr, "Failed allocating new vector on heap.\n");
        exit(-1);
    }
    return vec;
}

/* Expand vector dynamically as it grows */
void _reallocate_vec(struct Vector *vec) {
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
        exit(-1);
    }
}

/* Get a value from a vector by index */
int get(struct Vector *vec, unsigned int index) {
    if (index > vec->length-1) {
        fprintf(stderr, "Vector of length %ld does not have element at index %d\n", vec->length, index);
        exit(-1);
    }
    return vec->pointer[index];
}

/* Print a vector */
void vprint(struct Vector *vec) {
    if (vec->length == 0) {
        printf("[]\n");
    }
    else {
        printf("[");
        for (unsigned int i=0; i != vec->length; i++) {
            printf("%d", get(vec, i));
            if (i+1 != vec->length) {
                printf(", "); // insert a comma & space after element
            }
        }
        printf("]\n");
    }
}

/* Push a new value on the vector, increases capacity if needed */
void push(struct Vector *vec, int value) {
    _reallocate_vec(vec);
    vec->length++;
    vec->pointer[vec->length-1] = value;
}

/* Remove a value from the vector and return it to the caller */
int pop(struct Vector *vec, unsigned int index) {
    if (vec->length == 0 || index > vec->length-1) {
        fprintf(stderr, "Vector of length %ld does not have element at index %d\n", vec->length, index);
        exit(-1);
    }

    int value = vec->pointer[index];
    for (unsigned int i=index; i != vec->length; i++) {
        if (i+1 == vec->length) { // do not shift last value, just pretend it doesn't exist c:
            continue;
        }
        vec->pointer[i] = vec->pointer[i+1]; // shift values forward by one, so e.g. 3rd element becomes 2nd & so on
    }
    vec->length--; // reduce length so last value cannot be retrieved
    return value;
}

/* Shrink the capacity of the vector to length+1 */
void shrink_to_fit(struct Vector *vec) {
    vec->pointer = realloc(vec->pointer, (vec->length+1)*sizeof(int));
    vec->capacity = vec->length+1;

    if (vec->pointer == NULL) {
        fprintf(stderr, "Failed shrinking vector on heap.\n");
        exit(-1);
    }
}

/* Extend a vector with an array of elements. */
void extend(struct Vector *vec, unsigned int size, int array[]) {
    for(unsigned int i=0; i != size; i++) {
        push(vec, array[i]);
    }
}

/* Convert an array to a vector. */
struct Vector from_array(unsigned int size, int array[]) {
    struct Vector vec = new(size);
    extend(&vec, size, array);
    return vec;
}

/* Deallocate the vector, if you start adding elements again, the vector will be reallocated. */
void vfree(struct Vector *vec) {
    free(vec->pointer);
    vec->capacity = 0;
    vec->length = 0;
}

/* Driver code */
int main() {
    // new vector with no capacity, if you know the approximate starting size of your vector, insert here
    // this avoids needless reallocation
    struct Vector vec = new(0);

    vprint(&vec); // print vector contents

    push(&vec, 2); // add 2

    int arr[] = {1, 2, 3, 4, 5, 6};
    extend(&vec, 6, arr);

    int value = get(&vec, 0); // getting element of index 0
    int popped = pop(&vec, 3); // removing element of index 3 and returning it
    printf("Value: %d, Popped: %d\n", value, popped);

    shrink_to_fit(&vec); // shrink capacity to be length+1

    vprint(&vec);

    vfree(&vec); // deallocate vector

    return 0;
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