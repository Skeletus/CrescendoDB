#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "storage_manager.h" // Para el acceso al almacenamiento

namespace Crescendo {

    class TransactionManager {
    public:
        TransactionManager(StorageManager* storageManager);

        // Iniciar una nueva transacción
        void beginTransaction();

        // Confirmar la transacción actual
        void commitTransaction();

        // Revertir la transacción actual
        void rollbackTransaction();

        // Obtener el ID de la transacción actual
        int getCurrentTransactionId() const;

    private:
        int current_transaction_id_; // ID de la transacción actual
        StorageManager* storage_manager_; // Puntero al administrador de almacenamiento
        std::unordered_map<int, std::vector<std::string>> transaction_log_; // Mapa de log de transacciones

        // Función de ayuda para registrar operaciones
        void logOperation(const std::string& operation);
    };

} // namespace Crescendo

#endif // TRANSACTION_MANAGER_H
