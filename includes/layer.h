#ifndef LAYER_H
# define LAYER_H

# include "matrix.h"
# include <string.h>
# include <time.h>

// Structure représentant une couche de neurones
typedef struct s_layer
{
    Matrix	*weights;
    Matrix	*biases;
    int	input_size;
    int	output_size;
    InitMethod	init_method;
}				Layer;

// Fonction d'initialisation d'une couche
Layer *Layer_init(int input_size, int output_size, InitMethod method);

// Fonction pour libérer la mémoire d'une couche
void Layer_free(Layer *layer);

// Vérifie si la méthode d'initialisation est valide
int is_valid_init_method(InitMethod method);

void Layer_print(Layer *layer);

#endif

