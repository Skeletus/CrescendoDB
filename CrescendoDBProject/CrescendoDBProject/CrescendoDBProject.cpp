#include <iostream>
#include "Record.h"
#include "Varchar.h"

int main()
{
    Record obj;
    obj.AddAttribute("age", Attribute::Type::INT);
    obj.AddAttribute("height", Attribute::Type::DOUBLE);
    obj.AddAttribute("name", Attribute::Type::VARCHAR, 50);

    obj.SetValue("age", 30);
    obj.SetValue("height", 5.9);
    obj.SetValue("name", Varchar("John", 50));

    obj.PrintValues();

    return 0;
    //std::cout << "Hello World!\n";
}