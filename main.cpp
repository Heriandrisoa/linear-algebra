#include "EqLin.h"
using namespace std;
 

int main(int argc, char** argv)
{
//    cout << "ce programme résoud un système linéaire a l'aide de la factorisation LDU" << endl;
    try
    {
        Matrice A({-3,1,3,1}, {2,2});
        cout << A;
        Matrice B = A.inverse();
        cout  << B;
        Matrice C = A * B; 
        cout << C;
    }
    catch(const std::exception& e)
    {
        std::cerr <<"erreur :" <<  e.what() << endl;
    }
    return 0;
}