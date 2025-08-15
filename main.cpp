#include "Matrice.h"

using namespace std;
 

int main(int argc, char** argv)
{
    cout << "ce programme teste les transposee de matrices" << endl;
    try
    {
        Matrice A({-3,1,3,1}, {2,2});
        cout << A;
        Matrice B = A.transposee();
        cout  << B;
         
    }
    catch(const std::exception& e)
    {
        std::cerr <<"erreur :" <<  e.what() << endl;
    }
    return 0;
}