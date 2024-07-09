#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>
#include <stdexcept>
#include "Attribute.h"
#include "Varchar.h"

class Record 
{
public:
    using ValueType = std::variant<int, double, Varchar>;

    void AddAttribute(const std::string& name, Attribute::Type type, size_t length = 0) 
    {
        if (attributes.find(name) != attributes.end()) 
        {
            throw std::invalid_argument("Attribute already exists");
        }
        attributes[name] = Attribute(name, type, length);
    }

    void SetValue(const std::string& name, const ValueType& value) 
    {
        if (attributes.find(name) == attributes.end()) 
        {
            throw std::invalid_argument("Attribute does not exist");
        }
        if (!IsTypeMatching(name, value)) 
        {
            throw std::invalid_argument("Type mismatch for attribute " + name);
        }
        values[name] = value;
    }

    ValueType GetValue(const std::string& name) const 
    {
        auto it = values.find(name);
        if (it == values.end())
        {
            throw std::invalid_argument("Attribute does not have a value set");
        }
        return it->second;
    }

    void PrintValues() const 
    {
        for (const auto& [name, attribute] : attributes) 
        {
            std::cout << name << ": ";
            if (auto it = values.find(name); it != values.end()) 
            {
                std::visit([](auto&& arg) {
                    if constexpr (std::is_same_v<decltype(arg), Varchar>) 
                    {
                        std::cout << arg.getValue() << '\n';
                    }
                    else 
                    {
                        std::cout << arg << '\n';
                    }
                    }, it->second);
            }
            else 
            {
                std::cout << "No value set\n";
            }
        }
    }

private:
    std::unordered_map<std::string, Attribute> attributes;
    std::unordered_map<std::string, ValueType> values;

    bool IsTypeMatching(const std::string& name, const ValueType& value) const 
    {
        Attribute::Type type = attributes.at(name).GetType();
        switch (type) 
        {
        case Attribute::Type::INT:
            return std::holds_alternative<int>(value);
        case Attribute::Type::DOUBLE:
            return std::holds_alternative<double>(value);
        case Attribute::Type::VARCHAR:
            return std::holds_alternative<Varchar>(value);
        }
        return false;
    }
};