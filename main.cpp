/*
Elaborado por: Raquel Escalante y Rafael Vasquez
*/
#include <iostream>
using namespace std;

int main()
{
    int N, m, i;
    char op;
    int indx1, indx2, val;
    ////////////////////// Lecturas de variables iniciales ///////////////////////////////
    cin >> N;
    cout << "Tamanio del arreglo: " << N <<endl;

    cin >> m;
    cout << "Numero de operaciones: " << m <<endl;
    cin.ignore();   // Elimina el \n del final despues de leer m
    //////////////////////////////////////////////////////////////////////////////////////

    ////////////////////// Inicializacion de el arbol de fenwick /////////////////////////


    //////////////////////////////////////////////////////////////////////////////////////

    ////////////////////// Operaciones sobre el arbol de fenwick /////////////////////////
    for( i = 0; i < m; i++ ){
        cin >> op;
        if(op == 'c'){
            cin >> indx1 >> val ;
            cout << "Cambio de valor: " << indx1 << ", " << val << endl;
        }else{
            cin >> indx1 >> indx2 ;
            cout << "Consulta de signo: " << indx1 << ", " << indx2 << endl;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////
    return 0;
}
