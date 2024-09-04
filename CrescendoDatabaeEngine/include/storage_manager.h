#ifndef CRESCENDO_STORAGE_MANAGER_H
#define CRESCENDO_STORAGE_MANAGER_H

#include "page_manager.h"
#include <string>

namespace Crescendo {

// Representa un registro en la tabla
struct Record {
    std::unordered_map<std::string, std::string> data; // Nombre de columna -> valor

    void print() const {
        for (const auto& entry : data) {
            std::cout << entry.first << ": " << entry.second << " ";
        }
        std::cout << std::endl;
    }
};

class StorageManager {
public:
    StorageManager(const std::string& db_name) : page_manager_(db_name) {}

    Page* readPage(uint32_t page_id) {
        return page_manager_.fetchPage(page_id);
    }

    void writePage(Page* page) {
        page_manager_.writePage(page);
    }

    // Nueva función para realizar la selección de registros en una tabla
    void select(const std::string& table_name, const std::vector<std::string>& columns);

    // TODO: Implementar otras funciones como creación de tablas, manipulación de datos, etc.

private:
    PageManager page_manager_;

    // Función auxiliar para simular la obtención de registros de una tabla (provisional)
    std::vector<Record> fetchAllRecords(const std::string& table_name);

    void createTable(const std::string& table_name);
    void insertRecord(const std::string& table_name, const std::vector<std::string>& values);

};

}  // namespace CrescendoDB

#endif  // CRESCENDO_STORAGE_MANAGER_H
