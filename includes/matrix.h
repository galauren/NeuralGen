#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_matrix
{
    int rows;
    int cols;
    float **data;
}		Matrix;

Matrix *Matrix_create(int rows, int cols);
Matrix *Matrix_add(Matrix *A, Matrix *B);
Matrix *Matrix_expand(Matrix *M, int new_rows, int new_cols);
Matrix	*Matrix_mult(Matrix *a, Matrix *b);
Matrix	*Matrix_fuse(Matrix *a, Matrix *b);

void Matrix_randomize(Matrix *m);

int	print_error(char *str);
int	Matrix_print(Matrix *m);

int	Matrix_free(Matrix *m);

#endif
