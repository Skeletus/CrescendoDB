#pragma once
#include <stdexcept>
class Varchar 
{
public:
    Varchar(size_t maxLength) : maxLength(maxLength), value(nullptr)
    {
        if (maxLength > 255)
        {
            throw std::invalid_argument("Maximum length for Varchar is 255");
        }
    }

    Varchar(const std::string& value, size_t maxLength) : maxLength(maxLength), value(nullptr)
    {
        if (maxLength > 255)
        {
            throw std::invalid_argument("Maximum length for Varchar is 255");
        }
        SetValue(value);
    }

    ~Varchar()
    {
        delete[] value;
    }

    void SetValue(const std::string& value)
    {
        if (value.length() > maxLength)
        {
            throw std::invalid_argument("Value exceeds maximum length for Varchar");
        }
        delete[] this->value; // Liberar memoria previamente asignada

        this->value = new char[value.length() + 1]; // Asignar memoria para el nuevo valor
        std::strcpy(this->value, value.c_str()); // Copiar el valor al buffer
    }

    const char* GetValue() 
    {
        return value;
    }

    size_t GetVarcharLength()
    {
        return maxLength;
    }

    friend std::ostream& operator<<(std::ostream& os, const Varchar& varchar) 
    {
        os << varchar.value;
        return os;
    }

private:
    size_t maxLength;
    char* value;
};