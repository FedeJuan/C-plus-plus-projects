#include <iostream>
#include <vector>

using namespace std;

void migracionVotos(const vector<int>& escrutinio, const vector<vector<int>>& migraciones, vector<int>& elecciones) {
    int n = escrutinio.size();

    // Inicializar el vector de elecciones con ceros
    elecciones.resize(n, 0);

    // Iterar sobre cada candidato
    for (int i = 0; i < n; i++) {
        // Iterar sobre cada conjunto de migraciones para el candidato i
        for (int j = 0; j < n; j++) {
            // Calcular el porcentaje de migración para el candidato i
            int migracion = (escrutinio[j] * migraciones[j][i]) / 100;
            // Acumular los votos migrados al candidato i
            elecciones[i] += migracion;
        }
    }
}

int main() {
    vector<string> candidatos = {
            "Javier Milei", "Patricia Bullrich", "","Sergio Massa", "", "Juan Schiaretti",
            "Miriam Bregman", "No lo tiene decidido", "Voto en blanco", "No va a votar"
    };
    vector<int> escrutinio = {7116352, 4022466 , 2675563, 5070104, 1390585, 907437, 442085, 911875, 1148342, 10474831};
    vector<vector<int>> migraciones = {{95, 3, 0, 0, 0, 0, 0, 2, 0, 0}, {14, 82, 0, 0, 0, 0, 0, 3, 1, 0}, {9, 63, 0, 10, 0, 1, 1, 16, 0, 0}, {2, 0, 0, 92, 0, 0, 0, 0, 5, 0}, {1, 2, 0, 83, 0, 2, 1, 9, 0, 2}, {2, 15, 0, 21, 0, 31, 0, 32, 0, 0}, {0, 6, 0, 31, 0, 0, 46, 14, 4, 0}, {10, 6, 0, 23, 0, 6, 13, 37, 3, 1}, {5, 7, 0, 20, 0, 0, 0, 47, 18, 3}, {25, 9, 0, 24, 0, 1, 1, 11, 2, 28}};
    vector<int> elecciones;

    int sumatotal = 0;
    for (int j = 0; j < escrutinio.size(); j++) {
        sumatotal = escrutinio[j] + sumatotal;
    }
    migracionVotos(escrutinio, migraciones, elecciones);

    int i = 0;
    cout << "" << endl;
    cout << "Votos de las próximas elecciones generales:" << endl;
    while (i < elecciones.size()) {
        if (elecciones[i] != 0) {cout << candidatos[i] << ": " << elecciones[i] << " votos" << endl;
        }
        i++;
    }
    cout << "" << endl;
    i = 0;
    cout << "Resultados de las próximas elecciones generales:" << endl;
    while (i < elecciones.size()) {
        if (elecciones[i] != 0) {cout << candidatos[i] << ": " << (elecciones[i]*100)/sumatotal << " %" << endl;
        }
        i++;
    }

    return 0;
}
