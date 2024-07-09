#pragma once
#include <string>

class Attribute 
{
public:
    enum class Type
    {
        INT,
        DOUBLE,
        STRING
    };

    Attribute(const std::string& name, Type type) : name(name), type(type) {}

    std::string GetName() const 
    {
        return name;
    }

    Type GetType() const 
    {
        return type;
    }

private:
    std::string name;
    Type type;
};