#ifndef QUERY_EXECUTOR_H
#define QUERY_EXECUTOR_H

#include "storage_manager.h"
#include "crescendo_parser.h"
#include <iostream>

namespace Crescendo {

class CrescendoExecutor {
public:
    CrescendoExecutor(Crescendo::StorageManager* storage_manager) 
        : storage_manager_(storage_manager) {}

    void execute(ASTNode* ast) {
        if (!ast) return;

        if (ast->type == TokenType::KEYWORD && ast->value == "SELECT") {
            executeSelect(ast);
        } else {
            std::cerr << "Error: Tipo de consulta no soportada." << std::endl;
        }
    }

private:
    Crescendo::StorageManager* storage_manager_;

    void executeSelect(ASTNode* ast) {
        if (ast->children.empty()) {
            std::cerr << "Error: el AST de la consulta SELECT está vacio." << std::endl;
            return;
        }

        // Obtener las columnas seleccionadas
        std::vector<std::string> columns;
        std::string table_name;

        // Extraer columnas y nombre de la tabla del AST
        for (const auto& child : ast->children) {
            if (child->value == "COLUMNS") {
                for (const auto& column : child->children) {
                    columns.push_back(column->value);
                }
            }
            else if (child->type == TokenType::IDENTIFIER) {
                table_name = child->value;
            }
        }

        if (table_name.empty()) {
            std::cerr << "Error: Nombre de tabla no especificado en la consulta SELECT." << std::endl;
            return;
        }

        // Leer la primera página de la tabla como ejemplo
        auto page = storage_manager_->readPage(0); // Simplificado: leer la página 0
        if (!page) {
            std::cerr << "Error: No se pudo leer la pagina de la tabla " << table_name << "." << std::endl;
            return;
        }

        // Ejemplo de procesamiento de datos: imprimir el contenido de la página
        std::cout << "Ejecutando consulta SELECT sobre la tabla: " << table_name << std::endl;
        std::cout << "Columnas seleccionadas: ";
        for (const auto& column : columns) {
            std::cout << column << " ";
        }
        std::cout << std::endl;

        // Mostrar contenido de la página (esto es solo un ejemplo)
        std::cout << "Contenido de la primera pagina: " << page->getData() << std::endl;
    }
};

}  // namespace Crescendo

#endif  // QUERY_EXECUTOR_H
