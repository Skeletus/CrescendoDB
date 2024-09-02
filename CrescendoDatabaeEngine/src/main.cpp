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

/*
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
        std::cout << "Consulta analizada con exito.\n";
        std::cout << "Arbol de analisis generado:\n";
        std::cout << "Nodo raiz: " << ast->value << "\n";
        for (const auto& child : ast->children) {
            std::cout << " - Nodo hijo: " << child->value << " (Tipo: " << static_cast<int>(child->type) << ")\n";
        }
    } else {
        std::cout << "Error al analizar la consulta.\n";
    }

    return 0;
}
*/

/*
#include "storage_manager.h"
#include <iostream>

int main() {
    Crescendo::StorageManager storage_manager("crescendo_db.dat");

    // Escribir una página de prueba
    auto page = new Crescendo::Page(0);
    strcpy(page->getData(), "Hello, CrescendoDB!");
    storage_manager.writePage(page);
    delete page;

    // Leer la página de prueba
    auto read_page = storage_manager.readPage(0);
    if (read_page) {
        std::cout << "Datos leidos de la pagina: " << read_page->getData() << std::endl;
    } else {
        std::cout << "Error al leer la pagina." << std::endl;
    }

    return 0;
}
*/

#include "storage_manager.h"
#include "crescendo_parser.h"
#include "query_executor.h"
#include <iostream>

int main() {
    // Inicializar el gestor de almacenamiento
    Crescendo::StorageManager storage_manager("crescendo_db.dat");

    // Consulta de ejemplo
    std::string query = "SELECT name, age FROM users";
    Crescendo::CrescendoParser parser(query);

    // Analizar la consulta
    Crescendo::ASTNode* ast = parser.parse();
    if (!ast) {
        std::cerr << "Error: No se pudo analizar la consulta." << std::endl;
        return 1;
    }

    // Ejecutar la consulta
    Crescendo::CrescendoExecutor executor(&storage_manager);
    executor.execute(ast);

    // Liberar memoria del AST
    delete ast;

    return 0;
}



