#include "crescendo_api.h"
#include <iostream>

namespace Crescendo {

CrescendoDB::CrescendoDB() {
    std::cout << "Base de datos inicializada." << std::endl;
}

CrescendoDB::~CrescendoDB() {
    std::cout << "Base de datos cerrada." << std::endl;
}

void CrescendoDB::execute(const std::string& query) {
    std::cout << "Ejecutando consulta: " << query << std::endl;
    // Por ahora, solo imprimimos la consulta.
    // Aquí se invocará al parser y otros componentes en el futuro.
}

} // namespace MySQLiteClone
