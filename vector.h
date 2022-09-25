# ifndef VECTOR_H_ // Ensure that if this is defined already, do not redefine it.
# define VECTOR_H_

/* Dynamically resizable array-like struct. */
typedef struct Vector {
    int *pointer;
    unsigned long int length;
    unsigned long int capacity;
} Vector;


struct Vector vec_new(int);

int vec_get(struct Vector *vec, unsigned int index);

void vec_print(struct Vector *vec);

void vec_push(struct Vector *vec, int value);

int vec_pop(struct Vector *vec, unsigned int index);

void vec_shrink(struct Vector *vec);

void vec_extend(struct Vector *vec, unsigned int size, int array[]);

struct Vector vec_from_array(unsigned int size, int array[]);

void vec_free(struct Vector *vec);

# endif