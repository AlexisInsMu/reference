#include <bits/stdc++.h>
using namespace std;
const int Max = 1e8;

void constructTree(vector<int> &input, vector<int> &segTree, int l, int r, int pos){ //Armar el arbol
    if(l==r){
        segTree[pos]=input[l];
        return;
    }

    int mid = (l+r)/2;

    constructTree(input, segTree, l, mid, (pos*2)+1);           //Hijos derechos
    constructTree(input, segTree, mid+1, r, (pos*2)+2);         //Hijos izquierdos
    segTree[pos]=min(segTree[(pos*2)+1], segTree[(pos*2)+2]);   //Regresa el minimo de un rango dado
}

int rangeinQuery(vector<int> &segTree, int qlow, int qhigh, int l, int r, int pos){ //Verificar las querys
    if(qlow<=l && qhigh>=r){
        return segTree[pos];        //Total overlap
    }

    if(qlow>r || qhigh<l){
        return Max;                 //No overlap
    }

    int mid = (l + r)/2;
    return min(rangeinQuery(segTree, qlow, qhigh, l, mid, (pos*2)+1), rangeinQuery(segTree, qlow, qhigh, mid+1, r, (pos*2)+2));
}

int main(){
    int n, qlow, qhigh;;
    cin >> n;
    vector<int> input(n);
    vector<int> segTree((2*n)-1);

    for(int i=0; i<n; i++){
        cin >> input[i];
    }

    for(int i=0; i<n; i++){
        segTree[i] = Max;
    }

    cin >> qlow >> qhigh;

    constructTree(input, segTree, 0, n-1, 0);
    cout << rangeinQuery(segTree, qlow, qhigh, 0, n-1, 0) << "\n";
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////777
////////////////////////////////////////////////////////////////////////////////////////////////////////////7


#include <bits/stdc++.h>
using namespace std;
const int Max = 1e8;

void constructTree(vector<int> &input, vector<int> &segTree, int l, int r, int pos) {
    if (l == r) {
        segTree[pos] = input[l];
        return;
    }

    int mid = (l + r) / 2;

    constructTree(input, segTree, l, mid, (pos * 2) + 1); // Hijos izquierdos
    constructTree(input, segTree, mid + 1, r, (pos * 2) + 2); // Hijos derechos
    segTree[pos] = min(segTree[(pos * 2) + 1], segTree[(pos * 2) + 2]); // Regresa el mínimo de un rango dado
}

void updateTree(vector<int> &segTree, vector<int> &lazy, int startRange, int endRange, int valor, int low, int high, int pos) {
    if (low > high) {
        return;
    }

    if (lazy[pos] != 0) {
        segTree[pos] += lazy[pos];
        if (low != high) {
            lazy[(pos * 2) + 1] += lazy[pos]; // Propaga el valor de lazy
            lazy[(pos * 2) + 2] += lazy[pos];
        }
        lazy[pos] = 0; // Elimina lazy después de propagarlo
    }

    if (startRange <= low && endRange >= high) { // Total overlap
        segTree[pos] += valor;
        if (low != high) {
            lazy[(pos * 2) + 1] += valor;
            lazy[(pos * 2) + 2] += valor;
        }
        return;
    }

    if (startRange > high || endRange < low) { // No overlap
        return;
    }

    int mid = (low + high) / 2;
    updateTree(segTree, lazy, startRange, endRange, valor, low, mid, (pos * 2) + 1); // Hijos izquierdos
    updateTree(segTree, lazy, startRange, endRange, valor, mid + 1, high, (pos * 2) + 2); // Hijos derechos
    segTree[pos] = min(segTree[(pos * 2) + 1], segTree[(pos * 2) + 2]); // Retorna mínimo entre dos hijos al padre
}

int minimoEnRango(vector<int> &segTree, vector<int> &lazy, int qlow, int qhigh, int low, int high, int pos) {
    if (low > high) {
        return Max;
    }

    if (lazy[pos] != 0) {
        segTree[pos] += lazy[pos];
        if (low != high) { // Si no es un nodo hoja
            lazy[(pos * 2) + 1] += lazy[pos];
            lazy[(pos * 2) + 2] += lazy[pos];
        }
        lazy[pos] = 0;
    }

    if (qlow <= low && qhigh >= high) { // Total overlap
        return segTree[pos];
    }

    if (qlow > high || qhigh < low) { // No overlap
        return Max;
    }

    int mid = (low + high) / 2;
    return min(minimoEnRango(segTree, lazy, qlow, qhigh, low, mid, (pos * 2) + 1),
               minimoEnRango(segTree, lazy, qlow, qhigh, mid + 1, high, (pos * 2) + 2)); // Retorna mínimo entre hijo derecho o izquierdo al padre
}

int main() {
    int n, qlow, qhigh, operation, valor;
    cin >> n;
    vector<int> Nums(n);
    vector<int> segTree(4 * n, Max); // Incrementado el tamaño del segmento de árbol para evitar errores
    vector<int> lazy(4 * n, 0);
    for (int i = 0; i < n; i++) {
        cin >> Nums[i];
    }

    constructTree(Nums, segTree, 0, n - 1, 0);

    cout << "Quieres sumar x a todos los valores de un rango Press --> 1" << "\n";
    cout << "Quieres consultar el minimo en rango Press --> 2" << "\n";
    cin >> operation;

    cout << "Introduce el rango de la operacion" << "\n";
    cin >> qlow >> qhigh;
    if (operation == 1) {
        cout << "Introduce el valor que vas a sumar" << "\n";
        cin >> valor;
        updateTree(segTree, lazy, qlow, qhigh, valor, 0, n - 1, 0);
    } else {
        cout << minimoEnRango(segTree, lazy, qlow, qhigh, 0, n - 1, 0) << "\n";
    }

    // Imprimir el árbol segmentado después de la actualización
    for (int i : segTree) {
        if (i != Max) { // Solo imprime valores que no son el valor inicial Max
            cout << i << " ";
        }
    }
    cout << "\n";

    return 0;
}