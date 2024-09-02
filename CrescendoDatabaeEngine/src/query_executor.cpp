#include "query_executor.h"
#include <iostream>

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

}