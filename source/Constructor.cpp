#include <cstdlib>
#include <iomanip>
#include "../header/Matrice.h"

Matrice::Matrice()
{

}

Matrice::Matrice(const Matrice& other)
{
    this->shape = other.shape;
    this->tableau = other.tableau;
}

Matrice::Matrice(std::vector<int> shape)
{
    this->shape = shape;
    tableau.resize(shape[0]);
    for(int i = 0; i < shape[0]; i++)
    {
        tableau[i].resize(shape[1], 0);
    }
}

Matrice::Matrice(std::vector<float> data, std::vector<int> shape)
{
    this->shape = shape;
    tableau.resize(shape[0]);
    for(int i = 0; i < shape[0]; i++)
    {
        tableau[i].resize(shape[1], 0);
    }


    if(shape[0] * shape[1] != data.size())
    {
        throw std::invalid_argument("shape de la matrice ne correspond pas aux données fournis\n");
        exit(1);
    }

    for(int i = 0; i < shape[0]; i++)
    {
        for(int j = i * shape[1], k = 0; j < shape[1] * (i+1); j++, k++)
        {
            tableau[i][k] = data[j];
        }
    }
}
