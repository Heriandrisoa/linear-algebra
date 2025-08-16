#include <cstdlib>
#include <iomanip>
#include <cmath>
#include "../header/Matrice.h"

Matrice id(int dim)
{
    std::vector<int> shape ={dim, dim};
    Matrice A = Matrice(shape);
    for(int i = 0 ; i < dim; i++)
    {
        A[i][i] = 1;
    }
    return A;
}
Matrice Matrice::inverse()
{

    if(shape[0] != shape[1]) // les matrices rectangulaires ne sont pas inversible
    {
        throw std::logic_error("matrice non inversible");
    }
    Matrice copy = *this;
    Matrice identite = id(shape[0]);

    //triangularisation inférieur
    for (int k = 0; k < shape[0]; k++)
    {
        float pivot = copy.tableau[k][k];

        //pivotage partiel
        int line_pivot = k;
        for(int i = k; i < shape[0]; i++)
        {
            if(std::abs(copy[i][k]) > std::abs(pivot))
            {
                pivot = copy[i][k];
                line_pivot = i;
            }
        }

        if (pivot == 0)
        {
            throw std::logic_error("la Matrice A est non inversible");
        }
        
        if(line_pivot != k)
        {
            std::swap(copy.tableau[k], copy.tableau[line_pivot]);
            std::swap(identite.tableau[k], identite.tableau[line_pivot]);
        }

        // rendre le pivot = 1
        pivot = copy.tableau[k][k];
        for (int j = 0; j < shape[0]; j++)
        {
            copy.tableau[k][j] /= pivot;
            identite.tableau[k][j] /= pivot;
        }

        // élimination
        for (int i = k + 1; i < shape[0]; i++)
        {
            if (copy[i][k] == 0) continue;
            float coeff = copy[i][k];
            
            for (int j = 0; j < shape[0]; j++)
            {
                copy.tableau[i][j] -= coeff * copy.tableau[k][j];
                identite.tableau[i][j] -= coeff * identite.tableau[k][j];
            }
        }
    }

    //triangularisation supérieur
    for (int k = shape[0] - 1; k >= 0; k--)
    {
        float pivot = copy.tableau[k][k];

        if (pivot == 0)
        {
            throw std::logic_error("la Matrice A est non inversible");
        }

        // éliminer au-dessus
        for (int i = k - 1; i >= 0; i--)
        {
            if (copy[i][k] == 0) continue;
            float coeff = copy[i][k];
            
            for (int j = 0; j < shape[0]; j++)
            {
                copy.tableau[i][j] -= coeff * copy.tableau[k][j];
                identite.tableau[i][j] -= coeff * identite.tableau[k][j];
            }  
        }
    }
    return identite;
}


Matrice Matrice::transposee()
{
    Matrice tp({shape[1], shape[0]});

    for ( int i = 0; i < shape[0]; i++)
    {
        for (int j = 0; j < shape[1]; j++)
        {
            tp[j][i] = tableau[i][j];
        }
    }
    return tp;
}