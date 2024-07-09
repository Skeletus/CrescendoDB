#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>
#include <stdexcept>
#include "Attribute.h"

class Record 
{
public:
    using ValueType = std::variant<int, double, const char*>;

    Record() = default;

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
                    std::cout << arg << '\n';
                    }, it->second);
            }
            else 
            {
                std::cout << "No value set\n";
            }
        }
    }

    
    std::vector<char> Serialize() const
    {
        std::vector<char> data;

        // Serializar el número de atributos
        size_t numAttributes = attributes.size();
        data.insert(data.end(), reinterpret_cast<const char*>(&numAttributes), reinterpret_cast<const char*>(&numAttributes) + sizeof(numAttributes));

        // Serializar cada atributo
        for (const auto& [name, attribute] : attributes)
        {
            size_t nameSize = name.size();
            data.insert(data.end(), reinterpret_cast<const char*>(&nameSize), reinterpret_cast<const char*>(&nameSize) + sizeof(nameSize));
            data.insert(data.end(), name.begin(), name.end());

            auto type = attribute.GetType();
            data.insert(data.end(), reinterpret_cast<const char*>(&type), reinterpret_cast<const char*>(&type) + sizeof(type));

            auto length = attribute.GetVarcharLength();
            data.insert(data.end(), reinterpret_cast<const char*>(&length), reinterpret_cast<const char*>(&length) + sizeof(length));
        }

        // Serializar los valores
        size_t numValues = values.size();
        data.insert(data.end(), reinterpret_cast<const char*>(&numValues), reinterpret_cast<const char*>(&numValues) + sizeof(numValues));

        for (const auto& [name, value] : values)
        {
            size_t nameSize = name.size();
            data.insert(data.end(), reinterpret_cast<const char*>(&nameSize), reinterpret_cast<const char*>(&nameSize) + sizeof(nameSize));
            data.insert(data.end(), name.begin(), name.end());

            std::visit([&data](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double> || std::is_same_v<T, const char*>)
                {
                    data.insert(data.end(), reinterpret_cast<const char*>(&arg), reinterpret_cast<const char*>(&arg) + sizeof(arg));
                }
                }, value);
        }

        return data;
    }

    
    static Record Deserialize(const std::vector<char>& data)
    {
        Record record;
        size_t offset = 0;

        // Deserializar el número de atributos
        size_t numAttributes;
        std::memcpy(&numAttributes, &data[offset], sizeof(numAttributes));
        offset += sizeof(numAttributes);

        for (size_t i = 0; i < numAttributes; ++i)
        {
            size_t nameSize;
            std::memcpy(&nameSize, &data[offset], sizeof(nameSize));
            offset += sizeof(nameSize);

            std::string name(nameSize, ' ');
            std::memcpy(&name[0], &data[offset], nameSize);
            offset += nameSize;

            Attribute::Type type;
            std::memcpy(&type, &data[offset], sizeof(type));
            offset += sizeof(type);

            size_t length;
            std::memcpy(&length, &data[offset], sizeof(length));
            offset += sizeof(length);

            record.AddAttribute(name, type, length);
        }

        // Deserializar los valores
        size_t numValues;
        std::memcpy(&numValues, &data[offset], sizeof(numValues));
        offset += sizeof(numValues);

        for (size_t i = 0; i < numValues; ++i)
        {
            size_t nameSize;
            std::memcpy(&nameSize, &data[offset], sizeof(nameSize));
            offset += sizeof(nameSize);

            std::string name(nameSize, ' ');
            std::memcpy(&name[0], &data[offset], nameSize);
            offset += nameSize;

            auto type = record.attributes.at(name).GetType();
            switch (type)
            {
            case Attribute::Type::INT:
            {
                int intValue;
                std::memcpy(&intValue, &data[offset], sizeof(intValue));
                offset += sizeof(intValue);
                record.SetValue(name, intValue);
                break;
            }
            case Attribute::Type::DOUBLE:
            {
                double doubleValue;
                std::memcpy(&doubleValue, &data[offset], sizeof(doubleValue));
                offset += sizeof(doubleValue);
                record.SetValue(name, doubleValue);
                break;
            }
            case Attribute::Type::VARCHAR:
            {
                const char* varcharValue;
                std::memcpy(&varcharValue, &data[offset], sizeof(varcharValue));
                offset += sizeof(varcharValue);
                record.SetValue(name, varcharValue);
                break;
            }
            }
        }

        return record;
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
            return std::holds_alternative<const char*>(value);
        }
        return false;
    }
};