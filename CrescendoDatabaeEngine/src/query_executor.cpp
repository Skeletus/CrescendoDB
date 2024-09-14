#include "query_executor.h"
#include <iostream>
#include <filesystem>

namespace Crescendo {

// Constructor de la clase CrescendoExecutor
CrescendoExecutor::CrescendoExecutor(StorageManager* storageManager, TransactionManager* transactionManager)
    : storage_manager_(storageManager), transaction_manager_(transactionManager) {}

// Función principal para ejecutar un nodo AST
void CrescendoExecutor::execute(ASTNode* ast) {
    if (!ast) {
        std::cerr << "Error: AST nulo recibido para ejecutar." << std::endl;
        return;
    }

    // Verifica si el nodo es un comando de transacción
    if (ast->type == TokenType::KEYWORD && (ast->value == "BEGIN" || ast->value == "COMMIT" || ast->value == "ROLLBACK")) {
        executeTransactionCommand(ast);
    }
    // Verifica si el nodo es una consulta SELECT
    else if (ast->type == TokenType::KEYWORD && ast->value == "SELECT") {
        executeSelect(ast);
    } else {
        std::cerr << "Error: Tipo de comando SQL no soportado." << std::endl;
    }
}

// Función para ejecutar consultas SELECT
void CrescendoExecutor::executeSelect(ASTNode* ast) {
    if (!ast || ast->value != "SELECT") {
        std::cerr << "Error: Nodo AST inválido para consulta SELECT." << std::endl;
        return;
    }

    // Obtener la lista de columnas seleccionadas y el nombre de la tabla desde el AST
    std::vector<std::string> columns;
    std::string table_name;

    for (auto* child : ast->children) {
        if (child->type == TokenType::IDENTIFIER) {
            // Asume que el primer identificador es el nombre de la tabla
            if (table_name.empty()) {
                table_name = child->value;
            } else {
                columns.push_back(child->value);
            }
        }
    }

    // Verificar que se obtuvo un nombre de tabla
    if (table_name.empty()) {
        std::cerr << "Error: No se especificó un nombre de tabla en la consulta SELECT." << std::endl;
        return;
    }

     // Suponiendo que buscamos por clave primaria
    for (auto& child : ast->children[0]->children) {
            std::cout <<"Columna seleccionada: " << child->value << std::endl;
    }

    // Realizar búsqueda de ejemplo en el B-Tree para claves
    storage_manager_->searchInTable(table_name, 10);

    // Llama al StorageManager para ejecutar la operación SELECT
    storage_manager_->select(table_name, columns);
}

// Función para ejecutar comandos de transacción
void CrescendoExecutor::executeTransactionCommand(ASTNode* ast) {
    if (ast->value == "BEGIN") {
        transaction_manager_->beginTransaction();
    } else if (ast->value == "COMMIT") {
        transaction_manager_->commitTransaction();
    } else if (ast->value == "ROLLBACK") {
        transaction_manager_->rollbackTransaction();
    } else {
        std::cerr << "Error: Comando de transacción no reconocido: " << ast->value << std::endl;
    }
}

void CrescendoExecutor::executeCreateDatabase(ASTNode* node) {
    std::string db_name = node->children[0]->value;

    // Lógica para crear el directorio de la base de datos
    try {
        if (std::filesystem::create_directory(db_name)) {
            std::cout << "Base de datos '" << db_name << "' creada exitosamente." << std::endl;
        } else {
            std::cerr << "Error: no se pudo crear la base de datos o ya existe." << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error al crear la base de datos: " << e.what() << std::endl;
    }
}

void CrescendoExecutor::executeCreateTable(ASTNode* node) {
    std::string table_name = node->children[0]->value;
    // Lógica para crear la estructura de la tabla
    std::string table_file_path = "database/" + table_name + ".tbl";
    std::ofstream table_file(table_file_path);

    if (table_file.is_open()) {
        // Crear el encabezado de la tabla (especificación de columnas)
        for (size_t i = 1; i < node->children.size(); ++i) {
            ASTNode* column_node = node->children[i];
            table_file << column_node->value;
            if (i < node->children.size() - 1) {
                table_file << ",";
            }
        }
        table_file << std::endl; // Nueva línea al final de las columnas
        table_file.close();
        std::vector<std::string> columns;
        // Lógica para crear la tabla en el almacenamiento
        storage_manager_->createTable(table_name, columns);
        std::cout << "Tabla '" << table_name << "' creada exitosamente." << std::endl;
    } else {
        std::cerr << "Error: no se pudo crear el archivo de la tabla." << std::endl;
    }
}

void CrescendoExecutor::executeInsert(ASTNode* node) {
    std::string table_name = node->children[0]->value;
    // Lógica para insertar datos en la tabla
    std::string table_name = node->children[0]->value;
    std::string table_file_path = "database/" + table_name + ".tbl";
    
    std::ofstream table_file(table_file_path, std::ios::app); // Abrir el archivo en modo adjuntar

    if (table_file.is_open()) {
        // Lógica para insertar datos en la tabla
        for (size_t i = 1; i < node->children.size(); ++i) {
            ASTNode* value_node = node->children[i];
            table_file << value_node->value;
            if (i < node->children.size() - 1) {
                table_file << ",";
            }
        }
        table_file << std::endl; // Nueva línea al final del registro
        table_file.close();
        std::cout << "Registro insertado en la tabla '" << table_name << "' exitosamente." << std::endl;
    } else {
        std::cerr << "Error: no se pudo abrir el archivo de la tabla para insertar datos." << std::endl;
    }
}


}