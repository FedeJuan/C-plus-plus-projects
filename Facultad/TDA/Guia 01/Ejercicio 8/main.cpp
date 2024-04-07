#include<vector>
#include<iostream>

using namespace std;

const int INF = 333;

vector<vector<int> > memo;
vector<bool> cortes;

// Top Down
int min_costo(int i, int j) {
    if (i+1 == j) return 0;
    if (memo[i][j] == -1) {
        int costo = cortes.size(); // corte más largo
        bool hay_corte = false;
        for(int q = i + 1; q < j; q++) {
            // En caso de que el las posicion sea de un corte caluclo el minimo
            if (cortes[q]) {
                costo = min(costo, min_costo(i, q) + min_costo(q, j));
                hay_corte = true;
            }
        }
        if (hay_corte) memo[i][j] = costo + j - i;
        else memo[i][j] = 0;
    }
    return memo[i][j];
}

// Bottom Up

int min_costo_bu(int l) {
    int n = l + 1;
    vector<vector<int>> M(n, vector<int>(n, INF));

    // Casos base
    for (int i = 0; i < n; i++) {
        for (int j = 0; (j < i + 2 && j < n); j++)
            M[i][j] = 0;
    }
    for (int i=0; i<n; i++){
        for (int j = i+2; j < n; j++) {
            int nhc = 0;
            for (int a = 1; i + a < j; a++) {
                if (cortes[i + a]) nhc++;
            }
            if (nhc == 0) M[i][j] = 0;
            else
                if (nhc == 1) M[i][j] = j-i;
        }
    }
    // Calcular costos para longitudes mayores
    for (int j = 2; j < n; j++) {
        for (int i = 0; i < j-1; i++) {
            bool hc = false;
            for (int q = i + 1; q < j; q++) {
                 if (cortes[q]) {
                     M[i][j] = min(M[i][j], j - i + M[i][q] + M[q][j]); hc = true;
                 }
            }
            if (!hc) {M[i][j] = 0;};
        }
    }
    return M[0][l];
}


int main() {
    int l, c; cin >> l >> c;

    cortes = vector<bool>(l+1,false);
    memo = vector<vector<int> >(l+1, vector<int>(l+1, -1));

    while(c--) {
        int e; cin >> e;
        cortes[e] = true;
    }

    int coste = min_costo(0,l);

    cout << "Coste de los cortes (TD): " << coste << endl;

    coste = min_costo_bu(l);

    cout << "Coste de los cortes (BU): " << coste << endl;



}
