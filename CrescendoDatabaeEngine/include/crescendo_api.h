#ifndef CRESCENDO_API_H
#define CRESCENDO_API_H

#include <string>

namespace Crescendo {

    class CrescendoDB {
    public:
        CrescendoDB();  // Constructor
        ~CrescendoDB(); // Destructor

        // Función para ejecutar consultas SQL
        void execute(const std::string& query);

    private:
        // Añadir variables miembro necesarias para gestionar la base de datos
    };

} // namespace Crescendo

#endif // CRESCENDO_API_H
