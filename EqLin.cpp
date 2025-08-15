#include "EqLin.h"
#include <exception>
#include <stdexcept>
#include <fstream>

EqLin::EqLin(Matrice* A, std::vector<float>& b)
{
    this->b = b;
    this->A = A;

    // on aura A = L * D * U
    size_t n = b.size();
    P = new Matrice(id(n));
    L = new Matrice(id(n));
    U = new Matrice(*A);
    D = new Matrice(id(n));
    solus.resize(b.size());
}

EqLin::EqLin(std::string fichier)
{
    std::vector<float> data;
    std::vector<int> shape;
    std::ifstream fich(fichier);
    
    if(!fich)
    {
        throw std::invalid_argument("impossible d'ouvrir le fichier " + fichier);
    }
    std::string buffer;
    fich >> buffer;
    int sh = stoi(buffer);
    shape = {sh, sh};
    while(fich >> buffer)
    {
        if(buffer != "\n" &&  buffer!= " ")
        {
            data.push_back(stof(buffer));
            if(data.size() == sh * sh)
                break;
        }
    }
    
    while(fich >> buffer)
    {
        if(buffer != "\n" && buffer != " ")
        {
            b.push_back(stof(buffer));
        }
    }

    A = new Matrice(data, shape);
    size_t n = b.size();
    P = new Matrice(id(n));
    L = new Matrice(id(n));
    U = new Matrice(*A);
    D = new Matrice(id(n));
    solus.resize(b.size());
}
    

void EqLin::display()
{
    std::cout << "A:\n" << *A;
    std::cout << "b: [ ";
    for (const auto& val : b)
        std::cout << val << " ";
    std::cout << "]\n";
    std::cout << "solution = [ ";
    for (const auto& val:solus)
        std::cout << val << " ";
    std::cout << "]" << std::endl; 
}

void EqLin::factorize()  // factorisation LDU
{
    int n = b.size();

    for (int k = 0; k < n; ++k)
    {
        
        float pivot = (*U)[k][k];
        int line_pivot = k;


        //pivotage partiel
        for(int i = k; i < n; i++)
        {
            if((*U)[i][k] > pivot)
            {
                pivot = (*U)[i][k];
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
            Matrice switcher = id(n);
            switcher[k][k] = 0;
            switcher[line_pivot][line_pivot] = 0;
            switcher[line_pivot][k] = 1;
            switcher[k][line_pivot] = 1;
            (*U) = switcher * (*U);
        }

        for (int i = k + 1; i < n; ++i)
        {
            float coeff = (*U)[i][k] / pivot;
            (*L)[i][k] = coeff;

            for (int j = k; j < n; ++j)
                (*U)[i][j] -= coeff * (*U)[k][j];
        }
    }

    for (int i = 0; i < n; ++i)
    {
        (*D)[i][i] = (*U)[i][i];
        for (int j = 0; j < n; ++j)
        {
            if (i != j)
                (*U)[i][j] /= (*U)[i][i];
        }
        (*U)[i][i] = 1;
    }

    // std::cout << "L:\n" << *L;
    // std::cout << "D:\n" << *D;
    // std::cout << "U:\n" << *U;
}

void EqLin::solve()
{
    std::vector<float> y(b.size()), z(b.size());
    // L * y = b
    for (int i = 0; i < b.size(); ++i) {
        y[i] = b[i];
        for (int j = 0; j < i; ++j)
            y[i] -= (*L)[i][j] * y[j];
    }


    //D * z = y
    for (int i = 0; i < b.size(); ++i)
        z[i] = y[i] / (*D)[i][i];


    // U * x = z
    for (int i = b.size() - 1; i >= 0; --i) {
        solus[i] = z[i];
        for (int j = i + 1; j < b.size(); ++j)
            solus[i] -= (*U)[i][j] * solus[j];
    }
}

EqLin::~EqLin()
{
    delete P;
    delete L;
    delete U;
    delete D;  
}
