#include "layer.h"

// Fonction d'initialisation de la couche
Layer *Layer_init(int input_size, int output_size, InitMethod init_method)
{
    Layer *layer;
    layer = (Layer *)malloc(sizeof(Layer));
    if (!layer)
    {
        return (0); // Échec de l'allocation mémoire
    }

    layer->input_size = input_size;
    layer->output_size = output_size;
    layer->init_method = init_method;
    if (!layer->init_method)
    {
        free(layer);
        return (0); // Échec de l'allocation mémoire
    }

    // Création des matrices pour les poids et biais
    layer->weights = Matrix_create(input_size, output_size);
    if (!layer->weights)
    {
        free(layer);
        return (0); // Échec de l'allocation mémoire
    }

    layer->biases = Matrix_create(1, output_size);
    if (!layer->biases)
    {
        Matrix_free(layer->weights);
        free(layer);
        return (0); // Échec de l'allocation mémoire
    }

    // Initialisation des poids et des biais
	Matrix_randomize(layer->weights, init_method, input_size, output_size);

    // Initialisation des biais à zéro
    Matrix_fill(layer->biases, 0);

    return (layer);
}

// Vérifie que la méthode d'initialisation est valide
int is_valid_init_method(InitMethod method)
{
    return (method == XAVIER || method == HE || method == UNIFORM);
}

// Fonction pour libérer la mémoire de la couche
void Layer_free(Layer *layer)
{
    if (layer)
    {
        if (layer->weights)
        {
            Matrix_free(layer->weights);
        }
        if (layer->biases)
        {
            Matrix_free(layer->biases);
        }
        free(layer);
    }
}

// Fonction pour afficher les poids et biais de la couche (utile pour les tests)
void Layer_print(Layer *layer)
{
    if (layer)
    {
        printf("Weights:\n");
        Matrix_print(layer->weights);
        printf("Biases:\n");
        Matrix_print(layer->biases);
    }
}
/*
// Fonction main pour tester l'initialisation
int main(void)
{
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

    // Paramètres de la couche
    int input_size = 3;
    int output_size = 2;
    const char *init_method = "xavier"; // Vous pouvez tester "he" ou "uniform" ici

    // Créer une couche
    Layer *layer = Layer_init(input_size, output_size, init_method);
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
*/
