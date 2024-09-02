#ifndef CRESCENDO_PAGE_H
#define CRESCENDO_PAGE_H

#include <cstdint>
#include <cstring>
#include <iostream>

namespace Crescendo {

const size_t PAGE_SIZE = 4096;  // Tamaño de página típico de 4KB

class Page {
public:
    Page(uint32_t id) : id_(id) {
        memset(data_, 0, PAGE_SIZE);  // Inicializar con ceros
    }

    uint32_t getId() const { return id_; }
    char* getData() { return data_; }

    // Leer datos de la página
    void readFromDisk(std::istream& input) {
        input.read(data_, PAGE_SIZE);
    }

    // Escribir datos de la página al disco
    void writeToDisk(std::ostream& output) const {
        output.write(data_, PAGE_SIZE);
    }

private:
    uint32_t id_;          // ID de la página
    char data_[PAGE_SIZE]; // Datos de la página
};

}  // namespace Crescendo

#endif  // CRESCENDO_PAGE_H
