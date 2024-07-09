#pragma once
#include <string>

class Attribute 
{
public:
    enum class Type
    {
        INT,
        DOUBLE,
        VARCHAR
    };

    Attribute() : name(""), type(Type::INT), varcharLength(0) {} // Constructor predeterminado

    Attribute(const std::string& name, Type type, size_t length = 0)
        : name(name), type(type), varcharLength(length) {}

    std::string GetName() const 
    {
        return name;
    }

    Type GetType() const 
    {
        return type;
    }

    size_t getLength() const {
        return varcharLength;
    }

private:
    std::string name;
    Type type;
    size_t varcharLength;
};