#ifndef CRESCENDO_PAGE_MANAGER_H
#define CRESCENDO_PAGE_MANAGER_H

#include "page.h"
#include <unordered_map>
#include <fstream>
#include <string>

namespace Crescendo {

class PageManager {
public:
    PageManager(const std::string& file_name) : file_name_(file_name) {
        file_.open(file_name_, std::ios::in | std::ios::out | std::ios::binary);
        if (!file_.is_open()) {
            // Crear el archivo si no existe
            file_.clear();
            file_.open(file_name_, std::ios::out | std::ios::binary);
            file_.close();
            file_.open(file_name_, std::ios::in | std::ios::out | std::ios::binary);
        }
    }

    ~PageManager() {
        if (file_.is_open()) {
            file_.close();
        }
    }

    Page* fetchPage(uint32_t page_id) {
        // Buscar en la caché de páginas
        if (page_cache_.find(page_id) != page_cache_.end()) {
            return page_cache_[page_id].get();
        }

        // Si no está en la caché, cargar del disco
        auto page = std::make_unique<Page>(page_id);
        file_.seekg(page_id * PAGE_SIZE, std::ios::beg);
        page->readFromDisk(file_);
        Page* page_ptr = page.get();
        page_cache_[page_id] = std::move(page);
        return page_ptr;
    }

    void writePage(Page* page) {
        file_.seekp(page->getId() * PAGE_SIZE, std::ios::beg);
        page->writeToDisk(file_);
    }

private:
    std::unordered_map<uint32_t, std::unique_ptr<Page>> page_cache_;  // Caché de páginas
    std::string file_name_;                                          // Nombre del archivo de almacenamiento
    std::fstream file_;                                              // Archivo de almacenamiento
};

}  // namespace Crescendo

#endif  // CRESCENDO_PAGE_MANAGER_H
