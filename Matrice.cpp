#include <cstdlib>
#include <iomanip>
#include "Matrice.h"

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

std::ostream& operator<<(std::ostream& os,const Matrice& C)
{
    os << "[";
    for(int i = 0; i < C.shape[0]; i++)
    {
        os << "[";
        for(int j = 0; j < C.shape[1]; j++)
        {
            os << std::setw(3) << C[i][j]<< " ";
        }
        os << "]";
        if (i != C.shape[0] - 1)
        {
            os << std::endl;
        }
    }
    os << "]" << std::endl;
    return os;   
}

void sep()
{
    std::cout << "------<>-------" << std::endl;
}


Matrice Matrice::operator+(Matrice B)
{
    if(B.shape != shape)
    {
        throw std::logic_error("pour s'additionner, deux matrice doivent avoir les même shapes");
    }

    Matrice C = Matrice(shape);
    for(int i = 0; i < B.shape[0]; i++)
    {
        for(int j = 0; j < B.shape[1]; j++)
        {
            C.tableau[i][j] = this->tableau[i][j] + B.tableau[i][j];
        }
    }
    return C;
}

Matrice Matrice::operator*(Matrice B)
{
    if(this->shape[1] != B.shape[0])
    {
        throw std::logic_error("multiplication de matrice impossible: shape incompatible");
    }

    std::vector<int> new_shape = {this->shape[0], B.shape[1]};
    Matrice C = Matrice(new_shape);
    for(int i = 0; i < C.shape[0]; i++)
    {
        for(int j = 0; j < C.shape[1]; j++)
        {
            for(int k = 0; k < this->shape[0]; k++)
            {
                C.tableau[i][j] += this->tableau[i][k] * B.tableau[k][j];
            }
        }
    }
    return C;
}

std::vector<float>& Matrice::operator[](int index)
{
        return tableau[index];  
}


const std::vector<float>& Matrice::operator[](int index) const
{
    return tableau[index];  
}

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

void Matrice::operator=(Matrice B)
{
    shape = B.shape;
    tableau.resize(shape[0]);
    for(int i = 0; i < shape[0]; i++)
    {
        tableau[i].resize(shape[1]);
    }
    tableau = B.tableau;
}

std::vector<int> Matrice::get_shape()
{
    return shape;
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