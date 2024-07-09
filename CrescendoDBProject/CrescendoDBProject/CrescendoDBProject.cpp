#include <iostream>
#include "Record.h"

int main()
{
    Record obj;
    obj.AddAttribute("age", Attribute::Type::INT);
    obj.AddAttribute("height", Attribute::Type::DOUBLE);
    obj.AddAttribute("name", Attribute::Type::STRING);

    obj.SetValue("age", 30);
    obj.SetValue("height", 5.9);
    obj.SetValue("name", std::string("John"));

    obj.PrintValues();

    return 0;
    //std::cout << "Hello World!\n";
}