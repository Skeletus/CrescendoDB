#pragma once
#include <stdexcept>
class Varchar 
{
public:
    Varchar(size_t maxLength) : maxLength(maxLength) 
    {
        if (maxLength > 255) 
        {
            throw std::invalid_argument("Maximum length for Varchar is 255");
        }
    }

    Varchar(const std::string& value, size_t maxLength) : maxLength(maxLength) 
    {
        if (maxLength > 255) 
        {
            throw std::invalid_argument("Maximum length for Varchar is 255");
        }
        setValue(value);
    }

    void setValue(const std::string& value) 
    {
        if (value.length() > maxLength) 
        {
            throw std::invalid_argument("Value exceeds maximum length for Varchar");
        }
        this->value = value;
    }

    std::string getValue() const 
    {
        return value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Varchar& varchar) 
    {
        os << varchar.value;
        return os;
    }

private:
    size_t maxLength;
    std::string value;
};