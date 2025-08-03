#include "EqLin.h"
using namespace std;
 

int main(int argc, char** argv)
{
    cout << "ce programme résoud un système linéaire a l'aide de la factorisation LDU" << endl;
    try
    {
        string fich = "data.txt";
        cout << "data from:" << fich << endl;
        EqLin equation(fich);
        equation.factorize();
        equation.solve();
        equation.display();

    }
    catch(const std::exception& e)
    {
        std::cerr <<"erreur :" <<  e.what() << endl;
    }
    return 0;
}