#include <iostream>
#include "crescendo_api.h"

int main() {
    std::cout << "Bienvenido a CrescendoDB!" << std::endl;

    // Inicializa la base de datos (simulada por ahora)
    Crescendo::CrescendoDB db;

    // Ejecutar una consulta de prueba
    std::string query = "SELECT * FROM mi_tabla;";
    db.execute(query);

    return 0;
}
