#include "layer.h"
#include "matrix.h"

Matrix *Matrix_add(Matrix *A, Matrix *B)
{
		// Vérifier si les matrices sont compatibles ou peuvent être diffusées
		if ((A->rows != B->rows && A->cols != B->cols) && !(A->rows == 1 || B->rows == 1 || A->cols == 1 || B->cols == 1))
		{
				return (0); // Les dimensions ne sont pas compatibles
		}

		// Diffusion pour égaliser les dimensions
		if (A->rows == 1 || B->rows == 1)
		{
				int new_rows = (A->rows == 1) ? B->rows : A->rows;
				A = Matrix_expand(A, new_rows, A->cols);
				B = Matrix_expand(B, new_rows, B->cols);
		}

		if (A->cols == 1 || B->cols == 1)
		{
				int new_cols = (A->cols == 1) ? B->cols : A->cols;
				A = Matrix_expand(A, A->rows, new_cols);
				B = Matrix_expand(B, B->rows, new_cols);
		}

		// Additionner les matrices après la diffusion
		Matrix *result = Matrix_create(A->rows, A->cols);
		int i = 0;
		while (i < A->rows)
		{
				int j = 0;
				while (j < A->cols)
				{
						result->data[i][j] = A->data[i][j] + B->data[i][j];
						j++;
				}
				i++;
		}

		return (result);
}

// Fonction générique pour étendre les dimensions (lignes ou colonnes)
Matrix *Matrix_expand(Matrix *M, int new_rows, int new_cols)
{
		Matrix *new_matrix = Matrix_create(new_rows, new_cols);
		int i = 0;
		int j;

		while (i < new_rows)
		{
				j = 0;
				while (j < new_cols)
				{
						new_matrix->data[i][j] = M->data[i % M->rows][j % M->cols];  // Répéter les lignes et colonnes
						j++;
				}
				i++;
		}
		Matrix_free(M);
		return (new_matrix);
}


Matrix	*Matrix_mult(Matrix *a, Matrix *b)
{
		Matrix	*result;
		int	row = 0;
		int	col;

		if (a->cols != b->cols || a->rows != b->rows)
				return (0);
		result = Matrix_create(a->rows, b->cols);
		if (!result)
				return (0);
		while (row < a->rows)
		{
				col = 0;
				while (col < a->cols)
				{
						result->data[row][col] = a->data[row][col] * b->data[row][col];
						++col;
				}
				++row;
		}
		return (result);
}

Matrix	*Matrix_fuse(Matrix *a, Matrix *b)
{
		Matrix	*result;
		Matrix	*tmp;
		int	row = 0;
		int	col;
		int	mutual_idx;

		if (a->rows == b->cols)
		{
				tmp = a;
				a = b;
				b = tmp;
		}
		if (a->cols != b->rows)
				return (0);
		result = Matrix_create(a->rows, b->cols);
		if (!result)
				return (0);
		while (row < a->rows)
		{
				col = 0;
				while (col < b->cols)
				{
						result->data[row][col] = 0.0;
						mutual_idx = 0;
						while (mutual_idx < a->cols) /* a->cols == b->rows ici */
						{
								result->data[row][col] += (a->data[row][mutual_idx] * b->data[mutual_idx][col]);
								++mutual_idx;
						}
						++col;
				}
				++row;
		}
		return (result);
}
