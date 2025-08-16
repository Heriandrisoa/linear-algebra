#ifndef __MATRICE__
#define __MATRICE__
#include <iostream>
#include <vector>
class EqLin;

class Matrice
{
    public:
        Matrice();
        Matrice(const Matrice& autre);
        Matrice(std::vector<int> shape);
        Matrice(std::vector<float> data, std::vector<int> shape);

        std::vector<int> get_shape();
        
        Matrice operator*(Matrice B);
        Matrice operator+(Matrice B);
        void operator=(Matrice B);
        
        std::vector<float>& operator[](int index);
        const std::vector<float>& operator[](int index) const;

        Matrice inverse();
        Matrice transposee();
    private:
        std::vector<std::vector<float>> tableau;
        std::vector<int> shape;
        friend std::ostream& operator<<(std::ostream& os, const Matrice& C);
        friend class EqLin;
    };

std::ostream& operator<<(std::ostream& os, const Matrice& C);
void sep();
Matrice id(int dim);
#endif