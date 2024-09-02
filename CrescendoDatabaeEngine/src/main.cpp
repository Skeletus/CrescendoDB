/*
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
*/

#include "crescendo_parser.h"
#include <iostream>

int main() {
    std::string query = "SELECT name, age FROM users";
    Crescendo::CrescendoParser parser(query);

    auto tokens = parser.tokenize();
    std::cout << "Tokens obtenidos:\n";
    for (const auto& token : tokens) {
        std::cout << "Tipo: " << static_cast<int>(token.type) << ", Valor: " << token.value << "\n";
    }

    auto ast = parser.parse();
    if (ast) {
        std::cout << "Consulta analizada con éxito.\n";
    } else {
        std::cout << "Error al analizar la consulta.\n";
    }

    return 0;
}

