#include "header/Matrice.h"

using namespace std;
 

int main()
{
    cout << "ce programme teste les operateurs" << endl;
    try
    {
        Matrice A({-3,1,3,1}, {2,2});
        
        Matrice B = A.inverse();
        // A*=B;
        // A*=2;
        // A-=A;

        Matrice C = B.inverse();
        cout << C/A;
    }

    catch(const std::exception& e)
    {
        std::cerr <<"erreur :" <<  e.what() << endl;
    }

    return 0;
}