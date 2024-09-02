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

#include <iostream>
#include "storage_manager.h"
#include "transaction_manager.h"
#include "query_executor.h"
#include "crescendo_parser.h"

int main() {
    // Inicialización del StorageManager y TransactionManager
    std::string db_name = "test_db";
    Crescendo::StorageManager storage_manager(db_name);
    Crescendo::TransactionManager transaction_manager(&storage_manager);

    // Crear una transacción
    std::cout << "Iniciando prueba de transaccion..." << std::endl;
    transaction_manager.beginTransaction();

    // Simulación de algunas operaciones de base de datos dentro de la transacción
    try {
        std::cout << "Realizando operaciones dentro de la transaccion..." << std::endl;
        
        std::cout << "Insertando registro en la tabla 'users'..." << std::endl;
        
        // Confirmar transacción
        std::cout << "Haciendo commit de la transaccion..." << std::endl;
        transaction_manager.commitTransaction();
    } catch (const std::exception& e) {
        std::cerr << "Error durante la transaccion: " << e.what() << ". Realizando rollback." << std::endl;
        transaction_manager.rollbackTransaction();
    }

    // Verificar que el commit fue exitoso o el rollback fue realizado
    std::cout << "Estado de la base de datos despues de la transaccion:" << std::endl;
    storage_manager.select("users", {"name", "age"});

    return 0;
}


