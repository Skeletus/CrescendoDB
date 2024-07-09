#pragma once
#include <string>

/*
* int intAtrName
* float floatAtrName
* varchar(N) varcharName
*/
class Attribute 
{
public:
    enum class Type
    {
        INT,
        DOUBLE,
        VARCHAR
    };

    Attribute() : name(""), type(Type::INT), varcharLength(0) {} // Constructor

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

    size_t GetVarcharLength() const {
        return varcharLength;
    }

private:
    std::string name;
    Type type;
    size_t varcharLength;
};