#include "transaction_manager.h"
#include <iostream>

namespace Crescendo {

TransactionManager::TransactionManager(StorageManager* storageManager)
    : storage_manager_(storageManager), current_transaction_id_(0) {}

void TransactionManager::beginTransaction() {
    current_transaction_id_++;
    transaction_log_[current_transaction_id_] = {}; // Iniciar un nuevo log para esta transacción
    std::cout << "Transaccion " << current_transaction_id_ << " iniciada." << std::endl;
}

void TransactionManager::commitTransaction() {
    if (current_transaction_id_ == 0) {
        std::cerr << "Error: No hay una transaccion activa para confirmar." << std::endl;
        return;
    }

    // Guardar cambios de manera permanente
    std::cout << "Transaccion " << current_transaction_id_ << " confirmada." << std::endl;

    // Limpiar el log de la transacción
    transaction_log_.erase(current_transaction_id_);
    current_transaction_id_ = 0;
}

void TransactionManager::rollbackTransaction() {
    if (current_transaction_id_ == 0) {
        std::cerr << "Error: No hay una transaccion activa para revertir." << std::endl;
        return;
    }

    // Revertir todos los cambios en el log
    auto& operations = transaction_log_[current_transaction_id_];
    for (const auto& operation : operations) {
        std::cout << "Revertir operacion: " << operation << std::endl;
        // Implementar lógica específica de reversión según el tipo de operación
    }

    std::cout << "Transaccion " << current_transaction_id_ << " revertida." << std::endl;
    transaction_log_.erase(current_transaction_id_);
    current_transaction_id_ = 0;
}

int TransactionManager::getCurrentTransactionId() const {
    return current_transaction_id_;
}

void TransactionManager::logOperation(const std::string& operation) {
    if (current_transaction_id_ > 0) {
        transaction_log_[current_transaction_id_].push_back(operation);
        std::cout << "Operacion registrada: " << operation << std::endl;
    }
}

} // namespace Crescendo
