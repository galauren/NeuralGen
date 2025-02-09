#ifndef LAYER_H
#define LAYER_H

#include "matrix.h"

// Structure représentant une couche de neurones
typedef struct s_layer
{
    Matrix *weights;   // Matrice des poids
    Matrix *biases;    // Vecteur des biais
    int input_size;    // Nombre d'entrées
    int output_size;   // Nombre de neurones dans la couche
}				Layer;

// Enum pour choisir la méthode d'initialisation
typedef enum e_init_method
{
    UNIFORM,
    XAVIER,
    HE
}				InitMethod;

// Fonction d'initialisation d'une couche
Layer *Layer_init(int input_size, int output_size, InitMethod method);

// Fonction pour libérer la mémoire d'une couche
void Layer_free(Layer *layer);

// Vérifie si la méthode d'initialisation est valide
int is_valid_init_method(InitMethod method);

#endif

