/*
Elaborado por: Raquel Escalante y Rafael Vasquez
*/
#include <iostream>
using namespace std;

////////////////////// Definicion de Operaciones de FenTree ///////////////////////////
int FenTree_Sum(int FenTree[], int idx)
{
    int sum_neg = 0; //Almacena la suma de negativos en el tree
    idx = idx + 1;

    while (idx > 0)
    {
        sum_neg += FenTree[idx];
        idx -= idx & (-idx);
    }
    return sum_neg;
}

void FenTree_Update(int FenTree[], int n, int idx, int val)
{
    idx = idx + 1;
    while (idx <= n)
    {
        FenTree[idx] += val;
        idx += idx & (-idx);
    }
    //for (int i=1; i<=n; i++) cout << FenTree[i] << " ";
    cout << endl;
}

/*void change_xi(int a_xi[], int idx, int val)
{
    a_xi[idx] = val;
}
*/

int FenTree_Range(int FenTree[], int idx1, int idx2)
{
    int sum_neg = 0;
    sum_neg = FenTree_Sum(FenTree, idx2);
    sum_neg -= FenTree_Sum(FenTree, idx1);
    return sum_neg;
}

int *FenTree_constructor(int a_xi[], int n)
{
    int *FenTree = new int[n+1];
    for (int i=1 ; i<=n ; i++)
    {
        FenTree[i] = 0;
        cout << FenTree[i] << " ";
    }
    for (int i=0; i<n; i++)
        FenTree_Update(FenTree, n, i, a_xi[i]);

    cout << endl;
    return FenTree;
}


 //////////////////////////////////////////////////////////////////////////////////////

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
    ///////////////////////// Declaracion del arreglo de Xi //////////////////////////////
    /*int* arr_xi;
    arr_xi = new int[N];

    for (i = 0; i < N ; i++)
    {
        arr_xi[i] = 1;
        cout << arr_xi[i] << " ";
    }
    cout << endl;
    */
    int arr_xi[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = sizeof(arr_xi)/sizeof(arr_xi[0]);

    ////////////////////// Inicializacion de el arbol de fenwick /////////////////////////
    int *FTree = FenTree_constructor(arr_xi, n);
    //////////////////////////////////////////////////////////////////////////////////////
    //int rango;
    ////////////////////// Operaciones sobre el arbol de fenwick /////////////////////////
    /*for( i = 0; i < m; i++ ){
        cin >> op;
        if(op == 'c'){
            cin >> indx1 >> val ;
            cout << "Cambio de valor: " << indx1 << ", " << val << endl;
            change_xi(arr_xi, indx1,val);
            FenTree_Update(FTree, N, indx1, val);
        }else{
            cin >> indx1 >> indx2 ;
            cout << "Consulta: " << indx1 << ", " << indx2 << endl;
            rango = FenTree_Range(FTree, indx1, indx2);
            cout << rango << endl;
        }
    }
    */
    //////////////////////////////////////////////////////////////////////////////////////
    for(i=0; i<n; i++)
        cout << "\nSum of elements in arr[0..i] is "<< FenTree_Sum(FTree, i);

    // Let use test the update operation
    arr_xi[3] += 6;
    FenTree_Update(FTree, n, 3, 6); //Update BIT for above change in arr[]

    for(int i=0; i<n; i++)
        cout << "\nSum of elements in arr[0..i] after update is "<< FenTree_Sum(FTree, i);

    return 0;
}
