#include "storage_manager.h"
#include <fstream>

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

void StorageManager::createTable(const std::string& table_name, const std::vector<std::string>& columns) {
    std::string table_file_path = "database/" + table_name + ".tbl";
    
    // Lógica para crear una tabla en el almacenamiento
    std::ofstream table_file(table_file_path);
    if (table_file.is_open()) {
        // Guardar el esquema de la tabla
        table_schema_[table_name] = columns;

        // Escribir los nombres de las columnas como encabezado del archivo
        for (size_t i = 0; i < columns.size(); ++i) {
            table_file << columns[i];
            if (i < columns.size() - 1) {
                table_file << ",";
            }
        }
        table_file << std::endl; // Nueva línea al final de las columnas
        table_file.close();
        std::cout << "Tabla '" << table_name << "' creada exitosamente." << std::endl;
    } else {
        std::cerr << "Error: no se pudo crear la tabla '" << table_name << "'." << std::endl;
    }
}

void StorageManager::insertIntoTable(const std::string& table_name, const std::vector<std::string>& values) {
    std::string table_file_path = "database/" + table_name + ".tbl";

    // Verificar que la tabla existe
    if (table_schema_.find(table_name) == table_schema_.end()) {
        std::cerr << "Error: la tabla '" << table_name << "' no existe." << std::endl;
        return;
    }

    std::ofstream table_file(table_file_path, std::ios::app); // Abrir el archivo en modo adjuntar
    if (table_file.is_open()) {
        // Lógica para insertar un registro en una tabla
        for (size_t i = 0; i < values.size(); ++i) {
            table_file << values[i];
            if (i < values.size() - 1) {
                table_file << ",";
            }
        }
        table_file << std::endl; // Nueva línea al final del registro
        table_file.close();
        std::cout << "Registro insertado en la tabla '" << table_name << "' exitosamente." << std::endl;
    } else {
        std::cerr << "Error: no se pudo abrir la tabla '" << table_name << "' para insertar datos." << std::endl;
    }
}

}  // namespace Crescendo
