#include "header/Matrice.h"

using namespace std;
 

int main()
{
    cout << "ce programme teste les produits scalaires" << endl;
    try
    {
        Matrice A({-3,1,3,-1}, {1,4});
        Matrice B({1,1,1,1}, {1,4});
        
        cout << "scalar:" << A.scalar(B) << endl;
    }

    catch(const std::exception& e)
    {
        std::cerr <<"erreur :" <<  e.what() << endl;
    }

    return 0;
}