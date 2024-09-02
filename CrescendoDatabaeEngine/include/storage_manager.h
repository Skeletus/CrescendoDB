#ifndef CRESCENDO_STORAGE_MANAGER_H
#define CRESCENDO_STORAGE_MANAGER_H

#include "page_manager.h"
#include <string>

namespace Crescendo {

class StorageManager {
public:
    StorageManager(const std::string& db_name) : page_manager_(db_name) {}

    Page* readPage(uint32_t page_id) {
        return page_manager_.fetchPage(page_id);
    }

    void writePage(Page* page) {
        page_manager_.writePage(page);
    }

    // TODO: Implementar otras funciones como creación de tablas, manipulación de datos, etc.

private:
    PageManager page_manager_;
};

}  // namespace CrescendoDB

#endif  // CRESCENDO_STORAGE_MANAGER_H
