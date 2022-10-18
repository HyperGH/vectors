# ifndef VECTOR_H_ // Ensure that if this is defined already, do not redefine it.
# define VECTOR_H_

/* Dynamically resizable array-like struct. */
typedef struct Vector {
    int *pointer;
    unsigned long int length;
    unsigned long int capacity;
} Vector;

typedef enum return_code{
    success, 
    mem_alloc, 
    invalid_index
} return_code;

return_code vec_new(int capacity, Vector* out);

return_code vec_get(Vector *vec, unsigned int index, int* out);

return_code vec_print(Vector *vec);

return_code vec_push(Vector *vec, int value);

return_code vec_pop(Vector *vec, unsigned int index, int* out);

return_code vec_shrink(Vector *vec);

return_code vec_extend(struct Vector *vec, unsigned int size, int array[]);

return_code vec_from_array(unsigned int size, int array[], Vector* out);

void vec_free(struct Vector *vec);

# endif