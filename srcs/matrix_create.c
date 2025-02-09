#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

Matrix *Matrix_create(int rows, int cols)
{
	if (rows < 1 || cols < 1)
		return (0);
	Matrix *m = (Matrix *)malloc(sizeof(Matrix));
	m->rows = rows;
	m->cols = cols;
	m->data = (float **)malloc(rows * sizeof(float *));
	int i = 0;
	while (i < rows)
	{
		m->data[i] = (float *)malloc(cols * sizeof(float));
		++i;
	}
	return (m);
}

int	print_error(char *str)
{
	printf("%s\n", str);
	return (-1);
}

int Matrix_free(Matrix *m)
{
	int i = 0;

	if (!m)
		return (print_error("couldnt free this one"));
	while (i < m->rows)
	{
		free(m->data[i]);
		++i;
	}
	free(m->data);
	free(m);
	return (1);
}

int Matrix_print(Matrix *m)
{
	int i = 0;
	int j;

	if (!m)
		return (print_error("something bad happend"));
	while (i < m->rows)
	{
		printf("[");
		j = 0;
		while (j < m->cols)
		{
			printf("  %f  ", m->data[i][j]);
			++j;
		}
		printf("]\n");
		++i;
	}
	printf("\n");
	return (1);
}

void Matrix_randomize(Matrix *m)
{
	int i = 0;
	int j;

	while (i < m->rows)
	{
		j = 0;
		while (j < m->cols)
		{
			m->data[i][j] = (float)rand() / RAND_MAX * 2.0 - 1.0; // Valeurs entre -1 et 1
			++j;
		}
		++i;
	}
}

int	ft_atoi(char *nbr)
{
	int	result;

	result = 0;
	while (*nbr)
	{
		if (*nbr < 48 || *nbr > 57)
			return (-1);
		result = result * 10 + *nbr - 48;
		++nbr;
	}
	return (result);
}

int main(int ac, char **av)
{
	Matrix *tmp;

	if (ac != 3)
		return (print_error("creating a matrix...\nWrong Format ! Requesting : ./Matrix.exe  rows  cols\n"));
	Matrix *ma = Matrix_create(ft_atoi(av[1]), ft_atoi(av[2]));
	if (!ma)
		return (print_error("You should use only digits u know ?"));
	Matrix *mb = Matrix_create(ft_atoi(av[2]), ft_atoi(av[1]));
	if (!mb)
		return (print_error("You should use only digits u know ?"));
	Matrix *mc = Matrix_create(ft_atoi(av[1]), ft_atoi(av[2]));
	if (!mc)
		return (print_error("You should use only digits u know ?"));
	Matrix_randomize(ma);
	Matrix_randomize(mb);
	Matrix_randomize(mc);
	printf("TOUT AVANT LA TRANSFO :\n\n");
	Matrix_print(ma);
	Matrix_print(mb);
	Matrix_print(mc);

	printf("\n-------------------------\nTOUT APRES LA TRANSFO :\n\n");
	printf("Fusion a et b :\n");
	tmp = Matrix_fuse(ma, mb);
	Matrix_print(tmp);
	Matrix_free(tmp);

	printf("Mult a et b :\n");
	tmp = Matrix_mult(ma, mb);
	Matrix_print(tmp);
	Matrix_free(tmp);

	printf("Fusion a et c :\n");
	tmp = Matrix_fuse(ma, mc);
	Matrix_print(tmp);
	Matrix_free(tmp);

	printf("Mult a et c :\n");
	tmp = Matrix_mult(ma, mc);
	Matrix_print(tmp);
	Matrix_free(tmp);

	Matrix_free(ma);
	Matrix_free(mb);
	Matrix_free(mc);
	return (0);
}
