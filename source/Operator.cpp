#include <cstdlib>
#include <iomanip>
#include "../header/Matrice.h"

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