/*
Elaborado por: Raquel Escalante y Rafael Vasquez
*/
#include <iostream>
#include <cmath>
using namespace std;

class BITreeValue{
public:
    int negatives;
    int zeroes;
};

///////////////////////////////// Funciones de Consulta //////////////////////////////////////
BITreeValue FenTree_Sum(BITreeValue FenTree[], int idx)
{
    BITreeValue sum;
    sum.negatives = 0;
    sum.zeroes = 0;
    idx = idx + 1;

    while (idx > 0)
    {
        sum.negatives += FenTree[idx].negatives;
        sum.zeroes += FenTree[idx].zeroes;
        idx -= idx & (-idx);
    }
    return sum;
}

BITreeValue FenTree_Range(BITreeValue FenTree[],int val_arr[], int idx1, int idx2)
{
    BITreeValue sum, aux;

    sum = FenTree_Sum(FenTree, idx2);
    aux = FenTree_Sum(FenTree, idx1);
    sum.negatives -= aux.negatives;
    sum.zeroes -= aux.zeroes;
    if(val_arr[idx1] < 0) sum.negatives++;
    if(val_arr[idx1] == 0) sum.zeroes++;

    return sum;
}
///////////////////////////////////// Funciones de Update ///////////////////////////////////////


BITreeValue calculate_difference(int val, int idx, BITreeValue FenTree[], int freq[])
{
    BITreeValue result;
    result.zeroes = 0;
    result.negatives = 0;

    if(freq[idx - 1] == 0){// Si el valor viejo es igual a cero...
        if(val == 0){       // ...y el valor nuevo es cero: No aumentamos ningun contador.
            result.zeroes = 0;
            result.negatives = 0;
        }else{
            if(val > 0){    // ...y el valor nuevo es positivo: restamos uno al contador de ceros.
                result.zeroes = -1;
                result.negatives = 0;
            }else{          // ...y el valor nuevo es negativo: invertimos el signo y contamos un negativo.
                result.zeroes = -1;
                result.negatives = 1;
            }
        }
    }else{
        if(freq[idx - 1] > 0){      //Si el valor viejo es positivo...
            if(val == 0){           // ...y el valor nuevo es cero: aumentamos el contador de ceros.
                result.zeroes = 1;
                result.negatives = 0;
            }else{
                if(val > 0){        // ...y el valor nuevo es positivo: No aumentamos ningun contador.
                    result.zeroes = 0;
                    result.negatives = 0;
                }else{              // ...y el valor nuevo es negativo: contamos un negativo.
                    result.zeroes = 0;
                    result.negatives = 1;
                }
            }
        }else{                      //Si el valor viejo es negativo...
            if(val == 0){           // ...y el valor nuevo es cero: restamos un negativo e aumentamos un cero.
                result.zeroes = 1;
                result.negatives = -1;
            }else{
                if(val > 0){        // ...y el valor nuevo es positivo: restamos un negativo.
                    result.zeroes = 0;
                    result.negatives = -1;
                }else{              // ...y el valor nuevo es negativo: No aumentamos ningun contador.
                    result.zeroes = 0;
                    result.negatives = 0;
                }
            }
        }
    }

    return result;
}


void FenTree_Update(BITreeValue FenTree[], int n, int idx, int val, int val_arr[])
{
    BITreeValue diff;

    idx = idx + 1;
    diff = calculate_difference(val, idx, FenTree, val_arr);

    while (idx <= n)
    {
        FenTree[idx].negatives += diff.negatives;
        FenTree[idx].zeroes += diff.zeroes;
        idx += idx & (-idx);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////Constructor///////////////////////////////////////////////
BITreeValue *FenTree_constructor(int a_xi[], int n)
{
    BITreeValue *FenTree = new BITreeValue[n+1];
    for (int i=1 ; i<=n ; i++)
    {   // Inicializamos todos los valores del BIT en 0.
        FenTree[i].negatives = 0;
        FenTree[i].zeroes = 0;
    }

    for (int i=0; i<n; i++) FenTree_Update(FenTree, n, i, a_xi[i],a_xi);

    return FenTree;
}
///////////////////////////// Funciones de Operaciones ////////////////////////////////////////
void changeValue(int val_arr[], BITreeValue FenTree[], int n, int index, int val){

    FenTree_Update(FenTree, n, index-1, val, val_arr);
    val_arr[index-1] = val;
   /*cout <<"Updt: ";
    for (int i=1; i<=n; i++) cout <<" (" <<FenTree[i].negatives << ", "<<FenTree[i].zeroes << ")";
    cout << "\n\n" ;*/
}

char querySignRange(int val_arr[], BITreeValue FenTree[], int idx1, int idx2){
    BITreeValue result = FenTree_Range(FenTree, val_arr, idx1-1, idx2-1);
    if (result.zeroes != 0) return '0';
    if (result.negatives % 2) return '-';
    return '+';
}


////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int N, m, i;
    char op;
    int indx1, indx2, val;
    BITreeValue result;
    ////////////////////// Lecturas de variables iniciales ///////////////////////////////
    cin >> N;
    //cout << "Tamanio del arreglo: " << N <<endl;

    cin >> m;
    //cout << "Numero de operaciones: " << m <<endl;
    cin.ignore();   // Elimina el \n del final despues de leer m
    //////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////// Declaracion del arreglo de Xi //////////////////////////////

    int *arr_xi = new int[N+1];
    for (i = 1; i <= N; i++){
        arr_xi[i] = 1; //Inicializamos el arreglo de Xi con todos los valores en 1
        //cout << arr_xi[i] << " ";
    }

    //int arr_xi[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    //int n = sizeof(arr_xi)/sizeof(arr_xi[0]);

    ////////////////////// Inicializacion del arbol de fenwick /////////////////////////
    BITreeValue *FTree = FenTree_constructor(arr_xi, N);
    //////////////////////////////////////////////////////////////////////////////////////

    ////////////////////// Operaciones sobre el arbol de fenwick /////////////////////////
    for(i = 0; i < m; i++){
        cin >> op;
        if(op == 'c'){
            cin >> indx1 >> val ;
            //cout << "Cambio de valor: " << indx1 << ", " << val << endl;
            changeValue(arr_xi, FTree, N, indx1, val);
        }else{
            cin >> indx1 >> indx2 ;
            //cout << "Consulta: " << indx1 << ", " << indx2 << endl;
            cout << querySignRange(arr_xi, FTree, indx1, indx2) <<"\n";
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////

    /*
    changeValue(arr_xi, FTree, n, 1, 7);
    changeValue(arr_xi, FTree, n, 2, -4);
    cout << querySignRange(arr_xi, FTree, 1, 2) <<"\n";
    cout << querySignRange(arr_xi, FTree, 3, 5) <<"\n";
    */

    delete[] arr_xi;
    delete[] FTree;
    return 0;
}
