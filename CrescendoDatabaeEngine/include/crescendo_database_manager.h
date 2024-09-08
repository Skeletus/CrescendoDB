#ifndef CRESCENDO_DATABASE_MANAGER_H
#define CRESCENDO_DATABASE_MANAGER_H

#include <string>
#include <filesystem>
#include <iostream>

namespace Crescendo {

class DatabaseManager {
public:
    // Constructor
    DatabaseManager(const std::string& base_path) : base_path_(base_path) {}

    // Crear base de datos
    bool createDatabase(const std::string& db_name) {
        std::filesystem::path db_path = base_path_ / db_name;
        if (std::filesystem::exists(db_path)) {
            std::cerr << "Error: La base de datos '" << db_name << "' ya existe." << std::endl;
            return false;
        }

        try {
            // Lógica para crear el directorio de la base de datos
            std::filesystem::create_directories(db_path);
            std::cout << "Base de datos '" << db_name << "' creada exitosamente." << std::endl;
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error al crear la base de datos: " << e.what() << std::endl;
            return false;
        }
    }

private:
    std::filesystem::path base_path_;
};

}  // namespace Crescendo

#endif  // CRESCENDO_DATABASE_MANAGER_H
