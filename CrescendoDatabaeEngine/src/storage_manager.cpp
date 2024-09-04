#include "storage_manager.h"

namespace Crescendo {

// Implementación de la función select
void StorageManager::select(const std::string& table_name, const std::vector<std::string>& columns) {
    // Obtener todos los registros de la tabla (simulado aquí)
    std::vector<Record> records = fetchAllRecords(table_name);

    // Imprimir los registros seleccionados
    std::cout << "Ejecutando consulta SELECT sobre la tabla: " << table_name << std::endl;
    for (const auto& record : records) {
        for (const auto& column : columns) {
            if (record.data.find(column) != record.data.end()) {
                std::cout << column << ": " << record.data.at(column) << " ";
            } else {
                std::cout << column << ": [NULL] ";
            }
        }
        std::cout << std::endl;
    }
}

// Función auxiliar para obtener todos los registros de una tabla (provisional)
std::vector<Record> StorageManager::fetchAllRecords(const std::string& table_name) {
    // Esta función simula la obtención de registros de una tabla.
    // En una implementación real, leerías datos de páginas usando PageManager.

    // Datos de muestra
    std::vector<Record> records;

    // Simulación de algunos registros
    Record r1;
    r1.data["name"] = "John Doe";
    r1.data["age"] = "30";

    Record r2;
    r2.data["name"] = "Jane Smith";
    r2.data["age"] = "25";

    records.push_back(r1);
    records.push_back(r2);

    return records;
}

void StorageManager::createTable(const std::string& table_name) {
    // Lógica para crear una tabla en el almacenamiento
}

void StorageManager::insertRecord(const std::string& table_name, const std::vector<std::string>& values) {
    // Lógica para insertar un registro en una tabla
}


}  // namespace Crescendo
