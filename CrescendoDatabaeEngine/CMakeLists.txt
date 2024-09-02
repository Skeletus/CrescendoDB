cmake_minimum_required(VERSION 3.15)
project(CrescendoDatabaseEngine)

# Establece el estándar de C++
set(CMAKE_CXX_STANDARD 17)

# Incluir el directorio de cabeceras
include_directories(include)

# Agrega los archivos fuente principales
add_executable(CrescendoDatabaseEngine
    src/main.cpp
    src/crescendo_api.cpp
    src/crescendo_parser.cpp
    src/vm.cpp
    src/storage_manager.cpp
    src/page_manager.cpp
    src/transaction_manager.cpp
    src/query_optimizer.cpp
)
