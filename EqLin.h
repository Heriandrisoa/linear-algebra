#ifndef __LIN_EQ
#define __LIN_EQ
#include "Matrice.h"
#include <vector>
#include <string>

class Matrice;
class EqLin
{
    public:
        EqLin(std::string fichier);
        EqLin(Matrice* A, std::vector<float>& b);
        ~EqLin();
        void factorize();
        void solve();
        void display();
    private:
        Matrice* A;
        Matrice* L;
        Matrice* U;
        Matrice* D;
        Matrice* P;
        std::vector<float> b;
        std::vector<float> solus;
};

#endif