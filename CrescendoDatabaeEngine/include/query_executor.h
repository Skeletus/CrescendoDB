#ifndef QUERY_EXECUTOR_H
#define QUERY_EXECUTOR_H

#include "storage_manager.h"
#include "crescendo_parser.h"
#include "transaction_manager.h"
#include <iostream>

namespace Crescendo {

    class CrescendoExecutor {
    public:
        // Constructor que inicializa el almacenamiento y el gestor de transacciones
        CrescendoExecutor(StorageManager* storageManager, TransactionManager* transactionManager);

        // Ejecuta un nodo del árbol de sintaxis abstracta (AST)
        void execute(ASTNode* ast);

    private:
        StorageManager* storage_manager_; // Puntero al administrador de almacenamiento
        TransactionManager* transaction_manager_; // Puntero al administrador de transacciones

        // Ejecuta consultas SELECT
        void executeSelect(ASTNode* ast);

        // Ejecuta comandos de transacción como BEGIN, COMMIT y ROLLBACK
        void executeTransactionCommand(ASTNode* ast);
    };

}  // namespace Crescendo

#endif  // QUERY_EXECUTOR_H
