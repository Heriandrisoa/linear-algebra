#include <cstdlib>
#include <iomanip>
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
            if(copy[i][k] > pivot)
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
            // par matrice élémentaire
            Matrice switcher = id(shape[0]);
            switcher[k][k] = 0;
            switcher[line_pivot][line_pivot] = 0;
            switcher[line_pivot][k] = 1;
            switcher[k][line_pivot] = 1;
            copy = switcher * copy;
        }

        //

        for (int i = k + 1; i < shape[0]; i++)
        {
        
            if (copy[i][k] == 0)
            {
                continue;
            }
            float coeff = pivot/copy[i][k];
            
            for (int j = k; j < shape[0]; j++)
            {
                copy.tableau[i][j] = copy.tableau[k][j] - coeff * copy[i][j];
                identite.tableau[i][j] = identite[k][j] - coeff * identite[i][j];
            }
        }
    }

    //triangularisation supérieur
    for (int k = shape[0] - 1; k >= 0; k--)
    {
        float pivot = copy.tableau[k][k];

        //pivotage partiel
        int line_pivot = k;
        for(int i = k; i >= 0; i--)
        {
            if(copy[i][k] > pivot)
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
            // par matrice élémentaire
            Matrice switcher = id(shape[0]);
            switcher[k][k] = 0;
            switcher[line_pivot][line_pivot] = 0;
            switcher[line_pivot][k] = 1;
            switcher[k][line_pivot] = 1;
            copy = switcher * copy;
        }

        for (int i = k - 1; i >= 0; i--)
        {
            if (copy[i][k] == 0)
            {
                continue;
            }
            float coeff = pivot/copy[i][k];
            
            for (int j = k; j >= 0; j--)
            {
                copy.tableau[i][j] = copy.tableau[k][j] - coeff * copy[i][j];
                identite.tableau[i][j] = identite[k][j] - coeff * identite[i][j];
            }
        }

        // rendre les diagonales égal a 1
        for (int i = 0; i < shape[0]; i++)
        {
            identite[k][i] = (float) identite[k][i]/copy[k][k]; 
        }

        copy[k][k] = copy[k][k]/copy[k][k];
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