#ifndef MATRIX_H
# define MATRIX_H

# include <stdio.h>
# include <stdlib.h>

// Enum pour choisir la méthode d'initialisation
typedef enum e_init_method
{
    UNIFORM,
    XAVIER,
    HE
}				InitMethod;

typedef struct s_matrix
{
    int rows;
    int cols;
    float **data;
}				Matrix;

Matrix *Matrix_create(int rows, int cols);
void Matrix_fill(Matrix *matrix, double value);

Matrix *Matrix_add(Matrix *A, Matrix *B);
Matrix *Matrix_expand(Matrix *M, int new_rows, int new_cols);
Matrix	*Matrix_mult(Matrix *a, Matrix *b);
Matrix	*Matrix_fuse(Matrix *a, Matrix *b);

void Matrix_randomize(Matrix *matrix, InitMethod method, int input_size, int output_size);

int	print_error(char *str);
int	Matrix_print(Matrix *m);

int	Matrix_free(Matrix *m);

#endif
