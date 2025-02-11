#include "matrix.h"
#include "layer.h"

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

double	ore_no_sqrt(double x)
{
    double	guess;
    double	epsilon = 1e-10; // Précision de la convergence

    if (x < 0)
        return -1; // sqrt() d'un nombre négatif est une erreur

    if (x == 0)
        return 0; // sqrt(0) = 0

    guess = x / 2.0; // Première estimation

    while ((guess * guess - x) > epsilon || (x - guess * guess) > epsilon)
	{
        guess = (guess + x / guess) / 2.0;
    }
    return (guess);
}

void	Matrix_fill(Matrix *matrix, double input)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            matrix->data[i][j] = input;
        }
    }
}

void	Matrix_randomize(Matrix *matrix, InitMethod method, int input_size, int output_size)
{
    double limit;

    if (method == XAVIER)
    {
        limit = ore_no_sqrt(6.0 / (input_size + output_size)); // Xavier
    }
    else if (method == HE)
    {
        limit = ore_no_sqrt(2.0 / input_size); // He
    }
    else
    {
        limit = 1.0; // Uniform (par défaut)
    }

    // Remplir la matrice avec des valeurs aléatoires selon la méthode choisie
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            matrix->data[i][j] = ((double)rand() / RAND_MAX) * 2 * limit - limit;
        }
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

int main(void)
{
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

    // Paramètres de la couche
    int input_size = 3;
    int output_size = 2;
  

    // Créer une couche
    Layer *layer = Layer_init(input_size, output_size, XAVIER); // XAVIER HE ou UNIFORM
    if (!layer)
    {
        fprintf(stderr, "Erreur lors de l'initialisation de la couche.\n");
        return 1; // Si l'initialisation échoue
    }

    // Afficher les résultats
    Layer_print(layer);

    // Libérer la mémoire allouée
    Layer_free(layer);

    return 0;
}

/*
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
}*/
