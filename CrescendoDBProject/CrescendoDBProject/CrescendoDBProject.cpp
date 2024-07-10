#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring> // Para strlen

int main() {
    // Solicitar al usuario que ingrese un entero
    std::cout << "Ingrese el tama�o del array de caracteres: ";
    int n;
    std::cin >> n;

    // Verificar si el tama�o ingresado es v�lido
    if (n <= 0) {
        std::cerr << "El tama�o debe ser un entero positivo." << std::endl;
        return 1; // Terminar el programa con un c�digo de error
    }

    // Solicitar al usuario que ingrese una cadena de caracteres
    std::cout << "Ingrese una cadena de caracteres: ";
    std::string inputString;
    std::cin >> inputString;

    // Verificar si la longitud de la cadena es mayor que el tama�o del array
    if (inputString.length() > static_cast<size_t>(n)) {
        std::cout << " xd: " << inputString.length() << " > " << static_cast<size_t>(n) << "\n";
        std::cerr << "Error: La longitud de la cadena es mayor que el tama�o del array." << std::endl;
        return 1; // Terminar el programa con un c�digo de error
    }
    std::cout << " ta bien";

    
    // Crear un array de caracteres de tama�o n
    char* charArray = new char[n+1];
    // Copiar la cadena de entrada al array de caracteres
    strncpy(charArray, inputString.c_str(), n);
    // Asegurarse de que el array est� correctamente terminado con '\0'
    charArray[n] = '\0';
    std::cout << "El array de caracteres creado es: " << charArray << std::endl;
    
    // Liberar la memoria asignada
    delete[] charArray;

    return 0;
}
